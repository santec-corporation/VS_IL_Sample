// Form2.cpp : 实现文件
//

#include "stdafx.h"
#include "ILSTS_Sample_MFC.h"
#include "Form2.h"
#include "afxdialogex.h"
#include "ILSTS_Sample_MFCDlg.h"
#include <vector>
#include <string>

using namespace std;


IMPLEMENT_DYNAMIC(Form2, CDialogEx)

Form2::Form2(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	q_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

Form2::~Form2()
{
}

void Form2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, chklst_ch, lst_ch);
	DDX_Control(pDX, chklst_range, lst_range);
	DDX_Control(pDX, cmbspeed, SPEED_LIST);

}

char* Form2::getDAQList() {
	char* ret = "";
	int a = 0;
	HINSTANCE hInst = LoadLibrary(_T("librayForMFCIL.dll"));
	if (hInst)
	{
		typedef char*(*pFunc)();
		pFunc doFunc = NULL;
		pFunc Func_GetDAQList = (pFunc)GetProcAddress(hInst, "getDAQList");
		CString text;

		if (Func_GetDAQList)
		{
			char error[100] = { NULL };
			ret = Func_GetDAQList();
		}
		else
		{
			::MessageBoxA(NULL, "Get function fail.", "Fail", MB_OK);
		}
		//free library
		FreeLibrary(hInst);
		hInst = nullptr;
	}
	else
	{
		::MessageBoxA(NULL, "Load dll fail.", "Fail", MB_OK);
		exit(0);
	}
	return ret;
}

