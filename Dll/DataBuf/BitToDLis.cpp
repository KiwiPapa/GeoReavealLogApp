// BitToDLis.cpp: implementation of the CBitToDLis class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "_Comext.h"
#include "BitToDLis.h"
#include <math.h>
#include <time.h>
#include "SetDlisParaDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBitToDLis::CBitToDLis()
{
	ItemNum=NULL;
}

CBitToDLis::~CBitToDLis()
{
	if(ItemNum)
	{
		delete []ItemNum; ItemNum=NULL;
	}
}

bool CBitToDLis::BitToDLis(CString SourceFile,CString sObjectPath,int nCurvesRadio,CString sProducer,FILE *fo)
{
	m_SourceFile=SourceFile; //源文件名   
	m_sObjectPath=sObjectPath;  //输出目录
	m_nCurvesRadio=nCurvesRadio;//过滤开关
	m_sProducer=sProducer;
	fp=fo;
	pGuage= new CProgressDlg;
	pGuage->Create(CWnd::GetActiveWindow());
	pGuage->SetRange(0,100);
	pGuage->SetStep(1);
	pGuage->OffsetPos(0);
	pGuage->ShowWindow(SW_SHOW);

	BitR=new CBitR ;
	DlisWrite=new CDlisWrite ; 
	bool bResult=Transform();
	delete pGuage;  //删除进度条
	delete BitR; BitR=NULL;
	delete DlisWrite; DlisWrite=NULL;

	return bResult;
}

bool CBitToDLis::Transform()
{
	if(!IsBIT(m_SourceFile))
	{
		fprintf(fp,"%s is not BIT Format\n\n",m_SourceFile);
		return false;
	}
	CString s;
	//根据输出目录及输入文件名确定输出文件名
	DlisFileName.Format ("%s\\%s.dlis",m_sObjectPath,MyGetFileTitle(m_SourceFile));
	ModiFileName(DlisFileName); //根据条件决定是否修改文件名

	if(!BitR->Open(m_SourceFile))
		return false;
	BitR->Open(m_SourceFile);
	BitR->ReadHead();
	SelectCurves();//选择曲线或对曲线改名
	if(CurveIndex.GetSize()==0)
	{
		BitR->Close();
		fprintf(fp,"\n!!!!没有曲线输出\n\n");
		return false;
	}
	//输出信息
	fprintf(fp,"DataBuff: %s\n",(const char*)m_SourceFile);
	fprintf(fp,"ToObject: %s\n",(const char*)DlisFileName);
	////////////////////////////////////////////
	GetDlisFDataIndexFromBit(); //对BIT通道信息进行分组
	Prt_FdataItemInfo(); //打印帧分组信息
	SetDlisChannelsFromBit(); //根据BIT信息设置通道信息
	SetDlisFrameFromBit(); //设置DLIS帧对象属性
	SetAxisFromBit(); //设置DLIS轴对象属性
	SetStoUnitLab(); //设置DLIS存储标志
	SetFileHeader(); //设置文件头信息
	SetOrigin(); //设置源信息
	SetDlisParameter(); //修改或补充参数
	DlisWrite->Open(DlisFileName,fp); //打开DLIS文件
	DlisWrite->SetTrailLengthFlag(); //记录尾长度设置
	DlisWrite->WriteStoUnitLab(); //写DLIS存储标志
	DlisWrite->WriteFileHeader(); //写文件头信息记录
	DlisWrite->WriteOrigin(); //写源信息记录
	DlisWrite->WriteParameter(); //写静态参数记录
	DlisWrite->WriteChannel(); //写通道信息记录
	DlisWrite->WriteFrame(); //写帧信息记录
	DlisWrite->WriteAxis(); //写轴信息记录
	BitDataToDlis(); //输出数据
	CurveIndex.RemoveAll(); //源曲线索引号
	SelCurveName.RemoveAll(); //选择曲线名表
	NewCurveName.RemoveAll(); //新曲线名表
	NewUnits.RemoveAll(); ////新单位名表
	DlisWrite->Close(); //关闭DLIS文件
	DlisWrite->Prt_Header();
	return !sp_Break_Status;
}

