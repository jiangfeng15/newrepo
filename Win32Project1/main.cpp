#pragma once
#include <UIlib.h>
#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <atlconv.h>
#include <string.h>
using namespace DuiLib;

#ifdef _DEBUG
# ifdef _UNICODE
# pragma comment(lib, "DuiLib_ud.lib")
# else
# pragma comment(lib, "DuiLib_d.lib")
# endif
#else
# ifdef _UNICODE
# pragma comment(lib, "DuiLib_u.lib")
# else
# pragma comment(lib, "DuiLib.lib")
# endif
#endif

#define WM_UPDATERELEASEINFO WM_USER+10
#define WM_UPDATESTATECOLOR WM_USER+11
#define MaxNum 120

#define m_hBrhRed		0xFFFF0000
#define m_hBrhGray		0xFFB4B4B4 
#define m_hBrhGreen		0xFF00E600 
#define m_hBrhWhite		0xFFFFFFFF 
#define m_hBrhDeepBlue	0xFF458B73 
#define m_hBrhLightBlue	0xFFB4B4FF 
#define m_hBrhPinkRed	0xFFFFC8C8 
#define m_hBrhBlack		0xFFE2E2E2 


class CDuiFrameWnd : public WindowImplBase
{
public:
	virtual LPCTSTR GetWindowClassName() const { return _T("DUIMainFrame"); }
	virtual CDuiString GetSkinFile() { return _T("UiConfig.xml"); }
	virtual CDuiString GetSkinFolder() { return _T("SysBtn\\"); }
	CDuiFrameWnd();
	~CDuiFrameWnd();
	virtual void InitWindow();

	virtual void Notify(TNotifyUI& msg);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//多字节转宽字符
	wchar_t * CharToWchar(char *c);
	//宽字符转多字节
	std::string WcharToChar(LPCTSTR str);
	//释放指针资源
	bool ReleasePointer();

	void ShowFullWindow();
	//板卡复位
	void btnResetBoardFunc();
	//清除勾选
	void btnClearSelectFunc();
	//连接板卡
	void btnConnectBoardFunc();
	//启动服务
	void btnStartIssueFunc(TNotifyUI& msg);
	//停止服务
	void btnStopIssueFunc();
	//统计数量
	void btnCalCountFunc();
	//退出系统
	void btnExitSysFunc();
	//通过索引和bFlag设置复选框的选中状态
	void SetCheckByIndex(int index, bool bflag);
	//取消所有复选框的选中状态
	void SetAllCheckFalse();
	//获取每个板卡的选中状态
	bool GetCheckByIndex(int index);
	//设置卡板对应的状态颜色
	bool SetBoardColorByIndex(int index, DWORD dwColor);
	//获取批次编号信息
	bool GetBatchNum(char * cBatchNum);
	//获取物料代码
	bool GetMaterialCode(char * cMaterialCode);
	//获取机台编号
	bool GetMachineName(char * cMachineName);
	//获取选中的芯片类型
	bool GetSelChipType(char * cChipType);
	//插入芯片类型
	bool InsertChipType(char * cChipType);
	//插入应用类型代码和应用类型名称
	bool InsertAppType(char * cAppTypeCode, char * cAppTypeName);
	//获取列表控件中选中的应用类型代码和应用类型名称
	bool GetCheckedAppType(char * cAppTypeCode, char * cAppTypeName);
	//清空发行状态信息
	bool ClearPrintInfo();
	//打印发行状态信息
	bool PrintStateInfo(char * cReleaseInfo);
	//在状态栏打印输出信息
	bool PrintStatusBarInfo(char *cStatusBarInfo);
	//设置Button控件禁用状态
	bool SetEnableButton(char * cButtonName, bool bFlag);

	bool GetSelTaskName(char * cTaskName);
	//接口测试函数
	void test();

	void OnClick(TNotifyUI& msg);

	// 测试线程
	static DWORD WINAPI Threadproc(LPVOID lparam);

	//DUI_DECLARE_MESSAGE_MAP()
public:
	CDuiString m_szMsg;
	CRichEditUI * m_pEditBatchNum;
	CRichEditUI * m_pEditMaterialCode;
	CRichEditUI * m_pEditMachineName;
	CComboUI * m_pComboChipType;
	CRichEditUI *m_pRichEditMsg;
	COptionUI * m_pOption[MaxNum];
	CLabelUI * m_pBoardState[MaxNum];
	CLabelUI * m_pStatusBarLabel;

