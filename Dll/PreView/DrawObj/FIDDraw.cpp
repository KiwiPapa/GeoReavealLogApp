/******************************************************************
*   FIDDrw.cpp - implementation of the FID draw object base class *           
*******************************************************************/

#include "stdafx.h" 
#include "PreView.h"
#include "LogPlotDoc.h"
#include "FIDDraw.h"
#include "TrackDraw.h"
#include "GeoFIDio.h"
#include "DepthDialog.h"
//#include "StyleDialog.h"
//#include "MinFontDialog.h"
//#include "LineListPage.h"
//#include "FillListPage.h"
//#include "FIDBasePage.h"


IMPLEMENT_SERIAL(CFIDDrawObj, CDrawObj, 0)
CFIDDrawObj::CFIDDrawObj()
{
	m_Rlev = 0;	m_SDep = 0; m_EDep = 0;
	m_EEdep = 999999; m_SSdep = 0;
	bFlush = TRUE;
	bErrorFID = FALSE;
	m_ScripFileName="";
}

CFIDDrawObj::CFIDDrawObj(CString strPathName, const CRect& rect, CDrawObj* pParentObj,CLogPlotDoc* pDocument)
						:CDrawObj(rect,pParentObj,pDocument)
{
	m_UnitText = "";
	m_ScripFileName="";
	m_strPathName = strPathName;
	CGeoFIDIO::GetFIDName(strPathName,m_AliasName.GetBuffer(128));
	m_AliasName.ReleaseBuffer();
	CGeoFIDIO::GetFullFIDName(strPathName,m_strPathName.GetBuffer(512));
	m_HeadRect = rect;
	m_HeadRect.bottom = m_HeadRect.top + 40;
	m_HeadRect.right = m_HeadRect.left + 100;
	m_Rect = m_HeadRect;
	m_Rect.top = m_HeadRect.bottom;
	m_DrawDirect = HORDIR;
	LOGFONT m_LogFont=
	{
		-14,					    //lfHeight
		0,							//lfWidth
		0,							//lfEscapement
		0,							//lfOrientation
		FW_NORMAL,					//lfWeight
		0,							//lfItalic
		0,							//lfUnderLine;
		0,							//lfStrikeOut;
		ANSI_CHARSET,				//lfCharSet
		OUT_TT_ONLY_PRECIS,			//lfOutPrecision
		CLIP_DEFAULT_PRECIS,		//lfClipPrecision
		DEFAULT_QUALITY,			//lfQuality
		VARIABLE_PITCH | FF_SWISS,	//lfPitchAndFamily
		"Times New Roman"			//lfFaceName
	};        
    m_NameFont = m_LogFont;
    m_NameColor = RGB(0,0x80,0);
	m_FramePen.lopnWidth = CPoint(2,2); 
	m_FramePen.lopnColor = 0x0; 
	m_FramePen.lopnStyle = 0;
	m_Brush.lbStyle = BS_NULL;
	m_Brush.lbColor = 0xffffff; 
	m_Brush.lbHatch = 1;
	m_LeftVal = 0.f;
	m_RightVal = 100.f;
	m_Rlev = 0;	m_SDep = 0; m_EDep = 0;
	m_PlotSdep = 0; m_PlotEdep = 100;
	m_EEdep = 999999; m_SSdep = 0;
	bFlush = TRUE;
	bErrorFID = FALSE;
}
int CFIDDrawObj::GetDrawDirect()
{return m_DrawDirect;}
void CFIDDrawObj::SetDrawDirect(int direct)
{m_DrawDirect = direct;}

