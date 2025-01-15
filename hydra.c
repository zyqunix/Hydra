#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define IDI_CUSTOM_ICON 101
#define IDI_CUSTOM_INFO 102

DWORD WINAPI MessageBoxThread(LPVOID lpParameter);

void CreateNewMessageBox() {
    CreateThread(NULL, 0, MessageBoxThread, NULL, 0, NULL);
    CreateThread(NULL, 0, MessageBoxThread, NULL, 0, NULL);
    // This will make 2 MessageBoxes, so if you close 1, 2 more will appear
}

DWORD WINAPI MessageBoxThread(LPVOID lparameter) {
    srand((unsigned int)time(NULL) ^ GetCurrentThreadId());
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    int x = rand() % (screenWidth - 300);
    int y = rand() % (screenHeight - 300);

    HWND hwnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW, "STATIC", "Cut 1 Head, and 2 more will appear", 
        WS_CAPTION | WS_VISIBLE | WS_SYSMENU,
        x, y, 300, 100,
        NULL, NULL, GetModuleHandle(NULL), NULL
    );

    HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_CUSTOM_ICON));
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

    int result = MessageBox(
        hwnd,
        "Cut 1 Head, and 2 more will appear",   // Message in the MessageBox
        "Hydra",                                // Title of the MessageBox
        MB_OK | MB_USERICON
    );

    if (result == IDOK) {
        CreateNewMessageBox();
    }

    return 0;
}

int main() {
    CreateNewMessageBox();
    while (1) Sleep(100);
    return 0;
}
