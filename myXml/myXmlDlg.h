
// myXmlDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "tinyxml.h"
#include "tinystr.h"

// CmyXmlDlg dialog
class CmyXmlDlg : public CDialogEx
{
// Construction
public:
	CmyXmlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MYXML_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
    void OnBnClickedOk();
    CTreeCtrl TreeCtrl;
    TiXmlDocument *pDoc;
    CImageList cImageList;  //Í¼ÏñÁÐ±í
    int LoadXML(char* filename);
    int MakeTree(TiXmlElement * node,HTREEITEM ht);
    void GBKToUTF8(char* &szOut);
    void UTF8ToGBK(char* &szOut);
    int SaveXML(TiXmlNode* node, HTREEITEM ht);
    afx_msg void OnBnClickedButton1();
};
