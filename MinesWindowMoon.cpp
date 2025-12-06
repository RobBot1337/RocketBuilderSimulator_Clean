#include "MinesWindowMoon.h"
#include "MainWindow.h" 
#include <windows.h>
#include <mmsystem.h>

Fl_Box* Money_Mines_Moon;

// СТАТИЧЕСКИЕ ИЗОБРАЖЕНИЯ (загружаются один раз)
static Fl_PNG_Image* static_bg = nullptr;
static Fl_PNG_Image* static_arrow = nullptr;
static Fl_PNG_Image* static_iron_mine = nullptr;
static Fl_PNG_Image* static_titan_mine = nullptr;
static Fl_PNG_Image* static_aluminium_mine = nullptr;
static Fl_PNG_Image* static_nickel_mine = nullptr;

// Callback функции покупки
void MinesWindowMoon::buy_nickel_cb(Fl_Widget* w, void* data) {
    if (Player.getMoney() >= MoonMines.at("NickelMine").getPrice() && 
        MoonMines.at("NickelMine").getCount() < MoonMines.at("NickelMine").getMaxCountOfMines()) {
        MoonMines.at("NickelMine").setCount(MoonMines.at("NickelMine").getCount() + 1);
        Player.setMoney(Player.getMoney() - MoonMines.at("NickelMine").getPrice());
        
        // ОБНОВЛЯЕМ ИНТЕРФЕЙС ПОСЛЕ ИЗМЕНЕНИЯ
        MinesWindowMoon* win = (MinesWindowMoon*)data;
        win->refreshAll();
    }
}

void MinesWindowMoon::buy_iron_cb(Fl_Widget* w, void* data) {
    if (Player.getMoney() >= MoonMines.at("IronMine").getPrice() && 
        MoonMines.at("IronMine").getCount() < MoonMines.at("IronMine").getMaxCountOfMines()) {
        MoonMines.at("IronMine").setCount(MoonMines.at("IronMine").getCount() + 1);
        Player.setMoney(Player.getMoney() - MoonMines.at("IronMine").getPrice());
        
        // ОБНОВЛЯЕМ ИНТЕРФЕЙС ПОСЛЕ ИЗМЕНЕНИЯ
        MinesWindowMoon* win = (MinesWindowMoon*)data;
        win->refreshAll();
    }
}

void MinesWindowMoon::buy_titan_cb(Fl_Widget* w, void* data) {
    if (Player.getMoney() >= MoonMines.at("TitanMine").getPrice() && 
        MoonMines.at("TitanMine").getCount() < MoonMines.at("TitanMine").getMaxCountOfMines()) {
        MoonMines.at("TitanMine").setCount(MoonMines.at("TitanMine").getCount() + 1);
        Player.setMoney(Player.getMoney() - MoonMines.at("TitanMine").getPrice());
        
        // ОБНОВЛЯЕМ ИНТЕРФЕЙС ПОСЛЕ ИЗМЕНЕНИЯ
        MinesWindowMoon* win = (MinesWindowMoon*)data;
        win->refreshAll();
    }
}

void MinesWindowMoon::buy_aluminium_cb(Fl_Widget* w, void* data) {
    if (Player.getMoney() >= MoonMines.at("AluminiumMine").getPrice() && 
        MoonMines.at("AluminiumMine").getCount() < MoonMines.at("AluminiumMine").getMaxCountOfMines()) {
        MoonMines.at("AluminiumMine").setCount(MoonMines.at("AluminiumMine").getCount() + 1);
        Player.setMoney(Player.getMoney() - MoonMines.at("AluminiumMine").getPrice());
        
        // ОБНОВЛЯЕМ ИНТЕРФЕЙС ПОСЛЕ ИЗМЕНЕНИЯ
        MinesWindowMoon* win = (MinesWindowMoon*)data;
        win->refreshAll();
    }
}