inline vector<string> split(const string& s, const string& seperator) {
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

char* Form2::getUSBList() {
	char* ret = "";
	HINSTANCE hInst = LoadLibrary(_T("librayForMFCIL.dll"));
	if (hInst)
	{
		typedef char*(*pFunc)();
		pFunc doFunc = NULL;
		pFunc Func_GetUSBList = (pFunc)GetProcAddress(hInst, "getUSBList");
		CString text;

		if (Func_GetUSBList)
		{
			char error[100] = { NULL };
			ret = Func_GetUSBList();
		}
		else
		{
			::MessageBoxA(NULL, "Get function fail.", "Fail", MB_OK);
		}
		//free library
		FreeLibrary(hInst);
		hInst = nullptr;
	}
	else
	{
		::MessageBoxA(NULL, "Load dll fail.", "Fail", MB_OK);
	}
	return ret;
}

BOOL Form2::OnInitDialog()
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

	SetIcon(q_hIcon, TRUE);			
	SetIcon(q_hIcon, FALSE);		

	// -------------------------------------------------------------------------
	// Form Load    (MainForm)
	// -------------------------------------------------------------------------
	char* spudev = NULL;                        // spu device name
	int errorcode;                                // errorcode 
	char* usb_resource = NULL;                  // usb communication resource


	spudev = getDAQList();  // ----Check Connction of spu deviece

	 // ----Check usb resource
	usb_resource = getUSBList();

	// ------show Setting Form
	CILSTS_Sample_MFCDlg set_form = new CILSTS_Sample_MFCDlg();

	//set_form.Owner = this;
	set_form.SPU_Resource = spudev;
	set_form.USB_Resource = usb_resource;
	set_form.DoModal();

	// ---Apply to communication parametere from Instrument setting form

	// ----tsl　Communication method
	if (set_form.TSL_Communicater == "GPIB")
	{

		int reValue = ConnectTSLGPIB(_ttof((LPSTR)(LPCSTR)set_form.TSL_Address));
		if (reValue == 0) {

			char* speedList = getSpeedList();
			string a = speedList;
			int cnt = a.find(_T(","));

			if (cnt >= 0) {
				vector<string> obj = split(speedList, ",");
				for (int i = 0; i < obj.size(); i++) {
					string str1 = obj.at(i);
					SPEED_LIST.AddString(CString(str1.c_str()));
				}
				SPEED_LIST.SetCurSel(0);
			}
			else {
				SPEED_LIST.AddString(speedList);
				SPEED_LIST.SetCurSel(0);
			}
		}
		else {
			::MessageBoxA(NULL, "Connect TSL Failed.", "Fail", MB_OK);
			exit(0);
		}
	}
	else if (set_form.TSL_Communicater == "LAN")
	{
		CString IPAddress;
		CString Port;

		int reValue = ConnectTSL((LPSTR)(LPCSTR)(set_form.TSL_Address), set_form.TSL_Portnumber);
		if (reValue == 0) {

			char* speedList = getSpeedList();
			string a = speedList;
			int cnt = a.find(_T(","));

			if (cnt >= 0) {
				vector<string> obj = split(speedList, ",");
				for (int i = 0; i < obj.size(); i++) {
					string str1 = obj.at(i);
					SPEED_LIST.AddString(CString(str1.c_str()));
				}
				SPEED_LIST.SetCurSel(0);
			}
			else {
				SPEED_LIST.AddString(speedList);
				SPEED_LIST.SetCurSel(0);
			}
		}
		else {
			::MessageBoxA(NULL, "Connect TSL Failed.", "Fail", MB_OK);
			exit(0);
		}

	}
	else
	{
		// USB 

		int reValue = ConnectTSLUSB(_ttof((LPSTR)(LPCSTR)set_form.TSL_Address));
		if (reValue == 0) {

			char* speedList = getSpeedList();
			string a = speedList;
			int cnt = a.find(_T(","));

			if (cnt >= 0) {
				vector<string> obj = split(speedList, ",");
				for (int i = 0; i < obj.size(); i++) {
					string str1 = obj.at(i);
					SPEED_LIST.AddString(CString(str1.c_str()));
				}
				SPEED_LIST.SetCurSel(0);
			}
			else {
				SPEED_LIST.AddString(speedList);
				SPEED_LIST.SetCurSel(0);
			}
		}
		else {
			::MessageBoxA(NULL, "Connect TSL Failed.", "Fail", MB_OK);
			exit(0);
		}
	}

	// ---mpm Communicatipon method
	int loop1;


	mpmcount = set_form.MPM_Count;

	//mpm = new MPM[mpmcount];

	for (loop1 = 0; loop1 <= mpmcount - 1; loop1++)
	{
		//mpm[loop1] = new MPM();
		int reValue;
		if (set_form.MPM_Communicater == "GPIB") {
			reValue = ConnectGPIBMPM(_ttof((LPSTR)(LPCSTR)set_form.MPM_Address[loop1]), loop1 + 1);
		}
		else
		{
			reValue = ConnectMPM((LPSTR)(LPCSTR)(set_form.MPM_Address[loop1]), set_form.MPM_Portnumber[loop1], loop1 + 1);
		}
		if (reValue == 0) {
			CheckModuleInformation();
		}
		else {
			::MessageBoxA(NULL, "Connect MPM Failed.", "Fail", MB_OK);
			exit(0);
		}

	}

	if (ConnectDAQ(set_form.SPU_DeviveID) != 0) {
		::MessageBoxA(NULL, "Connect DAQ Failed.", "Fail", MB_OK);
		exit(0);
	}

	Referect_EnableCh_for_form();                // mpm Eanble ch
	Referect_EnableRange_for_form();             // mpm selectable range

	return TRUE;  
}

void Form2::Referect_EnableRange_for_form()
{
	// -----------------------------------------------------
	// Refelect mpm Range
	// -------------------------------------------------------

	HINSTANCE hInst = LoadLibrary(_T("librayForMFCIL.dll"));
	if (hInst)
	{
		typedef int(*pFunc)();
		pFunc Func_Flag_213 = (pFunc)GetProcAddress(hInst, "GetFlag_213");
		pFunc Func_Flag_215 = (pFunc)GetProcAddress(hInst, "GetFlag_215");

		if (Func_Flag_213)
		{
			char error[100] = { NULL };
			Flag_213 = Func_Flag_213();

		}
		else
		{
			::MessageBoxA(NULL, "Get function fail.", "Fail", MB_OK);
		}
		if (Func_Flag_215)
		{
			char error[100] = { NULL };
			Flag_215 = Func_Flag_215();

		}
		else
		{
			::MessageBoxA(NULL, "Get function fail.", "Fail", MB_OK);
		}
		//free library
		FreeLibrary(hInst);
		hInst = nullptr;

	}
	else
	{
		::MessageBoxA(NULL, "Load dll fail.", "Fail", MB_OK);
	}
	// mpm-213 can use just 1 to 4 range
	if (Flag_213 == true)
	{
		lst_range.AddString(_T("Range1"));
		lst_range.AddString(_T("Range2"));
		lst_range.AddString(_T("Range3"));
		lst_range.AddString(_T("Range4"));
	}
	else
	{
		lst_range.AddString(_T("Range1"));
		lst_range.AddString(_T("Range2"));
		lst_range.AddString(_T("Range3"));
		lst_range.AddString(_T("Range4"));
		lst_range.AddString(_T("Range5"));
	}

	// mpm-215 can't select range
	if (Flag_215 == true)
		GetDlgItem(chklst_range)->EnableWindow(FALSE);
}