void CBitToDLis::SelectCurves()
{
	CString s;
	bool *CurveID=new bool[BitR->BitHead.NumLog];
	for(int i=0;i<BitR->BitHead.NumLog;i++)
		CurveID[i]=false;
	CString sCurveName;
	switch(m_nCurvesRadio)
	{
	case 0://曲线过滤
		for(i=0;i<BitR->BitHead.NumLog;i++)
		{
			bool bOk=false;
			sCurveName.Format ("%-.4s",BitR->BitHead.CurveName[i]);
			sCurveName.TrimRight();
			for(int j=0;j<sp_FilterCurves.GetSize();j++)
			{
				if(sCurveName.CompareNoCase(sp_FilterCurves.GetAt(j))==0)
				{
					bOk=true;
					break;
				}
			}
			CurveID[i]=bOk;
		}
		break;
	case 2://常规曲线
		for(i=0;i<BitR->NumConvLog;i++)
			CurveID[i]=true;
		break;
	default://交互选择或全部曲线
		for(i=0;i<BitR->BitHead.NumLog;i++)
			CurveID[i]=true;
		break;
	}
	//////////////////////////////////////////////
	SelCurveName.RemoveAll(); //选择曲线名表
	NewCurveName.RemoveAll(); //新曲线名表
	NewUnits.RemoveAll(); ////新单位名表
	CurveIndex.RemoveAll(); //源曲线索引号
	for(i=0;i<BitR->BitHead.NumLog;i++)
	{
		if(!CurveID[i]) continue;
		s.Format("%-.4s",BitR->BitHead.CurveName[i]);
		SelCurveName.Add(s);
		s.TrimRight();
		NewCurveName.Add(s);
		NewUnits.Add("");
		CurveIndex.Add(i);
	}
	delete []CurveID; CurveID=NULL;
	///////////////////////////////////////////
	//根据开关设置决定是否进行交互选择
	if(m_nCurvesRadio==3)
	{
		CReCurNamDlg ReCurNamDlg;
		ReCurNamDlg.m_nMaxLen=255; //最大曲线长度
		ReCurNamDlg.m_nMaxLog=99999; //最多曲线数
		for(int i=0;i<CurveIndex.GetSize();i++)
		{
			int index=CurveIndex.GetAt(i);
			int NumDim=1;
			if(index>=BitR->NumConvLog)
			{
				NumDim=2;
			}
			ReCurNamDlg.m_SourceName.Add(SelCurveName.GetAt(i));
			ReCurNamDlg.m_Units.Add(NewUnits.GetAt(i));
			ReCurNamDlg.m_ObjectName.Add(NewCurveName.GetAt(i));//预置新曲线名
			ReCurNamDlg.m_NumDim.Add(NumDim);
		}
		SelCurveName.RemoveAll();
		NewCurveName.RemoveAll();
		NewUnits.RemoveAll();
		int Result=ReCurNamDlg.DoModal();
		for(i=0;i<ReCurNamDlg.m_SourceName.GetSize();i++)
		{
			SelCurveName.Add(ReCurNamDlg.m_SourceName.GetAt(i));//原名称
			s=ReCurNamDlg.m_ObjectName.GetAt(i);//新名称
			s.MakeUpper();
			NewCurveName.Add(s);
			NewUnits.Add(ReCurNamDlg.m_Units.GetAt(i));//单位
		}
		ReCurNamDlg.m_SourceName.RemoveAll();
		ReCurNamDlg.m_ObjectName.RemoveAll();
		ReCurNamDlg.m_NumDim.RemoveAll();
		ReCurNamDlg.m_Units.RemoveAll();
		//重新索引
		CWordArray NewIndex;
		for(i=0;i<SelCurveName.GetSize();i++)
		{
			for(int j=0;j<CurveIndex.GetSize();j++)
			{
				int index=CurveIndex.GetAt(j);
				s.Format ("%-.4s",BitR->BitHead.CurveName[index]);
				if(s.CompareNoCase(SelCurveName.GetAt(i))==0)
				{
					NewIndex.Add(index);
					break;
				}
			}
		}
		//将索引值换回
		CurveIndex.RemoveAll();
		for(i=0;i<NewIndex.GetSize();i++)
		{
			CurveIndex.Add(NewIndex.GetAt(i));
		}
		NewIndex.RemoveAll();
	}
}