void CFIDDrawObj::Serialize(CArchive& ar)
{
	CDrawObj::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_UnitText;
		ar << m_HeadRect;
		ar << m_PlotSdep;
		ar << m_PlotEdep;
		ar << m_Rlev;
		ar << m_LeftVal;
		ar << m_RightVal;
		ar << m_strPathName;
		ar << m_AliasName;
//		ar << m_ScripFileName;
		ar << (LONG) m_NameColor;
		SerializeLogFont(ar,m_NameFont);
		SerializeLogPen(ar,m_FramePen);
		SerializeLogBrush(ar,m_Brush);
		ar << m_DrawDirect;
	}
	else
	{
		pDoc = (CLogPlotDoc*)ar.m_pDocument;
		ASSERT_VALID(pDoc);
		ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CLogPlotDoc)));
		LONG l;
		ar >> m_UnitText;
		ar >> m_HeadRect;
		ar >> m_PlotSdep;
		ar >> m_PlotEdep;
		ar >> m_Rlev;
		ar >> m_LeftVal;
		ar >> m_RightVal;
		ar >> m_strPathName;
		ar >> m_AliasName;
		
/*		CString ver;
		ver=pDoc->m_VersionNo;
		ver.TrimLeft ();ver.TrimRight ();
		m_ScripFileName="";
		if(atof(ver)>2.0)
			ar >> m_ScripFileName;*/
		ar >> l; 
		m_NameColor = (COLORREF) l;
		SerializeLogFont(ar,m_NameFont);
		SerializeLogPen(ar,m_FramePen);
		SerializeLogBrush(ar,m_Brush);
		ar >> m_DrawDirect;
	}
}

BOOL CFIDDrawObj::Properties(CView* pView)
{
	/*CString szHT;
	szHT.LoadString(IDS_DRAWINGPROPERTIES);
	CPropertySheet m_Sheet(szHT);
	CFIDBasePage m_BasePage(this);
	m_Sheet.AddPage(&m_BasePage);
	CLineListPage m_LineList;
	CFillListPage m_FillList;
 	if ((m_ParentType != 0) || (m_DrawDirect == VERDIR))
	{
		szHT.LoadString(IDS_FRAMELINE);
		m_LineList.AddPen(&m_FramePen,szHT);
		szHT.LoadString(IDS_FRAMELINE);
		m_FillList.AddFill(&m_Brush,szHT);
		m_Sheet.AddPage(&m_LineList);
		m_Sheet.AddPage(&m_FillList);
	}
	TEXTFONT m_TextFont;
	szHT.LoadString(IDS_ALIASFONT);
	m_TextFont.m_ItemName = szHT.GetBuffer(128);
	szHT.ReleaseBuffer();
	m_TextFont.m_Text = m_AliasName;
	m_TextFont.m_ForeGround = m_NameColor;
	m_TextFont.m_BackGround = RGB(255,255,255);
	m_TextFont.lf = m_NameFont;
	CMinFontPage m_FontPage;
	m_FontPage.AddFont(&m_TextFont);
	m_Sheet.AddPage(&m_FontPage);
	double m_PlotSdep1 = m_PlotSdep;
	double m_PlotEdep1 = m_PlotEdep;
	if (m_Sheet.DoModal() == IDOK)
	{
		m_FontPage.OnOK();
		m_NameColor = m_TextFont.m_ForeGround;
		m_NameFont = m_TextFont.lf;
		if (m_DrawDirect == HORDIR) m_NameFont.lfEscapement = 0;
		CRect m_SaveRect = m_Rect;
		m_SaveRect.top = m_HeadRect.top;
		if (m_ParentType != 0) 
		{
			if ((m_PlotSdep != m_PlotSdep1) || (m_PlotEdep != m_PlotEdep1))
			{
				double m_PlotSdep2 = m_PlotSdep;
				double m_PlotEdep2 = m_PlotEdep;
				m_PlotSdep = m_PlotSdep1;
				m_PlotEdep = m_PlotEdep1;
				SetDepth(m_PlotSdep2,m_PlotEdep2);
				if (m_SaveRect.bottom<m_Rect.bottom) m_SaveRect.bottom = m_Rect.bottom;
			}
		}
		pDoc->SetModifiedFlag();
		InvalidateRect(m_SaveRect);
		return TRUE;
	}*/
	return FALSE;
}
void CFIDDrawObj::OnSetDepth()
{   
	CPlotDepthDialog dialog; 
	double sdep,edep;
	dialog.m_DepthScale=pDoc->m_DepthScale;
	dialog.SetDepth(m_PlotSdep,m_PlotEdep);
	if (dialog.DoModal() == IDOK)
	{
		dialog.GetDepth(sdep,edep);
		SetDepth(sdep,edep);
		pDoc->UpdateAllViews(NULL,HINT_UPDATE_WINDOW);
	}	
}