	CEditUI * m_pEditMsg;

	wchar_t * m_chart;
	int testn;
};


//DUI_BEGIN_MESSAGE_MAP(CDuiFrameWnd, WindowImplBase)
//	DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
//	DUI_ON_CLICK_CTRNAME(_T("btnStartIssue"), btnStartIssueFunc)
//DUI_END_MESSAGE_MAP()

void CDuiFrameWnd::ShowFullWindow()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	return ;
}

void CDuiFrameWnd::OnClick(TNotifyUI& msg)
{
	MessageBox(NULL, _T("click action"), NULL, NULL);
}

CDuiFrameWnd::CDuiFrameWnd()
{
	m_szMsg = _T("");
	m_pRichEditMsg = NULL;
	m_pEditBatchNum = NULL;
	m_pEditMaterialCode = NULL;
	m_pEditMachineName = NULL;
	m_pStatusBarLabel = NULL;
	memset(m_pOption, NULL, sizeof(COptionUI *)* 120);
	memset(m_pBoardState, NULL, sizeof(CLabelUI *)* 120);

	m_chart = NULL;
	testn = 0;

}

CDuiFrameWnd::~CDuiFrameWnd()
{

}

void CDuiFrameWnd::InitWindow()
{
	//m_pRichEditMsg = static_cast<CRichEditUI *>(m_PaintManager.FindControl(_T("editmsg")));

	m_pEditMsg = static_cast<CEditUI *>(m_PaintManager.FindControl(_T("editmsg1")));

	ASSERT(m_pEditMsg);

	m_pStatusBarLabel = static_cast<CLabelUI *>(m_PaintManager.FindControl(_T("statusBarInfo")));

	m_pEditBatchNum = static_cast<CRichEditUI *>(m_PaintManager.FindControl(_T("BatchNum")));
}

void CDuiFrameWnd::Notify(TNotifyUI& msg)
{

	if (msg.sType == _T("click"))
	{

		if (msg.pSender->GetName() == _T("btnResetBoard"))
		{
			btnResetBoardFunc();
		}
		else if (msg.pSender->GetName() == _T("btnClearSelect"))
		{
			btnClearSelectFunc();
		}
		else if (msg.pSender->GetName() == _T("btnConnectBoard"))
		{
			btnConnectBoardFunc();
		}
		else if (msg.pSender->GetName() == _T("btnStartIssue"))
		{
			btnStartIssueFunc(msg);
		}
		else if (msg.pSender->GetName() == _T("btnStopIssue"))
		{
			btnStopIssueFunc();
		}
		else if (msg.pSender->GetName() == _T("btnCalCount"))
		{
			btnCalCountFunc();
		}
		else if (msg.pSender->GetName() == _T("btnExitSys"))
		{
			btnExitSysFunc();
		}
		else if (msg.pSender->GetName() == _T("minbtn"))
		{
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
			return;
		}
		else if (msg.pSender->GetName() == _T("maxbtn"))
		{
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
			return;
		}
		else if (msg.pSender->GetName() == _T("closebtn"))
		{
			PostQuitMessage(0);
			return;
		}
		else if (msg.pSender->GetName() == _T("restorebtn"))
		{
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			return;
		}

	}
}

LRESULT CDuiFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	if (uMsg == WM_NCACTIVATE)
	{
		if (!::IsIconic(m_hWnd))
		{
			return (wParam == 0) ? TRUE : FALSE;
		}
	}
	else if (uMsg == WM_NCCALCSIZE)
	{
		return 0;
	}
	else if (uMsg == WM_NCPAINT)
	{
		return 0;
	}

	if (uMsg == WM_SIZE)
	{
/*		if (wParam == SIZE_MAXIMIZED)
		{
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		}	*/	
	}
	if (uMsg == WM_UPDATERELEASEINFO)
	{
		char * cPrintInfo = (char *)wParam;
		PrintStateInfo(cPrintInfo);
	}
	if (uMsg == WM_UPDATESTATECOLOR)
	{
		int index = (int)wParam;
		DWORD dColor = (DWORD)lParam;
		SetBoardColorByIndex(index, dColor);
	}
	//if (uMsg == WM_KEYDOWN)
	//{
	//	switch (wParam)
	//	{
	//	case VK_ESCAPE:
	//	{
	//		MessageBox(NULL, _T("esc down"), NULL, NULL);
	//		return false;
	//	}
	//	default:
	//		break;
	//	}
	//}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

