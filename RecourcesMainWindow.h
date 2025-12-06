#ifndef RECOURCESMAINWINDOW_H
#define RECOURCESMAINWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <string>
#include "UI_widgets.h"
#include "Person.h"
#include "Planet.h"

class MainWindow;

class RecourcesMainWindow {
private:
    Fl_Window* window;
    Fl_PNG_Image* bg;
    Fl_Box* background;
    MainWindow* mainWindow;
    PictureButton* back_Button;
    PictureButton* simple_recources_Button;
    PictureButton* alloys_Button;
    
public:
    RecourcesMainWindow(MainWindow* mainWin);
    void show();
    void hide();

    static void back_cb(Fl_Widget* w, void* data);  
    void return_to_main();  

    static void open_recources_cb(Fl_Widget* w, void* data);
    static void open_alloys_cb(Fl_Widget* w, void* data);

    void open_recources_window();
    void open_alloys_window();
};

#endif