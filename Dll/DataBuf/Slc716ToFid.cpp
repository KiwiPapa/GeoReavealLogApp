// Slc716ToFid.cpp: implementation of the CSlc716ToFid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "_comext.h"
#include "Slc716ToFid.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSlc716ToFid::CSlc716ToFid()
{

}

CSlc716ToFid::~CSlc716ToFid()
{

}
bool CSlc716ToFid::Slc716ToFid(CString SourceFile,CString sObjectPath,int nCurvesRadio,FILE *fo)
{
	CString s;
	m_SourceFile=SourceFile; //源文件名   
	m_sObjectPath=sObjectPath;  //输出目录
	m_nCurvesRadio=nCurvesRadio;//过滤开关
	fp=fo;

	pGuage= new CProgressDlg;
	pGuage->Create(CWnd::GetActiveWindow());
	pGuage->SetRange(0,100);
	pGuage->SetStep(1);
	pGuage->OffsetPos(0);
	pGuage->ShowWindow(SW_SHOW);

	Slc716R=new CSlc716R ;
	FidWrite=new CFidWrite ; //输出类
	CurveIndex.RemoveAll();
	bool bResult=Transform();
	//输出转换结果信息
	if(bResult)
	{
		FidWrite->PrintHead(fp);
	}

	delete pGuage;  //删除进度条
	delete FidWrite; FidWrite=NULL;
	delete Slc716R;	Slc716R=NULL;
	SelCurveName.RemoveAll();
	NewCurveName.RemoveAll();
	NewUnits.RemoveAll();
	CurveIndex.RemoveAll();
	return bResult;
}
bool CSlc716ToFid::Transform()
{
	CString s;
	if(!IsSLC716(m_SourceFile))
	{
		fprintf(fp,"%s is not SLC716 Format\n\n",m_SourceFile);
		return false;
	}
	//根据输出目录及输入文件名确定井名和输出路径
	CString sFileTitle=MyGetFileTitle(m_SourceFile);
	CString sOutWellPath=m_sObjectPath+"\\#"+sFileTitle;
	ModiFileName(sOutWellPath); //根据条件决定是否修改文件名
	sFileTitle=MyGetFileTitle(sOutWellPath);
	CString sWellName=sFileTitle.Mid(1); //去掉“#”
	FidWrite->SetFidFileName(m_sObjectPath,sWellName);

	if(!Slc716R->Open(m_SourceFile)) 
	{
		fprintf(fp,"\n!!!!链接的数据文件打开失败\n\n");
	}
	else
	{
		Slc716R->ReadHead(); //读SLC716头
		//Slc716R->Prt_Header(fp);
		SelectCurves();
		SetFidHead();
		FidWrite->WriteFidInfo();
		int NumPoint=Slc716R->NumPoint;
		float *buf=new float[Slc716R->NumBlock*int(Slc716R->Slc716Head.Spcpr)];
		pGuage->m_nTextMode=1; //文本模式
		pGuage->SetRange(0,FidWrite->FidHead.NumLog);
		for(int i=0;i<FidWrite->FidHead.NumLog;i++)
		{
			pGuage->m_sTextInfo=NewCurveName.GetAt(i);
			pGuage->SetPos(i+1);  //设置进度条当前值
			if (pGuage->CheckCancelButton())
			{
				sp_Break_Status=true;
				break;
			}
			int index=CurveIndex.GetAt(i);
			Slc716R->ReadChannel(index,buf);//读一条曲线数据
			FidWrite->WriteGenData(i,NumPoint,buf);
		}
		delete []buf; buf=NULL;
		Slc716R->Close(); //关闭输入文件
	}
	//输出信息
	fprintf(fp,"DataBuff: %s\n",(const char*)m_SourceFile);
	fprintf(fp,"ToObject: %s\n",(const char*)FidWrite->m_sFidFile);
	return !sp_Break_Status;
}
void CSlc716ToFid::DataNormalization(int NumPoint,int NumLog,float *buf)
{
	//如果为上测，则将数据重新排序
	if(Slc716R->Slc716Head.Rlev>0) return;
	for(int i=0;i<NumLog;i++)
	{
		int n1=i*NumPoint;
		int n2=i*NumPoint+NumPoint/2;
		for(int j=n1;j<n2;j++)
		{
			int n=(i+1)*NumPoint-j+n1-1;
			float fTemp=buf[j];
			buf[j]=buf[n];
			buf[n]=fTemp;
		}
	}
}

