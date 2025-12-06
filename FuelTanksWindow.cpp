#include "FuelTanksWindow.h"
#include "ResearchesWindow.h"
#include "Mines.h"
#include "PartsOfRocket.h"
#include "Config.h"
#include <windows.h>
#include <mmsystem.h>

static Fl_PNG_Image* static_bg = nullptr;
static Fl_PNG_Image* static_arrow = nullptr;
Fl_Box* MoneyTank;

// СТАТИЧЕСКИЕ CALLBACK ФУНКЦИИ
void FuelTanksWindow::unlock_tank1_cb(Fl_Widget* w, void* data){
    if(Player.getMoney() >= Rockets_parts.at("FuelTank1").getPrice()){
        Player.setMoney(Player.getMoney() - Rockets_parts.at("FuelTank1").getPrice());
        Rockets_parts.at("FuelTank1").changeUnlocked(true);
        FuelTanksWindow* win = (FuelTanksWindow*) data;

        w->deactivate();
        w->color(FL_BACKGROUND_COLOR);
        w->redraw();

        win->refreshAll();
        win->updateButtonsState();
    }
}

void FuelTanksWindow::unlock_tank2_cb(Fl_Widget* w, void* data){
    if(Player.getMoney() >= Rockets_parts.at("FuelTank2").getPrice() && Moon.getPercentColonization() != 0){
        Player.setMoney(Player.getMoney() - Rockets_parts.at("FuelTank2").getPrice());
        Rockets_parts.at("FuelTank2").changeUnlocked(true);
        FuelTanksWindow* win = (FuelTanksWindow*) data;

        w->deactivate();
        w->color(FL_BACKGROUND_COLOR);
        w->redraw();

        win->refreshAll();
        win->updateButtonsState();
    }
}

void FuelTanksWindow::back_cb(Fl_Widget* w, void* data) {
    FuelTanksWindow* allWin = (FuelTanksWindow*)data;
    allWin->return_to_main();
}

FuelTanksWindow::FuelTanksWindow(ResearchesWindow* mainWin){
    resWindow = mainWin;

    window = new Fl_Window(1440, 820, "Исследовать топливные баки");
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

    // Топливный бак 1
    std::string tank1Path = config.getPicturePath("Топливный1.png");
    Picture tank1(100, 100, 96, 96, tank1Path.c_str());
    
    unlock_tank1 = new Button(196, 123, 450, 50, 20, "Исследовать топливный бак 1-го уровня");
    unlock_tank1->getButton()->callback(unlock_tank1_cb, this);
    unlock_tank1->getButton()->tooltip("Цена: 300 M");
    
    // Топливный бак 2
    std::string tank2Path = config.getPicturePath("Топливный2.png");
    Picture tank2(100, 196, 96, 96, tank2Path.c_str());
    
    unlock_tank2 = new Button(196, 219, 450, 50, 20, "Исследовать топливный бак 2-го уровня");
    unlock_tank2->getButton()->callback(unlock_tank2_cb, this);
    unlock_tank2->getButton()->tooltip("Цена: 600 M\nТребуется: начало колонизации Луны");

    Text money_Title(1129, 330, 250, 50, 20, "Баланс");
    MoneyTank = new Fl_Box(1129, 382, 250, 50, "0 M");
    MoneyTank->labelsize(20);
    MoneyTank->box(FL_BORDER_BOX);
    MoneyTank->align(FL_ALIGN_CENTER);
    MoneyTank->labelfont(FL_COURIER_BOLD);
    std::string newText = std::to_string(Player.getMoney()) + " M";
    MoneyTank->copy_label(newText.c_str());

    updateButtonsState();
}

FuelTanksWindow::~FuelTanksWindow() {
    // Деструктор
}

void FuelTanksWindow::show() {
    window->show();
    refreshAll();
}

void FuelTanksWindow::hide() {
    window->hide();
}

void FuelTanksWindow::return_to_main() {
    resWindow->show();
    this->hide();
}

void FuelTanksWindow::refreshAll() {
    std::string newText = std::to_string(Player.getMoney()) + " M";
    MoneyTank->copy_label(newText.c_str());
    
    if (window->visible()) {
        window->redraw();
    }
}

void FuelTanksWindow::updateButtonsState(){
    // Топливный бак 1
    if (Rockets_parts.at("FuelTank1").getIsUnlocked()) {
        unlock_tank1->deactivate();
        unlock_tank1->setColor(FL_BACKGROUND_COLOR);
        unlock_tank1->getButton()->copy_label("Исследовано ✓");
        unlock_tank1->getButton()->tooltip("Топливный бак 1 уже исследован");
    } else if (Player.getMoney() >= 300) {  // Цена напрямую
        unlock_tank1->activate();
        unlock_tank1->setColor(FL_GREEN);
        unlock_tank1->getButton()->copy_label("Исследовать топливный бак 1-го уровня");
        unlock_tank1->getButton()->tooltip("Цена: 150 M");
    } else {
        unlock_tank1->deactivate();
        unlock_tank1->setColor(FL_RED);
        unlock_tank1->getButton()->copy_label("Исследовать топливный бак 1-го уровня");
        unlock_tank1->getButton()->tooltip("Цена: 150 M\nНедостаточно денег");
    }

    // Топливный бак 2
    if (Rockets_parts.at("FuelTank2").getIsUnlocked()) {
        unlock_tank2->deactivate();
        unlock_tank2->setColor(FL_BACKGROUND_COLOR);
        unlock_tank2->getButton()->copy_label("Исследовано ✓");
        unlock_tank2->getButton()->tooltip("Топливный бак 2 уже исследован");
    } else if (Player.getMoney() >= 600 && Moon.getPercentColonization() != 0) {  // Цена напрямую
        unlock_tank2->activate();
        unlock_tank2->setColor(FL_GREEN);
        unlock_tank2->getButton()->copy_label("Исследовать топливный бак 2-го уровня");
        unlock_tank2->getButton()->tooltip("Цена: 300 M\nТребуется: начало колонизации Луны");
    } else {
        unlock_tank2->deactivate();
        unlock_tank2->setColor(FL_RED);
        unlock_tank2->getButton()->copy_label("Исследовать топливный бак 2-го уровня");
        unlock_tank2->getButton()->tooltip("Цена: 300 M\nТребуется: начало колонизации Луны\nНедостаточно денег");
    }
}