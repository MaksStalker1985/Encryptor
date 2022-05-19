#pragma once
#include <string>
#include <vector>
#include "blowfish.h"

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

HWND GroupBox;
HWND hLineEdit;
HWND passLine;
HWND passConfLine;
HWND passLine1;
HWND passConfLine1;

HANDLE HFileSearchHandle;
WIN32_FIND_DATA FileFindData;
HANDLE ReadThread;
int idx;

std::string value;

volatile bool _b_docx_selected = false;
volatile bool _b_xlsx_selected = false;
volatile bool _b_txt_selected = false;
volatile bool _b_dwg_selected = false;
volatile bool _b_pst_selected = false;
volatile bool _b_type = false;

int searchMaskQuantities = 0;

std::string txtMask = "txt";
std::string pstMask = "pst";
std::string xlsxMask = "xlsx";
std::string docxMask = "docs";
std::string dwgMask = "dwg";

std::vector<std::wstring> maskVector;

void initFileHandler();
DWORD WINAPI SearchEngine(LPVOID lpParameter);
LRESULT CALLBACK SoftMainProcedure(HWND hWnd, UINT uMsg, WPARAM wparam, LPARAM lparam);
WNDCLASS MainWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);

volatile TCHAR strText[255];
void MainWindowAddMenus(HWND hWnd);
void MainWidowDrawWidgets(HWND hWnd);
void DrawSingleFileList(HWND hWnd);
void DrawDriveList(HWND hWnd);
void SearchFiles();
void refreshDiskLabels();
void singleFileProcess();
void driveProcess();
void AddMask(std::string mask);
void RemoveMask(std::string mask);


bool SetDocx();
bool SetXlsx();
bool SetTxt();
bool SetPst();
bool setDwg();
bool type = false;

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