BOOL CFIDDrawObj::IsDepthUnitOK(CGeoFIDIO* pFIDIO)
{
	ASSERT(pFIDIO != NULL);
	char m_Unit[5];
	if (pDoc->m_DepthUnit == UNIT_M) strcpy(m_Unit,"M");
	else strcpy(m_Unit,"FEET");
	if (stricmp(pFIDIO->GetContent(1)->unit,m_Unit))
	{
		AfxMessageBox(m_strPathName + "\n深度单位不匹配",MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	return TRUE;
}

void CFIDDrawObj::GetWellName(CString& m_WellName)
{
	CGeoFIDIO::GetFullWellName(m_strPathName,m_WellName.GetBuffer(512));
	m_WellName.ReleaseBuffer();
}

void CFIDDrawObj::GetCurveName(CString& m_CurveName)
{
	CGeoFIDIO::GetFIDName(m_strPathName,m_CurveName.GetBuffer(512));
	m_CurveName.ReleaseBuffer();
}

BOOL CFIDDrawObj::MatchCurve(CString strPathName)
{
	if (!m_strPathName.CompareNoCase(strPathName)) return TRUE;
	return FALSE;
}

BOOL CFIDDrawObj::MatchWell(CString strWellName)
{
	CString m_WellName;
	GetWellName(m_WellName);
	if (!m_WellName.CompareNoCase(strWellName)) return TRUE;
	return FALSE;
}

void CFIDDrawObj::SetRect(const CRect& rect)
{              
	if (m_Rect == rect) return;
	bFlush = TRUE;
	m_HeadRect.left = rect.left; m_HeadRect.right = rect.right;	
	if (m_SelectMode != size)
	{
		CPoint point; 
		CRect rect1 = rect;
		rect1.NormalizeRect();
		point.x = rect1.left - m_Rect.left;
		point.y = rect1.top - m_Rect.top;
		m_Rect = rect1;
	
		POSITION pos = m_ObjList.GetHeadPosition();
		while (pos != NULL)
		{
			CDrawObj* pObj = (CDrawObj*) m_ObjList.GetNext(pos);
			if (pObj != NULL) pObj->SetRect(pObj->GetRect()+point);
		}
	}
	else m_Rect = rect;
}

void CFIDDrawObj::SetHeadRect(const CRect& rect)
{   
	if (m_HeadRect == rect) return;
	m_HeadRect = rect;
	CRect m_Rect1 = m_Rect;
	m_Rect1.left = rect.left; m_Rect1.right = rect.right;	
	SetRect(m_Rect1);
}

int CFIDDrawObj::GetMinHeight()
{
	if (m_DrawDirect ==HORDIR) return 10;
	else return 20;
}

int CFIDDrawObj::GetMinWidth()
{
	if (m_DrawDirect ==VERDIR) return 10;
	else return 20;
}

void CFIDDrawObj::Move(const CPoint& point)
{
	m_Rect += point;
	m_HeadRect += point;
}


void CFIDDrawObj::DrawClient(CDC* pDC)
{
	CRect rect = m_Rect;
	if (!pDC->RectVisible(rect)) return;
	CRect m_ClipRect;
	pDC->GetClipBox(&m_ClipRect);
	m_ClipRect &= rect;
	if ((m_Brush.lbStyle != BS_NULL) && ((m_DrawDirect == VERDIR) || (m_ParentType != 0)))
 	{
		if (m_Brush.lbStyle == BS_OWNER)
		{
			if (m_Brush.lbHatch < 0) return;
			LithFillBox(m_ClipRect,(int)m_Brush.lbHatch,m_Brush.lbColor,rect.TopLeft(),pDC);
		}
		else
		{
			CBrush br;
		 	if (m_Brush.lbStyle == BS_HATCHED) 
			 	br.CreateHatchBrush((int)m_Brush.lbHatch,m_Brush.lbColor);
	   		else br.CreateBrushIndirect(&m_Brush);
				pDC->FillRect(m_ClipRect,&br);
		}
	}
}

void CFIDDrawObj::DrawFrame(CDC* pDC)
{
	if (!(m_bSelected || (m_DrawDirect == VERDIR) 
		|| (m_pParentObj == NULL) || (m_ParentType != 0))) 
		return;
	if (m_FramePen.lopnWidth.x <= 0) return;
	CPen m_Pen;
	m_Pen.CreatePenIndirect(&m_FramePen);
	CPen* pOldPen = pDC->SelectObject(&m_Pen); 
	CRect m_ClipRect,m_ClipRect1;
	pDC->GetClipBox(&m_ClipRect1);
	m_ClipRect1.InflateRect(2,2);

	CRect rect = m_Rect;
	pDoc->LPtoPP(&rect);
	
	if (m_ClipRect.IntersectRect(rect,m_ClipRect1))
	{
		pDC->MoveTo(rect.left,m_ClipRect.top);
		pDC->LineTo(rect.left,m_ClipRect.bottom);
		pDC->MoveTo(rect.right,m_ClipRect.top);
		pDC->LineTo(rect.right,m_ClipRect.bottom);
		pDC->MoveTo(rect.left,rect.top);
		pDC->LineTo(rect.right,rect.top);
		pDC->MoveTo(rect.left,rect.bottom);
		pDC->LineTo(rect.right,rect.bottom);
	}
	rect = m_HeadRect; 
	pDoc->LPtoPP(&rect);
	if (m_ClipRect.IntersectRect(rect,m_ClipRect1))
	{
		pDC->MoveTo(rect.left,rect.top);
		pDC->LineTo(rect.right,rect.top);
		pDC->LineTo(rect.right,rect.bottom);
		pDC->LineTo(rect.left,rect.bottom);
		pDC->LineTo(rect.left,rect.top);
	}
	if (pDoc->m_DrawFIDHeadMode == 1)
	{
		rect = m_HeadRect;
		CPoint pt(0,0);
		pt.y = m_Rect.bottom - m_HeadRect.top + m_Rect.top - m_HeadRect.bottom;
		rect += pt;
		pDoc->LPtoPP(&rect);
		if (m_ClipRect.IntersectRect(rect,m_ClipRect1))
		{
			pDC->MoveTo(rect.left,rect.top);
			pDC->LineTo(rect.right,rect.top);
			pDC->LineTo(rect.right,rect.bottom);
			pDC->LineTo(rect.left,rect.bottom);
			pDC->LineTo(rect.left,rect.top);
		}
	}
	pDC->SelectObject(pOldPen);
}

void CFIDDrawObj::Draw(CView* pView,CDC* pDC)
{
	DrawHead(pDC);
	DrawClient(pDC);
	if (pDoc->m_DrawFIDHeadMode == 1)
	{
		CRect m_SaveRect = m_HeadRect;
		CPoint pt(0,0);
		pt.y = m_Rect.bottom - m_HeadRect.top + m_Rect.top - m_HeadRect.bottom;
		m_HeadRect += pt;
		DrawHead(pDC);
		m_HeadRect = m_SaveRect;
	}
	DrawFrame(pDC);
}

void CFIDDrawObj::DrawHead(CDC *pDC)
{
	CRect rect = m_HeadRect;
	pDoc->LPtoPP(&rect);
	if (!pDC->RectVisible(rect)) return;
	if((m_Brush.lbStyle != BS_NULL) && ((m_DrawDirect == VERDIR) || (m_ParentType != 0)))
 	{
		if (m_Brush.lbStyle == BS_OWNER)
		{
			if (m_Brush.lbStyle < 0) return;
			LithFillBox(rect,m_Brush.lbStyle,m_Brush.lbColor,rect.TopLeft(),pDC);
		}
		else
		{
			CBrush br;
		 	if (m_Brush.lbStyle == BS_HATCHED) 
			 	br.CreateHatchBrush((int)m_Brush.lbHatch,m_Brush.lbColor);
	   		else br.CreateBrushIndirect(&m_Brush);
				pDC->FillRect(rect,&br);
		}
	}	
}
                   
void CFIDDrawObj::DrawTracker(CView* pView, CDC* pDC, TrackerState state)
{
    if ((m_bSelected) && (m_SelectMode == none))
    {
	    COLORREF color = m_FramePen.lopnColor; 
    	m_FramePen.lopnColor = RGB(0xff,0,0);
		DrawFrame(pDC);
	    m_FramePen.lopnColor = color;
    }	
}

int CFIDDrawObj::GetHandleCount()
{
	return 5;
}            

int CFIDDrawObj::HitTest(CView* pView,const CPoint& point)
{
    CRect rect = m_HeadRect;
    rect.left = m_HeadRect.right - 3;
    rect.right = m_HeadRect.right + 3;
   	if (rect.PtInRect(point)) return 1;
    rect.left = m_HeadRect.left - 3;
    rect.right = m_HeadRect.left + 3;
   	if (rect.PtInRect(point)) return 2;
	rect = m_HeadRect;
    rect.top = m_HeadRect.top - 3;
    rect.bottom = m_HeadRect.top + 3;
   	if (rect.PtInRect(point)) return 3;
	if (m_HeadRect.PtInRect(point)) return 0;
	if (m_ParentType != 0)
	{
	    CRect rect = m_Rect;
		rect.left = m_Rect.right - 3;
	    rect.right = m_Rect.right + 3;
   		if (rect.PtInRect(point)) return 1;
	    rect.left = m_Rect.left - 3;
		rect.right = m_Rect.left + 3;
	   	if (rect.PtInRect(point)) return 2;
		if (m_Rect.PtInRect(point)) return 0;
	}
	return -1;
}

void CFIDDrawObj::MoveHandle(CView* pView,int nHandle, const CPoint& point)
{
	ASSERT_VALID(this);
	if ((point.x == 0) && (point.y == 0 )) return;
    CRect rect = m_Rect;
	switch (nHandle)
	{
	default:
		ASSERT(FALSE);

	case 0:
		{
			m_Rect += point;
			m_HeadRect += point;
		}	
		break;
	case 1:
		if (((m_Rect.right + point.x < m_xMax) && (point.x > 0)) ||
			((m_Rect.right + point.x > m_xMin) && (point.x < 0)))
		{
			m_Rect.right += point.x;
			m_HeadRect.right += point.x;
		}	
		break;
	case 2:
		if (((m_Rect.left + point.x < m_xMax) && (point.x > 0)) ||
			((m_Rect.left + point.x > m_xMin) && (point.x < 0)))
		{
			m_Rect.left += point.x;
			m_HeadRect.left += point.x;
		}	
		break;
	case 3:
		if (((m_HeadRect.top + point.y < m_yMax) && (point.y > 0)) ||
			((m_HeadRect.top + point.y > m_yMin) && (point.y < 0)))
			m_HeadRect.top += point.y;			
		break;
	}
	if (rect != m_Rect) pDoc->SetModifiedFlag();
}

HCURSOR CFIDDrawObj::GetHandleCursor(int nHandle)
{
	ASSERT_VALID(this);

	switch (nHandle)
	{
    case 0:
		return AfxGetApp()->LoadCursor(IDC_CURSOR_SELECT);
	case 3:
		return AfxGetApp()->LoadCursor(IDC_CURSOR_SIZENS);
	case 9:
		return AfxGetApp()->LoadCursor(IDC_CURSOR_CROSS);
	default:
		return AfxGetApp()->LoadCursor(IDC_CURSOR_SIZEWE);
	}
}

void CFIDDrawObj::OnLButtonDown(CView* pView, UINT nFlags, const CPoint& point)
{
    if (m_bSelected)
    {
	    CDrawObj::OnLButtonDown(pView,nFlags,point);
		nDragHandle = HitTest(pView,point); 
		if (nDragHandle == 0) 
		{
			m_SelectMode = move;     
			CRect rect = pDoc->GetRect();
			m_xMin = rect.left; m_xMax = rect.right;
			m_yMin = rect.top; m_yMax = rect.bottom;
		}
		else if (nDragHandle > 0) 
		{
			m_SelectMode = size; 
			switch (nDragHandle)
			{
			case 1:
				{   
					m_xMin = m_Rect.left + GetMinWidth();
					if (m_xMin == m_Rect.left) m_xMin = m_Rect.left + 10;
					if ((m_pParentObj == NULL) || (m_ParentType != 0))
						m_xMax = pDoc->GetRect().right;
					else 
					{
						ASSERT(m_pParentObj->IsKindOf(RUNTIME_CLASS(CTrackObj)));
						if (m_DrawDirect == HORDIR) 
							m_xMax = ((CTrackObj*)m_pParentObj)->GetHoriFIDRect().right;
						else if (m_DrawDirect == VERDIR) 
							m_xMax = ((CTrackObj*)m_pParentObj)->GetHeadRect().right;
					}		
				}
				break;	 
			case 2:
				{   
					m_xMax = m_Rect.right - GetMinWidth();
					if (m_xMax == m_Rect.right) m_xMax = m_Rect.right - 10;
					if ((m_pParentObj == NULL) || (m_ParentType != 0))
						m_xMin = pDoc->GetRect().left;
					else 
					{
						ASSERT(m_pParentObj->IsKindOf(RUNTIME_CLASS(CTrackObj)));
						if (m_DrawDirect == HORDIR) 
							m_xMin = ((CTrackObj*)m_pParentObj)->GetHoriFIDRect().left;
						else if (m_DrawDirect == VERDIR) 
							m_xMin = ((CTrackObj*)m_pParentObj)->GetHeadRect().left;
					}		
				}
				break;	 
			case 3:
				{
					m_yMax = m_HeadRect.bottom - GetMinHeight();
					m_yMin = pDoc->GetRect().top;
				}	
				break;
			default:
				ASSERT(FALSE);
				break;	
			}
		}	
		else return;
		SetCursor(GetHandleCursor(nDragHandle));
	}	
	if (m_SelectMode == move)
	{
		POSITION pos = m_ObjList.GetHeadPosition();
		while (pos != NULL)
		{
			CDrawObj* pObj = (CDrawObj*)m_ObjList.GetNext(pos);
			if (pObj != NULL) pObj->OnLButtonDown(pView, nFlags, point);
		}                  
	}	
	CreateFocusObj(pView);
}

void CFIDDrawObj::OnLButtonUp(CView* pView, UINT nFlags, const CPoint& point)
{
	if (m_SelectMode == move)
	{
		POSITION pos = m_ObjList.GetHeadPosition();
		while (pos != NULL)
		{
			CDrawObj* pObj = (CDrawObj*)m_ObjList.GetNext(pos);
			if (pObj != NULL) pObj->OnLButtonUp(pView, nFlags, point);
		}                  
		if (!m_bSelected)
		{
			DeleteFocusObj(pView);
			return;
		}	
	}	
	if (m_bSelected)
	{
		if (m_SelectMode == move)
		{
	    	m_pFocusObj->m_Rect.NormalizeRect();
	    	m_pFocusObj->m_HeadRect.NormalizeRect();
			SetRect(m_pFocusObj->m_Rect);
			SetHeadRect(m_pFocusObj->m_HeadRect); 	           
			DeleteFocusObj(pView);
			if (m_ParentType != 2)
			{
				CDrawObj* pObj1 = m_pParentObj;
				int nParentType = m_ParentType;
				CDrawObj* pObj = pDoc->GetLocateObject(this);
				if (pObj1 == NULL) pDoc->RemoveObj(this);
				else
				{
					if (pObj1 == pObj) pObj1->RemoveObj(this,0);
					else pObj1->RemoveObj(this,1);
				}
				if (pObj != NULL) pObj->AddObj(this,0);
				else
				{ 
					if (m_HeadRect.bottom != m_Rect.top)
					{
						CPoint point(0,0);
						point.y = m_Rect.top - m_HeadRect.bottom;
						SetRect(m_Rect - point);
					}
					pDoc->AddObj(this); 
				}	
				if (pObj1 != pObj)
				{
					if (pObj1 == NULL) pDoc->OnChildRemove(this,nParentType);
					else pObj1->OnChildRemove(this,nParentType);
				}	   
			}
		}	
		else if (m_SelectMode == size)
		{
			CRect nSaveRect = m_HeadRect;
			SetHeadRect(m_pFocusObj->m_HeadRect);
			DeleteFocusObj(pView);
			if ((m_HeadRect.left != nSaveRect.left) || (m_HeadRect.right != nSaveRect.right))
			{
				if (m_pParentObj == NULL) pDoc->OnChildWidthChange(this);
				else m_pParentObj->OnChildWidthChange(this);
			}
			if ((m_HeadRect.top != nSaveRect.top) || (m_HeadRect.bottom != nSaveRect.bottom))
			{
				if (m_pParentObj == NULL) pDoc->OnChildHeightChange(this);
				else m_pParentObj->OnChildHeightChange(this);
			}
		}
		CDrawObj::OnLButtonUp(pView,nFlags,point);
	}	
}

void CFIDDrawObj::OnMouseMove(CView* pView, UINT nFlags, const CPoint& point)
{
	CPoint delta = (CPoint)(point - c_last);
	m_pFocusObj->DrawFocus(pView);
	if (m_SelectMode == move)
	{
		CPoint point1 = point;
		if (m_bSelected)
		{
			CRect rect = m_pFocusObj->m_HeadRect;
			rect.NormalizeRect();
			if ((rect.right + delta.x > m_xMax) && (delta.x > 0)) 
			{
				if (rect.right < m_xMax)
					point1.x = m_xMax - rect.right + c_last.x;
				else point1.x = c_last.x;	
			}
			if ((rect.left + delta.x < m_xMin) && (delta.x < 0)) 
			{
				if (rect.left > m_xMin)
					point1.x = m_xMin - rect.left + c_last.x;
				else point1.x = c_last.x;	
			}	
			if ((rect.bottom + delta.y > m_yMax) && (delta.y > 0)) 
			{
				if (rect.bottom < m_yMax)
					point1.y = m_yMax - rect.bottom + c_last.y;
				else point1.y = c_last.y;
			}	
			if ((rect.top + delta.y < m_yMin) && (delta.y < 0)) 
			{
				if (rect.top > m_yMin)
					point1.y = m_yMin - rect.top + c_last.y;
				else point1.y = c_last.y;	
			}	
			if (point1.x != point.x) delta.x = point1.x - c_last.x;
			if (point1.y != point.y) delta.y = point1.y - c_last.y;
		}
		POSITION pos = m_ObjList.GetHeadPosition();
		while (pos != NULL)
		{
			CDrawObj* pObj = (CDrawObj*)m_ObjList.GetNext(pos);
			if (pObj != NULL) pObj->OnMouseMove(pView, nFlags, point);
		}                  
		m_pFocusObj->MoveHandle(pView,nDragHandle, delta);
	}	
	if (m_SelectMode == size)
		m_pFocusObj->MoveHandle(pView,nDragHandle, delta);
	m_pFocusObj->DrawFocus(pView);
	if (m_bSelected) 
	{
		DoScroll((CScrollView*)pView);
		CDrawObj::OnMouseMove(pView,nFlags,point);
	}
}

void CFIDDrawObj::CreateFocusObj(CView* pView)
{
	m_pFocusObj = new CFIDDrawObj(m_strPathName, m_Rect,m_pParentObj,pDoc);
	m_pFocusObj->m_Rect = m_Rect;
	m_pFocusObj->m_HeadRect = m_HeadRect;
	m_pFocusObj->m_AliasName = m_AliasName;
	m_pFocusObj->DrawFocus(pView);
}

void CFIDDrawObj::DeleteFocusObj(CView* pView)
{
	ASSERT((m_pFocusObj != NULL) && (pView != NULL));
	if (m_pFocusObj == NULL) return;
	if (pView != NULL) m_pFocusObj->DrawFocus(pView);
	delete m_pFocusObj;
	m_pFocusObj = NULL;
}   

void CFIDDrawObj::DrawFocusObj(CView* pView)
{
	ASSERT((m_pFocusObj != NULL) && (pView != NULL));
	if ((m_pFocusObj == NULL) || (pView == NULL)) return;
	m_pFocusObj->DrawFocus(pView);
	if (m_SelectMode != move) return;
	POSITION pos = m_ObjList.GetHeadPosition();
	while (pos != NULL)
	{
		CDrawObj* pObj = (CDrawObj*)m_ObjList.GetNext(pos);
		if (pObj != NULL) pObj->DrawFocusObj(pView);
	}                  
}

void CFIDDrawObj::DrawFocus(CView* pView)
{
	ASSERT(pView != NULL);
	if (pView == NULL) return;
	CClientDC dc(pView);
	pView->OnPrepareDC(&dc,NULL);
	if (nDragHandle >= 0)
	{
		dc.SetROP2(R2_XORPEN);
	    CPen m_Pen(PS_DOT,1,RGB(0,0,0));
    	CPen *pOldPen = dc.SelectObject(&m_Pen);
	    CBrush* pOldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);
		CRect rect = m_HeadRect;
		pDoc->LPtoPP(&rect);
		dc.Rectangle(rect);
		rect = m_Rect;
		pDoc->LPtoPP(&rect);
		dc.Rectangle(rect);
		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBrush);
		dc.SetROP2(R2_COPYPEN);
	}
}

