#pragma once
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "blowfish.h"
#include <malloc.h>
#include <ios>
#include <fstream>

#define OnSettingsClicked		1
#define OnHelpMenuClicked		2
#define OnExitSoftwareClicked	3
#define onEncryptTypeClicked	4
#define OnDecryptTypeClicked	5
#define onSelectClicked			6
#define onSingleProcessClicked	7
#define onRefreshClicked		8
#define onConfirmClicked		9
#define onDriveProcessClicked	10
#define ondocxSelect			11
#define	onxlsxSelect			12
#define ontxtSelect				13
#define ondwgSelect				14
#define	onpstSelect				15
#define CRIPT_KEY "115792089237316195423570985008687907853269984665640564039457583884239776304168"

#define SIZE_BLOCK (1<<20)
HWND GroupBox;
HWND hLineEdit;
HWND passLine;
HWND passConfLine;
HWND passLine1;
HWND passConfLine1;
HANDLE HFileSearchHandle;
WIN32_FIND_DATA FileFindData;
OPENFILENAME ofn;

volatile bool _b_docx_selected = false;
volatile bool _b_xlsx_selected = false;
volatile bool _b_txt_selected = false;
volatile bool _b_dwg_selected = false;
volatile bool _b_pst_selected = false;
volatile bool _b_type = false;
wchar_t filename[MAX_PATH] = {0};

void initFileHandler(HWND hWnd);
DWORD WINAPI SearchEngine(LPVOID lpParameter);
LRESULT CALLBACK SoftMainProcedure(HWND hWnd, UINT uMsg, WPARAM wparam, LPARAM lparam);
WNDCLASS MainWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
DWORD WINAPI EncodeThread(LPVOID lpParameter);
DWORD WINAPI DecodeThread(LPVOID lpParameter);
void setFileName(wchar_t* p);



void setOpenFileParams(HWND hWnd);
volatile WCHAR strText[255];
void MainWindowAddMenus(HWND hWnd);
void MainWidowDrawWidgets(HWND hWnd);
void DrawSingleFileList(HWND hWnd);
void DrawDriveList(HWND hWnd);
void SearchFiles(HWND hWnd,LPWSTR path);
void refreshDiskLabels();
void singleFileProcess(LPWSTR fileName);
void LoadFile(HWND hWnd);

bool Encode(LPWSTR fileName);
bool Decode(LPWSTR fileName);
bool SetDocx();
bool SetXlsx();
bool SetTxt();
bool SetPst();
bool setDwg();

enum FileType {
	DocX = 1,
	Xlsx,
	Txt,
	Pst,
	Dwg
};
enum Type {
	EncrypionType = 0,
	DecryptionType
};

volatile WCHAR _c_txt[MAX_PATH];
volatile int txt = 0;
volatile int docx = 0;
volatile int xlsx = 0;
volatile int dwg = 0;
volatile int pst = 0;
volatile int idx = 0;

volatile std::string value;