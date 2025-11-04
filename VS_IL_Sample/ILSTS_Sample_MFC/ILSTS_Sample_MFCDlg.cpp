
// ILSTS_Sample_MFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ILSTS_Sample_MFC.h"
#include "ILSTS_Sample_MFCDlg.h"
#include "afxdialogex.h"
#include "afxwin.h"
#include <vector>
#include <string>
#include "Form2.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ILSTS_SAMPLE_MFC_DIALOG)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()



inline vector<string> split(const string& s, const string& seperator)
{
	vector<string> result;
	unsigned int posBegin = 0;
	unsigned int posSeperator = s.find(seperator);

	while (posSeperator != s.npos) {
		result.push_back(s.substr(posBegin, posSeperator - posBegin));// 
		posBegin = posSeperator + seperator.size(); 
		posSeperator = s.find(seperator, posBegin);

	}
	if (posBegin != s.length()) 
		result.push_back(s.substr(posBegin));

	return result;
}

CILSTS_Sample_MFCDlg::CILSTS_Sample_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ILSTS_SAMPLE_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CILSTS_Sample_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, cmbspu_dev, DAQ_LIST);
	DDX_Control(pDX, cmbtsl_usb, USB_LIST);

}

BEGIN_MESSAGE_MAP(CILSTS_Sample_MFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(btnConnect, &CILSTS_Sample_MFCDlg::OnBnClickedbtnconnect)
	ON_BN_CLICKED(rdo570, &CILSTS_Sample_MFCDlg::OnBnClickedrdo570)
	ON_BN_CLICKED(rdotsl_gpib, &CILSTS_Sample_MFCDlg::OnBnClickedgpib)
	ON_BN_CLICKED(rdo_tsltcpip, &CILSTS_Sample_MFCDlg::OnBnClickedtsltcpip)
	ON_BN_CLICKED(rdo_tslusb, &CILSTS_Sample_MFCDlg::OnBnClickedtslusb)
	ON_BN_CLICKED(chkmulti_dev, &CILSTS_Sample_MFCDlg::OnBnClickeddev)
	ON_BN_CLICKED(rdo_mpmgpib, &CILSTS_Sample_MFCDlg::OnBnClickedmpmgpib)
	ON_BN_CLICKED(rdo550, &CILSTS_Sample_MFCDlg::OnBnClickedrdo550)
	ON_BN_CLICKED(rdo_mpmtcpip, &CILSTS_Sample_MFCDlg::OnBnClickedmpmtcpip)
END_MESSAGE_MAP()



BOOL CILSTS_Sample_MFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		
	// ---------------------------------------------------------------
	// Sub Form Load
	// ---------------------------------------------------------------
	int loop1;
	string SPU = SPU_Resource;
	string USB = USB_Resource;
	int cnt = SPU.find(_T(","));
	int cnt1 = USB.find(_T(","));


	// ---Add in SPU resource to comboboxfrom main form
	//for (loop1 = 0; loop1 <= SPU_Resource.GetUpperBound(0); loop1++)
	//	cmbspu_dev.Items.Add(SPU_Resource[loop1]);

	if (cnt >= 0) {
		vector<string> obj = split(SPU_Resource, ",");
		for (int i = 0; i < obj.size(); i++) {
			string str1 = obj.at(i);
			DAQ_LIST.AddString(CString(str1.c_str()));
		}
	}
	else {
		DAQ_LIST.AddString(SPU_Resource);
	}
	DAQ_LIST.SetCurSel(0);

	// ----Add in USB resource to combobox from main form
	//for (loop1 = 0; loop1 <= USB_Resource.GetUpperBound(0); loop1++)
	//	cmbtsl_usb.Items.Add(USB_Resource[loop1]);
	if (cnt1 >= 0) {
		vector<string> obj = split(USB_Resource, ",");
		for (int i = 0; i < obj.size(); i++) {
			string str1 = obj.at(i);
			USB_LIST.AddString(CString(str1.c_str()));
		}
	}
	else {
		USB_LIST.AddString(USB_Resource);
	}
	USB_LIST.SetCurSel(0);
	((CButton *)GetDlgItem(rdo570))->SetCheck(1);
	((CButton *)GetDlgItem(rdotsl_gpib))->SetCheck(1);
	((CButton *)GetDlgItem(rdo_mpmgpib))->SetCheck(1);
	GetDlgItem(txttsl_gpibadd)->SetWindowTextA("1");
	GetDlgItem(txttsl_ipadd)->SetWindowTextA("192.168.1.100");
	GetDlgItem(txttsl_lanport)->SetWindowTextA("5000");
	GetDlgItem(txtmpm_gpibadd1)->SetWindowTextA("16");
	GetDlgItem(txtmpm_gpibadd2)->SetWindowTextA("15");
	GetDlgItem(txtmpm_ipadd1)->SetWindowTextA("192.168.1.161");
	GetDlgItem(txtmpm_ipadd2)->SetWindowTextA("192.168.1.161");
	GetDlgItem(txtmpm_lanport1)->SetWindowTextA("5000");
	GetDlgItem(txtmpm_lanport2)->SetWindowTextA("5000");

	//GetDlgItem(txtmpm_ipadd1)->GetWindowText(Address);
	return TRUE;  
}