void CBitToDLis::GetDlisFDataIndexFromBit()
{
	CString s;
	typedef struct tagCurve
	{
		float Start;
		float Stop;
		float Rlev;
	}_Curve;
	const double er=0.001;
	NumItem=0; //组数
	if(CurveIndex.GetSize()==0) return;
	_Curve *Curve=new _Curve[CurveIndex.GetSize()];
	if(ItemNum)
	{
		delete []ItemNum; ItemNum=NULL;
	}
	ItemNum=new int[CurveIndex.GetSize()];
	for(int i=0;i<CurveIndex.GetSize();i++)
	{
		int index=CurveIndex.GetAt(i);
		float Start=BitR->BitHead.Stdep;
		float Rlev=BitR->BitHead.Rlev;
		float Stop=BitR->BitHead.Endep;
		bool bFind=false;
		for(int j=0;j<NumItem;j++)
		{
			if(fabs(Start-Curve[j].Start)<er && fabs(Stop-Curve[j].Stop)<er	&&  fabs(Rlev-Curve[j].Rlev)<er)
			{
				bFind=true;
				ItemNum[i]=j;
				break;
			}
		}
		if(!bFind)
		{
			Curve[NumItem].Start=Start;
			Curve[NumItem].Stop=Stop;
			Curve[NumItem].Rlev=Rlev;
			ItemNum[i]=NumItem;
			NumItem++;
		}
	}
	delete []Curve; Curve=NULL;
}
void CBitToDLis::Prt_FdataItemInfo()
{
	for(int i=0;i<NumItem;i++)
	{
		fprintf(fp,"第%2d组: ",i+1);
		int nc=0;
		for(int j=0;j<CurveIndex.GetSize();j++)
		{
			if(ItemNum[j]==i)
			{
				fprintf(fp," %-8.8s",NewCurveName.GetAt(j));
				nc++;
				if(nc%5==0)
				{
					fprintf(fp,"\n%-8s","");
				}
			}
		}
		fprintf(fp,"\n");
	}
}
void CBitToDLis::SetDlisChannelsFromBit()
{
	CString s;
	DlisWrite->SetFrameNumber(NumItem);
	DlisWrite->SetChannelNumber(CurveIndex.GetSize());
	for(int i=0;i<CurveIndex.GetSize();i++)
	{
		int index=CurveIndex.GetAt(i);
		DlisWrite->Channel[i].Origin=1;  //对象O=1,C=0
		DlisWrite->Channel[i].CopyNum=0; //对象O=1,C=0
		strcpy(DlisWrite->Channel[i].Name,NewCurveName.GetAt(i));

		strcpy(DlisWrite->Channel[i].LongName,"");
		strcpy(DlisWrite->Channel[i].Properties,"");
		strcpy(DlisWrite->Channel[i].Units,NewUnits.GetAt(i));
		if(stricmp(DlisWrite->Channel[i].Units,"none")==0)
		{
			strcpy(DlisWrite->Channel[i].Units,"");
		}
		if(index<BitR->NumConvLog)
		{
			DlisWrite->Channel[i].RepCode=DLIS_REPC_FSINGL;
			DlisWrite->Channel[i].NumDim=1; //常规或波形
			DlisWrite->Channel[i].Dimension[0]=1; //维元素
			DlisWrite->Channel[i].Dimension[1]=0; //维元素
			DlisWrite->Channel[i].Dimension[2]=0; //维元素
		}
		else
		{
			DlisWrite->Channel[i].RepCode=DLIS_REPC_SSHORT;
			DlisWrite->Channel[i].NumDim=1; //波形
			DlisWrite->Channel[i].Dimension[0]=BitR->BitHead.NumSample;//维元素
			DlisWrite->Channel[i].Dimension[1]=0; //维元素
			DlisWrite->Channel[i].Dimension[2]=0; //维元素
		}
	}
}
void CBitToDLis::SetDlisFrameFromBit()
{
	CString s;
	for(int i=0;i<NumItem;i++)
	{
		DlisWrite->Frame[i].Origin=1;//源(对象)
		DlisWrite->Frame[i].CopyNum=0;//拷贝数(对象)
		sprintf(DlisWrite->Frame[i].Name,"B%d",i+1);//帧名(对象名)
		strcpy(DlisWrite->Frame[i].Index_Type,"BOREHOLE-DEPTH"); //索引类型
		strcpy(DlisWrite->Frame[i].Direction,"INCREASING"); //测井方向
		strcpy(DlisWrite->Frame[i].IndexUnits,"m"); //索引单位 
		int NumCurve=0; //本帧曲线数
		for(int k=0;k<CurveIndex.GetSize();k++)
		{
			if(ItemNum[k]==i)
			{
				int index=CurveIndex.GetAt(k);
				if(BitR->BitHead.Stdep<BitR->BitHead.Endep)
				{
					DlisWrite->Frame[i].Index_Start=BitR->BitHead.Stdep; //索引最小值
					DlisWrite->Frame[i].Index_Stop=BitR->BitHead.Endep; //索引最大值
				}
				else
				{
					DlisWrite->Frame[i].Index_Start=BitR->BitHead.Endep; //索引最小值
					DlisWrite->Frame[i].Index_Stop=BitR->BitHead.Stdep; //索引最大值
				}
				DlisWrite->Frame[i].Index_Step=float(fabs(BitR->BitHead.Rlev)); //步长
				DlisWrite->Frame[i].ChannelID[NumCurve]=k;
				NumCurve++;
			}
		}
		DlisWrite->Frame[i].NumCurve=NumCurve; //本帧曲线数
	}
}
void CBitToDLis::SetAxisFromBit()
{
	CString s;
	int NumAxis=0;
	for(int i=0;i<CurveIndex.GetSize();i++)
	{
		int index=CurveIndex.GetAt(i);
		if(index>=BitR->NumConvLog)
		{
			NumAxis+=1;
		}
	}
	fprintf(fp,"====NumAxis=%d\n",NumAxis);
	fflush(fp);
	if(NumAxis==0) return;
	DlisWrite->SetDlisAxisNumber(NumAxis);
	int nAx=0;
	for(i=0;i<CurveIndex.GetSize();i++)
	{
		int index=CurveIndex.GetAt(i); //BIT曲线索引号
		int NumDim=1;
		if(index>=BitR->NumConvLog)
		{
			NumDim=2;
		}
		DlisWrite->Channel[i].nAxis=NumDim-1; //曲线轴维数
		if(DlisWrite->Channel[i].nAxis==0) continue;
		DlisWrite->Axis[nAx].NumC=0; //坐标数
		//第一维
		int kDim=NumDim-1;
		DlisWrite->Axis[nAx].Origin=1; //源
		DlisWrite->Axis[nAx].CopyNum=0; //拷贝数
		DlisWrite->Axis[nAx].NumC=1; //坐标数
		DlisWrite->Channel[i].Axis[0].Origin=1; //轴：R=OBNAME	
		DlisWrite->Channel[i].Axis[0].CopyNum=0; //轴：R=OBNAME	
		sprintf(DlisWrite->Axis[nAx].Name,"%d",1000+nAx); //轴名，对应于对象名
		strcpy(DlisWrite->Channel[i].Axis[0].Name,DlisWrite->Axis[nAx].Name); //轴：R=OBNAME
		strcpy(DlisWrite->Axis[nAx]. AxisID,"MICRO_TIME");//轴ID号:C=1,R=IDENT
		DlisWrite->Axis[nAx].Coordinates[0]=0; //坐标
		DlisWrite->Axis[nAx].Spacing=BitR->BitHead.RlevTime; //间隔
		strcpy(DlisWrite->Axis[nAx].Units,"us"); //坐标单位
		nAx++;
	}
}
void CBitToDLis::SetStoUnitLab()
{
	char str[256];
	memcpy(DlisWrite->StoUnitLab.SeqNum,"   1",4); //储存序号
	memcpy(DlisWrite->StoUnitLab.DLISVer,"V1.00",5); //版本号
	memcpy(DlisWrite->StoUnitLab.Stru,"RECORD",6); //存储单结构
	sprintf(str,"%5d",DlisWrite->MaxPhyLen); 
	memcpy(DlisWrite->StoUnitLab.MaxRecLen,str,5); 
	sprintf(str,"%-60.60s","BIT to DLIS Conversion"); //存储单标志
	memcpy(DlisWrite->StoUnitLab.StoSetIden,str,60);
}
void CBitToDLis::SetFileHeader()
{
	sprintf(DlisWrite->FileHeader.SequenceNumber,"%10.10s","1");//序列号
	sprintf(DlisWrite->FileHeader.ID,"%-65.65s","BIT.001");//ID号
}
void CBitToDLis::SetOrigin()
{
	CString s;
	strcpy(DlisWrite->Origin.FileID,"BIT.001");//FILE-ID
	strcpy(DlisWrite->Origin.FileSetName,"BIT-TO-DLIS-CONVERSION");//FILE-SET-NAME
	strcpy(DlisWrite->Origin.FileSetNumber,"1");//FILE-SET-NUMBER
	strcpy(DlisWrite->Origin.FileNumber,"1"); //FILE-NUMBER
	strcpy(DlisWrite->Origin.FileType,"RE-FMT"); //FILE-TYPE
	strcpy(DlisWrite->Origin.Product,"GeoReveal "); //PRODUCT
	strcpy(DlisWrite->Origin.Version,"1.0"); //VERSION
	strcpy(DlisWrite->Origin.Programs,"BIT-TO-DLIS"); //PROGRAMS
	CTime t=CTime::GetCurrentTime(); //取当前系统日期和时间
	sprintf(DlisWrite->Origin.CreationTime,"YEAR=%d MONTH=%d DAY=%d HOUR=%d MINUTE=%d SECOND=%d",
		t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),
		t.GetSecond()); //CREATION-TIME
	strcpy(DlisWrite->Origin.OrderNumber,""); //ORDER-NUMBER
	strcpy(DlisWrite->Origin.DescentNumber,""); //DESCENT-NUMBER
	strcpy(DlisWrite->Origin.RunNumber,""); //RUN-NUMBER
	strcpy(DlisWrite->Origin.WellID,""); //WELL-ID
	s.Format ("%-.72s",BitR->BitHead.WellName);
	s.TrimRight();
	strcpy(DlisWrite->Origin.WellName,s); //WELL-NAME
	strcpy(DlisWrite->Origin.FieldName,""); //FIELD-NAME
	s=m_sProducer;
	s.TrimLeft();
	s.TrimRight();
	int sl=(m_sProducer).GetLength();
	if(sl>6)
	{
		strcpy(DlisWrite->Origin.ProducerName,s.Left(sl-6));//PRODUCER-NAME
		strcpy(DlisWrite->Origin.ProducerCode,s.Mid(sl-4,3));//PRODUCER-CODE
		strcpy(DlisWrite->Origin.NameSpaceName,""); //NAME-SPACE-NAME
	}
	else
	{
		strcpy(DlisWrite->Origin.ProducerName,"Schlumberger"); 
		strcpy(DlisWrite->Origin.ProducerCode,"440"); 
		strcpy(DlisWrite->Origin.NameSpaceName,"SLB"); //NAME-SPACE-NAME
	}
	s.Format ("%-.72s",BitR->BitHead.CompanyName);
	s.TrimRight();
	strcpy(DlisWrite->Origin.Company,s); //COMPANY

	strcpy(DlisWrite->Origin.NameSpaceVersion,"0"); //NAME-SPACE-VERSION
}