void Form2::Referect_EnableCh_for_form()
{
	// ------------------------------------------------
	// Reflect mpm ch 
	// ------------------------------------------------
	int loop1;
	int loop2;
	char* enable_slot = "";
	char* slot_type = "";
	CString str2;
	CString str1;
	CString enable_slot1 = "";
	vector<string> obj;
	for (loop1 = 0; loop1 <= mpmcount - 1; loop1++)
	{
		// get insert module count with "mpm Information" class 
		HINSTANCE hInst = LoadLibrary(_T("librayForMFCIL.dll"));
		if (hInst)
		{
			typedef char*(*pFunc)(int);
			pFunc Func_GetModuleEnable = (pFunc)GetProcAddress(hInst, "GetModuleEnable");
			if (Func_GetModuleEnable)
			{
				char error[100] = { NULL };
				enable_slot = Func_GetModuleEnable(loop1);
			}
			enable_slot1 = A2T(enable_slot);
			int cnt = enable_slot1.Find(_T(","));
			if (cnt >= 0) {
				obj = split(enable_slot, ",");
			}
		}
		//enable_slot = mpm[loop1].Information.ModuleEnable;

		// modeule loop(Maximum 5 slot)
		for (loop2 = 0; loop2 <= 4; loop2++)
		{
			string a = "True";
			if (obj[loop2] == a)
			{
				// get module type with "mpm Information" class 
				if (hInst)
				{
					typedef char*(*pFunc)(int, int);
					pFunc Func_GetModuleType = (pFunc)GetProcAddress(hInst, "GetModuleType");
					if (Func_GetModuleType)
					{
						char error[100] = { NULL };
						slot_type = Func_GetModuleType(loop1, loop2);
					}

				}

				//slot_type = mpm[loop1].Information.ModuleType[loop2];
				str1.Format(_T("%d"), loop1 + 1);
				str2.Format(_T("%d"), loop2);

				if (slot_type != "MPM-212")
				{
					lst_ch.AddString(_T("mpm" + str1 + " Slot" + str2 + " Ch1"));
					lst_ch.AddString(_T("mpm" + str1 + " Slot" + str2 + " Ch2"));
					lst_ch.AddString(_T("mpm" + str1 + " Slot" + str2 + " Ch3"));
					lst_ch.AddString(_T("mpm" + str1 + " Slot" + str2 + " Ch4"));
				}
				else
				{
					lst_ch.AddString(_T("mpm" + str1 + " Slot" + str2 + " Ch1"));
					lst_ch.AddString(_T("mpm" + str1 + " Slot" + str2 + " Ch2"));
				}
			}
		}
		//free library
		FreeLibrary(hInst);
		hInst = nullptr;
	}
}

int Form2::ConnectDAQ(CString txt)
{
	int ret;
	HINSTANCE hInst = LoadLibrary(_T("librayForMFCIL.dll"));
	if (hInst)
	{
		typedef int(*pFunc)(char*);
		pFunc doFunc = NULL;
		pFunc Func_SetDAQConnection = (pFunc)GetProcAddress(hInst, "setDAQConnection");

		if (Func_SetDAQConnection)
		{
			char error[100] = { NULL };
			char* cIP = (LPSTR)(LPCSTR)(txt);
			ret = Func_SetDAQConnection(cIP);
		}
		else
		{
			::MessageBoxA(NULL, "Get function fail.", "Fail", MB_OK);
		}
		//free library
		FreeLibrary(hInst);
		hInst = nullptr;
	}
	else
	{
		::MessageBoxA(NULL, "Load dll fail.", "Fail", MB_OK);
	}
	return ret;

}