void CILSTS_Sample_MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


void CILSTS_Sample_MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CILSTS_Sample_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CILSTS_Sample_MFCDlg::OnBnClickedbtnconnect()
{
	// ----------------------------------------------------------
	// Connect       
	// ----------------------------------------------------------


	// ----TSL Communication diteal
	CString Address;
	CString Port;
	CString spu_dev;

	//set_form.Owner = this;
	//set_form.SPU_Resource = spudev;
	//set_form.USB_Resource = usb_resource;
	//set_form.DoModal();

	// GPIB Communcation?
	if (((CButton *)GetDlgItem(rdotsl_gpib))->GetCheck())
	{
		TSL_Communicater = "GPIB";
		GetDlgItem(txttsl_gpibadd)->GetWindowText(TSL_Address);
		TSL_Portnumber = 0;
	}

	// TCP/IP Communciation?
	if (((CButton *)GetDlgItem(rdo_tsltcpip))->GetCheck())
	{
		TSL_Communicater = "LAN";
		GetDlgItem(txttsl_ipadd)->GetWindowText(TSL_Address);
		GetDlgItem(txttsl_lanport)->GetWindowText(Port);
		TSL_Portnumber = _ttof((LPSTR)(LPCSTR)Port);
	}

	// USB Communcation?
	if (((CButton *)GetDlgItem(rdo_tslusb))->GetCheck())
	{
		TSL_Communicater = "USB";
	    USB_LIST.GetLBText(USB_LIST.GetCurSel(), TSL_Address);
		TSL_Portnumber = 0;
	}

	// -----MPM Communcation diteal

	// Multi Device?
	if (((CButton *)GetDlgItem(chkmulti_dev))->GetCheck())
	{
		MPM_Count = 2;

		// GPIB communcation?
		if (((CButton *)GetDlgItem(rdo_mpmgpib))->GetCheck())
		{
			GetDlgItem(txtmpm_gpibadd1)->GetWindowText(Address);
			MPM_Address[0] = Address;

			GetDlgItem(txtmpm_gpibadd2)->GetWindowText(Address);

			MPM_Address[1] = Address;
			MPM_Portnumber[0] = 0;
			MPM_Portnumber[1] = 0;

			MPM_Communicater = "GPIB";
		}
		else
		{
			// TCL/IP communcation?
			GetDlgItem(txtmpm_ipadd1)->GetWindowText(Address);
			MPM_Address[0] = Address;
			GetDlgItem(txtmpm_ipadd2)->GetWindowText(Address);
			MPM_Address[1] = Address;
			GetDlgItem(txtmpm_lanport1)->GetWindowText(Port);
			MPM_Portnumber[0] = _ttof((LPSTR)(LPCSTR)Port);
			GetDlgItem(txtmpm_lanport2)->GetWindowText(Port);
			MPM_Portnumber[1] = _ttof((LPSTR)(LPCSTR)Port);
			MPM_Communicater = "LAN";
		}
	}
	else
	{
		MPM_Count = 1;

		// GPIB communcation?
		if (((CButton *)GetDlgItem(rdo_mpmgpib))->GetCheck())
		{
			GetDlgItem(txtmpm_gpibadd1)->GetWindowText(Address);
			MPM_Address[0] = Address;
			MPM_Address[1] = "";
			MPM_Portnumber[0] = 0;
			MPM_Portnumber[1] = 0;

			MPM_Communicater = "GPIB";
		}
		else
		{
			// TCL/IP communcation?
			GetDlgItem(txtmpm_ipadd1)->GetWindowText(Address);
			MPM_Address[0] = Address;
			MPM_Address[1] = "";
			GetDlgItem(txtmpm_lanport1)->GetWindowText(Port);
			MPM_Portnumber[0] = _ttof((LPSTR)(LPCSTR)Port);
			MPM_Portnumber[1] = 0;

			MPM_Communicater = "LAN";
		}
	}


	// SPU Resouce

	if (((CButton *)GetDlgItem(cmbspu_dev))->GetCheck())
	{
		::MessageBox(NULL, "Please enter to the SPU device resouce", "", MB_OK);
		return;
	}
	GetDlgItem(cmbspu_dev)->GetWindowText(spu_dev);

	SPU_DeviveID = spu_dev;

	CILSTS_Sample_MFCDlg::EndDialog(0);
}


