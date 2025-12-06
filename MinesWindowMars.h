#ifndef MINESWINDOWMARS_H
#define MINESWINDOWMARS_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <string>
#include "UI_widgets.h"
#include "Person.h"
#include "Planet.h"
#include "Mines.h"

class MainWindow;

class MinesWindowMars {
private:
    Fl_Box* Count_of_iron_mines;
    Fl_Box* Count_of_nickel_mines;
    Fl_Box* Count_of_titan_mines;
    Fl_Box* Count_of_aluminium_mines;
    Fl_Box* Count_of_cobalt_mines;

    Fl_Window* window;
    MainWindow* mainWindow;
    Fl_PNG_Image* bg;
    Fl_Box* background;
    PictureButton* back_Button;
    
    // Кнопки покупки (добавь их как члены класса)
    Button* buy_iron_mine;
    Button* buy_titan_mine;
    Button* buy_aluminium_mine;
    Button* buy_nickel_mine;
    Button* buy_cobalt_mine;
    
public:
    MinesWindowMars(MainWindow* mainWin);
    ~MinesWindowMars(); // Деструктор для очистки
    void show();
    void hide();

    // Методы для обновления в реальном времени
    void refreshAll();
    void updateButtonsState();
    static void updateData(void* data);

    static void back_cb(Fl_Widget* w, void* data);  
    void return_to_main();  

    // Callback функции для кнопок покупки
    static void buy_iron_cb(Fl_Widget* w, void* data);
    static void buy_nickel_cb(Fl_Widget* w, void* data);
    static void buy_titan_cb(Fl_Widget* w, void* data);
    static void buy_aluminium_cb(Fl_Widget* w, void* data);
    static void buy_cobalt_cb(Fl_Widget* w, void* data);

};

#endif