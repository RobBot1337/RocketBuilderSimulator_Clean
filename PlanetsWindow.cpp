#include "PlanetsWindow.h"
#include "MainWindow.h" 
#include <windows.h>
#include <mmsystem.h>

Fl_Box* Percent_Earth_colonization;
Fl_Box* Percent_Moon_colonization;
Fl_Box* Percent_Mars_colonization;

// Добавляем кнопки как глобальные переменные
Button* send_rocket_moon_btn = nullptr;
Button* send_rocket_mars_btn = nullptr;
Button* choose_moon_btn = nullptr;
Button* choose_mars_btn = nullptr;

// СТАТИЧЕСКИЕ ИЗОБРАЖЕНИЯ (загружаются один раз)
static Fl_PNG_Image* static_bg = nullptr;
static Fl_PNG_Image* static_arrow = nullptr;
static Fl_PNG_Image* static_earth_small = nullptr;
static Fl_PNG_Image* static_moon_small = nullptr;
static Fl_PNG_Image* static_mars_small = nullptr;

void SetEarth(Fl_Widget* widget, void* data){
    Player.setPlanet(&Earth);
    PlanetsWindow* planetsWin = (PlanetsWindow*)data;
    planetsWin->return_to_main();
}

void SetMoon(Fl_Widget* widget, void* data){
    if(Moon.getPercentColonization() != 0){
        Player.setPlanet(&Moon);
        PlanetsWindow* planetsWin = (PlanetsWindow*)data;
        planetsWin->return_to_main();
    }
}

void SetMars(Fl_Widget* widget, void* data){
    if(Mars.getPercentColonization() != 0){
        Player.setPlanet(&Mars);
        PlanetsWindow* planetsWin = (PlanetsWindow*)data;
        planetsWin->return_to_main();
    }
}

void Send_Rocket_Moon_cb(Fl_Widget* widget, void* data){
    if(Moon.getPercentColonization() != 100 && Player.getRocket() != nullptr && Player.getRocket()->getLevel() >= 1){
        double colonizationIncrease = Player.getRocket()->getPower() / Moon.getProtection();
        if(Moon.getPercentColonization() + colonizationIncrease >= 100){
            Moon.setPercentColonization(100);
        }
        else{
            Moon.setPercentColonization(Moon.getPercentColonization() + colonizationIncrease);
        }
        Player.setRocket(nullptr);
        
        // Обновляем интерфейс
        PlanetsWindow* win = (PlanetsWindow*)data;
        win->refreshAll();
        win->updateButtonsState();
    }
}

void Send_Rocket_Mars_cb(Fl_Widget* widget, void* data){
    if(Mars.getPercentColonization() != 100 && Player.getRocket() != nullptr && Player.getRocket()->getLevel() >= 2){
        double colonizationIncrease = Player.getRocket()->getPower() / Mars.getProtection();
        if(Mars.getPercentColonization() + colonizationIncrease >= 100){
            Mars.setPercentColonization(100);
        }
        else{
            Mars.setPercentColonization(Mars.getPercentColonization() + colonizationIncrease);
        }
        Player.setRocket(nullptr);
        
        // Обновляем интерфейс
        PlanetsWindow* win = (PlanetsWindow*)data;
        win->refreshAll();
        win->updateButtonsState();
    }
}

