#include "MainWindow.h"
#include "PlanetsWindow.h"
#include "MinesWindowEarth.h"
#include "MinesWindowMoon.h"
#include "MinesWindowMars.h"
#include "RecourcesWindow.h" // ДОБАВЛЯЕМ
#include "Mines.h"
#include <windows.h>
#include <mmsystem.h>
#include <iostream>

// Функция для воспроизведения фоновой музыки
void playBackgroundMusic() {
    // Флаг SND_ASYNC - воспроизведение в фоне
    // Флаг SND_LOOP - зацикливание
    // Флаг SND_FILENAME - воспроизведение из файла
    PlaySound(TEXT("C:/Users/Zenbook/Desktop/Graphproject/Sounds/Music.wav"), 
              NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);
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