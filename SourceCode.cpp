#include <iostream>
#include <Windows.h>
#include <thread>
#include <atomic>
#include <chrono>

std::atomic<bool> clicking(false);
int clickDelay = 10;
int mouseButton = 1; 

void ClickMouseButton() {
    INPUT input[2] = { 0 };
    input[0].type = INPUT_MOUSE;
    input[1].type = INPUT_MOUSE;

    if (mouseButton == 1) {
        input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
    } else {
        input[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
        input[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    }

    SendInput(2, input, sizeof(INPUT));
}

void AutoClickerLoop() {
    while (clicking.load()) {
        ClickMouseButton();
        if (clickDelay > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(clickDelay));
        }
    }
}

int main() {
    setlocale(LC_ALL, "Turkish");

    std::cout << "==================================================" << std::endl;
    std::cout << "          HER KLAVYEYE UYUMLU CLICKER             " << std::endl;
    std::cout << "==================================================" << std::endl;
    
    std::cout << "Tus Secimi (1: SOL, 2: SAG): ";
    std::cin >> mouseButton;

    std::cout << "Gecikme (ms) [0 = Full Hiz]: ";
    std::cin >> clickDelay;

    std::cout << "\n--------------------------------------------------" << std::endl;
    std::cout << "  KONTROLLER (F Tuslari her klavyede vardir):" << std::endl;
    std::cout << "  [F6] -> BASLAT" << std::endl;
    std::cout << "  [F7] -> DURDUR" << std::endl;
    std::cout << "  [F10] -> PROGRAMI KAPAT (Cikis)" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    while (true) {
        // F6 ile Başlat
        if (GetAsyncKeyState(VK_F6) & 0x8000) {
            if (!clicking.load()) {
                clicking.store(true);
                std::thread(AutoClickerLoop).detach();
                std::cout << ">>> DURUM: CALISIYOR          \r" << std::flush;
            }
        }
        
        // F7 ile Durdur
        if (GetAsyncKeyState(VK_F7) & 0x8000) {
            if (clicking.load()) {
                clicking.store(false);
                std::cout << ">>> DURUM: DURDURULDU         \r" << std::flush;
            }
        }

        // F10 ile Çıkış (End yerine F10)
        if (GetAsyncKeyState(VK_F10) & 0x8000) {
            clicking.store(false);
            std::cout << "\n\nProgram sonlandirildi. Gule gule!" << std::endl;
            break;
        }
    }

    return 0;
}
