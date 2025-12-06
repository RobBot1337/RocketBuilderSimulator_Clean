#include "CraftsFuelTankWindow.h"
#include "CraftsWindow.h"
#include "Mines.h"
#include "PartsOfRocket.h"
#include <windows.h>
#include <mmsystem.h>

static Fl_PNG_Image* static_bg = nullptr;
static Fl_PNG_Image* static_arrow = nullptr;

Fl_Box* Fueltank1_count;
Fl_Box* Fueltank2_count;

// СТАТИЧЕСКИЕ CALLBACK ФУНКЦИИ
void CraftsFuelTankWindow::craft_fueltank1_cb(Fl_Widget* w, void* data){
    if(Rockets_parts.at("FuelTank1").getIsUnlocked()==true && Rockets_parts.at("FuelTank1").getRecipe().at("iron")<= iron && Rockets_parts.at("FuelTank1").getRecipe().at("coal")<= coal){
        Rockets_parts.at("FuelTank1").setCount(Rockets_parts.at("FuelTank1").getCount()+1);
        iron -= Rockets_parts.at("FuelTank1").getRecipe().at("iron");
        coal -= Rockets_parts.at("FuelTank1").getRecipe().at("coal");

        CraftsFuelTankWindow* win = (CraftsFuelTankWindow*)data;
        win->refreshAll();
        win->updateButtonsState();
    }
}

void CraftsFuelTankWindow::craft_fueltank2_cb(Fl_Widget* w, void* data){
    if(Rockets_parts.at("FuelTank2").getIsUnlocked()==true && Rockets_parts.at("FuelTank2").getRecipe().at("iron")<= iron && Rockets_parts.at("FuelTank2").getRecipe().at("coal")<= coal){
        Rockets_parts.at("FuelTank2").setCount(Rockets_parts.at("FuelTank2").getCount()+1);
        iron -= Rockets_parts.at("FuelTank2").getRecipe().at("iron");
        coal -= Rockets_parts.at("FuelTank2").getRecipe().at("coal");
        CraftsFuelTankWindow* win = (CraftsFuelTankWindow*)data;
        win->refreshAll();
        win->updateButtonsState();
    }
}

void CraftsFuelTankWindow::back_cb(Fl_Widget* w, void* data) {
    CraftsFuelTankWindow* allWin = (CraftsFuelTankWindow*)data;
    allWin->return_to_main();
}

CraftsFuelTankWindow::CraftsFuelTankWindow(CraftsWindow* mainWin){
    crWindow = mainWin;

    window = new Fl_Window(1440, 820, "Крафт топливных баков");
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

    Picture fueltank1(100, 100, 96, 96, "C:/Users/Zenbook/Desktop/Graphproject/Pictures/Топливный1.png");
    craft_fueltank1 = new Button(196, 123, 450, 50, 20, "Создать топливный бак 1-го уровня");
    craft_fueltank1->getButton()->callback(craft_fueltank1_cb, this);
    Text Fueltank1_Title(696, 123, 150, 50, 20, "Количество");

    Fueltank1_count = new Fl_Box(846, 123, 120, 50, "0");
    Fueltank1_count->labelsize(20);
    Fueltank1_count->box(FL_BORDER_BOX);
    Fueltank1_count->align(FL_ALIGN_CENTER);
    Fueltank1_count->labelfont(FL_COURIER_BOLD);

    Picture fueltank2(100, 196, 96, 96, "C:/Users/Zenbook/Desktop/Graphproject/Pictures/Топливный2.png");
    craft_fueltank2 = new Button(196, 219, 450, 50, 20, "Создать топливный бак 2-го уровня");
    craft_fueltank2->getButton()->callback(craft_fueltank2_cb, this);
    Text Fueltank2_Title(696, 219, 150, 50, 20, "Количество");

    Fueltank2_count = new Fl_Box(846, 219, 120, 50, "0");
    Fueltank2_count->labelsize(20);
    Fueltank2_count->box(FL_BORDER_BOX);
    Fueltank2_count->align(FL_ALIGN_CENTER);
    Fueltank2_count->labelfont(FL_COURIER_BOLD);

    updateButtonsState();
}

CraftsFuelTankWindow::~CraftsFuelTankWindow() {
    // Деструктор
}

void CraftsFuelTankWindow::show() {
    window->show();
    refreshAll();
}

void CraftsFuelTankWindow::hide() {
    window->hide();
}

void CraftsFuelTankWindow::return_to_main() {
    crWindow->show();
    this->hide();
}

void CraftsFuelTankWindow::refreshAll(){
    std::string fueltank1Text = std::to_string(Rockets_parts.at("FuelTank1").getCount());
    Fueltank1_count->copy_label(fueltank1Text.c_str());

    std::string fueltank2Text = std::to_string(Rockets_parts.at("FuelTank2").getCount());
    Fueltank2_count->copy_label(fueltank2Text.c_str());
}

void CraftsFuelTankWindow::updateButtonsState(){
    if (Rockets_parts.at("FuelTank1").getIsUnlocked()==true && Rockets_parts.at("FuelTank1").getRecipe().at("iron")<= iron && Rockets_parts.at("FuelTank1").getRecipe().at("coal")<= coal){
        craft_fueltank1->activate();
        craft_fueltank1->setColor(FL_GREEN);
    } else {
        craft_fueltank1->deactivate();
        craft_fueltank1->setColor(FL_RED);
    }

    if (Rockets_parts.at("FuelTank2").getIsUnlocked()==true && Rockets_parts.at("FuelTank2").getRecipe().at("iron")<= iron && Rockets_parts.at("FuelTank2").getRecipe().at("coal")<= coal){
        craft_fueltank2->activate();
        craft_fueltank2->setColor(FL_GREEN);
    } else {
        craft_fueltank2->deactivate();
        craft_fueltank2->setColor(FL_RED);
    }
}

void CraftsFuelTankWindow::updateData(void* data) {
    // Метод для обновления данных
}