void CBitToDLis::SetDlisParameter()
{
	sInWellName=MyGetFileTitle(m_SourceFile); //得到的井名
	sInField=MyGetPathName(m_SourceFile); 
	sInField=MyGetFileTitle(sInField); //得到的油田名
	CString s;
	BOOL b1=IsAsciiString(DlisWrite->Origin.Company);
	if(!b1)
	{
		strcpy(DlisWrite->Origin.Company,"SiChuan Petroleum Administration"); //COMPANY
	}
	BOOL b2=IsAsciiString(DlisWrite->Origin.FieldName);	
	if(!b2)
	{
		strcpy(DlisWrite->Origin.FieldName,sInField); //得到油田名
	}
	BOOL b3=IsAsciiString(DlisWrite->Origin.WellName);
	if(!b3)
	{
		strcpy(DlisWrite->Origin.WellName,sInWellName); //得到井名
	}
	if(sp_bAllIgnore) 
		return; //忽略修改

/*	BOOL bModify=b1&b2&b3;
	if(!bModify)
	{
		CSetDlisParaDlg SetDlisParaDlg;
		SetDlisParaDlg.m_FileName=m_SourceFile;
		SetDlisParaDlg.m_Company=DlisWrite->Origin.Company;
		SetDlisParaDlg.m_Field=DlisWrite->Origin.FieldName;
		SetDlisParaDlg.m_Well=DlisWrite->Origin.WellName;
		SetDlisParaDlg.m_Field.Remove('[');
		SetDlisParaDlg.m_Field.Remove(']');
		SetDlisParaDlg.m_Well.Remove('[');
		SetDlisParaDlg.m_Well.Remove(']');
		SetDlisParaDlg.m_DefaultVal=DlisWrite->Origin.DefaultVal;
		SetDlisParaDlg.DoModal();
		//不论是确定还是取消均重新取值,确定为人工修正，取消则修正为缺省值
		strcpy(DlisWrite->Origin.Company,(const char*)SetDlisParaDlg.m_Company);
		strcpy(DlisWrite->Origin.FieldName,(const char*)SetDlisParaDlg.m_Field);
		strcpy(DlisWrite->Origin.WellName,(const char*)SetDlisParaDlg.m_Well);
		DlisWrite->Origin.DefaultVal=SetDlisParaDlg.m_DefaultVal;
		sp_bAllIgnore=SetDlisParaDlg.m_bAllIgnore;
	}*/
}

