#include <Windows.h>
#include <thread>
#include "SoftDefinitions.h"
#include <string>
#include <CommCtrl.h>
#include <thread>

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

DWORD WINAPI EncodeThread(LPVOID lpParameter)
{
	Encode((LPWSTR)_c_txt);
	MessageBox(0, L"Finish Encrypting", L"INFO", MB_OK | MB_ICONINFORMATION);
	ExitThread(0);
}

DWORD WINAPI DecodeThread(LPVOID lpParameter)
{
	Decode((LPWSTR)_c_txt);
	MessageBox(0, L"Finish Decrypting", L"INFO", MB_OK | MB_ICONINFORMATION);
	ExitThread(0);
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
		case onEncryptTypeClicked:
			_b_type = true;
			break;
		case OnDecryptTypeClicked:
			_b_type = false;
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
		case onSingleProcessClicked:
			GetWindowTextW(hLineEdit, (LPWSTR)_c_txt, MAX_PATH);
			if (_b_type) {
				HANDLE ReadThread = CreateThread(NULL, 0, EncodeThread, NULL, 0, 0);
				CloseHandle(ReadThread);
			}
			else {
				HANDLE ReadThread = CreateThread(NULL, 0, DecodeThread, NULL, 0, 0);
				CloseHandle(ReadThread);
			}	
			break;
		case onDriveProcessClicked:
			if (_b_type) {
				if (!_b_docx_selected && !_b_dwg_selected && !_b_pst_selected && !_b_txt_selected && !_b_xlsx_selected) {
					MessageBoxA(hWnd, "No search mask selected", "File Coder", MB_OK);
				}
				else {
					try {
						txt = 0; pst = 0; dwg = 0; xlsx = 0; docx = 0;
						std::string message = "Finish Encrypting all ";
						if (_b_docx_selected) {
							if (_b_dwg_selected && _b_pst_selected && _b_txt_selected && _b_xlsx_selected) {
								message.append("DOCX, ");
							}
							else {
								message.append("DOCX ");
							}
						}
						if (_b_xlsx_selected) {
							if (_b_dwg_selected && _b_pst_selected && _b_txt_selected && _b_docx_selected) {
								message.append("XLSX, ");
							}
							else {
								message.append("XLSX ");
							}
						}
						if (_b_txt_selected) {
							if (_b_dwg_selected && _b_pst_selected && _b_docx_selected && _b_xlsx_selected) {
								message.append("TXT, ");
							}
							else {
								message.append("TXT ");
							}
						}
						if (_b_pst_selected) {
							if (_b_dwg_selected && _b_docx_selected && _b_txt_selected && _b_xlsx_selected) {
								message.append("PST, ");
							}
							else {
								message.append("PST ");
							}
						}
						if (_b_dwg_selected) {
							if (_b_docx_selected && _b_pst_selected && _b_txt_selected && _b_xlsx_selected) {
								message.append("DWG, ");
							}
							else {
								message.append("DWG ");
							}
						}
						message.append("files");
						HANDLE ReadThread = CreateThread(NULL, 0, SearchEngine, NULL, 0, 0);
						CloseHandle(ReadThread);
						MessageBoxA(0, message.c_str(), "INFO", MB_OK | MB_ICONINFORMATION);
					}
					catch (int e) {

					}
				}
			}
			else {
				HANDLE ReadThread = CreateThread(NULL, 0, SearchEngine, NULL, 0, 0);
				CloseHandle(ReadThread);
				MessageBox(0, L"Finish Decrypting all *.encr files", L"INFO", MB_OK | MB_ICONINFORMATION);
			}
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
	CreateWindow(L"button", L"Start process", WS_VISIBLE | WS_CHILD, 600, 130, 100, 50, hWnd,(HMENU)onSingleProcessClicked, NULL, NULL);
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
	CreateWindow(L"button", L"Start process", WS_VISIBLE | WS_CHILD, 600, 330, 100, 50, hWnd, (HMENU)onDriveProcessClicked, NULL, NULL);

}

