#include <Windows.h>
#include <windowsx.h>
#include <thread>
#include "SoftDefinitions.h"
#include <string>
#include <CommCtrl.h>



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInt, LPSTR args, int nCmdShow) {
	initFileHandler();
	WNDCLASS SoftwareMainClass = MainWindowClass((HBRUSH)COLOR_WINDOW,
														LoadCursor(NULL,IDC_ARROW),
														hInst,
														LoadIcon(NULL, IDI_WINLOGO),
														L"MainWindow",
														SoftMainProcedure);

	if (!RegisterClassW(&SoftwareMainClass)) { return -1; }
	MSG SoftMainMessage = { 0 };
	CreateWindow(L"MainWindow", L"File Coder", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 500, NULL, NULL, NULL, NULL);

	while (GetMessage(&SoftMainMessage, NULL, NULL, NULL)) {
		TranslateMessage(&SoftMainMessage);
		DispatchMessage(&SoftMainMessage);
	}
	return 0;

}

WNDCLASS MainWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure) {
	WNDCLASS MWC = { 0 };
	MWC.hIcon = Icon;
	MWC.hCursor = Cursor;
	MWC.hInstance = hInst;
	MWC.lpszClassName = Name;
	MWC.hbrBackground = BGColor;
	MWC.lpfnWndProc = Procedure;

	return MWC;
}


void initFileHandler()
{

}

LRESULT CALLBACK SoftMainProcedure(HWND hWnd, UINT uMsg, WPARAM wparam, LPARAM lparam) {
	switch (uMsg) {
	case WM_COMMAND: {

		if (HIWORD(wparam) == CBN_SELCHANGE) {
			idx = SendMessage(GroupBox, CB_GETCURSEL, 0, 0);
			SendMessage(GroupBox, CB_GETLBTEXT, (WPARAM)idx, (LPARAM)strText);
		}

		switch (wparam)
		{
		case OnHelpMenuClicked:
			MessageBoxA(hWnd, "File Crypter \nCrytp and decrytp files\nMade by Maksym Rozhdestvenskyi", "File Coder", MB_OK);
			break;
		case OnExitSoftwareClicked:
			PostQuitMessage(0);
			break;
		case OnDecryptTypeClicked:
			
			break;
		case ondocxSelect:
			_b_docx_selected = SetDocx();
			
			break;
		case onxlsxSelect:
			_b_xlsx_selected = SetXlsx();
	
			break;
		case onpstSelect:
			_b_pst_selected = SetPst();
			
			break;
		case ondwgSelect:
			_b_dwg_selected = setDwg();
		
			break;
		case ontxtSelect:
			_b_txt_selected = SetTxt();
		
			break;
		case onRefreshClicked:
			refreshDiskLabels();
			break;

		default: break;
		}
		break;
	}

	case WM_CREATE:
			MainWindowAddMenus(hWnd);
			MainWidowDrawWidgets(hWnd);
			DrawSingleFileList(hWnd);
			DrawDriveList(hWnd);
			refreshDiskLabels();
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default: return DefWindowProc(hWnd,uMsg,wparam,lparam);
	}
}

void MainWindowAddMenus(HWND hWnd) {
	HMENU RootMenu = CreateMenu();
	HMENU SubMenu = CreateMenu();
	HMENU HelpSubMenu = CreateMenu();

	AppendMenuW(HelpSubMenu, MF_STRING, OnHelpMenuClicked, L"About...");

	AppendMenuW(SubMenu, MF_STRING, OnSettingsClicked, L"Settings...");
	AppendMenuW(SubMenu, MF_STRING, OnExitSoftwareClicked, L"Close Program");
	
	AppendMenuW(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"File");
	AppendMenuW(RootMenu, MF_POPUP, (UINT_PTR)HelpSubMenu, L"Help");
	SetMenu(hWnd, RootMenu);

}

void MainWidowDrawWidgets(HWND hWnd) {
	CreateWindowEx(WS_EX_WINDOWEDGE,L"BUTTON", L"Type of mode", WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 250, 10,
		300, 50,hWnd, NULL,
		NULL, NULL);
	CreateWindow(L"BUTTON",L"Encrypt mode", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON |WS_GROUP, 280, 30, 120, 20, hWnd,(HMENU)onEncryptTypeClicked, NULL, NULL);
	CreateWindow(L"BUTTON", L"Decrypt mode", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 400, 30, 120, 20, hWnd, (HMENU)OnDecryptTypeClicked, NULL, NULL);
}