void CILSTS_Sample_MFCDlg::OnBnClickedrdo570()
{
	// -----------------------------------------------------
	// 570 Checked
	// -----------------------------------------------------

	if (((CButton *)GetDlgItem(rdo570))->GetCheck())
	{
		// TSL-570
		GetDlgItem(rdo_tsltcpip)->EnableWindow(TRUE);
		GetDlgItem(rdo_tslusb)->EnableWindow(TRUE);
	}
	else
	{
		// TSL-550/710
		// There can control only GPIB
		GetDlgItem(rdo_tslusb)->EnableWindow(FALSE);
		GetDlgItem(rdo_tsltcpip)->EnableWindow(FALSE);
		GetDlgItem(rdotsl_gpib)->EnableWindow(TRUE);
	}

}


void CILSTS_Sample_MFCDlg::OnBnClickedgpib()
{
	// ------------------------------------------------------
	// TSL Control GPIB
	// ------------------------------------------------------

	if (((CButton *)GetDlgItem(rdotsl_gpib))->GetCheck())
	{
		GetDlgItem(txttsl_gpibadd)->EnableWindow(TRUE);
		GetDlgItem(txttsl_ipadd)->EnableWindow(FALSE);
		GetDlgItem(txttsl_lanport)->EnableWindow(FALSE);
		GetDlgItem(cmbtsl_usb)->EnableWindow(FALSE);
	}

}


void CILSTS_Sample_MFCDlg::OnBnClickedtsltcpip()
{
	// ------------------------------------------------------
	// TSL Control TCP/IP
	// ------------------------------------------------------

	if (((CButton *)GetDlgItem(rdo_tsltcpip))->GetCheck())
	{
		GetDlgItem(txttsl_gpibadd)->EnableWindow(FALSE);
		GetDlgItem(cmbtsl_usb)->EnableWindow(FALSE);
		GetDlgItem(txttsl_ipadd)->EnableWindow(TRUE);
		GetDlgItem(txttsl_lanport)->EnableWindow(TRUE);
	}

}


void CILSTS_Sample_MFCDlg::OnBnClickedtslusb()
{
	// ------------------------------------------------------
	// TSL Control USB
	// ------------------------------------------------------

	if (((CButton *)GetDlgItem(rdo_tslusb))->GetCheck())
	{
		GetDlgItem(cmbtsl_usb)->EnableWindow(TRUE);
		GetDlgItem(txttsl_gpibadd)->EnableWindow(FALSE);
		GetDlgItem(txttsl_ipadd)->EnableWindow(FALSE);
		GetDlgItem(txttsl_lanport)->EnableWindow(FALSE);
	}

}


void CILSTS_Sample_MFCDlg::OnBnClickeddev()
{
	// ------------------------------------------------------------------
	// Selecet MPM Multi-Device
	// -------------------------------------------------------------------
	if (((CButton *)GetDlgItem(chkmulti_dev))->GetCheck())
	{
		if (((CButton *)GetDlgItem(rdo_mpmgpib))->GetCheck())
		{
			GetDlgItem(txtmpm_gpibadd2)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(txtmpm_ipadd2)->EnableWindow(TRUE);
			GetDlgItem(txtmpm_lanport2)->EnableWindow(TRUE);
		}
	}
	else
	{
		GetDlgItem(txtmpm_gpibadd2)->EnableWindow(FALSE);
		GetDlgItem(txtmpm_ipadd2)->EnableWindow(FALSE);
		GetDlgItem(txtmpm_lanport2)->EnableWindow(FALSE);
	}
}