std::string CDuiFrameWnd::WcharToChar(LPCTSTR str)
{
#ifdef _UNICODE
	int size_str = WideCharToMultiByte(CP_ACP, 0, str, -1, 0, 0, NULL, NULL);
	char * point_new_array = new char[size_str];
	WideCharToMultiByte(CP_ACP, 0, str, -1, point_new_array, size_str, NULL, NULL);
	std::string return_string(point_new_array);
	delete[] point_new_array;
	point_new_array = NULL;
	return return_string;
#else
	return std::string(str);
#endif
}

wchar_t * CDuiFrameWnd::CharToWchar(char *c)
{

	int len = MultiByteToWideChar(CP_ACP, 0, c, strlen(c), NULL, 0);
	m_chart = new wchar_t[len + 1];
	MultiByteToWideChar(CP_ACP, 0, c, strlen(c), m_chart, len);
	
	m_chart[len] = '\0';
	
	return m_chart;
}

bool CDuiFrameWnd::GetSelTaskName(char * cTaskName)
{
	COptionUI *pOption1, *pOption2, *pOption3;
#ifdef _UNICODE
	CDuiString szTemp = CharToWchar(cTaskName);
	ReleasePointer();
#else
	CDuiString szTemp = cTaskName;
#endif
	pOption1 = static_cast<COptionUI *>(m_PaintManager.FindControl("optiontask1"));
	pOption2 = static_cast<COptionUI *>(m_PaintManager.FindControl("optiontask2"));
	pOption3 = static_cast<COptionUI *>(m_PaintManager.FindControl("optiontask3"));
	if (pOption1->IsSelected())
	{
		//cTaskName = pOption1->GetText();
		MessageBox(NULL, _T("选择了第一个！"), _T("信息提示"), MB_OKCANCEL);
	}
	if (pOption2->IsSelected())
	{
		MessageBox(NULL, _T("选择了第二个！"), _T("信息提示"), MB_OKCANCEL);
		m_pEditBatchNum->SetEnabled(FALSE);
		m_pEditBatchNum->SetAttribute("bkimage", "editdisabled.png");
	}
	if (pOption3->IsSelected())
	{
		MessageBox(NULL, _T("选择了第三个！"), _T("信息提示"), MB_OKCANCEL);
	}
	return true;
}