int Form2::ConnectMPM(char* ip, int port, int index)
{
	int ret;
	HINSTANCE hInst = LoadLibrary(_T("librayForMFCIL.dll"));
	if (hInst)
	{
		typedef int(*pFunc)(char*, int, int);
		pFunc doFunc = NULL;
		pFunc Func_setMPMConnection = (pFunc)GetProcAddress(hInst, "setMPMConnection");

		if (Func_setMPMConnection)
		{

			ret = Func_setMPMConnection(ip, port, index);
		}
		else
		{
			::MessageBoxA(NULL, "Get function fail.", "Fail", MB_OK);
		}
		//free library
		FreeLibrary(hInst);
		hInst = nullptr;
	}
	else
	{
		::MessageBoxA(NULL, "Load dll fail.", "Fail", MB_OK);
	}
	return ret;

}

int Form2::ConnectGPIBMPM(int address, int index)
{
	int ret;
	HINSTANCE hInst = LoadLibrary(_T("librayForMFCIL.dll"));
	if (hInst)
	{
		typedef int(*pFunc)(int, int);
		pFunc doFunc = NULL;
		pFunc Func_SetMPMGPIBConnection = (pFunc)GetProcAddress(hInst, "setMPMGPIBConnection");

		if (Func_SetMPMGPIBConnection)
		{

			ret = Func_SetMPMGPIBConnection(address, index);
		}
		else
		{
			::MessageBoxA(NULL, "Get function fail.", "Fail", MB_OK);
		}
		//free library
		FreeLibrary(hInst);
		hInst = nullptr;
	}
	else
	{
		::MessageBoxA(NULL, "Load dll fail.", "Fail", MB_OK);
	}
	return ret;

}

int Form2::CheckModuleInformation()
{
	int ret;
	HINSTANCE hInst = LoadLibrary(_T("librayForMFCIL.dll"));
	if (hInst)
	{
		typedef int(*pFunc)();
		pFunc doFunc = NULL;
		pFunc Func_CheckModuleInformation = (pFunc)GetProcAddress(hInst, "Check_Module_Information");

		if (Func_CheckModuleInformation)
		{
			ret = Func_CheckModuleInformation();
			if (ret == 1)
			{
				GetDlgItem(chklst_range)->EnableWindow(FALSE);
				addRange(1,  1);
			}
		}
		else
		{
			::MessageBoxA(NULL, "Get function fail.", "Fail", MB_OK);
		}
		//free library
		FreeLibrary(hInst);
		hInst = nullptr;
	}
	else
	{
		::MessageBoxA(NULL, "Load dll fail.", "Fail", MB_OK);
	}
	return ret;

}

int Form2::ConnectTSLUSB(int addr)
{
	int ret;
	HINSTANCE hInst = LoadLibrary(_T("librayForMFCIL.dll"));
	if (hInst)
	{
		typedef int(*pFunc)(int);
		pFunc doFunc = NULL;
		pFunc Func_SetTSLUSBConnection = (pFunc)GetProcAddress(hInst, "setTSLUSBConnection");

		if (Func_SetTSLUSBConnection)
		{

			ret = Func_SetTSLUSBConnection(addr);
		}
		else
		{
			::MessageBoxA(NULL, "Get function fail.", "Fail", MB_OK);
		}
		//free library
		FreeLibrary(hInst);
		hInst = nullptr;
	}
	else
	{
		::MessageBoxA(NULL, "Load dll fail.", "Fail", MB_OK);
	}
	return ret;

}

int Form2::ConnectTSL(char* ip, int port)
{
	int ret;
	HINSTANCE hInst = LoadLibrary(_T("librayForMFCIL.dll"));
	if (hInst)
	{
		typedef int(*pFunc)(char*, int);
		pFunc doFunc = NULL;
		pFunc Func_setTSLConnection = (pFunc)GetProcAddress(hInst, "setTSLConnection");
		CString text;

		if (Func_setTSLConnection)
		{

			ret = Func_setTSLConnection(ip, port);
		}
		else
		{
			::MessageBoxA(NULL, "Get function fail.", "Fail", MB_OK);
		}
		//free library
		FreeLibrary(hInst);
		hInst = nullptr;
	}
	else
	{
		::MessageBoxA(NULL, "Load dll fail.", "Fail", MB_OK);
	}
	return ret;

}

int Form2::ConnectTSLGPIB(int addr)
{
	int ret;
	HINSTANCE hInst = LoadLibrary(_T("librayForMFCIL.dll"));
	if (hInst)
	{
		typedef int(*pFunc)(int);
		pFunc doFunc = NULL;
		pFunc Func_SetTSLGPIBConnection = (pFunc)GetProcAddress(hInst, "setTSLGPIBConnection");
		if (Func_SetTSLGPIBConnection)
		{

			ret = Func_SetTSLGPIBConnection(addr);
		}
		else
		{
			::MessageBoxA(NULL, "Get function fail.", "Fail", MB_OK);
		}
		//free library
		FreeLibrary(hInst);
		hInst = nullptr;
	}
	else
	{
		::MessageBoxA(NULL, "Load dll fail.", "Fail", MB_OK);
	}
	return ret;

}

