#include "CraftsWindow.h"
#include "CraftsEngineWindow.h"
#include "CraftsHullWindow.h"
#include "CraftsRocketWindow.h"
#include "CraftsFuelTankWindow.h"
#include "MainWindow.h" 
#include "Config.h"  // Добавляем Config
#include <windows.h>
#include <mmsystem.h>

static Fl_PNG_Image* static_bg = nullptr;
static Fl_PNG_Image* static_arrow = nullptr;
static Fl_PNG_Image* static_engine_icon = nullptr;
static Fl_PNG_Image* static_hull_icon = nullptr;
static Fl_PNG_Image* static_fuel_tank_icon = nullptr;
static Fl_PNG_Image* static_rocket_icon = nullptr;

// CALLBACK ФУНКЦИИ
void CraftsWindow::craft_engine_cb(Fl_Widget* w, void* data) {
    CraftsWindow* craftsWin = (CraftsWindow*)data;
    craftsWin->open_craft_engine_window();
}

void CraftsWindow::craft_hull_cb(Fl_Widget* w, void* data) {
    CraftsWindow* craftsWin = (CraftsWindow*)data;
    craftsWin->open_craft_hull_window();
}

void CraftsWindow::craft_fuel_tank_cb(Fl_Widget* w, void* data) {
    CraftsWindow* craftsWin = (CraftsWindow*)data;
    craftsWin->open_craft_fuel_tank_window();
}

void CraftsWindow::craft_rocket_cb(Fl_Widget* w, void* data) {
    CraftsWindow* craftsWin = (CraftsWindow*)data;
    craftsWin->open_craft_rocket_window();
}

CraftsWindow::CraftsWindow(MainWindow* mainWin){
    mainWindow = mainWin;

    window = new Fl_Window(1440, 820, "Крафт");
    window->position(10, 10);

    Config& config = Config::getInstance();
    
    // ЗАГРУЖАЕМ ИЗОБРАЖЕНИЯ С ИСПОЛЬЗОВАНИЕМ КОНФИГА
    if (!static_bg) {
        std::string bgPath = config.getPicturePath("Небо.png");
        std::string arrowPath = config.getPicturePath("Cтрелка.png");
        std::string enginePath = config.getPicturePath("Двигатель1.png");
        std::string hullPath = config.getPicturePath("Корпус1.png");
        std::string fuelTankPath = config.getPicturePath("Топливный1.png");
        std::string rocketPath = config.getPicturePath("Ракета2.png");
        
        static_bg = new Fl_PNG_Image(bgPath.c_str());
        static_arrow = new Fl_PNG_Image(arrowPath.c_str());
        static_engine_icon = new Fl_PNG_Image(enginePath.c_str());
        static_hull_icon = new Fl_PNG_Image(hullPath.c_str());
        static_fuel_tank_icon = new Fl_PNG_Image(fuelTankPath.c_str());
        static_rocket_icon = new Fl_PNG_Image(rocketPath.c_str());
    }

    bg = static_bg;
    background = new Fl_Box(0, 0, 1440, 820);
    background->image(bg);

    back_Button = new PictureButton(0, 0, 96, 96, static_arrow);
    back_Button->getButton()->callback(back_cb, this);

    // РАСПОЛОЖЕНИЕ КНОПОК С ПРАВИЛЬНОЙ ЦЕНТРОВКОЙ
    // ДВИГАТЕЛИ
    Text engine_title(120, 300, 300, 60, 20, "Крафт двигателей");
    craft_engine_button = new PictureButton(230, 380, 96, 96, static_engine_icon);
    craft_engine_button->getButton()->callback(craft_engine_cb, this);
    craft_engine_button->getButton()->tooltip("Открыть окно крафта двигателей");

    // КОРПУСА
    Text hull_title(420, 300, 300, 60, 20, "Крафт корпусов");
    craft_hull_button = new PictureButton(530, 380, 96, 96, static_hull_icon);
    craft_hull_button->getButton()->callback(craft_hull_cb, this);
    craft_hull_button->getButton()->tooltip("Открыть окно крафта корпусов");

    // ТОПЛИВНЫЕ БАКИ
    Text fuel_tank_title(720, 300, 300, 60, 20, "Крафт топливных баков");
    craft_fuel_tank_button = new PictureButton(830, 380, 96, 96, static_fuel_tank_icon);
    craft_fuel_tank_button->getButton()->callback(craft_fuel_tank_cb, this);
    craft_fuel_tank_button->getButton()->tooltip("Открыть окно крафта топливных баков");

    // РАКЕТЫ
    Text rocket_title(1020, 300, 300, 60, 20, "Крафт ракет");
    craft_rocket_button = new PictureButton(1130, 380, 96, 96, static_rocket_icon);
    craft_rocket_button->getButton()->callback(craft_rocket_cb, this);
    craft_rocket_button->getButton()->tooltip("Открыть окно сборки ракет");
}

void CraftsWindow::show() {
    window->show();
}

void CraftsWindow::hide() {
    window->hide();
}

void CraftsWindow::back_cb(Fl_Widget* w, void* data) {
    CraftsWindow* craftsWin = (CraftsWindow*)data;
    craftsWin->return_to_main();
}

void CraftsWindow::return_to_main() {
    mainWindow->show();
    this->hide();
}

// ФУНКЦИИ ДЛЯ ОТКРЫТИЯ ОКОН КРАФТА
void CraftsWindow::open_craft_engine_window() {
    CraftsEngineWindow* engWin = new CraftsEngineWindow(this);
    engWin->show();
    this->hide();
}

void CraftsWindow::open_craft_hull_window() {
    CraftsHullWindow* hullWin = new CraftsHullWindow(this);
    hullWin->show();
    this->hide();
}

void CraftsWindow::open_craft_fuel_tank_window() {
    CraftsFuelTankWindow* tankWin = new CraftsFuelTankWindow(this);
    tankWin->show();
    this->hide();
}

void CraftsWindow::open_craft_rocket_window() {
    CraftsRocketWindow* rocketWin = new CraftsRocketWindow(this);
    rocketWin->show();
    this->hide();
}