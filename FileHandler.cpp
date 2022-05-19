#include "FileHandler.h"

void FileHandler::SearchEngine(LPCWSTR Filter, LPCWSTR DriveLetter)
{
}

void FileHandler::setFileType(bool value, int type)
{
    switch (type)
    {
    case FileType::DocX:
        _b_docx_selected = value;
        break;
    case FileType::Xlsx:
        _b_xlsx_selected = value;
        break;
    case FileType::Txt:
        _b_txt_selected = value;
        break;
    case FileType::Pst:
        _b_pst_selected = value;
        break;
    case FileType::Dwg:
        _b_dwg_selected = value;
        break;
    default:
        break;
    }
}

bool FileHandler::SetFileCompressSize(uint32_t value)
{
    try {
        _u_compress_size = value;
        return true;
    }
    catch (int e) {
        return false;
    }
    return false;
}

void FileHandler::scanForFiles(LPCWSTR driveLetter)
{
    LPCWSTR xlsx_filter = L"*.xlsx";

    if (_b_xlsx_selected) {
        
    }
    if (_b_docx_selected) {
        docx_filter = "*.docx";
    }
    if (_b_txt_selected) {
        txt_filter = "*.txt";
    }
    if (_b_dwg_selected) {
        dwg_filter = "*.dwg";
    }
    if (_b_pst_selected) {
        pst_filter = "*.pst";
    }
    
   
}
