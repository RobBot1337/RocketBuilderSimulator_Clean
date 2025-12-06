#ifndef HULLSWINDOW_H
#define HULLSWINDOW_H

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

class HullsWindow {
private:
    Fl_PNG_Image* bg;
    Fl_Box* background;
    Fl_Window* window;
    ResearchesWindow* resWindow;
    PictureButton* back_Button;
    

    Button* unlock_hull1;
    Button* unlock_hull2;


public:
    HullsWindow(ResearchesWindow* mainWin);
    ~HullsWindow(); // Деструктор для очистки
    void show();
    void hide();

    // Методы для обновления в реальном времени
    void refreshAll();
    void updateButtonsState();
    static void updateData(void* data);

    static void back_cb(Fl_Widget* w, void* data);  
    void return_to_main();  

    // Callback функции для кнопок покупки
    static void unlock_hull1_cb(Fl_Widget* w, void* data);
    static void unlock_hull2_cb(Fl_Widget* w, void* data);
};

#endif