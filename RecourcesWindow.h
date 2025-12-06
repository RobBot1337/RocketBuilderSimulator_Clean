#ifndef RECOURCESWINDOW_H
#define RECOURCESWINDOW_H

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

class RecourcesWindow {
private:
    Fl_PNG_Image* bg;
    Fl_Box* background;
    Fl_Window* window;
    RecourcesMainWindow* resWindow;
    PictureButton* back_Button;
    
    // ПЕРЕМЕННЫЕ ДЛЯ ОТОБРАЖЕНИЯ РЕСУРСОВ (ПРИВАТНЫЕ)
    Fl_Box* Iron_Count;
    Fl_Box* Coal_Count;
    Fl_Box* Copper_Count;
    Fl_Box* Aluminium_Count;
    Fl_Box* Titanium_Count;
    Fl_Box* Magnesium_Count;
    Fl_Box* Oil_Count;
    Fl_Box* Nickel_Count;
    Fl_Box* Cobalt_Count;
    
public:
    RecourcesWindow(RecourcesMainWindow* mainWin);
    ~RecourcesWindow();
    void show();
    void hide();

    // Методы для обновления в реальном времени
    void refreshAll();
    void updateButtonsState();
    static void updateData(void* data);

    static void back_cb(Fl_Widget* w, void* data);  
    void return_to_main();  

    // ДОБАВЛЯЕМ НОВЫЕ МЕТОДЫ
    void refreshResources(); // Публичный метод для внешнего обновления
    bool isVisible() const { return window->visible(); } // Метод для проверки видимости окна
    
    // СТАТИЧЕСКИЙ МЕТОД ДЛЯ ПОЛУЧЕНИЯ ТЕКУЩЕГО ОКНА
    static RecourcesWindow* getCurrentWindow();
};

#endif