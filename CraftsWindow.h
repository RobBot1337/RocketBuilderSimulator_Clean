#ifndef CRAFTSWINDOW_H
#define CRAFTSWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <string>
#include "UI_widgets.h"
#include "Person.h"
#include "Planet.h"

class MainWindow;

class CraftsWindow {
private:
    Fl_Window* window;
    Fl_PNG_Image* bg;
    Fl_Box* background;
    MainWindow* mainWindow;
    PictureButton* back_Button;
    PictureButton* craft_engine_button;
    PictureButton* craft_hull_button;
    PictureButton* craft_fuel_tank_button;
    PictureButton* craft_rocket_button;
    
public:
    CraftsWindow(MainWindow* mainWin);
    void show();
    void hide();

    static void back_cb(Fl_Widget* w, void* data);  
    void return_to_main();  

    static void craft_engine_cb(Fl_Widget* w, void* data);
    static void craft_hull_cb(Fl_Widget* w, void* data);
    static void craft_fuel_tank_cb(Fl_Widget* w, void* data);
    static void craft_rocket_cb(Fl_Widget* w, void* data);

    void open_craft_engine_window();
    void open_craft_hull_window();
    void open_craft_fuel_tank_window();
    void open_craft_rocket_window();
};

#endif