void CBitToDLis::BitDataToDlis()
{
	CString s;
	int NumLog=-1; //已输出的曲线数
	for(int nItem=0;nItem<NumItem;nItem++)
	{
		if(sp_Break_Status) break;
		int NumCurve=DlisWrite->Frame[nItem].NumCurve;
		float Start=DlisWrite->Frame[nItem].Index_Start;
		float Stop=DlisWrite->Frame[nItem].Index_Stop;
		float Step=DlisWrite->Frame[nItem].Index_Step;
		int NumPoint=int((Stop-Start)/Step+0.5)+1;
		DlisWrite->StartWriteData(nItem);
		pGuage->SetRange(0,NumCurve);
		for(int i=0;i<NumCurve;i++)
		{
			if(sp_Break_Status) break;
			pGuage->SetPos(i+1);
			if (pGuage->CheckCancelButton())
			{
				sp_Break_Status=true;
				break;
			}
			NumLog++; //已输出曲线数
			//index曲线在DLIS通道中索引
			int index=DlisWrite->Frame[nItem].ChannelID[i]; 
			int IndexBit=CurveIndex.GetAt(index); //曲线在BIT中索引
			s=SelCurveName.GetAt(index)+"("+NewCurveName.GetAt(index)+")";
			s.Remove(' ');
			/////////////////////////////////////////////////////////////////
			if(IndexBit<BitR->NumConvLog)
			{
				fprintf(fp,"====Transform Generic Curve: %-8s %5d\n",s,DlisWrite->Channel[index].Sample);
				float *buf=new float[NumPoint];
				BitR->ReadChannel(IndexBit,buf);
				DlisWrite->WriteCurveData(nItem,i,NumPoint,buf);
				delete []buf; buf=NULL;
			}
			else
			{
				fprintf(fp,"====Transform Waveform Curve: %-8s %5d\n",s,DlisWrite->Channel[index].Sample);
				int Count=DlisWrite->Channel[index].Sample;
				char *buf=new char[Count];
				for(int j=0;j<Count;j++)
				{
					buf[j]=0;
				}
				int nWave=IndexBit-BitR->NumConvLog;
				pGuage->SetRange(0,NumPoint);
				for(j=0;j<NumPoint;j++)
				{
					pGuage->SetPos(j+1);
					if (pGuage->CheckCancelButton())
					{
						sp_Break_Status=true;
						break;
					}
					float depth=Start+j*Step;
					BitR->ReadWaveform(nWave,depth,buf);
					DlisWrite->WriteArrayData(nItem,i,j,Count,buf);
				}
				delete []buf ; buf=NULL;
			}
		}
		DlisWrite->StopWriteData(nItem);
	}
}
