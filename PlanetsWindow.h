#ifndef PLANETSWINDOW_H
#define PLANETSWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <string>
#include "UI_widgets.h"
#include "Person.h"
#include "Planet.h"

class MainWindow;

class PlanetsWindow {
private:
    Fl_Window* window;
    Fl_PNG_Image* bg;
    Fl_Box* background;
    MainWindow* mainWindow;
    PictureButton* back_Button;
    
public:
    PlanetsWindow(MainWindow* mainWin);
    void show();
    void hide();
    void updateButtonsState();  // Добавь эту строку
    void refreshAll();  

    static void back_cb(Fl_Widget* w, void* data);  
    void return_to_main();  
};

#endif