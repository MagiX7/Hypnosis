#include "FileDialog.h"

#include <Windows.h>
#include <commdlg.h>

namespace Hypnosis {
	std::string FileDialog::OpenFile(const char* filter)
	{
		OPENFILENAME file;
		char size[260] = {};
		ZeroMemory(&file, sizeof(OPENFILENAME));
		file.lStructSize = sizeof(OPENFILENAME);

		file.hwndOwner = GetActiveWindow();
		file.lpstrFile = size;
		file.nMaxFile = sizeof(file);
		file.lpstrFilter = filter;
		file.nFileExtension = (WORD)".png";
		file.nFilterIndex = 1;
		file.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetOpenFileName(&file))
		{
			return file.lpstrFile;
		}

		return std::string();
	}

	std::string FileDialog::SaveFile(const char* filter)
	{
		OPENFILENAME file;
		char size[260] = {};
		ZeroMemory(&file, sizeof(OPENFILENAME));
		file.lStructSize = sizeof(OPENFILENAME);

		file.hwndOwner = GetActiveWindow();
		file.lpstrFile = size;
		file.nMaxFile = sizeof(file);
		file.lpstrFilter = filter;
		file.nFileExtension = (WORD)".png";
		file.nFilterIndex = 1;
		file.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetSaveFileName(&file))
		{
			return file.lpstrFile;
		}

		return std::string();
	}

}