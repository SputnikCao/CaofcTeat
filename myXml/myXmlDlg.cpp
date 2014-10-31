
// myXmlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "myXml.h"
#include "myXmlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmyXmlDlg dialog
CmyXmlDlg::CmyXmlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmyXmlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmyXmlDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TREE1, TreeCtrl);
}

BEGIN_MESSAGE_MAP(CmyXmlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CmyXmlDlg::OnTvnSelchangedTree1)
    ON_BN_CLICKED(IDOK, &CmyXmlDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON1, &CmyXmlDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CmyXmlDlg message handlers

BOOL CmyXmlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CmyXmlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

//UTF8��ʽת��ΪGBK
void CmyXmlDlg::UTF8ToGBK(char *&szOut)
{
    unsigned short *wszGBK;
    char *szGBK;
    //����
    int len = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)szOut, -1, NULL, 0);//ӳ��һ���ַ�����һ�����ַ���unicode�����ַ���,1��ָ��ִ��ת�����ַ���
                                                                          //2ת�����ͣ�3��ת���ַ�����4
                                                                          //Returns the number of characters written to the buffer indicated by lpWideCharStr if successful.
    wszGBK = new unsigned short[len+1];
    memset(wszGBK, 0, len * 2 + 2);
    MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)szOut, -1, (LPWSTR)wszGBK, len);

    len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
    szGBK = new char[len+1];
    memset(szGBK, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, szGBK, len, NULL, NULL);

    //szOut = szGBK; 
    //�����õ���szOut����ȷ����Ϊ�˾������ǽ�szGBK���׵�ַ����szOut����delete []szGBKִ�к�szGBK����
    //��ռ佫���ͷţ���ʱ���ò���szOut������

    memset(szOut,'\0',strlen(szGBK)+1); //�Ľ�szGBK�����ݸ���szOut ��������ʹszGBK���ͷ�Ҳ�ܵõ���ȷ��ֵ
    memcpy(szOut,szGBK,strlen(szGBK));

    delete []szGBK;
    delete []wszGBK;
}

//GBK��ʽת��ΪUTF��ʽ
void CmyXmlDlg::GBKToUTF8(char* &szOut)
{
    char* strGBK = szOut;

    int len=MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strGBK, -1, NULL,0);
    unsigned short * wszUtf8 = new unsigned short[len+1];
    memset(wszUtf8, 0, len * 2 + 2);
    MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strGBK, -1, (LPWSTR)wszUtf8, len);

    len = WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wszUtf8, -1, NULL, 0, NULL, NULL);
    char *szUtf8=new char[len + 1];
    memset(szUtf8, 0, len + 1);
    WideCharToMultiByte (CP_UTF8, 0, (LPWSTR)wszUtf8, -1, szUtf8, len, NULL,NULL);

    //szOut = szUtf8;
    memset(szOut,'\0',strlen(szUtf8)+1);
    memcpy(szOut,szUtf8,strlen(szUtf8));

    delete[] szUtf8;
    delete[] wszUtf8;
}

int CmyXmlDlg::MakeTree(TiXmlElement *node,HTREEITEM ht)
{
    TiXmlNode *pChilds;
    const char* nameAttribute = node->Attribute("Name");
    if (nameAttribute != NULL)
    {
        int len = strlen(nameAttribute);
        char *buf = new char[len+1];
        strcpy(buf, nameAttribute);
        UTF8ToGBK(buf);
        const char* nodeName = node->Value();
        if (strcmp(nodeName,"View") == 0)
        {
            ht = TreeCtrl.InsertItem(CString(buf),ht,TVI_LAST);
        }
        else if (strcmp(nodeName,"Group") == 0)
        {
            ht = TreeCtrl.InsertItem(CString(buf),ht,TVI_LAST);
        }
        else if (strcmp(nodeName,"User") == 0)
        {
            TreeCtrl.InsertItem(CString(buf),ht,TVI_LAST);	
        }
    }
    if(!(node->NoChildren()))
    {
        pChilds = node->FirstChild();
        MakeTree((TiXmlElement*)pChilds,ht);
        pChilds = pChilds->NextSiblingElement();//��ȡ����ʾ�Ľ���ͬ����һ�����
        while ( NULL != pChilds )               //�ݹ鴦��˽���µ����н��
        {
            MakeTree((TiXmlElement*)pChilds,ht);
            pChilds = pChilds->NextSiblingElement();
        }
    }
    return 0;
}

