#pragma once
class Form2 : public CDialogEx
{
	DECLARE_DYNAMIC(Form2)

public:
	Form2(CWnd* pParent = NULL);   
	virtual ~Form2();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1};
#endif

protected:
	HICON q_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CCheckListBox lst_ch;
	CCheckListBox lst_range;
	int mpmcount;                     // mpm count
	 bool Flag_213;                                         // Exist 213 flag      T: Exist F: nothing
	 bool Flag_215;                                         // Exist 215 flag      T: Exist F: nothing
	 void Form2::Referect_EnableRange_for_form();

	char* Form2::getDAQList();
	char* Form2::getUSBList();
	int Form2::ConnectDAQ(CString txt);
	int Form2::ConnectTSL(char* ip, int port);
	char* Form2::getSpeedList();
	int Form2::ConnectMPM(char* ip, int port, int index);
	int Form2::CheckModuleInformation();
	void Form2::addChannel(int index, int channel);
	void Form2::addRange(int index, int range);
	int Form2::setCondition(double startWL, double stopWL, double step, double pSpeed, double power, bool chkeach);
	void Form2::setMeasureFilePath(char* filePath);
	int Form2::referenceAction();
	int Form2::measureAction();
	int Form2::rawData(char* path);
	int Form2::ConnectTSLGPIB(int addr);
	int Form2::ConnectTSLUSB(int addr);
	int Form2::ConnectGPIBMPM(int address, int index);
	void Form2::ConnectTSLWithLAN();
	void Form2::ConnectTSLWithGPIB();
	void Form2::ConnectTSLWithUSB();
	void Form2::ConnectMPMWithLAN();
	void Form2::ConnectMPMWithGPIB();
	void Form2::Referect_EnableCh_for_form();
	int Form2::saveRefData(char* path);
	int Form2::loadRefData(char* path);
	CComboBox SPEED_LIST;
	afx_msg void OnBnClickedbtnset();
	afx_msg void OnBnClickedreference();
	afx_msg void OnBnClickedbtnmeas();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedrawdata();
	afx_msg void OnBnClickedbtnsaverawdata();
};
