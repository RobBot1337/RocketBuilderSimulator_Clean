#include "CraftsRocketWindow.h"
#include "CraftsWindow.h"
#include "Mines.h"
#include "PartsOfRocket.h"
#include <windows.h>
#include <mmsystem.h>

static Fl_PNG_Image* static_bg = nullptr;
static Fl_PNG_Image* static_arrow = nullptr;

// СТАТИЧЕСКИЕ CALLBACK ФУНКЦИИ
void CraftsRocketWindow::craft_rocket1_cb(Fl_Widget* w, void* data){
    if(Rockets_parts.at("Engine1").getCount() >= 1 && 
       Rockets_parts.at("Hull1").getCount() >= 1 && 
       Rockets_parts.at("FuelTank1").getCount() >= 1 &&
       Player.getRocket()==nullptr &&
       Moon.getPercentColonization()!=100) {
        
        // Собираем ракету уровня 1
        Rockets_parts.at("Engine1").setCount(Rockets_parts.at("Engine1").getCount() - 1);
        Rockets_parts.at("Hull1").setCount(Rockets_parts.at("Hull1").getCount() - 1);
        Rockets_parts.at("FuelTank1").setCount(Rockets_parts.at("FuelTank1").getCount() - 1);
        
        // Создаем ракету для игрока
        Player.setRocket(&Rocket1);

        CraftsRocketWindow* win = (CraftsRocketWindow*)data;
        win->refreshAll();
        win->updateButtonsState();
    }
}

void CraftsRocketWindow::craft_rocket2_cb(Fl_Widget* w, void* data){
    if(Rockets_parts.at("Engine2").getCount() >= 1 && 
       Rockets_parts.at("Hull2").getCount() >= 1 && 
       Rockets_parts.at("FuelTank2").getCount() >= 1 &&
       Player.getRocket()==nullptr) {
        
        // Собираем ракету уровня 2
        Rockets_parts.at("Engine2").setCount(Rockets_parts.at("Engine2").getCount() - 1);
        Rockets_parts.at("Hull2").setCount(Rockets_parts.at("Hull2").getCount() - 1);
        Rockets_parts.at("FuelTank2").setCount(Rockets_parts.at("FuelTank2").getCount() - 1);
        
        // Создаем ракету для игрока
        Player.setRocket(&Rocket2);

        CraftsRocketWindow* win = (CraftsRocketWindow*)data;
        win->refreshAll();
        win->updateButtonsState();
    }
}

void CraftsRocketWindow::back_cb(Fl_Widget* w, void* data) {
    CraftsRocketWindow* allWin = (CraftsRocketWindow*)data;
    allWin->return_to_main();
}

CraftsRocketWindow::CraftsRocketWindow(CraftsWindow* mainWin){
    crWindow = mainWin;

    window = new Fl_Window(1440, 820, "Сборка ракет");
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

    Picture rocket1(100, 100, 96, 96, "C:/Users/Zenbook/Desktop/Graphproject/Pictures/Ракета1.png");
    craft_rocket1 = new Button(196, 123, 450, 50, 20, "Собрать ракету 1-го уровня");
    craft_rocket1->getButton()->callback(craft_rocket1_cb, this);


    Picture rocket2(100, 196, 96, 96, "C:/Users/Zenbook/Desktop/Graphproject/Pictures/Ракета2.png");
    craft_rocket2 = new Button(196, 219, 450, 50, 20, "Собрать ракету 2-го уровня");
    craft_rocket2->getButton()->callback(craft_rocket2_cb, this);

    updateButtonsState();
}

CraftsRocketWindow::~CraftsRocketWindow() {
    // Деструктор
}

void CraftsRocketWindow::show() {
    window->show();
    refreshAll();
}

void CraftsRocketWindow::hide() {
    window->hide();
}

void CraftsRocketWindow::return_to_main() {
    crWindow->show();
    this->hide();
}

void CraftsRocketWindow::refreshAll(){
    // Обновляем состояние кнопок
    updateButtonsState();
}

void CraftsRocketWindow::updateButtonsState(){
    // Проверяем достаточно ли деталей для ракеты 1 уровня
    if (Rockets_parts.at("Engine1").getCount() >= 1 && 
        Rockets_parts.at("Hull1").getCount() >= 1 && 
        Rockets_parts.at("FuelTank1").getCount() >= 1 &&
        Player.getRocket()==nullptr &&
        Moon.getPercentColonization()!=100){
        craft_rocket1->activate();
        craft_rocket1->setColor(FL_GREEN);
    } else {
        craft_rocket1->deactivate();
        craft_rocket1->setColor(FL_RED);
    }

    // Проверяем достаточно ли деталей для ракеты 2 уровня
    if (Rockets_parts.at("Engine2").getCount() >= 1 && 
        Rockets_parts.at("Hull2").getCount() >= 1 && 
        Rockets_parts.at("FuelTank2").getCount() >= 1 &&
        Player.getRocket()==nullptr) {
        craft_rocket2->activate();
        craft_rocket2->setColor(FL_GREEN);
    } else {
        craft_rocket2->deactivate();
        craft_rocket2->setColor(FL_RED);
    }
}

void CraftsRocketWindow::updateData(void* data) {
    // Метод для обновления данных
}