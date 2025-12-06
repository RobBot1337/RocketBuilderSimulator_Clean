#ifndef FUELTANKSWINDOW_H
#define FUELTANKSWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <string>
#include "UI_widgets.h"
#include "Person.h"
#include "Planet.h"
#include "Mines.h"

class ResearchesWindow;

class FuelTanksWindow {
private:
    Fl_PNG_Image* bg;
    Fl_Box* background;
    Fl_Window* window;
    ResearchesWindow* resWindow;
    PictureButton* back_Button;
    

    Button* unlock_tank1;
    Button* unlock_tank2;


public:
    FuelTanksWindow(ResearchesWindow* mainWin);
    ~FuelTanksWindow(); // Деструктор для очистки
    void show();
    void hide();

    // Методы для обновления в реальном времени
    void refreshAll();
    void updateButtonsState();
    static void updateData(void* data);

    static void back_cb(Fl_Widget* w, void* data);  
    void return_to_main();  

    // Callback функции для кнопок покупки
    static void unlock_tank1_cb(Fl_Widget* w, void* data);
    static void unlock_tank2_cb(Fl_Widget* w, void* data);
};

#endif