void DrawSingleFileList(HWND hWnd) {
	
	CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Single File", WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 10, 75,
		765, 150, hWnd, NULL,
		NULL, NULL);
	CreateWindow(L"static", L"File: ", WS_VISIBLE | WS_CHILD | ES_RIGHT, 80, 90, 50, 20, hWnd, NULL, NULL, NULL);
	hLineEdit = CreateWindow(L"edit", L"File name", WS_VISIBLE|WS_BORDER | WS_CHILD, 150, 90, 300, 20, hWnd, NULL, NULL, NULL);
	CreateWindow(L"button", L"Select file", WS_VISIBLE | WS_CHILD, 500, 90, 100, 20,hWnd,NULL,NULL,NULL);
	CreateWindow(L"static", L"Enter Passsword: ", WS_VISIBLE | WS_CHILD | ES_RIGHT, 80, 130, 150, 20, hWnd, NULL, NULL, NULL);
	passLine = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD |WS_BORDER|ES_PASSWORD, 250, 130, 300, 20, hWnd, NULL, NULL, NULL);
	CreateWindow(L"static", L"Confirm Passsword: ", WS_VISIBLE | WS_CHILD | ES_RIGHT, 80, 155, 150, 20, hWnd, NULL, NULL, NULL);
	passConfLine = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD|WS_BORDER | ES_PASSWORD, 250, 155, 300, 20, hWnd, NULL, NULL, NULL);
	CreateWindow(L"button", L"Start process", WS_VISIBLE | WS_CHILD, 600, 130, 100, 50, hWnd, NULL, NULL, NULL);
}

void DrawDriveList(HWND hWnd) {
	CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Whole drive", WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 10, 230,
		765, 180, hWnd, NULL,
		NULL, NULL);
	CreateWindow(L"static", L"Drive Letter: ", WS_VISIBLE | WS_CHILD | ES_RIGHT, 80, 250, 50, 20, hWnd, NULL, NULL, NULL);
	GroupBox = CreateWindow(WC_COMBOBOX, L"", WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | CBS_DROPDOWN | CBS_HASSTRINGS | WS_VSCROLL, 150, 250, 50, 200, hWnd,NULL,NULL, NULL);
	CreateWindow(L"Button", L"Refresh", WS_VISIBLE | WS_CHILD, 220, 250, 100, 20,hWnd,(HMENU)onRefreshClicked, NULL, NULL);
	CreateWindow(L"button", L"Select all docx files", BS_AUTOCHECKBOX | WS_TABSTOP | WS_VISIBLE | WS_CHILD, 350, 250, 150, 20, hWnd, (HMENU)ondocxSelect, NULL, NULL);
	CreateWindow(L"button", L"Select all xlsx files", BS_AUTOCHECKBOX | WS_TABSTOP | WS_VISIBLE | WS_CHILD, 350, 275, 150, 20, hWnd, (HMENU)onxlsxSelect, NULL, NULL);
	CreateWindow(L"button", L"Select all txt files", BS_AUTOCHECKBOX | WS_TABSTOP | WS_VISIBLE | WS_CHILD, 500, 250, 150, 20, hWnd, (HMENU)ontxtSelect, NULL, NULL);
	CreateWindow(L"button", L"Select all pst files", BS_AUTOCHECKBOX | WS_TABSTOP | WS_VISIBLE | WS_CHILD, 500, 275, 150, 20, hWnd, (HMENU)onpstSelect, NULL, NULL);
	CreateWindow(L"button", L"Select all dwg files", BS_AUTOCHECKBOX | WS_TABSTOP | WS_VISIBLE | WS_CHILD, 350, 300, 150, 20, hWnd, (HMENU)ondwgSelect, NULL, NULL);
	CreateWindow(L"static", L"Enter Passsword: ", WS_VISIBLE | WS_CHILD | ES_RIGHT, 80, 330, 150, 20, hWnd, NULL, NULL, NULL);
	passLine1 = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 250, 330, 300, 20, hWnd, NULL, NULL, NULL);
	CreateWindow(L"static", L"Confirm Passsword: ", WS_VISIBLE | WS_CHILD | ES_RIGHT, 80, 355, 150, 20, hWnd, NULL, NULL, NULL);
	passConfLine1 = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 250, 355, 300, 20, hWnd, NULL, NULL, NULL);
	CreateWindow(L"button", L"Start process", WS_VISIBLE | WS_CHILD, 600, 330, 100, 50, hWnd, NULL, NULL, NULL);
}

void SearchFiles()
{

}

void refreshDiskLabels()
{
	SendMessage(GroupBox, CB_RESETCONTENT, 0, 0);
	wchar_t szDrives[MAX_PATH];
	if (GetLogicalDriveStrings(MAX_PATH, szDrives))
	{
		wchar_t* pDrive = szDrives;
		while (*pDrive)
		{
			wprintf(pDrive);
			SendMessageW(GroupBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(pDrive));
			pDrive += wcslen(pDrive) + 1;
		}
		
	}
	SendMessage(GroupBox, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
}


bool SetDocx()
{
	if (_b_docx_selected) {
		return false;
	}
	else
	{
		return true;
	}
	
}

bool SetXlsx()
{
	if (_b_xlsx_selected) {
		return false;
	}
	else {
		return true;
	}
}

bool SetTxt()
{
	if (_b_txt_selected) {
		return false;
	}
	else {
		return true;
	}
}

bool SetPst()
{
	if (_b_pst_selected) {
		return false;
	}
	else {
		return true;
	}
}

bool setDwg()
{
	if (_b_dwg_selected) {
		return false;
	}
	else {
		return true;
	}
}


DWORD WINAPI SearchEngine(LPVOID lpParameter) {
	CBlowFish blowFish();
	LPCWCH param = (LPCWCH)lpParameter;
	LPWSTR tmp = (LPWSTR)param;
	tmp += '\\';
	
	wprintf(tmp);
	return 0;
}

