


#pragma once
#include "afxwin.h"


class CILSTS_Sample_MFCDlg : public CDialogEx
{
public:
	CILSTS_Sample_MFCDlg(CWnd* pParent = NULL);	

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ILSTS_SAMPLE_MFC_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV Ö§³Ö


protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:
	CCheckListBox m_listbox;
	char* CILSTS_Sample_MFCDlg::SPU_Resource; // SPU resource name 
	char* CILSTS_Sample_MFCDlg::USB_Resource; // USB resource name 
	CComboBox DAQ_LIST;
	CComboBox USB_LIST;

	CString CILSTS_Sample_MFCDlg::TSL_Communicater;               // TSL Communicator name
	CString CILSTS_Sample_MFCDlg::MPM_Communicater;               // MPM Communicator name

	CString TSL_Address;                    // TSL address
	int TSL_Portnumber;                // TSL LAN port number

	int MPM_Count;                     // MPM number of device 
	CString MPM_Address[2];                 // MPM address 
    int MPM_Portnumber[2];             // MPM LAN port number

	CString SPU_DeviveID;                   // SPU Deviece resource

	afx_msg void OnBnClickedbtnconnect();
	afx_msg void OnBnClickedrdo570();
	afx_msg void OnBnClickedgpib();
	afx_msg void OnBnClickedtsltcpip();
	afx_msg void OnBnClickedtslusb();
	afx_msg void OnBnClickeddev();
	afx_msg void OnBnClickedmpmgpib();
	afx_msg void OnBnClickedrdo550();
	afx_msg void OnBnClickedmpmtcpip();
};