int CmyXmlDlg::LoadXML(char* filename)
{
    HTREEITEM ht;
    TiXmlDocument myDocument(filename); //����һ��XML����
    myDocument.LoadFile();
    TiXmlElement *RootElement = myDocument.RootElement(); //��ø�Ԫ��

    TreeCtrl.DeleteAllItems();

    //UpdateWindow();

    ht = TreeCtrl.InsertItem(_T("��֯"),0,0,TVI_ROOT,TVI_LAST);		

    MakeTree(RootElement,ht);

    /*HICON hIcon;
    cImageList.Create(18, 18,  ILC_COLOR32| ILC_MASK, 4, 2);
    hIcon= ::AfxGetApp()->LoadIconW(IDI_ICON1);
    cImageList.Add(hIcon);
    hIcon= ::AfxGetApp()->LoadIconW(IDI_ICON2);
    cImageList.Add(hIcon);
    hIcon= ::AfxGetApp()->LoadIconW(IDI_ICON3);
    cImageList.Add(hIcon);
    hIcon= ::AfxGetApp()->LoadIconW(IDI_ICON4);
    cImageList.Add(hIcon);

    TreeCtrl.SetImageList(&cImageList, TVSIL_NORMAL);*/

    //TreeCtrl.Expand(ht,TVE_EXPAND);  //���ؼ���չ�����۵�����
    //ht = TreeCtrl.GetChildItem(ht);  //�����Ĳ���
    //TreeCtrl.Expand(ht,TVE_EXPAND);

    return 0;

}

int CmyXmlDlg::SaveXML(TiXmlNode* node, HTREEITEM ht)
{   
   
    //ht = TreeCtrl.GetSelectedItem();//�����ص�ǰѡ�еĸ����ľ��
    //ht = TreeCtrl.GetChildItem(ht);
    CString NodeName = TreeCtrl.GetItemText(ht); //���ڵõ���ǰ������ʾ�ַ�
    char* nodename = NodeName.GetBuffer(0);      //CStringת��Ϊchar*
    GBKToUTF8(nodename);                         //GBKתUTF8
    
    TiXmlElement* Elemen = new TiXmlElement(nodename);  // ��xml�ļ������ɽڵ�
    node->LinkEndChild(Elemen);

    //if(!(node->NoChildren()))
    //{
    //    pChilds = node->FirstChild();
    //    MakeTree((TiXmlElement*)pChilds,ht);
    //    pChilds = pChilds->NextSiblingElement();//��ȡ����ʾ�Ľ���ͬ����һ�����
    //    while ( NULL != pChilds )               //�ݹ鴦��˽���µ����н��
    //    {
    //        MakeTree((TiXmlElement*)pChilds,ht);
    //        pChilds = pChilds->NextSiblingElement();
    //    }
    //}

    if (TreeCtrl.GetChildItem(ht) != NULL)
    {
        //TiXmlNode* node1 = node->LastChild();
        ht = TreeCtrl.GetChildItem(ht);
        SaveXML(Elemen,ht);
        ht = TreeCtrl.GetNextSiblingItem(ht);
        while (ht != NULL)
        {
            SaveXML(Elemen,ht);
            ht = TreeCtrl.GetNextSiblingItem(ht);
        }       
    }
    return 0;    
}
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CmyXmlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CmyXmlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmyXmlDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    // TODO: Add your control notification handler code here
    *pResult = 0;
}


void CmyXmlDlg::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    LoadXML("org.xml");
}


void CmyXmlDlg::OnBnClickedButton1()
{
    // TODO: Add your control notification handler code here
    HTREEITEM ht = TreeCtrl.GetRootItem();  //�����ص�ǰѡ�еĸ����ľ��
    pDoc = new TiXmlDocument;//����һ��TiXmlDocument��ָ��
    //CString NodeName = TreeCtrl.GetItemText(ht); //���ڵõ���������ʾ�ַ�
    //char* nodename = NodeName.GetBuffer(0);      //CStringת��Ϊchar*
    //GBKToUTF8(nodename);                         //GBKתUTF8
    TiXmlElement *pRootEle = new TiXmlElement("ORG");  // ���ɸ��ڵ�
    pDoc->LinkEndChild(pRootEle);

    ht = TreeCtrl.GetChildItem(ht);
    SaveXML(pRootEle,ht);
    pDoc->SaveFile("1.xml");
}
