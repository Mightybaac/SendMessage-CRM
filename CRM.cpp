#include <iostream>
#include <string>
#include <Windows.h>

int main() {
    std::string input;
    std::cout << "Enter text to be written in the CRM and copied to another application: ";
    std::getline(std::cin, input);

    // Write the text to the CRM
    // Assume the CRM application is open and active
    // Replace "CRM_Application" with the actual name of the CRM application
    HWND crm = FindWindow(NULL, "CRM_Application");
    if (crm != NULL) {
        // Send the text to the CRM's input field
        SendMessage(crm, WM_SETTEXT, 0, (LPARAM)input.c_str());
    } else {
        std::cout << "CRM application not found." << std::endl;
    }

    // Copy the text to the clipboard
    // This will allow the text to be pasted in another application
    if (OpenClipboard(NULL)) {
        HGLOBAL hglbCopy;
        char* buffer;

        EmptyClipboard();
        hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (input.size() + 1) * sizeof(char));
        buffer = (char*)GlobalLock(hglbCopy);
        strcpy_s(buffer, input.size() + 1, input.c_str());
        GlobalUnlock(hglbCopy);
        SetClipboardData(CF_UNICODETEXT, hglbCopy);
        CloseClipboard();
    }
    else {
        std::cout << "Failed to open clipboard" << std::endl;
    }

    return 0;
}