void CSlc716ToFid::SelectCurves()
{
	CString s;
	bool *CurveID=new bool[Slc716R->Slc716Head.NumLog];
	for(int i=0;i<Slc716R->Slc716Head.NumLog;i++)
	{
		CurveID[i]=false;
	}
	CString sCurveName;
	switch(m_nCurvesRadio)
	{
	case 0://曲线过滤	
		for(i=0;i<Slc716R->Slc716Head.NumLog;i++)
		{
			bool bOk=false;
			sCurveName.Format ("%-.4s",Slc716R->Slc716Head.CurveName[i]);
			sCurveName.TrimRight();
			for(int j=0;j<sp_FilterCurves.GetSize();j++)
			{
				if(sCurveName.CompareNoCase(sp_FilterCurves.GetAt(j))==0)
				{
					bOk=true;
					break;
				}
			}
			if(bOk)
			{
				CurveID[i]=true;
			}
		}
		break;
	case 1: //全部曲线
	case 2: //常规曲线
	case 3: //交互选择
		for(i=0;i<Slc716R->Slc716Head.NumLog;i++)
		{
			CurveID[i]=true;
		}
		break;
	}
	SelCurveName.RemoveAll();
	NewCurveName.RemoveAll();
	NewUnits.RemoveAll();
	//根据开关设置决定是否进行交互选择
	if(m_nCurvesRadio !=3 )
	{	//没有交互操作
		for(i=0;i<Slc716R->Slc716Head.NumLog;i++)
		{
			if(!CurveID[i]) continue;
			sCurveName.Format("%-.4s",Slc716R->Slc716Head.CurveName[i]);
			SelCurveName.Add(sCurveName);
			sCurveName.MakeUpper();
			sCurveName.TrimRight();
			NewCurveName.Add(sCurveName);
			NewUnits.Add("");
		}
	}
	else
	{	//交互操作
		CReCurNamDlg ReCurNamDlg;
		ReCurNamDlg.m_nMaxLen=15; //最大曲线长度
		ReCurNamDlg.m_nMaxLog=99999; //最多曲线数
		for(int i=0;i<Slc716R->Slc716Head.NumLog;i++)
		{
			if(!CurveID[i]) continue;
			sCurveName.Format ("%-.4s",Slc716R->Slc716Head.CurveName[i]);
			ReCurNamDlg.m_SourceName.Add(sCurveName);
			sCurveName.TrimLeft();
			sCurveName.TrimRight();
			sCurveName.Remove(' ');
			ReCurNamDlg.m_ObjectName.Add(sCurveName);//预置新曲线名
			ReCurNamDlg.m_Units.Add("");
			ReCurNamDlg.m_NumDim.Add(1);
		}
		int Result=ReCurNamDlg.DoModal();
		for(i=0;i<ReCurNamDlg.m_SourceName.GetSize();i++)
		{
			//原名称
			SelCurveName.Add(ReCurNamDlg.m_SourceName.GetAt(i));
			//新名称
			s=ReCurNamDlg.m_ObjectName.GetAt(i);
			s.MakeUpper();
			NewCurveName.Add(s);
			//单位
			NewUnits.Add(ReCurNamDlg.m_Units.GetAt(i));
		}
		ReCurNamDlg.m_SourceName.RemoveAll();
		ReCurNamDlg.m_ObjectName.RemoveAll();
		ReCurNamDlg.m_NumDim.RemoveAll();
		ReCurNamDlg.m_Units.RemoveAll();
	}
	///////////////////////////////////////////////////
	delete []CurveID; CurveID=NULL;
	CurveIndex.RemoveAll();
	for(i=0;i<SelCurveName.GetSize();i++)
	{
		for(int j=0;j<Slc716R->Slc716Head.NumLog;j++)
		{
			s.Format ("%-.4s",Slc716R->Slc716Head.CurveName[j]);
			if(s.CompareNoCase(SelCurveName.GetAt(i))==0)
			{
				CurveIndex.Add(j);
				break;
			}
		}
	}
}

