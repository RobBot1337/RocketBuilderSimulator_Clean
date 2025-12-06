#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <string>
#include "UI_widgets.h"
#include "Person.h"
#include "Planet.h"

class PlanetsWindow;
class MinesWindowEarth;
class MinesWindowMoon;

class MainWindow {
private:
    Fl_Window* window;
    Fl_PNG_Image* bg;
    Fl_Box* background;
    PictureButton* choose_other_planet_Button;
    PictureButton* planet_Button;
    PictureButton* mines_Button;
    PictureButton* recources_Button;
    PictureButton* researches_Button;
    PictureButton* crafts_Button;
    
    void updateMinesButton();

public:
    MainWindow();
    void show();
    void hide();
    void updatePlanetDisplay();
    void updateMoneyDisplay(); 
    
    // Callback функции - ДЕЛАЕМ СТАТИЧЕСКИМИ
    static void open_planets_cb(Fl_Widget* w, void* data);
    static void open_recources_main_cb(Fl_Widget* w, void* data);
    static void open_researches_cb(Fl_Widget* w, void* data);
    static void open_crafts_cb(Fl_Widget* w, void* data);
    static void open_mines_earth_cb(Fl_Widget* w, void* data);
    static void open_mines_moon_cb(Fl_Widget* w, void* data);
    static void open_mines_mars_cb(Fl_Widget* w, void* data);
    
    // Методы открытия окон
    void open_planets_window();
    void open_recources_main_window();
    void open_researches_window();
    void open_crafts_window();
    void open_mines_window_earth();
    void open_mines_window_moon();
    void open_mines_window_mars();
};

#endif