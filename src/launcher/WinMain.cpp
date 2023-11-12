#include <iostream>

#define REFLECTIVEDLLINJECTION_VIA_LOADREMOTELIBRARYR
#include "LoadLibraryR.h"

#define printf_r(a) (-!!printf(a))

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    PROCESS_INFORMATION pi{};
    STARTUPINFOA si{};

    if (!CreateProcessA("Defiance.exe", lpCmdLine, nullptr, nullptr, false, CREATE_SUSPENDED, nullptr, nullptr, &si, &pi)) {
        return printf_r("e: failed to create the process.\n");
    }

    HANDLE hFile = CreateFileA("libmod.dll", GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile == INVALID_HANDLE_VALUE)
        return printf_r("failed to open the dll\n");

    DWORD dwLength = GetFileSize(hFile, nullptr);
    if (dwLength == INVALID_FILE_SIZE || dwLength == 0)
        return printf_r("failed to get the dll size\n");

    LPVOID lpBuffer = HeapAlloc(GetProcessHeap(), 0, dwLength);
    if (!lpBuffer)
        return printf_r("failed to allocate the dll\n");

    DWORD dwBytesRead;
    if (!ReadFile(hFile, lpBuffer, dwLength, &dwBytesRead, nullptr))
        return printf_r("failed to read the dll\n");

    HANDLE hToken;
    TOKEN_PRIVILEGES privileges{0};
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        privileges.PrivilegeCount = 1;
        privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        if (LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &privileges.Privileges[0].Luid))
            AdjustTokenPrivileges(hToken, FALSE, &privileges, 0, nullptr, nullptr);

        CloseHandle(hToken);
    }

    HANDLE hModule = LoadRemoteLibraryR(pi.hProcess, lpBuffer, dwLength, nullptr);
    if (!hModule)
        return printf_r("failed to load libmod.dll\n");

    WaitForSingleObject(hModule, -1);

    ResumeThread(pi.hThread);

    HeapFree(GetProcessHeap(), 0, lpBuffer);

    if (!CloseHandle(pi.hProcess))
        return printf_r("could not release process handle.\n");

    return 0;
}
