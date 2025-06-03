#include <iostream>
#include <Windows.h>
#include <thread>
#include <atomic>

std::atomic<bool> clicking = false;

void ClickMouseButton() {
    INPUT input[2];

    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    input[0].mi.dx = 0;
    input[0].mi.dy = 0;
    input[0].mi.mouseData = 0;
    input[0].mi.time = 0;
    input[0].mi.dwExtraInfo = 0;

    input[1].type = INPUT_MOUSE;
    input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
    input[1].mi.dx = 0;
    input[1].mi.dy = 0;
    input[1].mi.mouseData = 0;
    input[1].mi.time = 0;
    input[1].mi.dwExtraInfo = 0;

    SendInput(2, input, sizeof(INPUT));
}

void AutoClickerLoop() {
    std::cout << "\n[Clicker]: Clicking loop started. Press '0' to stop." << std::endl;
    
    while (clicking.load()) {
        ClickMouseButton();
    }
    std::cout << "[Clicker]: Clicking loop stopped. Press '1' to start." << std::endl;
}

int main() {
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "  Ultra-Fast AutoClicker (C++)" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "  Press '1' to START the clicker." << std::endl;
    std::cout << "  Press '0' to STOP the clicker." << std::endl;
    std::cout << "  Press Ctrl+C at any time to EXIT the program." << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    std::thread click_thread;

    while (true) {
        if (GetAsyncKeyState(0x31) & 0x8000) {
            if (!clicking.load()) {
                clicking.store(true);
                click_thread = std::thread(AutoClickerLoop);
                click_thread.detach();
                std::cout << "\n[Control]: AutoClicker STARTED. Press '0' to stop." << std::endl;
            }
        }
        
        if (GetAsyncKeyState(0x30) & 0x8000) {
            if (clicking.load()) {
                clicking.store(false);
                std::cout << "\n[Control]: AutoClicker STOPPED. Press '1' to start." << std::endl;
            }
        }
    }

    return 0;
}
