#include "EnginesWindow.h"
#include "ResearchesWindow.h"
#include "Mines.h"
#include "PartsOfRocket.h"
#include "Config.h"
#include <windows.h>
#include <mmsystem.h>

static Fl_PNG_Image* static_bg = nullptr;
static Fl_PNG_Image* static_arrow = nullptr;
Fl_Box* MoneyEngine;

// Статические цены для tooltip
const int ENGINE1_PRICE = 150;
const int ENGINE2_PRICE = 300;

// СТАТИЧЕСКИЕ CALLBACK ФУНКЦИИ
void EnginesWindow::unlock_engine1_cb(Fl_Widget* w, void* data){
    if(Player.getMoney() >= Rockets_parts.at("Engine1").getPrice()){
        Player.setMoney(Player.getMoney() - Rockets_parts.at("Engine1").getPrice());
        Rockets_parts.at("Engine1").changeUnlocked(true);
        EnginesWindow* win = (EnginesWindow*) data;

        w->deactivate();
        w->color(FL_BACKGROUND_COLOR);
        w->redraw();

        win->refreshAll();
        win->updateButtonsState();
    }
}

void EnginesWindow::unlock_engine2_cb(Fl_Widget* w, void* data){
    if(Player.getMoney() >= Rockets_parts.at("Engine2").getPrice() && Moon.getPercentColonization() != 0){
        Player.setMoney(Player.getMoney() - Rockets_parts.at("Engine2").getPrice());
        Rockets_parts.at("Engine2").changeUnlocked(true);
        EnginesWindow* win = (EnginesWindow*) data;

        w->deactivate();
        w->color(FL_BACKGROUND_COLOR);
        w->redraw();

        win->refreshAll();
        win->updateButtonsState();
    }
}

void EnginesWindow::back_cb(Fl_Widget* w, void* data) {
    EnginesWindow* allWin = (EnginesWindow*)data;
    allWin->return_to_main();
}

EnginesWindow::EnginesWindow(ResearchesWindow* mainWin){
    resWindow = mainWin;

    window = new Fl_Window(1440, 820, "Исследовать двигатели");
    window->position(10, 10);

    Config& config = Config::getInstance();
    
    if (!static_bg) {
        std::string bgPath = config.getPicturePath("Небо.png");
        std::string arrowPath = config.getPicturePath("Cтрелка.png");
        
        static_bg = new Fl_PNG_Image(bgPath.c_str());
        static_arrow = new Fl_PNG_Image(arrowPath.c_str());
    }

    bg = static_bg;
    background = new Fl_Box(0, 0, 1440, 820);
    background->image(bg);

    back_Button = new PictureButton(0, 0, 96, 96, static_arrow);
    back_Button->getButton()->callback(back_cb, this);

    // Двигатель 1
    std::string engine1Path = config.getPicturePath("Двигатель1.png");
    Picture engine1(100, 100, 96, 96, engine1Path.c_str());
    
    unlock_engine1 = new Button(196, 123, 450, 50, 20, "Исследовать двигатель 1-го уровня");
    unlock_engine1->getButton()->callback(unlock_engine1_cb, this);
    unlock_engine1->getButton()->tooltip("Цена: 150 M");
    
    // Двигатель 2
    std::string engine2Path = config.getPicturePath("Двигатель2.png");
    Picture engine2(100, 196, 96, 96, engine2Path.c_str());
    
    unlock_engine2 = new Button(196, 219, 450, 50, 20, "Исследовать двигатель 2-го уровня");
    unlock_engine2->getButton()->callback(unlock_engine2_cb, this);
    unlock_engine2->getButton()->tooltip("Цена: 300 M\nТребуется: начало колонизации Луны");

    Text money_Title(1129, 330, 250, 50, 20, "Баланс");
    MoneyEngine = new Fl_Box(1129, 382, 250, 50, "0 M");
    MoneyEngine->labelsize(20);
    MoneyEngine->box(FL_BORDER_BOX);
    MoneyEngine->align(FL_ALIGN_CENTER);
    MoneyEngine->labelfont(FL_COURIER_BOLD);
    std::string newText = std::to_string(Player.getMoney()) + " M";
    MoneyEngine->copy_label(newText.c_str());

    updateButtonsState();
}

EnginesWindow::~EnginesWindow() {
    // Деструктор
}

void EnginesWindow::show() {
    window->show();
    refreshAll();
}

void EnginesWindow::hide() {
    window->hide();
}

void EnginesWindow::return_to_main() {
    resWindow->show();
    this->hide();
}

void EnginesWindow::refreshAll() {
    std::string newText = std::to_string(Player.getMoney()) + " M";
    MoneyEngine->copy_label(newText.c_str());
    
    if (window->visible()) {
        window->redraw();
    }
}

void EnginesWindow::updateButtonsState(){
    // Двигатель 1
    if (Rockets_parts.at("Engine1").getIsUnlocked()) {
        unlock_engine1->deactivate();
        unlock_engine1->setColor(FL_BACKGROUND_COLOR);
        unlock_engine1->getButton()->copy_label("Исследовано ✓");
        unlock_engine1->getButton()->tooltip("Двигатель 1 уже исследован");
    } else if (Player.getMoney() >= ENGINE1_PRICE) {
        unlock_engine1->activate();
        unlock_engine1->setColor(FL_GREEN);
        unlock_engine1->getButton()->copy_label("Исследовать двигатель 1-го уровня");
        unlock_engine1->getButton()->tooltip("Цена: 150 M");
    } else {
        unlock_engine1->deactivate();
        unlock_engine1->setColor(FL_RED);
        unlock_engine1->getButton()->copy_label("Исследовать двигатель 1-го уровня");
        unlock_engine1->getButton()->tooltip("Цена: 150 M\nНедостаточно денег");
    }

    // Двигатель 2
    if (Rockets_parts.at("Engine2").getIsUnlocked()) {
        unlock_engine2->deactivate();
        unlock_engine2->setColor(FL_BACKGROUND_COLOR);
        unlock_engine2->getButton()->copy_label("Исследовано ✓");
        unlock_engine2->getButton()->tooltip("Двигатель 2 уже исследован");
    } else if (Player.getMoney() >= ENGINE2_PRICE && Moon.getPercentColonization() != 0) {
        unlock_engine2->activate();
        unlock_engine2->setColor(FL_GREEN);
        unlock_engine2->getButton()->copy_label("Исследовать двигатель 2-го уровня");
        unlock_engine2->getButton()->tooltip("Цена: 300 M\nТребуется: начало колонизации Луны");
    } else {
        unlock_engine2->deactivate();
        unlock_engine2->setColor(FL_RED);
        unlock_engine2->getButton()->copy_label("Исследовать двигатель 2-го уровня");
        unlock_engine2->getButton()->tooltip("Цена: 300 M\nТребуется: начало колонизации Луны\nНедостаточно денег");
    }
}