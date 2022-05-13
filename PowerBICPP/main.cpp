#include <cstdio>
#include <Windows.h>
#include <WinBase.h>
#include <tlhelp32.h>
#include <stdio.h> 
#include <direct.h>
#include <string>
#include "Clicker.h"

#pragma comment(lib, "user32")
using namespace std;
HWND WinHwnd = NULL;

BOOL __stdcall EnumWindowsCallback(HWND hwnd, LPARAM lParam) {

    DWORD proc;
    GetWindowThreadProcessId(hwnd, &proc);
        if (proc==lParam) {

            WinHwnd = hwnd;
            return FALSE;

        }
        return TRUE;
}

bool getHandle(char* proc) {

    bool r = false;
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (_stricmp(entry.szExeFile, proc) == 0)
            {
                EnumWindows(EnumWindowsCallback,entry.th32ProcessID);
                r = true;
                break;

                //CloseHandle(hProcess);
            }
        }
    }

    CloseHandle(snapshot);
    return r;

}

string GetINI(char *txt)
{
    std::string tmp(txt);
    tmp.append("\\PowerBI.ini");
    return tmp;
}

int e_exit(const char *txt) {
    printf("%s\n", txt);
    system("pause");
    return 0;
}

int main() {

    char current_work_dir[FILENAME_MAX];

    TCHAR browserProcess[32];
    TCHAR WheelRoll[8];
    TCHAR sleep[8];
    //TCHAR sleepUpdate[8];
    TCHAR drawDelay[8];
    TCHAR UpdateButtonX[8];
    TCHAR UpdateButtonY[8];
    TCHAR FilterMainButtonX[8];
    TCHAR FilterMainButtonY[8];
    TCHAR FilterButtonX[8];
    TCHAR FilterButtonY[8];
    TCHAR FilterListX[8];
    TCHAR FilterListY[8];
    TCHAR filterWheelRoll[8];

    _getcwd(current_work_dir, sizeof(current_work_dir));

    string ini = GetINI(current_work_dir);
    //string ini = "C:\\exe\\PowerBI.ini";

    if (GetFileAttributes(ini.c_str()) == INVALID_FILE_ATTRIBUTES) {
        return e_exit("PowerBI.ini not found!");
    }

    if (GetPrivateProfileString(LPCTSTR("MainSettings"), LPCTSTR("browserExeProcess"), LPCTSTR(""), browserProcess, 32, ini.c_str()) == 0) 
        return e_exit("INI attribute browserExeProcess in MainSettings not found!");

    if (GetPrivateProfileString(LPCTSTR("MainSettings"), LPCTSTR("mouseWheelRoll"), LPCTSTR(""), WheelRoll, 8, ini.c_str()) == 0)
        return e_exit("INI attribute mouseWheelRoll in MainSettings not found!");

    if (GetPrivateProfileString(LPCTSTR("MainSettings"), LPCTSTR("SleepTime"), LPCTSTR(""), sleep, 8, ini.c_str()) == 0)
        return e_exit("INI attribute SleepTime in MainSettings not found!");

    //if (GetPrivateProfileString(LPCTSTR("MainSettings"), LPCTSTR("SleepToUpdateTime"), LPCTSTR(""), sleepUpdate, 8, ini.c_str()) == 0)
        //return e_exit("INI attribute SleepToUpdateTime in MainSettings not found!");

    if (GetPrivateProfileString(LPCTSTR("MainSettings"), LPCTSTR("DrawDelayTime"), LPCTSTR(""), drawDelay, 8, ini.c_str()) == 0)
        return e_exit("INI attribute DrawDelayTime in MainSettings not found!");

    if (GetPrivateProfileString(LPCTSTR("ClickerSettings"), LPCTSTR("UpdateButtonCursorPosX"), LPCTSTR(""), UpdateButtonX, 8, ini.c_str()) == 0)
        return e_exit("INI attribute UpdateButtonCursorPosX not found!");

    if (GetPrivateProfileString(LPCTSTR("ClickerSettings"), LPCTSTR("UpdateButtonCursorPosY"), LPCTSTR(""), UpdateButtonY, 8, ini.c_str()) == 0)
        return e_exit("INI attribute UpdateButtonCursorPosY in ClickerSettings not found!");

    if (GetPrivateProfileString(LPCTSTR("ClickerSettings"), LPCTSTR("FilterMainButtonCursorPosX"), LPCTSTR(""), FilterMainButtonX, 8, ini.c_str()) == 0)
        return e_exit("INI attribute FilterMainButtonCursorPosX in ClickerSettings not found!");

    if (GetPrivateProfileString(LPCTSTR("ClickerSettings"), LPCTSTR("FilterMainButtonCursorPosY"), LPCTSTR(""), FilterMainButtonY, 8, ini.c_str()) == 0)
        return e_exit("INI attribute FilterMainButtonCursorPosY in ClickerSettings not found!");

    if (GetPrivateProfileString(LPCTSTR("ClickerSettings"), LPCTSTR("FilterButtonCursorPosX"), LPCTSTR(""), FilterButtonX, 8, ini.c_str()) == 0)
        return e_exit("INI attribute FilterButtonCursorPosX in ClickerSettings not found!");

    if (GetPrivateProfileString(LPCTSTR("ClickerSettings"), LPCTSTR("FilterButtonCursorPosY"), LPCTSTR(""), FilterButtonY, 8, ini.c_str()) == 0)
        return e_exit("INI attribute FilterButtonCursorPosY in ClickerSettings not found!");

    if (GetPrivateProfileString(LPCTSTR("ClickerSettings"), LPCTSTR("FilterListCursorPosX"), LPCTSTR(""), FilterListX, 8, ini.c_str()) == 0)
        return e_exit("INI attribute FilterListCursorPosX in ClickerSettings not found!");

    if (GetPrivateProfileString(LPCTSTR("ClickerSettings"), LPCTSTR("FilterListCursorPosY"), LPCTSTR(""), FilterListY, 8, ini.c_str()) == 0)
        return e_exit("INI attribute FilterListCursorPosY in ClickerSettings not found!");

    if (GetPrivateProfileString(LPCTSTR("ClickerSettings"), LPCTSTR("mouseWheelRollFilter"), LPCTSTR(""), filterWheelRoll, 8, ini.c_str()) == 0)
        return e_exit("INI attribute mouseWheelRollFilter in ClickerSettings not found!");

    if (not getHandle(browserProcess)) {
        printf("%s%s%s\n", "Process browser ", browserProcess, " not found!");
        system("pause");
        return 0;
    }

    if (WinHwnd != NULL) {

        SetForegroundWindow(WinHwnd);
        SetActiveWindow(WinHwnd);

        Clicker Clicker;

        Clicker.kButtonClick(VK_F11, KEYEVENTF_KEYUP);
        Sleep(strtol(drawDelay, NULL, 10));
        Clicker.SetCursorPosition(strtol(FilterMainButtonX, NULL, 10), strtol(FilterMainButtonY, NULL, 10));
        Sleep(strtol(drawDelay, NULL, 10));
        Clicker.mButtonClick(MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP);
        Sleep(strtol(drawDelay, NULL, 10));
        Clicker.SetCursorPosition(strtol(FilterButtonX, NULL, 10), strtol(FilterButtonY, NULL, 10));
        Sleep(strtol(drawDelay, NULL, 10));
        Clicker.mButtonClick(MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP);
        Sleep(strtol(drawDelay, NULL, 10));
        Clicker.SetCursorPosition(strtol(FilterListX, NULL, 10), strtol(FilterListY, NULL, 10));
        Sleep(strtol(drawDelay, NULL, 10));
        Clicker.mWheelRoll(filterWheelRoll);
        Sleep(strtol(drawDelay, NULL, 10));
        Clicker.mButtonClick(MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP);
        Sleep(strtol(drawDelay, NULL, 10));
        Clicker.SetCursorPosition(strtol(FilterMainButtonX, NULL, 10), strtol(FilterMainButtonY, NULL, 10));
        Sleep(strtol(drawDelay, NULL, 10));
        Clicker.mButtonClick(MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP);
        Sleep(strtol(drawDelay, NULL, 10));
        Clicker.SetCursorPosition(strtol(UpdateButtonX, NULL, 10), strtol(UpdateButtonY, NULL, 10)+200);
        Clicker.mWheelRoll(WheelRoll);
        Sleep(strtol(drawDelay, NULL, 10));

        SecureZeroMemory(FilterMainButtonX, sizeof(FilterMainButtonX));
        SecureZeroMemory(FilterMainButtonY, sizeof(FilterMainButtonY));
        SecureZeroMemory(filterWheelRoll, sizeof(filterWheelRoll));
        SecureZeroMemory(FilterListX, sizeof(FilterListX));
        SecureZeroMemory(FilterListY, sizeof(FilterListY));
        SecureZeroMemory(FilterButtonY, sizeof(FilterButtonY));
        SecureZeroMemory(FilterButtonX, sizeof(FilterButtonX));
        SecureZeroMemory(&ini, sizeof(ini));
        SecureZeroMemory(current_work_dir, sizeof(current_work_dir));
        SecureZeroMemory(browserProcess, sizeof(browserProcess));

        while (true) {

            Clicker.SetCursorPosition(strtol(UpdateButtonX, NULL, 10), strtol(UpdateButtonY, NULL, 10));
            Sleep(strtol(drawDelay, NULL, 10));
            Clicker.mButtonClick(MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP);

            Sleep(strtol(sleep, NULL, 10));

        }

        return 0;

    }

    printf("%s\n", "Browser window not found!");
    system("pause");
    return 0;
}