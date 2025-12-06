#include "CraftsEngineWindow.h"
#include "CraftsWindow.h"
#include "Mines.h"
#include "PartsOfRocket.h"
#include <windows.h>
#include <mmsystem.h>

static Fl_PNG_Image* static_bg = nullptr;
static Fl_PNG_Image* static_arrow = nullptr;

Fl_Box* Engine1_count;
Fl_Box* Engine2_count;
// СТАТИЧЕСКИЕ CALLBACK ФУНКЦИИ
void CraftsEngineWindow::craft_engine1_cb(Fl_Widget* w, void* data){
    if(Rockets_parts.at("Engine1").getIsUnlocked()==true && Rockets_parts.at("Engine1").getRecipe().at("iron")<= iron && Rockets_parts.at("Engine1").getRecipe().at("coal")<= coal){
        Rockets_parts.at("Engine1").setCount(Rockets_parts.at("Engine1").getCount()+1);
        iron -= Rockets_parts.at("Engine1").getRecipe().at("iron");
        coal -= Rockets_parts.at("Engine1").getRecipe().at("coal");

        CraftsEngineWindow* win = (CraftsEngineWindow*)data;
        win->refreshAll();
        win->updateButtonsState();
    }
}

void CraftsEngineWindow::craft_engine2_cb(Fl_Widget* w, void* data){
    if(Rockets_parts.at("Engine2").getIsUnlocked()==true && Rockets_parts.at("Engine2").getRecipe().at("iron")<= iron && Rockets_parts.at("Engine2").getRecipe().at("coal")<= coal){
        Rockets_parts.at("Engine2").setCount(Rockets_parts.at("Engine2").getCount()+1);
        iron -= Rockets_parts.at("Engine2").getRecipe().at("iron");
        coal -= Rockets_parts.at("Engine2").getRecipe().at("coal");
        CraftsEngineWindow* win = (CraftsEngineWindow*)data;
        win->refreshAll();
        win->updateButtonsState();
    }
}

void CraftsEngineWindow::back_cb(Fl_Widget* w, void* data) {
    CraftsEngineWindow* allWin = (CraftsEngineWindow*)data;
    allWin->return_to_main();
}

CraftsEngineWindow::CraftsEngineWindow(CraftsWindow* mainWin){
    crWindow = mainWin;

    window = new Fl_Window(1440, 820, "Исследовать двигатели");
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

    Picture engine1(100, 100, 96, 96, "C:/Users/Zenbook/Desktop/Graphproject/Pictures/Двигатель1.png");
    craft_engine1 = new Button(196, 123, 450, 50, 20, "Создать двигатель 1-го уровня");
    craft_engine1->getButton()->callback(craft_engine1_cb, this);
    Text Engine1_Title(696, 123, 150, 50, 20, "Количество");

    Engine1_count = new Fl_Box(846, 123, 120, 50, "0");
    Engine1_count->labelsize(20);
    Engine1_count->box(FL_BORDER_BOX);
    Engine1_count->align(FL_ALIGN_CENTER);
    Engine1_count->labelfont(FL_COURIER_BOLD);


    Picture engine2(100, 196, 96, 96, "C:/Users/Zenbook/Desktop/Graphproject/Pictures/Двигатель2.png");
    craft_engine2 = new Button(196, 219, 450, 50, 20, "Создать двигатель 2-го уровня");
    craft_engine2->getButton()->callback(craft_engine2_cb, this);
    Text Engine2_Title(696, 219, 150, 50, 20, "Количество");

    Engine2_count = new Fl_Box(846, 219, 120, 50, "0");
    Engine2_count->labelsize(20);
    Engine2_count->box(FL_BORDER_BOX);
    Engine2_count->align(FL_ALIGN_CENTER);
    Engine2_count->labelfont(FL_COURIER_BOLD);


    updateButtonsState();
}

CraftsEngineWindow::~CraftsEngineWindow() {
    // Деструктор
}

void CraftsEngineWindow::show() {
    window->show();
    refreshAll();
}

void CraftsEngineWindow::hide() {
    window->hide();
}

void CraftsEngineWindow::return_to_main() {
    crWindow->show();
    this->hide();
}

void CraftsEngineWindow::refreshAll(){
    std::string engine1Text = std::to_string(Rockets_parts.at("Engine1").getCount());
    Engine1_count->copy_label(engine1Text.c_str());

    std::string engine2Text = std::to_string(Rockets_parts.at("Engine2").getCount());
    Engine2_count->copy_label(engine2Text.c_str());
}
void CraftsEngineWindow::updateButtonsState(){
    if (Rockets_parts.at("Engine1").getIsUnlocked()==true && Rockets_parts.at("Engine1").getRecipe().at("iron")<= iron && Rockets_parts.at("Engine1").getRecipe().at("coal")<= coal){
        craft_engine1->activate();
        craft_engine1->setColor(FL_GREEN);
    } else {
        craft_engine1->deactivate();
        craft_engine1->setColor(FL_RED);
    }

    if (Rockets_parts.at("Engine2").getIsUnlocked()==true && Rockets_parts.at("Engine2").getRecipe().at("iron")<= iron && Rockets_parts.at("Engine2").getRecipe().at("coal")<= coal){
        craft_engine2->activate();
        craft_engine2->setColor(FL_GREEN);
    } else {
        craft_engine2->deactivate();
        craft_engine2->setColor(FL_RED);
    }
}
