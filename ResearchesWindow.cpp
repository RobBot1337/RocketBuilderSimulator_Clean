#include "ResearchesWindow.h"
#include "MainWindow.h"
#include "HullsWindow.h"
#include "FuelTanksWindow.h"
#include "EnginesWindow.h"
#include "Config.h"
#include <windows.h>
#include <mmsystem.h>

// CALLBACK ФУНКЦИИ
void ResearchesWindow::research_hulls_cb(Fl_Widget* w, void* data) {
    ResearchesWindow* resMainWin = (ResearchesWindow*)data;
    resMainWin->open_research_hulls_window();
}

void ResearchesWindow::research_fuel_tanks_cb(Fl_Widget* w, void* data) {
    ResearchesWindow* resMainWin = (ResearchesWindow*)data;
    resMainWin->open_research_fuel_tanks_window();
}

void ResearchesWindow::research_engines_cb(Fl_Widget* w, void* data) {
    ResearchesWindow* resMainWin = (ResearchesWindow*)data;
    resMainWin->open_research_engines_window();
}

void ResearchesWindow::back_cb(Fl_Widget* w, void* data) {
    ResearchesWindow* researchesWin = (ResearchesWindow*)data;
    researchesWin->return_to_main();
}

ResearchesWindow::ResearchesWindow(MainWindow* mainWin) : 
    mainWindow(mainWin),
    bg(nullptr),
    arrow(nullptr),
    research_engine_icon(nullptr),
    research_hull_icon(nullptr),
    research_tank_icon(nullptr)
{
    window = new Fl_Window(1440, 820, "Исследования");
    window->position(10, 10);

    Config& config = Config::getInstance();
    
    // Загружаем изображения как члены класса
    bg = new Fl_PNG_Image(config.getPicturePath("Небо.png").c_str());
    arrow = new Fl_PNG_Image(config.getPicturePath("Cтрелка.png").c_str());
    research_engine_icon = new Fl_PNG_Image(config.getPicturePath("Двигатель1.png").c_str());
    research_hull_icon = new Fl_PNG_Image(config.getPicturePath("Корпус1.png").c_str());
    research_tank_icon = new Fl_PNG_Image(config.getPicturePath("Топливный1.png").c_str());

    background = new Fl_Box(0, 0, 1440, 820);
    background->image(bg);

    back_Button = new PictureButton(0, 0, 96, 96, arrow);
    back_Button->getButton()->callback(back_cb, this);

    // ВДОЛЬ ГОРИЗОНТАЛЬНОЙ ЛИНИИ
    Text hulls_title(150, 300, 350, 60, 20, "Исследовать корпуса");
    research_hulls_Button = new PictureButton(275, 380, 96, 96, research_hull_icon);
    research_hulls_Button->getButton()->callback(research_hulls_cb, this);
    research_hulls_Button->getButton()->tooltip("Исследовать различные корпуса для ракет");

    Text fuel_tanks_title(550, 300, 350, 60, 20, "Исследовать топливные баки");
    research_fuel_tanks_Button = new PictureButton(675, 380, 96, 96, research_tank_icon);
    research_fuel_tanks_Button->getButton()->callback(research_fuel_tanks_cb, this);
    research_fuel_tanks_Button->getButton()->tooltip("Исследовать различные топливные баки для ракет");

    Text engines_title(950, 300, 350, 60, 20, "Исследовать двигатели");
    research_engines_Button = new PictureButton(1075, 380, 96, 96, research_engine_icon);
    research_engines_Button->getButton()->callback(research_engines_cb, this);
    research_engines_Button->getButton()->tooltip("Исследовать различные двигатели для ракет");
}

ResearchesWindow::~ResearchesWindow() {
    // Очищаем ресурсы
    delete window;
    delete bg;
    delete arrow;
    delete research_engine_icon;
    delete research_hull_icon;
    delete research_tank_icon;
    delete back_Button;
    delete research_hulls_Button;
    delete research_fuel_tanks_Button;
    delete research_engines_Button;
    delete background;
}

void ResearchesWindow::show() {
    window->show();
}

void ResearchesWindow::hide() {
    window->hide();
}

void ResearchesWindow::return_to_main() {
    if(mainWindow) {
        mainWindow->show();
    }
    this->hide();
}

void ResearchesWindow::open_research_hulls_window() {
    HullsWindow* hullsWin = new HullsWindow(this);
    hullsWin->show();
    this->hide();
}

void ResearchesWindow::open_research_fuel_tanks_window() {
    FuelTanksWindow* tanksWin = new FuelTanksWindow(this);
    tanksWin->show();
    this->hide();
}

void ResearchesWindow::open_research_engines_window() {
    EnginesWindow* engWin = new EnginesWindow(this);
    engWin->show();
    this->hide();
}