void CILSTS_Sample_MFCDlg::OnBnClickedmpmgpib()
{
	// --------------------------------------------------------------------
	// MPM Control GPIB
	// --------------------------------------------------------------------

	if (((CButton *)GetDlgItem(rdo_mpmgpib))->GetCheck())
	{
		if (((CButton *)GetDlgItem(chkmulti_dev))->GetCheck())
		{
		GetDlgItem(txtmpm_gpibadd1)->EnableWindow(TRUE);
		GetDlgItem(txtmpm_gpibadd2)->EnableWindow(TRUE);
		GetDlgItem(txtmpm_ipadd1)->EnableWindow(FALSE);
		GetDlgItem(txtmpm_ipadd2)->EnableWindow(FALSE);
		GetDlgItem(txtmpm_lanport1)->EnableWindow(FALSE);
		GetDlgItem(txtmpm_lanport2)->EnableWindow(FALSE);
		}
		else
		{
			GetDlgItem(txtmpm_gpibadd1)->EnableWindow(TRUE);
			GetDlgItem(txtmpm_gpibadd2)->EnableWindow(FALSE);
			GetDlgItem(txtmpm_ipadd1)->EnableWindow(FALSE);
			GetDlgItem(txtmpm_ipadd2)->EnableWindow(FALSE);
			GetDlgItem(txtmpm_lanport1)->EnableWindow(FALSE);
			GetDlgItem(txtmpm_lanport2)->EnableWindow(FALSE);
		}
	}
	else
	{
		if (((CButton *)GetDlgItem(chkmulti_dev))->GetCheck())
		{
			GetDlgItem(txtmpm_gpibadd1)->EnableWindow(FALSE);
			GetDlgItem(txtmpm_gpibadd2)->EnableWindow(FALSE);
			GetDlgItem(txtmpm_ipadd1)->EnableWindow(TRUE);
			GetDlgItem(txtmpm_ipadd2)->EnableWindow(TRUE);
			GetDlgItem(txtmpm_lanport1)->EnableWindow(TRUE);
			GetDlgItem(txtmpm_lanport2)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(txtmpm_gpibadd1)->EnableWindow(FALSE);
			GetDlgItem(txtmpm_gpibadd2)->EnableWindow(FALSE);
			GetDlgItem(txtmpm_ipadd1)->EnableWindow(TRUE);
			GetDlgItem(txtmpm_ipadd2)->EnableWindow(FALSE);
			GetDlgItem(txtmpm_lanport1)->EnableWindow(TRUE);
			GetDlgItem(txtmpm_lanport2)->EnableWindow(FALSE);
		}
	}

}


void CILSTS_Sample_MFCDlg::OnBnClickedrdo550()
{
	// -----------------------------------------------------
	// 570 Checked
	// -----------------------------------------------------

	if (((CButton *)GetDlgItem(rdo570))->GetCheck())
	{
		// TSL-570
		GetDlgItem(rdo_tsltcpip)->EnableWindow(TRUE);
		GetDlgItem(rdo_tslusb)->EnableWindow(TRUE);
	}
	else
	{
		// TSL-550/710
		// There can control only GPIB
		GetDlgItem(rdo_tslusb)->EnableWindow(FALSE);
		GetDlgItem(rdo_tsltcpip)->EnableWindow(FALSE);
		GetDlgItem(rdotsl_gpib)->EnableWindow(TRUE);
	}

}


void CILSTS_Sample_MFCDlg::OnBnClickedmpmtcpip()
{
	// --------------------------------------------------------------------
	// MPM Control GPIB
	// --------------------------------------------------------------------

	if (((CButton *)GetDlgItem(rdo_mpmgpib))->GetCheck())
	{
		if (((CButton *)GetDlgItem(chkmulti_dev))->GetCheck())
		{
			GetDlgItem(txtmpm_gpibadd1)->EnableWindow(TRUE);
			GetDlgItem(txtmpm_gpibadd2)->EnableWindow(TRUE);
			GetDlgItem(txtmpm_ipadd1)->EnableWindow(FALSE);
			GetDlgItem(txtmpm_ipadd2)->EnableWindow(FALSE);
			GetDlgItem(txtmpm_lanport1)->EnableWindow(FALSE);
			GetDlgItem(txtmpm_lanport2)->EnableWindow(FALSE);
		}
		else
		{
			GetDlgItem(txtmpm_gpibadd1)->EnableWindow(TRUE);
			GetDlgItem(txtmpm_gpibadd2)->EnableWindow(FALSE);
			GetDlgItem(txtmpm_ipadd1)->EnableWindow(FALSE);
			GetDlgItem(txtmpm_ipadd2)->EnableWindow(FALSE);
			GetDlgItem(txtmpm_lanport1)->EnableWindow(FALSE);
			GetDlgItem(txtmpm_lanport2)->EnableWindow(FALSE);
		}
	}
	else
	{
		if (((CButton *)GetDlgItem(chkmulti_dev))->GetCheck())
		{
			GetDlgItem(txtmpm_gpibadd1)->EnableWindow(FALSE);
			GetDlgItem(txtmpm_gpibadd2)->EnableWindow(FALSE);
			GetDlgItem(txtmpm_ipadd1)->EnableWindow(TRUE);
			GetDlgItem(txtmpm_ipadd2)->EnableWindow(TRUE);
			GetDlgItem(txtmpm_lanport1)->EnableWindow(TRUE);
			GetDlgItem(txtmpm_lanport2)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(txtmpm_gpibadd1)->EnableWindow(FALSE);
			GetDlgItem(txtmpm_gpibadd2)->EnableWindow(FALSE);
			GetDlgItem(txtmpm_ipadd1)->EnableWindow(TRUE);
			GetDlgItem(txtmpm_ipadd2)->EnableWindow(FALSE);
			GetDlgItem(txtmpm_lanport1)->EnableWindow(TRUE);
			GetDlgItem(txtmpm_lanport2)->EnableWindow(FALSE);
		}
	}

}