void CSlc716ToFid::SetFidHead()
{
	sprintf(FidWrite->FidHead.Oil_Field,"%-80.80s","");
	sprintf(FidWrite->FidHead.Region,"%-80.80s","");
	sprintf(FidWrite->FidHead.Company,"%-80.80s",Slc716R->Slc716Head.CompanyName);
	sprintf(FidWrite->FidHead.Well,"%-80.80s",Slc716R->Slc716Head.WellName);
	sprintf(FidWrite->FidHead.X_Coordinate,"%-40.40s","");
	sprintf(FidWrite->FidHead.Y_Coordinate,"%-40.40s","");
	sprintf(FidWrite->FidHead.Exformation,"%-80.80s","");

	FidWrite->FidHead.NumLog=CurveIndex.GetSize();
	//根据曲线数(FidWrite->FidHead.NumLog)开辟空间
	FidWrite->InitFidChannel(); 
	for(int i=0;i<CurveIndex.GetSize();i++)
	{
		int k=CurveIndex.GetAt(i);
		strcpy(FidWrite->FidChannel[i].CurveName,NewCurveName.GetAt(i));
		FidWrite->FidChannel[i].NumOfDimension=2;
		
		//设置第一维数据
		strcpy(FidWrite->FidChannel[i].DimInfo[0].Name,"DEP");
		strcpy(FidWrite->FidChannel[i].DimInfo[0].Unit,"m");
		FidWrite->FidChannel[i].DimInfo[0].RepCode=4;
		FidWrite->FidChannel[i].DimInfo[0].CodeLen=4;
		FidWrite->FidChannel[i].DimInfo[0].Nps=1;
		FidWrite->FidChannel[i].DimInfo[0].Npw=0;
		if(Slc716R->Slc716Head.Rlev>0)
		{
			FidWrite->FidChannel[i].DimInfo[0].Start=Slc716R->Slc716Head.Stdep;
			FidWrite->FidChannel[i].DimInfo[0].Stop=Slc716R->Slc716Head.Endep;
			FidWrite->FidChannel[i].DimInfo[0].Rlev=Slc716R->Slc716Head.Rlev;
		}
		else
		{
			FidWrite->FidChannel[i].DimInfo[0].Start=Slc716R->Slc716Head.Endep;
			FidWrite->FidChannel[i].DimInfo[0].Stop=Slc716R->Slc716Head.Stdep;
			FidWrite->FidChannel[i].DimInfo[0].Rlev=float(fabs(Slc716R->Slc716Head.Rlev));
		}

		//设置第二维数据
		strcpy(FidWrite->FidChannel[i].DimInfo[1].Name,FidWrite->FidChannel[i].CurveName);
		if(NewUnits.GetAt(i).IsEmpty())
		{
			strcpy(FidWrite->FidChannel[i].DimInfo[1].Unit,"none");
		}
		else
		{
			strcpy(FidWrite->FidChannel[i].DimInfo[1].Unit,NewUnits.GetAt(i));
		}
		FidWrite->FidChannel[i].DimInfo[1].RepCode=4;
		FidWrite->FidChannel[i].DimInfo[1].CodeLen=4;
		FidWrite->FidChannel[i].DimInfo[1].Nps=1;
		FidWrite->FidChannel[i].DimInfo[1].Npw=1;
		FidWrite->FidChannel[i].DimInfo[1].Start=0;
		FidWrite->FidChannel[i].DimInfo[1].Stop=100;
		FidWrite->FidChannel[i].DimInfo[1].Rlev=0;
	}
}
