#include "HullsWindow.h"
#include "ResearchesWindow.h"
#include "Mines.h"
#include "PartsOfRocket.h"
#include <windows.h>
#include <mmsystem.h>

static Fl_PNG_Image* static_bg = nullptr;
static Fl_PNG_Image* static_arrow = nullptr;
Fl_Box* MoneyHull;

// СТАТИЧЕСКИЕ CALLBACK ФУНКЦИИ
void HullsWindow::unlock_hull1_cb(Fl_Widget* w, void* data){
    if(Player.getMoney()>=Rockets_parts.at("Hull1").getPrice()){
        Player.setMoney(Player.getMoney()-Rockets_parts.at("Hull1").getPrice());
        Rockets_parts.at("Hull1").changeUnlocked(true);
        HullsWindow* win = (HullsWindow*) data;

        w->deactivate();
        w->color(FL_BACKGROUND_COLOR); // Обычный цвет
        w->redraw();

        win->refreshAll();
        win->updateButtonsState();
    }
}

void HullsWindow::unlock_hull2_cb(Fl_Widget* w, void* data){
    if(Player.getMoney()>=Rockets_parts.at("Hull2").getPrice() && Moon.getPercentColonization()!=0){
        Player.setMoney(Player.getMoney()-Rockets_parts.at("Hull2").getPrice());
        Rockets_parts.at("Hull2").changeUnlocked(true);
        HullsWindow* win = (HullsWindow*) data;

        w->deactivate();
        w->color(FL_BACKGROUND_COLOR); // Обычный цвет
        w->redraw();

        win->refreshAll();
        win->updateButtonsState();
    }
}

void HullsWindow::back_cb(Fl_Widget* w, void* data) {
    HullsWindow* allWin = (HullsWindow*)data;
    allWin->return_to_main();
}

HullsWindow::HullsWindow(ResearchesWindow* mainWin){
    resWindow = mainWin;

    window = new Fl_Window(1440, 820, "Исследовать корпуса");
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
    unlock_hull1 = new Button(196, 123, 450, 50, 20, "Исследовать корпус 1-го уровня");
    unlock_hull1->getButton()->callback(unlock_hull1_cb, this);

    Picture hull2(100, 196, 96, 96, "C:/Users/Zenbook/Desktop/Graphproject/Pictures/Корпус2.png");
    unlock_hull2 = new Button(196, 219, 450, 50, 20, "Исследовать корпус 2-го уровня");
    unlock_hull2->getButton()->callback(unlock_hull2_cb, this);

    Text money_Title(1129, 330, 250, 50, 20, "Баланс");
    MoneyHull = new Fl_Box(1129, 382, 250, 50, "0 M");
    MoneyHull->labelsize(20);
    MoneyHull->box(FL_BORDER_BOX);
    MoneyHull->align(FL_ALIGN_CENTER);
    MoneyHull->labelfont(FL_COURIER_BOLD);
    std::string newText = std::to_string(Player.getMoney()) + " M";
    MoneyHull->copy_label(newText.c_str());

    updateButtonsState();
}

HullsWindow::~HullsWindow() {
    // Деструктор
}

void HullsWindow::show() {
    window->show();
    refreshAll();
}

void HullsWindow::hide() {
    window->hide();
}

void HullsWindow::return_to_main() {
    resWindow->show();
    this->hide();
}

void HullsWindow::refreshAll() {
    std::string newText = std::to_string(Player.getMoney()) + " M";
    MoneyHull->copy_label(newText.c_str());
    
    if (window->visible()) {
        window->redraw();
    }
}

void HullsWindow::updateButtonsState(){
    // Корпус 1
    if (Rockets_parts.at("Hull1").getIsUnlocked()) {
        unlock_hull1->deactivate();
        unlock_hull1->setColor(FL_BACKGROUND_COLOR); // Обычный цвет
        unlock_hull1->getButton()->copy_label("Исследовано ✓");
    } else if (Player.getMoney() >= Rockets_parts.at("Hull1").getPrice()) {
        unlock_hull1->activate();
        unlock_hull1->setColor(FL_GREEN);
    } else {
        unlock_hull1->deactivate();
        unlock_hull1->setColor(FL_RED);
    }

    // Корпус 2
    if (Rockets_parts.at("Hull2").getIsUnlocked()) {
        unlock_hull2->deactivate();
        unlock_hull2->setColor(FL_BACKGROUND_COLOR); // Обычный цвет
        unlock_hull2->getButton()->copy_label("Исследовано ✓");
    } else if (Player.getMoney() >= Rockets_parts.at("Hull2").getPrice() && Moon.getPercentColonization()!=0) {
        unlock_hull2->activate();
        unlock_hull2->setColor(FL_GREEN);
    } else {
        unlock_hull2->deactivate();
        unlock_hull2->setColor(FL_RED);
    }
}