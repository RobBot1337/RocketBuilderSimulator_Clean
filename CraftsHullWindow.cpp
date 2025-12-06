#include "CraftsHullWindow.h"
#include "CraftsWindow.h"
#include "Mines.h"
#include "PartsOfRocket.h"
#include <windows.h>
#include <mmsystem.h>

static Fl_PNG_Image* static_bg = nullptr;
static Fl_PNG_Image* static_arrow = nullptr;

Fl_Box* Hull1_count;
Fl_Box* Hull2_count;

// СТАТИЧЕСКИЕ CALLBACK ФУНКЦИИ
void CraftsHullWindow::craft_hull1_cb(Fl_Widget* w, void* data){
    if(Rockets_parts.at("Hull1").getIsUnlocked()==true && Rockets_parts.at("Hull1").getRecipe().at("iron")<= iron && Rockets_parts.at("Hull1").getRecipe().at("coal")<= coal){
        Rockets_parts.at("Hull1").setCount(Rockets_parts.at("Hull1").getCount()+1);
        iron -= Rockets_parts.at("Hull1").getRecipe().at("iron");
        coal -= Rockets_parts.at("Hull1").getRecipe().at("coal");

        CraftsHullWindow* win = (CraftsHullWindow*)data;
        win->refreshAll();
        win->updateButtonsState();
    }
}

void CraftsHullWindow::craft_hull2_cb(Fl_Widget* w, void* data){
    if(Rockets_parts.at("Hull2").getIsUnlocked()==true && Rockets_parts.at("Hull2").getRecipe().at("iron")<= iron && Rockets_parts.at("Hull2").getRecipe().at("coal")<= coal){
        Rockets_parts.at("Hull2").setCount(Rockets_parts.at("Hull2").getCount()+1);
        iron -= Rockets_parts.at("Hull2").getRecipe().at("iron");
        coal -= Rockets_parts.at("Hull2").getRecipe().at("coal");
        CraftsHullWindow* win = (CraftsHullWindow*)data;
        win->refreshAll();
        win->updateButtonsState();
    }
}

void CraftsHullWindow::back_cb(Fl_Widget* w, void* data) {
    CraftsHullWindow* allWin = (CraftsHullWindow*)data;
    allWin->return_to_main();
}

CraftsHullWindow::CraftsHullWindow(CraftsWindow* mainWin){
    crWindow = mainWin;

    window = new Fl_Window(1440, 820, "Крафт корпусов");
    window->position(10, 10);

    // ЗАГРУЖАЕМ ИЗОБРАЖЕНИЯ ТОЛЬКО ПРИ ПЕРВОМ СОЗДАНИИ
    if (!static_bg) {
        static_bg = new Fl_PNG_Image("C:/Users/Zenbook/Desktop/Graphproject/Pictures/Небо.png");
        static_arrow = new Fl_PNG_Image("C:/Users/Zenbook/Desktop/Graphproject/Pictures/Cтрелка.png");
    }

    bg = static_bg;
    background = new Fl_Box(0, 0, 1440, 820);
    background->image(bg);

    // ИСПОЛЬЗУЕМ УЖЕ ЗАГРУЖЕННЫЕ ИЗОБРАЖЕНИЯ
    back_Button = new PictureButton(0, 0, 96, 96, static_arrow);
    back_Button->getButton()->callback(back_cb, this);

    Picture hull1(100, 100, 96, 96, "C:/Users/Zenbook/Desktop/Graphproject/Pictures/Корпус1.png");
    craft_hull1 = new Button(196, 123, 450, 50, 20, "Создать корпус 1-го уровня");
    craft_hull1->getButton()->callback(craft_hull1_cb, this);
    Text Hull1_Title(696, 123, 150, 50, 20, "Количество");

    Hull1_count = new Fl_Box(846, 123, 120, 50, "0");
    Hull1_count->labelsize(20);
    Hull1_count->box(FL_BORDER_BOX);
    Hull1_count->align(FL_ALIGN_CENTER);
    Hull1_count->labelfont(FL_COURIER_BOLD);

    Picture hull2(100, 196, 96, 96, "C:/Users/Zenbook/Desktop/Graphproject/Pictures/Корпус2.png");
    craft_hull2 = new Button(196, 219, 450, 50, 20, "Создать корпус 2-го уровня");
    craft_hull2->getButton()->callback(craft_hull2_cb, this);
    Text Hull2_Title(696, 219, 150, 50, 20, "Количество");

    Hull2_count = new Fl_Box(846, 219, 120, 50, "0");
    Hull2_count->labelsize(20);
    Hull2_count->box(FL_BORDER_BOX);
    Hull2_count->align(FL_ALIGN_CENTER);
    Hull2_count->labelfont(FL_COURIER_BOLD);

    updateButtonsState();
}

CraftsHullWindow::~CraftsHullWindow() {
    // Деструктор
}

void CraftsHullWindow::show() {
    window->show();
    refreshAll();
}

void CraftsHullWindow::hide() {
    window->hide();
}

void CraftsHullWindow::return_to_main() {
    crWindow->show();
    this->hide();
}

void CraftsHullWindow::refreshAll(){
    std::string hull1Text = std::to_string(Rockets_parts.at("Hull1").getCount());
    Hull1_count->copy_label(hull1Text.c_str());

    std::string hull2Text = std::to_string(Rockets_parts.at("Hull2").getCount());
    Hull2_count->copy_label(hull2Text.c_str());
}

void CraftsHullWindow::updateButtonsState(){
    if (Rockets_parts.at("Hull1").getIsUnlocked()==true && Rockets_parts.at("Hull1").getRecipe().at("iron")<= iron && Rockets_parts.at("Hull1").getRecipe().at("coal")<= coal){
        craft_hull1->activate();
        craft_hull1->setColor(FL_GREEN);
    } else {
        craft_hull1->deactivate();
        craft_hull1->setColor(FL_RED);
    }

    if (Rockets_parts.at("Hull2").getIsUnlocked()==true && Rockets_parts.at("Hull2").getRecipe().at("iron")<= iron && Rockets_parts.at("Hull2").getRecipe().at("coal")<= coal){
        craft_hull2->activate();
        craft_hull2->setColor(FL_GREEN);
    } else {
        craft_hull2->deactivate();
        craft_hull2->setColor(FL_RED);
    }
}

void CraftsHullWindow::updateData(void* data) {
    // Метод для обновления данных
}