char* Form2::getSpeedList() {
	char* ret = NULL;
	HINSTANCE hInst = LoadLibrary(_T("librayForMFCIL.dll"));
	if (hInst)
	{
		typedef char*(*pFunc)();
		pFunc doFunc = NULL;
		pFunc Func_Add_TSL_Sweep_Speed = (pFunc)GetProcAddress(hInst, "Add_TSL_Sweep_Speed");
		if (Func_Add_TSL_Sweep_Speed)
		{
			char error[100] = { NULL };
			ret = Func_Add_TSL_Sweep_Speed();
		}
		else
		{
			::MessageBoxA(NULL, "Get function fail.", "Fail", MB_OK);

		}
		//free library
		FreeLibrary(hInst);
		hInst = nullptr;
	}
	else
	{
		::MessageBoxA(NULL, "Load dll fail.", "Fail", MB_OK);
	}
	return ret;
}



void Form2::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, q_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR Form2::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(q_hIcon);
}


BEGIN_MESSAGE_MAP(Form2, CDialogEx)
	ON_BN_CLICKED(btnset, &Form2::OnBnClickedbtnset)
	ON_BN_CLICKED(btnget_reference, &Form2::OnBnClickedreference)
	ON_BN_CLICKED(btnmeas, &Form2::OnBnClickedbtnmeas)
	ON_BN_CLICKED(Button1, &Form2::OnBnClickedButton1)
	ON_BN_CLICKED(btnsaveref_rawdata, &Form2::OnBnClickedrawdata)
	ON_BN_CLICKED(btnsaveRawdata, &Form2::OnBnClickedbtnsaverawdata)
END_MESSAGE_MAP()


// Form2 消息处理程序


void Form2::OnBnClickedbtnset()
{

	int mpmIndex;
	int moduleIndex;
	int channelIndex;
	int index = 0;
	CString text_st = "";
	for (int loop1 = 0; loop1 <= lst_ch.GetCount() - 1; loop1++)
	{
		if (lst_ch.GetCheck(loop1) == BST_CHECKED)
		{
			lst_ch.GetText(loop1, text_st);
			string a = text_st;
			int cnt = a.find(_T(" "));

			if (cnt >= 0)
			{
				string text_st1 = text_st.GetBuffer(0);
				vector<string> obj = split(text_st1, " ");
				for (int i = 0; i < obj.size(); i++)
				{
					obj.at(i);
				}
				// ch parameter
				mpmIndex = _ttoi(CString(obj[0].c_str()).Mid(3, 1));
				moduleIndex = _ttoi(CString(obj[1].c_str()).Mid(4, 1));
				channelIndex = _ttoi(CString(obj[2].c_str()).Mid(2, 1));
				addChannel(mpmIndex * 100 + moduleIndex * 10 + channelIndex, index + 1);
				index++;
			}
		}
	}

	int nIndex = 0;
	for (int loop1 = 0; loop1 <= lst_range.GetCount() - 1; loop1++)
	{
		if (lst_range.GetCheck(loop1) == BST_CHECKED)
		{
			addRange(loop1 + 1, nIndex + 1);
			nIndex++;
		}

	}

	CString strSpeed;
	CString cs_wavelength_start;
	CString cs_wavelength_stop;
	CString cs_step;
	CString cs_power;
	GetDlgItem(txtstartwave)->GetWindowText(cs_wavelength_start);
	GetDlgItem(txtstopwave)->GetWindowText(cs_wavelength_stop);
	GetDlgItem(txtstepwave)->GetWindowText(cs_step);
	GetDlgItem(txtpower)->GetWindowText(cs_power);
	GetDlgItem(cmbspeed)->GetWindowText(strSpeed);


	double i_wavlength_start = _ttof(cs_wavelength_start);
	double i_wavlength_stop = _ttof(cs_wavelength_stop);
	double i_step = _ttof(cs_step);
	double i_power = _ttof(cs_power);
	double i_speed = _ttof(strSpeed);

	int actionflag = setCondition(i_wavlength_start, i_wavlength_stop, i_step, i_speed, i_power, ((CButton *)GetDlgItem(chkeach_ch))->GetCheck());
}

