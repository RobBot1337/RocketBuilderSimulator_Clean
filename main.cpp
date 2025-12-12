#include "MainWindow.h"
#include "PlanetsWindow.h"
#include "MinesWindowEarth.h"
#include "MinesWindowMoon.h"
#include "MinesWindowMars.h"
#include "RecourcesWindow.h"
#include "Config.h"
#include "Mines.h"
#include <windows.h>
#include <mmsystem.h>
#include <iostream>

// Функция для воспроизведения фоновой музыки
#include "MainWindow.h"
#include "PlanetsWindow.h"
#include "MinesWindowEarth.h"
#include "MinesWindowMoon.h"
#include "MinesWindowMars.h"
#include "RecourcesWindow.h"
#include "Config.h"
#include "Mines.h"
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <fstream>

// Функция для воспроизведения фоновой музыки
void playBackgroundMusic() {
    // Пробуем несколько возможных путей
    const char* possiblePaths[] = {
        "Sounds/Music.wav",                    // Рядом с exe
        "../Sounds/Music.wav",                 // На уровень выше
        "../../Sounds/Music.wav",              // На 2 уровня выше
        "Music.wav",                           // Прямо в папке с exe      // В папке Resources
    };
    
    for (const char* path : possiblePaths) {
        std::ifstream testFile(path);
        if (testFile.good()) {
            testFile.close();
            std::cout << "Играю музыку из: " << path << std::endl;
            PlaySoundA(path, NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);
            return;
        }
    }
    
}

void stopBackgroundMusic() {
    PlaySound(NULL, NULL, 0); // Остановить музыку
}

// Функция для автоматического сбора ресурсов
void autoCollectResources(void* data) {
    // Собираем ресурсы с Земли
    iron += EarthMines["IronMine"].getRecources();
    coal += EarthMines["CoalMine"].getRecources();
    copper += EarthMines["CooperMine"].getRecources();
    aluminium += EarthMines["AluminiumMine"].getRecources();
    titanium += EarthMines["TitanMine"].getRecources();
    magnesium += EarthMines["MagnesiumMine"].getRecources();
    oil += EarthMines["OilPumping"].getRecources();
    
    // Собираем ресурсы с Луны
    iron += MoonMines["IronMine"].getRecources();
    nickel += MoonMines["NickelMine"].getRecources();
    titanium += MoonMines["TitanMine"].getRecources();
    aluminium += MoonMines["AluminiumMine"].getRecources();
    
    // Собираем ресурсы с Марса
    iron += MarsMines["IronMine"].getRecources();
    nickel += MarsMines["NickelMine"].getRecources();
    titanium += MarsMines["TitanMine"].getRecources();
    aluminium += MarsMines["AluminiumMine"].getRecources();
    cobalt += MarsMines["CobaltMine"].getRecources();
    
    // ОБНОВЛЯЕМ ОКНО РЕСУРСОВ ЕСЛИ ОНО ОТКРЫТО
    RecourcesWindow* currentWindow = RecourcesWindow::getCurrentWindow();
    if (currentWindow && currentWindow->isVisible()) {
        currentWindow->refreshResources();
    }
    
    // Перезапускаем таймер (каждую секунду)
    Fl::repeat_timeout(1.0, autoCollectResources);
}

int main() {
    // ЗАПУСКАЕМ ФОНОВУЮ МУЗЫКУ
    playBackgroundMusic();
    
    // Запускаем таймер автоматического сбора ресурсов
    Fl::add_timeout(1.0, autoCollectResources);
    
    MainWindow mainWindow;
    mainWindow.show();
    
    return Fl::run();
}