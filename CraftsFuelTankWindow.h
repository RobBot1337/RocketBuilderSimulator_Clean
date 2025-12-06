#ifndef CRAFTSFUELTANKWINDOW_H
#define CRAFTSFUELTANKWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <string>
#include "UI_widgets.h"
#include "Person.h"
#include "Planet.h"
#include "Mines.h"

class CraftsWindow;

class CraftsFuelTankWindow {
private:
    Fl_PNG_Image* bg;
    Fl_Box* background;
    Fl_Window* window;
    CraftsWindow* crWindow;
    PictureButton* back_Button;
    

    Button* craft_fueltank1;
    Button* craft_fueltank2;


public:
    CraftsFuelTankWindow(CraftsWindow* mainWin);
    ~CraftsFuelTankWindow(); // Деструктор для очистки
    void show();
    void hide();

    // Методы для обновления в реальном времени
    void refreshAll();
    void updateButtonsState();
    static void updateData(void* data);

    static void back_cb(Fl_Widget* w, void* data);  
    void return_to_main();  

    // Callback функции для кнопок покупки
    static void craft_fueltank1_cb(Fl_Widget* w, void* data);
    static void craft_fueltank2_cb(Fl_Widget* w, void* data);
};

#endif