void Form2::addRange(int range, int index)
{
	HINSTANCE hInst = LoadLibrary(_T("librayForMFCIL.dll"));
	if (hInst)
	{
		typedef void(*pFunc)(int, int);
		pFunc doFunc = NULL;
		pFunc Func_SetRange = (pFunc)GetProcAddress(hInst, "setRange");
		CString text;

		if (Func_SetRange)
		{

			Func_SetRange(range, index);
		}
		else
		{
			::MessageBoxA(NULL, "Get function fail.", "Fail", MB_OK);
		}
		//free library
		FreeLibrary(hInst);
		hInst = nullptr;
	}
	else
	{
		::MessageBoxA(NULL, "Load dll fail.", "Fail", MB_OK);
	}
}

void Form2::addChannel(int channel, int index)
{
	HINSTANCE hInst = LoadLibrary(_T("librayForMFCIL.dll"));
	if (hInst)
	{
		typedef void(*pFunc)(int, int);
		pFunc doFunc = NULL;
		pFunc Func_SetChannel = (pFunc)GetProcAddress(hInst, "setChannel");
		CString text;

		if (Func_SetChannel)
		{

			Func_SetChannel(channel, index);
		}
		else
		{
			::MessageBoxA(NULL, "Get function fail.", "Fail", MB_OK);
		}
		//free library
		FreeLibrary(hInst);
		hInst = nullptr;
	}
	else
	{
		::MessageBoxA(NULL, "Load dll fail.", "Fail", MB_OK);
	}
}

int Form2::setCondition(double startWL, double stopWL, double step, double pSpeed, double power,bool chkeach)
{
	HINSTANCE hInst = LoadLibrary(_T("librayForMFCIL.dll"));
	if (hInst)
	{
		typedef int(*pFunc)(double, double, double, double, double,bool);
		pFunc doFunc = NULL;
		pFunc Func_SetSweepCondition = (pFunc)GetProcAddress(hInst, "setSweepCondition");
		CString text;

		if (Func_SetSweepCondition)
		{

		 Func_SetSweepCondition(startWL, stopWL, step, pSpeed, power, chkeach);
		}
		else
		{
			::MessageBoxA(NULL, "Get function fail.", "Fail", MB_OK);
		}
		//free library
		FreeLibrary(hInst);
		hInst = nullptr;
	}
	else
	{
		::MessageBoxA(NULL, "Load dll fail.", "Fail", MB_OK);
	}
	return 0;
}



void Form2::OnBnClickedreference()
{
	HINSTANCE hInst = LoadLibrary(_T("librayForMFCIL.dll"));
	if (hInst)
	{
		typedef int(*pFunc)(bool);
		pFunc doFunc = NULL;
		pFunc Func_Reference = (pFunc)GetProcAddress(hInst, "reference");
		CString text;

		if (Func_Reference)
		{
			Func_Reference(((CButton *)GetDlgItem(chkeach_ch))->GetCheck());
		}
		else
		{
			::MessageBoxA(NULL, "Get function fail.", "Fail", MB_OK);
		}
		//free library
		FreeLibrary(hInst);
		hInst = nullptr;
	}
	else
	{
		::MessageBoxA(NULL, "Load dll fail.", "Fail", MB_OK);
	}

}


void Form2::setMeasureFilePath(char* filePath)
{
	int ret;
	HINSTANCE hInst = LoadLibrary(_T("librayForMFCIL.dll"));
	if (hInst)
	{
		typedef void(*pFunc)(char*);
		pFunc doFunc = NULL;
		pFunc Func_SetFileName = (pFunc)GetProcAddress(hInst, "setFileName");
		CString text;

		if (Func_SetFileName)
		{

			Func_SetFileName(filePath);
		}
		else
		{
			::MessageBoxA(NULL, "Get function fail.", "Fail", MB_OK);
		}
		//free library
		FreeLibrary(hInst);
		hInst = nullptr;
	}
	else
	{
		::MessageBoxA(NULL, "Load dll fail.", "Fail", MB_OK);
	}
}