bool CDuiFrameWnd::SetEnableButton(char * cButtonName, bool bFlag)
{
	try
	{
#ifdef _UNICODE
		CDuiString szTemp = CharToWchar(cButtonName);
		ReleasePointer();
#else  
		CDuiString szTemp = cButtonName;
#endif
		CButtonUI * pButton = static_cast<CButtonUI *>(m_PaintManager.FindControl(szTemp));
		pButton->SetEnabled(bFlag);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool CDuiFrameWnd::PrintStatusBarInfo(char *cStatusBarInfo)
{
	try
	{
#ifdef _UNICODE
		CDuiString szTemp = CharToWchar(cStatusBarInfo);
		ReleasePointer();
#else
		CDuiString szTemp = cStatusBarInfo;
#endif
		m_pStatusBarLabel->SetText(szTemp);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool CDuiFrameWnd::ReleasePointer()
{
	try
	{
		delete[] m_chart;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

void CDuiFrameWnd::test()
{
	//测试接口函数调用
	for (int j = 0; j < 2000000; j++)
	{
		//PrintStateInfo("开始清空数据");
		//SetAllCheckFalse();
		//PrintStateInfo("清空数据完成");
		int i;
		for (i = 0; i < 120; i++)
		{
			//SetBoardColorByIndex(i, m_hBrhRed);
			////Sleep(10);
			//SetBoardColorByIndex(i, m_hBrhGray);
			////Sleep(10);
			//SetBoardColorByIndex(i, m_hBrhGreen);
			////Sleep(10);
			//SetBoardColorByIndex(i, m_hBrhWhite);
			////Sleep(10);
			//SetBoardColorByIndex(i, m_hBrhDeepBlue);
			////Sleep(10);
			//SetBoardColorByIndex(i, m_hBrhPinkRed);
			////Sleep(10);
			//SetBoardColorByIndex(i, m_hBrhBlack);

			//SetCheckByIndex(i, true);

			SendMessage(WM_UPDATESTATECOLOR, i, m_hBrhRed);
			//Sleep(10);
			SendMessage(WM_UPDATESTATECOLOR, i, m_hBrhGray);
			//Sleep(10);
			SendMessage(WM_UPDATESTATECOLOR, i, m_hBrhGreen);
			//Sleep(10);
			SendMessage(WM_UPDATESTATECOLOR, i, m_hBrhWhite);
			//Sleep(10);
			SendMessage(WM_UPDATESTATECOLOR, i, m_hBrhDeepBlue);
			//Sleep(10);
			SendMessage(WM_UPDATESTATECOLOR, i, m_hBrhPinkRed);
			//Sleep(10);
			SendMessage(WM_UPDATESTATECOLOR, i, m_hBrhBlack);
		}
		//PrintStateInfo("颜色改变完成");
		if (i >= 120)
		{
			char temp[100] = { 0x00 };
			sprintf_s(temp, "测试完成%d", j);
			//PrintStateInfo(temp);
			SendMessage(WM_UPDATERELEASEINFO, (WPARAM)temp, 0);
			//InsertAppType("CE3D3", "教育部");
		}


		//获取编辑框内容测试
		char batch[100] = { 0x00 };
		char material[100] = { 0x00 };
		char machine[100] = { 0x00 };
		char chiptype[100] = { 0x00 };

		char apptypecode[100] = { 0x00 };
		char apptypename[100] = { 0x00 };
		bool bRet = GetBatchNum(batch);
		if (bRet)
		{
			SendMessage(WM_UPDATERELEASEINFO, (WPARAM)batch, 0);
		}
		else
		{
			SendMessage(WM_UPDATERELEASEINFO, (WPARAM)("获取批次编号失败！"), 0);
			break;
		}

		bRet = GetMaterialCode(material);
		if (bRet)
		{
			SendMessage(WM_UPDATERELEASEINFO, (WPARAM)material, 0);
		}
		else
		{
			SendMessage(WM_UPDATERELEASEINFO, (WPARAM)("获取物料代码失败！"), 0);
			break;
		}

		bRet = GetMachineName(machine);
		if (bRet)
		{
			SendMessage(WM_UPDATERELEASEINFO, (WPARAM)machine, 0);
		}
		else
		{
			SendMessage(WM_UPDATERELEASEINFO, (WPARAM)("获取机器名称失败！"), 0);
			break;
		}

		bRet = GetSelChipType(chiptype);
		if (bRet)
		{
			SendMessage(WM_UPDATERELEASEINFO, (WPARAM)chiptype, 0);
		}
		else
		{
			SendMessage(WM_UPDATERELEASEINFO, (WPARAM)("获取芯片类型失败！"), 0);
			break;
		}
		
		bRet = GetCheckedAppType(apptypecode, apptypename);
		string stemp("选择的芯片应用类型是：");
		stemp = stemp + apptypecode + "  " + apptypename;
		if (bRet)
		{
			SendMessage(WM_UPDATERELEASEINFO, (WPARAM)stemp.c_str(), 0);
		}
	}
}

DWORD CDuiFrameWnd::Threadproc(LPVOID lparam)
{
	CDuiFrameWnd *pdlg = (CDuiFrameWnd *)lparam;
	pdlg->test();
	return true;
}
bool CDuiFrameWnd::GetCheckByIndex(int index)
{
	bool bRet = false;
	try
	{
		CDuiString szCheckName(_T(""));
		szCheckName.Format(_T("check%d"), index + 1);
		m_pOption[index] = static_cast<COptionUI *>(m_PaintManager.FindControl(szCheckName));
		bRet = m_pOption[index]->IsSelected();
		return bRet;
	}
	catch (...)
	{
		return false;
	}
}

bool CDuiFrameWnd::PrintStateInfo(char * cReleaseInfo)
{
	try
	{
		if (m_pRichEditMsg->GetLineCount() > 400)
		{
			ClearPrintInfo();
		}
#ifdef _UNICODE
		CDuiString szTemp = CharToWchar(cReleaseInfo);
		ReleasePointer();
#else
		CDuiString szTemp = cReleaseInfo;
#endif
		m_szMsg = m_szMsg + szTemp + _T("\r\n");
		//m_pRichEditMsg = static_cast<CRichEditUI *>(m_PaintManager.FindControl(_T("editmsg")));
		m_pRichEditMsg->SetText(m_szMsg);
		int len = m_pRichEditMsg->GetLineCount();
		m_pRichEditMsg->LineScroll(len);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool CDuiFrameWnd::ClearPrintInfo()
{
	try
	{
		m_szMsg = _T("");
		m_pRichEditMsg->SetText(m_szMsg);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool CDuiFrameWnd::GetCheckedAppType(char * cAppTypeCode, char * cAppTypeName)
{
	try
	{
		int index, nCheck=0, nElementCount=0;
		CListUI * pList = static_cast<CListUI *>(m_PaintManager.FindControl(_T("listex")));
		CListContainerElementUI *pElementUI = NULL;
		CHorizontalLayoutUI *pHLUI = NULL;
		CCheckBoxUI * pCheckBoxTemp = NULL;
		CLabelUI * pLabelTemp = NULL;
		string sAppTypeCode(""), sAppTypeName("");
		CDuiString szDuiAppTypeCode(_T("")), szDuiAppTypeName(_T(""));

		for (index = 0; index < pList->GetCount(); index++)
		{
			pElementUI = static_cast<CListContainerElementUI *>(pList->GetItemAt(index));
			pHLUI = static_cast<CHorizontalLayoutUI *>(pElementUI->GetItemAt(0));
			pCheckBoxTemp = static_cast<CCheckBoxUI *>(pHLUI->GetItemAt(0));
			if (pCheckBoxTemp->GetCheck())
			{
				//获取第1列的值
				pLabelTemp = static_cast<CLabelUI *>(pHLUI->GetItemAt(1));
				szDuiAppTypeCode = pLabelTemp->GetText();
				sAppTypeCode = WcharToChar(szDuiAppTypeCode);
				//获取第2列的值
				pLabelTemp = static_cast<CLabelUI *>(pHLUI->GetItemAt(2));
				szDuiAppTypeName = pLabelTemp->GetText();
				sAppTypeName = WcharToChar(szDuiAppTypeName);

				memcpy(cAppTypeCode, sAppTypeCode.c_str(), sAppTypeCode.length());
				memcpy(cAppTypeName, sAppTypeName.c_str(), sAppTypeName.length());
				nCheck++;
			}

		}

		if (nCheck == 0)
		{
			MessageBox(NULL, _T("请选择芯片应用类型！"), _T("信息提示"), MB_OKCANCEL);
			return false;
		}
		
		if (nCheck > 1)
		{
			cAppTypeCode = "";
			cAppTypeName = "";
			MessageBox(NULL, _T("此版本暂不支持多应用类型发行！"), _T("信息提示"), MB_OKCANCEL);
			return false;
		}
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool CDuiFrameWnd::InsertAppType(char * cAppTypeCode, char * cAppTypeName)
{
	try
	{
		CDuiString szAppTypeCode(_T("")), szAppTypeName(_T(""));
		szAppTypeCode = CharToWchar(cAppTypeCode);
		ReleasePointer();
		szAppTypeName = CharToWchar(cAppTypeName);
		ReleasePointer();

		CListUI * pList = static_cast<CListUI *>(m_PaintManager.FindControl(_T("listex")));
		CListContainerElementUI *pElementUI = new CListContainerElementUI;
		pElementUI->SetAttribute(_T("height"), _T("30"));
		
		pElementUI->NeedUpdate();

		CHorizontalLayoutUI *pHLUI = new CHorizontalLayoutUI;
		pHLUI->SetAttribute(_T("bkcolor"), _T("FFA4D1FF"));
		pHLUI->SetAttribute(_T("width"), _T("320"));


		CCheckBoxUI * pCheckBoxUI = new CCheckBoxUI;
		pCheckBoxUI->SetAttribute(_T("width"), _T("20"));
		pCheckBoxUI->SetAttribute(_T("height"), _T("20"));

		pCheckBoxUI->SetAttribute(_T("flag"), _T("true"));
		pCheckBoxUI->SetAttribute(_T("pos"), _T("15,0,0,0"));

		pCheckBoxUI->SetAttribute(_T("name"), _T("SelectAll"));
		pCheckBoxUI->SetAttribute(_T("selectedimage"), _T("file=\'checkbox_p.png\' dest=\'0,2,15,17\'"));
		pCheckBoxUI->SetAttribute(_T("normalimage"), _T("file=\'checkbox_h.png\' dest=\'0,2,15,17\'"));


		pCheckBoxUI->NeedUpdate();
		pHLUI->Add(pCheckBoxUI);

		CLabelUI *pLabelCol1 = new CLabelUI;
		pLabelCol1->SetAttribute(_T("width"), _T("145"));
		pLabelCol1->SetAttribute(_T("height"), _T("20"));
		pLabelCol1->SetAttribute(_T("align"), _T("center"));
		pLabelCol1->SetAttribute(_T("textcolor"), _T("#FF000000"));
		pLabelCol1->SetAttribute(_T("text"), szAppTypeCode);

		pLabelCol1->NeedUpdate();
		pHLUI->Add(pLabelCol1);

		CLabelUI *pLabelCol2 = new CLabelUI;
		pLabelCol2->SetAttribute(_T("width"), _T("145"));
		pLabelCol2->SetAttribute(_T("height"), _T("20"));
		pLabelCol2->SetAttribute(_T("align"), _T("center"));
		pLabelCol2->SetAttribute(_T("textcolor"), _T("#FF000000"));
		pLabelCol2->SetAttribute(_T("text"), szAppTypeName);

		pLabelCol2->NeedUpdate();
		pHLUI->Add(pLabelCol2);

		pElementUI->Add(pHLUI);

		pList->AddAt(pElementUI, pList->GetCount());
		pList->NeedUpdate();
	}
	catch (...)
	{
		return false;
	}
	return true;
}
bool CDuiFrameWnd::InsertChipType(char * cChipType)
{
	try
	{
#ifdef _UNICODE
		CDuiString szTemp = CharToWchar(cChipType);
		ReleasePointer();
#else
		CDuiString szTemp = cChipType;
#endif
		CListLabelElementUI *plistLabelElement = new CListLabelElementUI;
		plistLabelElement->SetText(szTemp);
		plistLabelElement->SetFixedHeight(23);
		m_pComboChipType = static_cast<CComboUI *>(m_PaintManager.FindControl(_T("ChipType")));
		m_pComboChipType->Add(plistLabelElement);

	}
	catch (...)
	{
		return false;
	}
	
	return true;
}

bool CDuiFrameWnd::GetSelChipType(char * cChipType)
{
	CDuiString szChipType(_T(""));
	string sTemp("");
	try
	{
		m_pComboChipType = static_cast<CComboUI *>(m_PaintManager.FindControl(_T("ChipType")));
		int nSel = m_pComboChipType->GetCurSel();
		if (nSel < 0)
		{
			return false;
		}
		szChipType = m_pComboChipType->GetText();
		int nLen = szChipType.GetLength();
		
		sTemp = WcharToChar(szChipType.GetData()); 
		memcpy(cChipType, sTemp.c_str(), sTemp.length());
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool CDuiFrameWnd::GetMachineName(char * cMachineName)
{
	CDuiString szMachineName(_T(""));
	string sTemp("");
	try
	{
		m_pEditMachineName = static_cast<CRichEditUI *>(m_PaintManager.FindControl(_T("MachineName")));
		szMachineName = m_pEditMachineName->GetText();

		if (szMachineName == _T(""))
		{
			MessageBox(NULL, _T("请输入机台名称！"), _T("信息提示"), MB_OKCANCEL);
			return false;
		}
		if (szMachineName.GetLength() > 30)
		{
			MessageBox(NULL, _T("机台名称不能超过30个字符！"), _T("信息提示"), MB_OKCANCEL);
			return false;
		}

		sTemp = WcharToChar(szMachineName);
		memcpy(cMachineName, sTemp.c_str(), sTemp.length());
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool CDuiFrameWnd::GetMaterialCode(char *cMaterialCode)
{
	CDuiString szMaterialCode(_T(""));
	string sTemp("");
	try
	{
		m_pEditMaterialCode = static_cast<CRichEditUI *>(m_PaintManager.FindControl(_T("MaterialCode")));
		szMaterialCode = m_pEditMaterialCode->GetText();

		if (szMaterialCode == _T(""))
		{
			MessageBox(NULL, _T("请输入物料代码！"), _T("信息提示"), MB_OKCANCEL);
			return false;
		}

		if (szMaterialCode.GetLength() > 20)
		{
			MessageBox(NULL, _T("物料代码不能超过20个字符！"), _T("信息提示"), MB_OKCANCEL);
			return false;
		}

		sTemp = WcharToChar(szMaterialCode);
		memcpy(cMaterialCode, sTemp.c_str(), sTemp.length());
	}
	catch (...)
	{
		return false;
	}

	return true;
	
}

bool CDuiFrameWnd::GetBatchNum(char * cBatchNum)
{

	CDuiString szBatch(_T(""));
	string sTemp("");
	try
	{
		m_pEditBatchNum = static_cast<CRichEditUI *>(m_PaintManager.FindControl(_T("BatchNum")));

		szBatch = m_pEditBatchNum->GetText();

		if (szBatch == _T(""))
		{
			MessageBox(NULL, _T("请输入批次编号！"), _T("信息提示"), MB_OKCANCEL);
			return false;
		}
		if (szBatch.GetLength() > 20)
		{
			MessageBox(NULL, _T("批次编号不能超过20个字符！"), _T("信息提示"), MB_OKCANCEL);
			return false;
		}

		sTemp = WcharToChar(szBatch);
		memcpy(cBatchNum, sTemp.c_str(), sTemp.length());
	}
	catch (...)
	{
		return false;
	}	
	return true;
}

LRESULT CDuiFrameWnd::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	SetAllCheckFalse();

	int i;
	for (i = 0; i < 120; i++)
	{
		SetBoardColorByIndex(i, m_hBrhRed);
		//Sleep(10);
		SetBoardColorByIndex(i, m_hBrhGray);
		//Sleep(10);
		SetBoardColorByIndex(i, m_hBrhGreen);
		//Sleep(10);
		SetBoardColorByIndex(i, m_hBrhWhite);
		//Sleep(10);
		SetBoardColorByIndex(i, m_hBrhDeepBlue);
		//Sleep(10);
		SetBoardColorByIndex(i, m_hBrhPinkRed);
		//Sleep(10);
		SetBoardColorByIndex(i, m_hBrhBlack);

		SetCheckByIndex(i, true);
	}

	testn++;
	SendMessage(WM_PAINT, 0, 0);
	char temp[100] = { 0x00 };
	sprintf_s(temp, "测试完成%d", testn);
	PrintStateInfo(temp);
	//PrintStateInfo("打印调试信息：");
	return 0;
}

bool CDuiFrameWnd::SetBoardColorByIndex(int index, DWORD dwColor)
{
	try
	{
		CDuiString szBoardStateName(_T(""));
		szBoardStateName.Format(_T("boardstate%d"), index + 1);
		m_pBoardState[index] = static_cast<CLabelUI *>(m_PaintManager.FindControl(szBoardStateName));
		m_pBoardState[index]->SetBkColor(dwColor);
		m_pBoardState[index]->NeedUpdate();
	}
	catch (...)
	{
		return false;
	}
	return true;
}

void CDuiFrameWnd::SetAllCheckFalse()
{
	CDuiString szCheckName(_T(""));
	for (int index = 0; index < MaxNum; index++)
	{
		szCheckName.Format(_T("check%d"), index+1);
		m_pOption[index] = static_cast<COptionUI *>(m_PaintManager.FindControl(szCheckName));
		m_pOption[index]->Selected(false);
	}
}

void CDuiFrameWnd::SetCheckByIndex(int index, bool bflag)
{
	CDuiString szCheckName(_T(""));
	szCheckName.Format(_T("check%d"), index+1);
	m_pOption[index] = static_cast<COptionUI *>(m_PaintManager.FindControl(szCheckName));
	m_pOption[index]->Selected(bflag);
}

void CDuiFrameWnd::btnResetBoardFunc()
{
	MessageBox(NULL, _T("点击了复位按钮控件！"), _T("事件提示"), MB_OKCANCEL);
}
void CDuiFrameWnd::btnClearSelectFunc()
{
	//MessageBox(NULL, _T("点击了清除选择按钮控件！"), _T("事件提示"), MB_OKCANCEL);
	HANDLE hThread = CreateThread(NULL, 0, Threadproc, this, NULL, NULL);
	if (hThread != 0)
	{
		CloseHandle(hThread);
	}
}
void CDuiFrameWnd::btnConnectBoardFunc()
{
	//MessageBox(NULL, _T("点击了板卡连接按钮控件！"), _T("事件提示"), MB_OKCANCEL);
	PrintStateInfo("测试打印状态信息！");
}
void CDuiFrameWnd::btnStartIssueFunc(TNotifyUI& msg)
{
	//MessageBox(NULL, _T("点击了启动服务按钮控件！"), _T("事件提示"), MB_OKCANCEL);
	ClearPrintInfo();
	//测试禁用button按钮
	//CButtonUI * pButton = static_cast<CButtonUI *>(m_PaintManager.FindControl(_T("btnConnectBoard")));
	//pButton->SetEnabled(false);
	SetEnableButton("btnConnectBoard",false);
}
void CDuiFrameWnd::btnStopIssueFunc()
{
	//MessageBox(NULL, _T("点击了停止服务按钮控件！"), _T("事件提示"), MB_OKCANCEL);

	InsertAppType("CE3D3","教育部");

	//CButtonUI * pButton = static_cast<CButtonUI *>(m_PaintManager.FindControl(_T("btnConnectBoard")));
	//pButton->SetEnabled(true);
	SetEnableButton("btnConnectBoard", true);
}

void CDuiFrameWnd::btnCalCountFunc()
{
	//MessageBox(NULL, _T("点击了统计数量按钮控件！"), _T("事件提示"), MB_OKCANCEL);
	InsertChipType("chiptype1231");
	PrintStatusBarInfo("就绪状态：");
	GetSelTaskName("");
}
void CDuiFrameWnd::btnExitSysFunc()
{
	//MessageBox(NULL, _T("点击了退出系统按钮控件！"), _T("事件提示"), MB_OKCANCEL);
	m_pRichEditMsg = static_cast<CRichEditUI *>(m_PaintManager.FindControl(_T("editmsg")));

	//for (int i = 0; i < 10; i++)
	//{
	//	CDuiString szno(_T(""));
	//	szno.Format(_T("输出调试信息%d"),testn);
	//	m_szMsg = m_pRichEditMsg->GetText();
	//	m_szMsg = m_szMsg + szno+ _T("\r\n");
	//	m_pRichEditMsg->SetText(m_szMsg);
	//	int len = m_pRichEditMsg->GetLineCount();
	//	m_pRichEditMsg->LineScroll(len);
	//	SendMessage(WM_PAINT, 0, 0);
	//	testn++;
	//}

	//HWND hwnd = m_PaintManager.GetPaintWindow();
	//SetTimer(hwnd, 1, 2000, NULL);

	char batch[100] = { 0x00 };
	char material[100] = { 0x00 };
	char machine[100] = { 0x00 };
	char chiptype[100] = { 0x00 };

	char apptypecode[100] = { 0x00 };
	char apptypename[100] = { 0x00 };
	bool bRet = GetBatchNum(batch);

	
	if (bRet)
	{
		::MessageBoxA(NULL, batch, "信息提示", MB_OKCANCEL);
	}
	bRet = GetMaterialCode(material);
	if (bRet)
	{
		::MessageBoxA(NULL, material, "信息提示", MB_OKCANCEL);
	}
	bRet = GetMachineName(machine);
	if (bRet)
	{
		::MessageBoxA(NULL, machine, "信息提示", MB_OKCANCEL);
	}
	bRet = GetSelChipType(chiptype);
	if (bRet)
	{
		::MessageBoxA(NULL, chiptype, "信息提示", MB_OKCANCEL);
	}
	else
	{
		::MessageBoxA(NULL, "请选择芯片类型", "信息提示", MB_OKCANCEL);
	}
	
	bRet = GetCheckedAppType(apptypecode, apptypename);
	string stemp("");
	stemp = stemp + apptypecode + "  " + apptypename;
	if (bRet)
	{
		::MessageBoxA(NULL, stemp.c_str(), "信息提示", MB_OKCANCEL);
	}

	

}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CDuiFrameWnd duiFrame;
	duiFrame.Create(NULL, _T("双界面模块UID发行系统"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	HICON hIcon = ::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	::SendMessage(duiFrame.GetHWND(), STM_SETICON, IMAGE_ICON, (LPARAM)(UINT)hIcon);

	duiFrame.CenterWindow();
	//::SendMessage(duiFrame.GetHWND(), WM_SIZE, SIZE_MAXIMIZED, 0);
	SendMessage(duiFrame.GetHWND(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	duiFrame.ShowModal();
	
	//::SendMessage(duiFrame.GetHWND(), WM_SIZE, SIZE_MAXIMIZED, 0);
	CPaintManagerUI::MessageLoop();

	::CoUninitialize();
	 
	return 0;
}