MinesWindowMoon::MinesWindowMoon(MainWindow* mainWin) {
    mainWindow = mainWin;

    // Инициализируем указатели на nullptr
    buy_iron_mine = nullptr;
    buy_titan_mine = nullptr;
    buy_aluminium_mine = nullptr;
    buy_nickel_mine = nullptr;

    window = new Fl_Window(1440, 820, "Планеты");
    window->position(10, 10);

    // ЗАГРУЖАЕМ ИЗОБРАЖЕНИЯ ТОЛЬКО ПРИ ПЕРВОМ СОЗДАНИИ
    if (!static_bg) {
        static_bg = new Fl_PNG_Image("C:/Users/Zenbook/Desktop/Graphproject/Pictures/ЛунныйФон.png");
        static_arrow = new Fl_PNG_Image("C:/Users/Zenbook/Desktop/Graphproject/Pictures/Cтрелка.png");
        static_iron_mine = new Fl_PNG_Image("C:/Users/Zenbook/Desktop/Graphproject/Pictures/ЖелезнаяШахта.png");
        static_titan_mine = new Fl_PNG_Image("C:/Users/Zenbook/Desktop/Graphproject/Pictures/ТитановаяШахта.png");
        static_aluminium_mine = new Fl_PNG_Image("C:/Users/Zenbook/Desktop/Graphproject/Pictures/АлюминиеваяШахта.png");
        static_nickel_mine = new Fl_PNG_Image("C:/Users/Zenbook/Desktop/Graphproject/Pictures/НикелеваяШахта.png");
    }
    bg = static_bg;
    background = new Fl_Box(0, 0, 1440, 820);
    background->image(bg);

    // ИСПОЛЬЗУЕМ УЖЕ ЗАГРУЖЕННЫЕ ИЗОБРАЖЕНИЯ
    back_Button = new PictureButton(0, 0, 96, 96, static_arrow);
    back_Button->getButton()->callback(back_cb, this);

    Fl_Box* nickel_mine_box = new Fl_Box(100, 100, 96, 96);
    nickel_mine_box->image(static_nickel_mine);
    
    Fl_Box* iron_mine_box = new Fl_Box(100, 196, 96, 96);
    iron_mine_box->image(static_iron_mine);

    Fl_Box* titan_mine_box = new Fl_Box(100, 292, 96, 96);
    titan_mine_box->image(static_titan_mine);
    
    Fl_Box* aluminium_mine_box = new Fl_Box(100, 388, 96, 96);
    aluminium_mine_box->image(static_aluminium_mine);
    
    // СОЗДАЕМ КНОПКИ КАК ЧЛЕНЫ КЛАССА
    buy_nickel_mine = new Button(196, 123, 200, 50, 20, "Купить шахту");
    buy_nickel_mine->getButton()->callback(buy_nickel_cb, this);

    buy_iron_mine = new Button(196, 219, 200, 50, 20, "Купить шахту");
    buy_iron_mine->getButton()->callback(buy_iron_cb, this);

    buy_titan_mine = new Button(196, 315, 200, 50, 20, "Купить шахту");
    buy_titan_mine->getButton()->callback(buy_titan_cb, this);

    buy_aluminium_mine = new Button(196, 411, 200, 50, 20, "Купить шахту");
    buy_aluminium_mine->getButton()->callback(buy_aluminium_cb, this);

    // Текстовые метки
    Text count_of_nickel_mines(423, 123, 250, 50, 20, "Количество шахт:");
    Text count_of_iron_mines(423, 219, 250, 50, 20, "Количество шахт:");
    Text count_of_titan_mines(423, 315, 250, 50, 20, "Количество шахт:");
    Text count_of_aluminium_mines(423, 411, 250, 50, 20, "Количество шахт:");

    // Счетчики шахт
    Count_of_nickel_mines = new Fl_Box(675, 123, 100, 50, "0");
    Count_of_nickel_mines->labelsize(20);
    Count_of_nickel_mines->box(FL_BORDER_BOX);
    Count_of_nickel_mines->align(FL_ALIGN_CENTER);
    Count_of_nickel_mines->labelfont(FL_COURIER_BOLD);

    Count_of_iron_mines = new Fl_Box(675, 219, 100, 50, "0");
    Count_of_iron_mines->labelsize(20);
    Count_of_iron_mines->box(FL_BORDER_BOX);
    Count_of_iron_mines->align(FL_ALIGN_CENTER);
    Count_of_iron_mines->labelfont(FL_COURIER_BOLD);

    Count_of_titan_mines = new Fl_Box(675, 315, 100, 50, "0");
    Count_of_titan_mines->labelsize(20);
    Count_of_titan_mines->box(FL_BORDER_BOX);
    Count_of_titan_mines->align(FL_ALIGN_CENTER);
    Count_of_titan_mines->labelfont(FL_COURIER_BOLD);

    Count_of_aluminium_mines = new Fl_Box(675, 411, 100, 50, "0");
    Count_of_aluminium_mines->labelsize(20);
    Count_of_aluminium_mines->box(FL_BORDER_BOX);
    Count_of_aluminium_mines->align(FL_ALIGN_CENTER);
    Count_of_aluminium_mines->labelfont(FL_COURIER_BOLD);

    // Деньги
    Text money_Title(1129, 330, 250, 50, 20, "Баланс");
    Money_Mines_Moon = new Fl_Box(1129, 382, 250, 50, "0 M");
    Money_Mines_Moon->labelsize(20);
    Money_Mines_Moon->box(FL_BORDER_BOX);
    Money_Mines_Moon->align(FL_ALIGN_CENTER);
    Money_Mines_Moon->labelfont(FL_COURIER_BOLD);

    // Первоначальное обновление данных
    refreshAll();
}