void Form2::OnBnClickedbtnmeas()
{
	CFileDialog dlg(TRUE, "csv", "IL data", OFN_HIDEREADONLY, NULL); 
	dlg.m_ofn.lpstrTitle = _T("IL data Save");
	if (dlg.DoModal() == IDOK)
	{
		CString str = dlg.GetPathName(); 
		char* cSelectedPath = (LPSTR)(LPCSTR)str;
		setMeasureFilePath(cSelectedPath);
	}
	else {
		setMeasureFilePath("");
	}

	HINSTANCE hInst = LoadLibrary(_T("librayForMFCIL.dll"));
	if (hInst)
	{
		typedef int(*pFunc)();
		pFunc doFunc = NULL;
		pFunc Func_Measure = (pFunc)GetProcAddress(hInst, "Measure");
		CString text;

		if (Func_Measure)
		{
			 Func_Measure();
		}
		else
		{
			::MessageBoxA(NULL, "Get function fail.", "Fail", MB_OK);
		}
		//free library
		FreeLibrary(hInst);
		hInst = nullptr;
	}
	else
	{
		::MessageBoxA(NULL, "Load dll fail.", "Fail", MB_OK);
	}
}



void Form2::OnBnClickedButton1()
{
	CFileDialog dlg(TRUE, "csv", NULL, OFN_HIDEREADONLY, NULL); 
	dlg.m_ofn.lpstrTitle = _T("Reference data");
	if (dlg.DoModal() == IDOK)
	{
		CString str = dlg.GetPathName();    
		char* cSelectedPath = (LPSTR)(LPCSTR)str;
		HINSTANCE hInst = LoadLibrary(_T("librayForMFCIL.dll"));
		if (hInst)
		{
			typedef int(*pFunc)(char*, bool);
			pFunc Func_LoadRefdata = (pFunc)GetProcAddress(hInst, "loadReference");
			if (Func_LoadRefdata)
			{

				  Func_LoadRefdata(cSelectedPath, ((CButton *)GetDlgItem(chkeach_ch))->GetCheck());
			}
			else
			{
				::MessageBoxA(NULL, "Get function fail.", "Fail", MB_OK);
			}
			//free library
			FreeLibrary(hInst);
			hInst = nullptr;
		}
		else
		{
			::MessageBoxA(NULL, "Load dll fail.", "Fail", MB_OK);
		}
	}
}




void Form2::OnBnClickedrawdata()
{
	CFileDialog dlg(TRUE, "csv", "Reference Raw data", OFN_HIDEREADONLY, NULL); 
	dlg.m_ofn.lpstrTitle = _T("Reference Raw data");

	if (dlg.DoModal() == IDOK)
	{
		CString str = dlg.GetPathName();  
		char* cSelectedPath = (LPSTR)(LPCSTR)str;
		HINSTANCE hInst = LoadLibrary(_T("librayForMFCIL.dll"));
		if (hInst)
		{
			typedef int(*pFunc)(char*, bool);
			pFunc Func_SaveRefdata = (pFunc)GetProcAddress(hInst, "saveReference");


			if (Func_SaveRefdata)
			{

				Func_SaveRefdata(cSelectedPath, ((CButton *)GetDlgItem(chkeach_ch))->GetCheck());
			}
			else
			{
				::MessageBoxA(NULL, "Get function fail.", "Fail", MB_OK);
			}
			//free library
			FreeLibrary(hInst);
			hInst = nullptr;
		}
		else
		{
			::MessageBoxA(NULL, "Load dll fail.", "Fail", MB_OK);
		}
	}
}



void Form2::OnBnClickedbtnsaverawdata()
{
	CFileDialog dlg(TRUE, "csv", "raw data", OFN_HIDEREADONLY, NULL); 
	if (dlg.DoModal() == IDOK)
	{
		CString str = dlg.GetPathName(); 
		char* cSelectedPath = (LPSTR)(LPCSTR)str;
		HINSTANCE hInst = LoadLibrary(_T("librayForMFCIL.dll"));
		if (hInst)
		{
			typedef int(*pFunc)(char*);
			pFunc Func_SaveRawdata = (pFunc)GetProcAddress(hInst, "saveRawdata");

			if (Func_SaveRawdata)
			{

				 Func_SaveRawdata(cSelectedPath);
			}
			else
			{
				::MessageBoxA(NULL, "Get function fail.", "Fail", MB_OK);
			}
			//free library
			FreeLibrary(hInst);
			hInst = nullptr;
		}
		else
		{
			::MessageBoxA(NULL, "Load dll fail.", "Fail", MB_OK);
		}
	}
}


