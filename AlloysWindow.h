#ifndef ALLOYSWINDOW_H
#define ALLOYSWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <string>
#include "UI_widgets.h"
#include "Person.h"
#include "Planet.h"
#include "Mines.h"

class RecourcesMainWindow;

class AlloysWindow {
private:
    Fl_PNG_Image* bg;
    Fl_Box* background;
    Fl_Window* window;
    RecourcesMainWindow* resWindow;
    PictureButton* back_Button;
    

    Button* craft_steel;
    Button* craft_aluminium_magnesium;
    Button* craft_duraluminium;
    Button* craft_copper_titanium;
    Button* craft_titanium_aluminium_iron;

public:
    AlloysWindow(RecourcesMainWindow* mainWin);
    ~AlloysWindow(); // Деструктор для очистки
    void show();
    void hide();

    // Методы для обновления в реальном времени
    void refreshAll();
    void updateButtonsState();
    static void updateData(void* data);

    static void back_cb(Fl_Widget* w, void* data);  
    void return_to_main();  

    // Callback функции для кнопок покупки
    static void craft_steel_cb(Fl_Widget* w, void* data);
    static void craft_duraluminium_cb(Fl_Widget* w, void* data);
    static void craft_aluminium_magnesium_cb(Fl_Widget* w, void* data);
    static void craft_copper_titanium_cb(Fl_Widget* w, void* data);
    static void craft_titanium_aluminium_iron_cb(Fl_Widget* w, void* data);
};

#endif