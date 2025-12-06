#ifndef RESEARCHESWINDOW_H
#define RESEARCHESWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <string>
#include "UI_widgets.h"

// Предварительные объявления вместо include
class MainWindow;
class HullsWindow;           // Добавь эту строку
class FuelTanksWindow;       // Добавь эту строку
class EnginesWindow;

class ResearchesWindow {
private:
    Fl_Window* window;
    Fl_PNG_Image* bg;
    Fl_Box* background;
    MainWindow* mainWindow;
    PictureButton* back_Button;
    PictureButton* research_hulls_Button;
    PictureButton* research_fuel_tanks_Button;
    PictureButton* research_engines_Button;
    
    // Убрал статические переменные - они должны быть членами класса
    Fl_PNG_Image* arrow;
    Fl_PNG_Image* research_engine_icon;
    Fl_PNG_Image* research_hull_icon;
    Fl_PNG_Image* research_tank_icon;
    
public:
    ResearchesWindow(MainWindow* mainWin);
    ~ResearchesWindow(); // Добавил деструктор
    
    void show();
    void hide();

    static void back_cb(Fl_Widget* w, void* data);  
    void return_to_main();  

    static void research_hulls_cb(Fl_Widget* w, void* data);
    static void research_fuel_tanks_cb(Fl_Widget* w, void* data);
    static void research_engines_cb(Fl_Widget* w, void* data);

    void open_research_hulls_window();
    void open_research_fuel_tanks_window();
    void open_research_engines_window();
};

#endif