PlanetsWindow::PlanetsWindow(MainWindow* mainWin){
    mainWindow = mainWin;

    window = new Fl_Window(1440, 820, "Планеты");
    window->position(10, 10);

    // ЗАГРУЖАЕМ ИЗОБРАЖЕНИЯ ТОЛЬКО ПРИ ПЕРВОМ СОЗДАНИИ
    if (!static_bg) {
        static_bg = new Fl_PNG_Image("C:/Users/Zenbook/Desktop/Graphproject/Pictures/Небо.png");
        static_arrow = new Fl_PNG_Image("C:/Users/Zenbook/Desktop/Graphproject/Pictures/Cтрелка.png");
        static_earth_small = new Fl_PNG_Image(Earth.getPathToSmallPNG().c_str());
        static_moon_small = new Fl_PNG_Image(Moon.getPathToSmallPNG().c_str());
        static_mars_small = new Fl_PNG_Image(Mars.getPathToSmallPNG().c_str());
    }

    bg = static_bg;
    background = new Fl_Box(0, 0, 1440, 820);
    background->image(bg);

    // ИСПОЛЬЗУЕМ УЖЕ ЗАГРУЖЕННЫЕ ИЗОБРАЖЕНИЯ
    back_Button = new PictureButton(0, 0, 96, 96, static_arrow);
    back_Button->getButton()->callback(back_cb, this);
    
    // Картинки планет используем уже загруженные
    Fl_Box* earth_box = new Fl_Box(100, 100, 96, 96);
    earth_box->image(static_earth_small);
    
    Fl_Box* moon_box = new Fl_Box(100, 196, 96, 96);
    moon_box->image(static_moon_small);
    
    Fl_Box* mars_box = new Fl_Box(100, 292, 96, 96);
    mars_box->image(static_mars_small);

    Button choose_earth(196, 123, 200, 50, 20, "Выбрать Землю");
    choose_earth.getButton()->callback(SetEarth, this);
    
    // Сохраняем кнопки выбора для управления
    choose_moon_btn = new Button(196, 219, 200, 50, 20, "Выбрать Луну");
    choose_moon_btn->getButton()->callback(SetMoon, this);

    choose_mars_btn = new Button(196, 315, 200, 50, 20, "Выбрать Марс");
    choose_mars_btn->getButton()->callback(SetMars, this);

    Button send_rocket_earth(423, 123, 350, 50, 20, "Отправить ракету на Землю");
    send_rocket_earth.deactivate();

    // Сохраняем кнопки отправки ракет для управления
    send_rocket_moon_btn = new Button(423, 219, 350, 50, 20, "Отправить ракету на Луну");
    send_rocket_moon_btn->getButton()->callback(Send_Rocket_Moon_cb, this);

    send_rocket_mars_btn = new Button(423, 315, 350, 50, 20, "Отправить ракету на Марс");
    send_rocket_mars_btn->getButton()->callback(Send_Rocket_Mars_cb, this);

    Text percent_of_colonization_Earth(800, 123, 250, 50, 20, "Процент колонизации:");
    Text percent_of_colonization_Moon(800, 219, 250, 50, 20, "Процент колонизации:");
    Text percent_of_colonization_Mars(800, 315, 250, 50, 20, "Процент колонизации:");

    Percent_Earth_colonization = new Fl_Box(1050, 123, 100, 50, "0 %");
    Percent_Earth_colonization->labelsize(20);
    Percent_Earth_colonization->box(FL_BORDER_BOX);
    Percent_Earth_colonization->align(FL_ALIGN_CENTER);
    Percent_Earth_colonization->labelfont(FL_COURIER_BOLD);

    std::string ColonInfoEarth = std::to_string(Earth.getPercentColonization()) + " %";
    Percent_Earth_colonization->copy_label(ColonInfoEarth.c_str());

    Percent_Moon_colonization = new Fl_Box(1050, 219, 100, 50, "0 %");
    Percent_Moon_colonization->labelsize(20);
    Percent_Moon_colonization->box(FL_BORDER_BOX);
    Percent_Moon_colonization->align(FL_ALIGN_CENTER);
    Percent_Moon_colonization->labelfont(FL_COURIER_BOLD);

    std::string ColonInfoMoon = std::to_string(Moon.getPercentColonization()) + " %";
    Percent_Moon_colonization->copy_label(ColonInfoMoon.c_str());

    Percent_Mars_colonization = new Fl_Box(1050, 315, 100, 50, "0 %");
    Percent_Mars_colonization->labelsize(20);
    Percent_Mars_colonization->box(FL_BORDER_BOX);
    Percent_Mars_colonization->align(FL_ALIGN_CENTER);
    Percent_Mars_colonization->labelfont(FL_COURIER_BOLD);

    std::string ColonInfoMars = std::to_string(Mars.getPercentColonization()) + " %";
    Percent_Mars_colonization->copy_label(ColonInfoMars.c_str());

    // Обновляем состояние кнопок при создании
    updateButtonsState();

    window->end();
}

void PlanetsWindow::show() {
    window->show();
    refreshAll();
}

void PlanetsWindow::hide() {
    window->hide();
}

void PlanetsWindow::back_cb(Fl_Widget* w, void* data) {
    PlanetsWindow* planetsWin = (PlanetsWindow*)data;
    planetsWin->return_to_main();
}

void PlanetsWindow::return_to_main() {
    mainWindow->show();
    this->hide();
}

// МЕТОД ДЛЯ ОБНОВЛЕНИЯ СОСТОЯНИЯ КНОПОК
void PlanetsWindow::updateButtonsState() {
    // Кнопки выбора планет
    if (Moon.getPercentColonization() != 0) {
        choose_moon_btn->activate();
    } else {
        choose_moon_btn->deactivate();
    }

    if (Mars.getPercentColonization() != 0) {
        choose_mars_btn->activate();
    } else {
        choose_mars_btn->deactivate();
    }

    // Кнопки отправки ракет
    if (Player.getRocket() != nullptr && 
        Player.getRocket()->getLevel() >= 1 && 
        Moon.getPercentColonization() != 100) {
        send_rocket_moon_btn->activate();
    } else {
        send_rocket_moon_btn->deactivate();
    }

    if (Player.getRocket() != nullptr && 
        Player.getRocket()->getLevel() >= 2 && 
        Mars.getPercentColonization() != 100) {
        send_rocket_mars_btn->activate();
    } else {
        send_rocket_mars_btn->deactivate();
    }
}

// МЕТОД ДЛЯ ОБНОВЛЕНИЯ ВСЕГО ИНТЕРФЕЙСА
void PlanetsWindow::refreshAll() {
    // Обновляем проценты колонизации
    std::string earthText = std::to_string(Earth.getPercentColonization()) + " %";
    Percent_Earth_colonization->copy_label(earthText.c_str());

    std::string moonText = std::to_string(Moon.getPercentColonization()) + " %";
    Percent_Moon_colonization->copy_label(moonText.c_str());

    std::string marsText = std::to_string(Mars.getPercentColonization()) + " %";
    Percent_Mars_colonization->copy_label(marsText.c_str());

    // Обновляем состояние кнопок
    updateButtonsState();
}