void SearchFiles(HWND hWnd, LPWSTR path)
{
	WIN32_FIND_DATA wfd = { 0 };
	SetCurrentDirectory(path);
	HANDLE search = FindFirstFile(L"*", &wfd);
	if (search == INVALID_HANDLE_VALUE) {
		return ;
	}
	do {
		LPWSTR strTmp = (LPWSTR)calloc(MAX_PATH + 1, sizeof(WCHAR));
		GetCurrentDirectory(MAX_PATH, strTmp);
		wcscat_s(strTmp, MAX_PATH, L"\\");
		wcscat_s(strTmp, MAX_PATH, wfd.cFileName);
		LPWSTR strTmp_ = (LPWSTR)calloc(wcslen(strTmp) + 1, sizeof(WCHAR));
		wcscpy_s(strTmp_, wcslen(strTmp) + 1, strTmp);
		if (wcscmp(wfd.cFileName, L".") && wcscmp(wfd.cFileName, L"..")) {
			wcscat_s(strTmp, MAX_PATH, L"\t\t\t");
			if (((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) && (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT))) {
				SearchFiles(hWnd, strTmp_);
				SetCurrentDirectory(path);
			}
			else {
				std::wstring ws = wfd.cFileName;
				std::string tmpString(ws.begin(),ws.end());
				bool tmpBool = false;
				if (_b_type) {
					if (tmpString.find(".encr") == std::string::npos) {
						if (_b_docx_selected && (tmpString.find(".docx") != std::string::npos)) {
							tmpBool = true;
							Encode(wfd.cFileName);
							docx++;
						}
						else if (_b_xlsx_selected && !tmpBool && (tmpString.find(".xlsx") != std::string::npos)) {
							tmpBool = true;
							Encode(wfd.cFileName);
							xlsx++;
						}
						else if (_b_txt_selected && !tmpBool && (tmpString.find(".txt") != std::string::npos)) {
							tmpBool = true;
							Encode(wfd.cFileName);
							txt++;
						}
						else if (_b_pst_selected && !tmpBool && (tmpString.find(".pst") != std::string::npos)) {
							tmpBool = true;
							Encode(wfd.cFileName);
							pst++;
						}
						else if ((tmpString.find(".dwg") != std::string::npos) && _b_dwg_selected && !tmpBool) {
							tmpBool = true;
							Encode(wfd.cFileName);
							dwg++;
						}
						tmpBool = false;
					}
				}
				else if(!_b_type) {
					if ((tmpString.find(".encr") != std::string::npos)) {
						Decode(wfd.cFileName);
					}
				}
			}

		}


	} while (FindNextFile(search,&wfd));


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

void singleFileProcess(LPWSTR fileName)
{
	if (_b_type) {
		Encode(fileName);
	}
	else {
		Decode(fileName);
	}
}


bool Encode(LPWSTR fileName)
{
	int length;
	DWORD ByteRet;
	Blowfish blowfish;
	unsigned char key[] = CRIPT_KEY;
	blowfish.SetKey(key, sizeof(key));
	std::wstring ws (fileName);
	std::string _s_fileName(ws.begin(), ws.end());
	std::string tmpString(ws.begin(), ws.end());
	tmpString.append(".encr");
	std::ifstream inFile(_s_fileName, std::ios::binary);
	std::ofstream outFile(tmpString, std::ios::binary);
	inFile.seekg(0, std::ios::end);
	length = inFile.tellg();
	char* buf = new char[length + 1]; 
	inFile.seekg(0, std::ios::beg);
	inFile.read(buf, length);
	char* outBuf = new char[length + 1];
	blowfish.Encrypt((unsigned char*)outBuf, (unsigned char*)buf, length);
	outFile.write(outBuf, length);
	inFile.close();
	outFile.close();
	remove(_s_fileName.c_str());
	delete[] buf;
	delete[] outBuf;
	return true;
}

bool Decode(LPWSTR fileName)
{
	int length;
	DWORD ByteRet;
	Blowfish blowfish;
	unsigned char key[] = CRIPT_KEY;
	blowfish.SetKey(key, sizeof(key));
	std::wstring ws(fileName);
	std::string _s_fileName(ws.begin(), ws.end());
	std::string tmpString(ws.begin(), ws.end());
	int index;
	index = tmpString.find(".encr");
	tmpString.erase(index);
	std::ifstream inFile(_s_fileName, std::ios::binary);
	std::ofstream outFile(tmpString, std::ios::binary);
	inFile.seekg(0, std::ios::end);
	length = inFile.tellg();
	char* buf = new char[length + 1];
	inFile.seekg(0, std::ios::beg);
	inFile.read(buf, length);
	char* outBuf = new char[length + 1];
	blowfish.Decrypt((unsigned char*)outBuf, (unsigned char*)buf, length);
	outFile.write(outBuf, length);
	inFile.close();
	outFile.close();
	remove(_s_fileName.c_str());
	delete[] buf;
	delete[] outBuf;
	return true;
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
	SearchFiles(NULL, (LPWSTR)strText);
	ExitThread(0);
}