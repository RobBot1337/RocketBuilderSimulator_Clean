#include "CraftsRocketWindow.h"
#include "CraftsWindow.h"
#include "Mines.h"
#include "PartsOfRocket.h"
#include "Config.h"  // Добавляем Config
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

    Config& config = Config::getInstance();
    
    // ЗАГРУЖАЕМ ИЗОБРАЖЕНИЯ С ИСПОЛЬЗОВАНИЕМ КОНФИГА
    if (!static_bg) {
        std::string bgPath = config.getPicturePath("Небо.png");
        std::string arrowPath = config.getPicturePath("Cтрелка.png");
        
        static_bg = new Fl_PNG_Image(bgPath.c_str());
        static_arrow = new Fl_PNG_Image(arrowPath.c_str());
    }

    bg = static_bg;
    background = new Fl_Box(0, 0, 1440, 820);
    background->image(bg);

    // ИСПОЛЬЗУЕМ УЖЕ ЗАГРУЖЕННЫЕ ИЗОБРАЖЕНИЯ
    back_Button = new PictureButton(0, 0, 96, 96, static_arrow);
    back_Button->getButton()->callback(back_cb, this);

    // Ракета 1
    std::string rocket1Path = config.getPicturePath("Ракета1.png");
    Picture rocket1(100, 100, 96, 96, rocket1Path.c_str());
    
    craft_rocket1 = new Button(196, 123, 450, 50, 20, "Собрать ракету 1-го уровня");
    craft_rocket1->getButton()->callback(craft_rocket1_cb, this);
    craft_rocket1->getButton()->tooltip("Требуется:\n- Двигатель 1: 1 шт\n- Корпус 1: 1 шт\n- Топливный бак 1: 1 шт");

    // Ракета 2
    std::string rocket2Path = config.getPicturePath("Ракета2.png");
    Picture rocket2(100, 196, 96, 96, rocket2Path.c_str());
    
    craft_rocket2 = new Button(196, 219, 450, 50, 20, "Собрать ракету 2-го уровня");
    craft_rocket2->getButton()->callback(craft_rocket2_cb, this);
    craft_rocket2->getButton()->tooltip("Требуется:\n- Двигатель 2: 1 шт\n- Корпус 2: 1 шт\n- Топливный бак 2: 1 шт");

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
        craft_rocket1->getButton()->tooltip("Требуется:\n- Двигатель 1: 1 шт\n- Корпус 1: 1 шт\n- Топливный бак 1: 1 шт\n\n✅ Все детали есть!");
    } else {
        craft_rocket1->deactivate();
        craft_rocket1->setColor(FL_RED);
        
        // Более детальный tooltip при недостатке
        std::string tooltip1 = "Требуется:\n";
        tooltip1 += "- Двигатель 1: 1 шт (есть: " + std::to_string(Rockets_parts.at("Engine1").getCount()) + ")\n";
        tooltip1 += "- Корпус 1: 1 шт (есть: " + std::to_string(Rockets_parts.at("Hull1").getCount()) + ")\n";
        tooltip1 += "- Топливный бак 1: 1 шт (есть: " + std::to_string(Rockets_parts.at("FuelTank1").getCount()) + ")\n";
        
        if (Player.getRocket() != nullptr) {
            tooltip1 += "\n❌ У игрока уже есть ракета";
        }
        if (Moon.getPercentColonization() == 100) {
            tooltip1 += "\n❌ Луна уже колонизирована";
        }
        
        craft_rocket1->getButton()->tooltip(tooltip1.c_str());
    }

    // Проверяем достаточно ли деталей для ракеты 2 уровня
    if (Rockets_parts.at("Engine2").getCount() >= 1 && 
        Rockets_parts.at("Hull2").getCount() >= 1 && 
        Rockets_parts.at("FuelTank2").getCount() >= 1 &&
        Player.getRocket()==nullptr) {
        craft_rocket2->activate();
        craft_rocket2->setColor(FL_GREEN);
        craft_rocket2->getButton()->tooltip("Требуется:\n- Двигатель 2: 1 шт\n- Корпус 2: 1 шт\n- Топливный бак 2: 1 шт\n\n✅ Все детали есть!");
    } else {
        craft_rocket2->deactivate();
        craft_rocket2->setColor(FL_RED);
        
        // Более детальный tooltip при недостатке
        std::string tooltip2 = "Требуется:\n";
        tooltip2 += "- Двигатель 2: 1 шт (есть: " + std::to_string(Rockets_parts.at("Engine2").getCount()) + ")\n";
        tooltip2 += "- Корпус 2: 1 шт (есть: " + std::to_string(Rockets_parts.at("Hull2").getCount()) + ")\n";
        tooltip2 += "- Топливный бак 2: 1 шт (есть: " + std::to_string(Rockets_parts.at("FuelTank2").getCount()) + ")\n";
        
        if (Player.getRocket() != nullptr) {
            tooltip2 += "\n❌ У игрока уже есть ракета";
        }
        
        craft_rocket2->getButton()->tooltip(tooltip2.c_str());
    }
}

void CraftsRocketWindow::updateData(void* data) {
    // Метод для обновления данных
}