void CFIDDrawObj::SetDepth(double sdep,double edep)
{                           
	CPoint point(0,0);
	point.y = m_Rect.top - DepthToYCoor(sdep);
	m_PlotSdep = sdep; m_PlotEdep = edep;
	bFlush = TRUE;
	m_Rect.bottom = DepthToYCoor(m_PlotEdep);
	POSITION pos = m_ObjList.GetTailPosition();
	while (pos != NULL)
	{
		CDrawObj* pObj = (CDrawObj*)m_ObjList.GetPrev(pos);
		if (pObj != NULL)
		{
			pObj->SetRect(pObj->GetRect()+point);
		}	
	}               
}

void CFIDDrawObj::OnChangeDepC(double depc, int flag)
{
	CPoint pt(0,0);
	pt.y = Round((depc / pDoc->m_DepC -1) * m_Rect.top);
	m_Rect += pt; 
	m_HeadRect += pt;
	m_Rect.bottom =  DepthToYCoor(m_PlotEdep);
	if (flag == 1) bErrorFID = FALSE;
	bFlush = TRUE;
	CDrawObj::OnChangeDepC(depc,flag);
}

double CFIDDrawObj::YCoorToDepth(int y)
{
	return (double)((y - m_Rect.top) * pDoc->m_DepC + m_PlotSdep);
}

int CFIDDrawObj::DepthToYCoor(double depth)
{
	return (int) ((depth - m_PlotSdep) / pDoc->m_DepC + m_Rect.top);
}

void CFIDDrawObj::InvalObj(CView* pView)
{
	ASSERT(pView != NULL);
	CClientDC dc(pView);              
	pView->OnPrepareDC(&dc);
	CRect rect = m_Rect;
	rect.top = m_HeadRect.top;
	if (pDoc->m_DrawFIDHeadMode == 1)
		rect.bottom = m_Rect.bottom + m_Rect.top - m_HeadRect.top;
	pDoc->LPtoPP(&rect);
	rect.InflateRect(5,5);
	dc.LPtoDP(rect);
	pView->InvalidateRect(rect,FALSE);
	pView->UpdateWindow();
}
