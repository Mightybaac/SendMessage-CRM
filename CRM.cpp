#include <iostream>
#include <string>
#include <Windows.h>

const char* CRM_APPLICATION = "CRM_Application";
const char* OTHER_APPLICATION = "Other_Application";

void SendTextToWindow(const char* windowName, const std::string& text) {
    HWND hwnd = FindWindow(NULL, windowName);
    if (hwnd != NULL) {
        SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)text.c_str());
    } else {
        std::cout << windowName << " application not found." << std::endl;
    }
}

bool CopyTextToClipboard(const std::string& text) {
    if (OpenClipboard(NULL)) {
        HGLOBAL hglbCopy;
        char* buffer;
        EmptyClipboard();
        hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (text.size() + 1) * sizeof(char));
        buffer = (char*)GlobalLock(hglbCopy);
        strcpy_s(buffer, text.size() + 1, text.c_str());
        GlobalUnlock(hglbCopy);
        SetClipboardData(CF_UNICODETEXT, hglbCopy);
        CloseClipboard();
        return true;
    } else {
        std::cout << "Failed to open clipboard" << std::endl;
        return false;
    }
}

int main() {
    std::string input;
    bool keepRunning = true;
    while (keepRunning) {
        std::cout << "Enter text to be written in the CRM and copied to another application (Enter 'q' to quit): ";
        std::getline(std::cin, input);

        if (input == "q") {
            keepRunning = false;
            continue;
        }

        SendTextToWindow(CRM_APPLICATION, input);

        if (!CopyTextToClipboard(input)) {
            continue;
        }

        SendTextToWindow(OTHER_APPLICATION, input);
    }

    return 0;
}