MinesWindowMoon::~MinesWindowMoon() {
    // ТАЙМЕР УБРАН - НИЧЕГО НЕ УДАЛЯЕМ
    
    // Освобождаем память
    delete buy_nickel_mine;
    delete buy_iron_mine;
    delete buy_titan_mine;
    delete buy_aluminium_mine;
}

void MinesWindowMoon::refreshAll() {
    // Обновляем счетчики шахт
    std::string ColonInfoNickelMines = std::to_string(MoonMines.at("NickelMine").getCount());
    Count_of_nickel_mines->copy_label(ColonInfoNickelMines.c_str());

    std::string ColonInfoIronMines = std::to_string(MoonMines.at("IronMine").getCount());
    Count_of_iron_mines->copy_label(ColonInfoIronMines.c_str());

    std::string ColonInfoTitanMines = std::to_string(MoonMines.at("TitanMine").getCount());
    Count_of_titan_mines->copy_label(ColonInfoTitanMines.c_str());

    std::string ColonInfoAluminiumMines = std::to_string(MoonMines.at("AluminiumMine").getCount());
    Count_of_aluminium_mines->copy_label(ColonInfoAluminiumMines.c_str());

    // Обновляем деньги
    std::string newText = std::to_string(Player.getMoney()) + " M";
    Money_Mines_Moon->copy_label(newText.c_str());

    // Обновляем состояние кнопок
    updateButtonsState();

    // Перерисовываем окно
    if (window->visible()) {
        window->redraw();
    }
}

void MinesWindowMoon::updateButtonsState() {
    // Никелевая шахта
    if (Player.getMoney() >= MoonMines.at("NickelMine").getPrice() && 
        MoonMines.at("NickelMine").getCount() < MoonMines.at("NickelMine").getMaxCountOfMines()) {
        buy_nickel_mine->activate();
        buy_nickel_mine->setColor(FL_GREEN);
    } else {
        buy_nickel_mine->deactivate();
        buy_nickel_mine->setColor(FL_RED);
    }

    // Железная шахта
    if (Player.getMoney() >= MoonMines.at("IronMine").getPrice() && 
        MoonMines.at("IronMine").getCount() < MoonMines.at("IronMine").getMaxCountOfMines()) {
        buy_iron_mine->activate();
        buy_iron_mine->setColor(FL_GREEN);
    } else {
        buy_iron_mine->deactivate();
        buy_iron_mine->setColor(FL_RED);
    }

    // Титановая шахта
    if (Player.getMoney() >= MoonMines.at("TitanMine").getPrice() && 
        MoonMines.at("TitanMine").getCount() < MoonMines.at("TitanMine").getMaxCountOfMines()) {
        buy_titan_mine->activate();
        buy_titan_mine->setColor(FL_GREEN);
    } else {
        buy_titan_mine->deactivate();
        buy_titan_mine->setColor(FL_RED);
    }

    // Алюминиевая шахта
    if (Player.getMoney() >= MoonMines.at("AluminiumMine").getPrice() && 
        MoonMines.at("AluminiumMine").getCount() < MoonMines.at("AluminiumMine").getMaxCountOfMines()) {
        buy_aluminium_mine->activate();
        buy_aluminium_mine->setColor(FL_GREEN);
    } else {
        buy_aluminium_mine->deactivate();
        buy_aluminium_mine->setColor(FL_RED);
    }
}

// ФУНКЦИЯ ДЛЯ ТАЙМЕРА - УБИРАЕМ ВОВСЕ
// void MinesWindowMoon::updateData(void* data) {
//     // ЭТУ ФУНКЦИЮ УДАЛЯЕМ
// }

void MinesWindowMoon::show() {
    window->show();
    // НЕ ЗАПУСКАЕМ ТАЙМЕР - обновляем только при действиях
    refreshAll(); // однократное обновление при показе
}

void MinesWindowMoon::hide() {
    // НЕ ОСТАНАВЛИВАЕМ ТАЙМЕР - его нет
    window->hide();
}

void MinesWindowMoon::back_cb(Fl_Widget* w, void* data) {
    MinesWindowMoon* minesWin = (MinesWindowMoon*)data;
    minesWin->return_to_main();
}

void MinesWindowMoon::return_to_main() {
    mainWindow->show();
    this->hide();
}