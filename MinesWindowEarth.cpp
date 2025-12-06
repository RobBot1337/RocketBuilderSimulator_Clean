#include "MinesWindowEarth.h"
#include "MainWindow.h" 
#include <windows.h>
#include <mmsystem.h>

Fl_Box* Money_Mines_Earth;

// СТАТИЧЕСКИЕ ИЗОБРАЖЕНИЯ (загружаются один раз)
static Fl_PNG_Image* static_bg = nullptr;
static Fl_PNG_Image* static_arrow = nullptr;
static Fl_PNG_Image* static_coal_mine = nullptr;
static Fl_PNG_Image* static_iron_mine = nullptr;
static Fl_PNG_Image* static_cooper_mine = nullptr;
static Fl_PNG_Image* static_titan_mine = nullptr;
static Fl_PNG_Image* static_aluminium_mine = nullptr;
static Fl_PNG_Image* static_magnesium_mine = nullptr;
static Fl_PNG_Image* static_oil_pumping = nullptr;

// Callback функции покупки
void MinesWindowEarth::buy_coal_cb(Fl_Widget* w, void* data) {
    if (Player.getMoney() >= EarthMines.at("CoalMine").getPrice() && 
        EarthMines.at("CoalMine").getCount() < EarthMines.at("CoalMine").getMaxCountOfMines()) {
        EarthMines.at("CoalMine").setCount(EarthMines.at("CoalMine").getCount() + 1);
        Player.setMoney(Player.getMoney() - EarthMines.at("CoalMine").getPrice());
        
        // ОБНОВЛЯЕМ ИНТЕРФЕЙС ПОСЛЕ ИЗМЕНЕНИЯ
        MinesWindowEarth* win = (MinesWindowEarth*)data;
        win->refreshAll();
    }
}

void MinesWindowEarth::buy_iron_cb(Fl_Widget* w, void* data) {
    if (Player.getMoney() >= EarthMines.at("IronMine").getPrice() && 
        EarthMines.at("IronMine").getCount() < EarthMines.at("IronMine").getMaxCountOfMines()) {
        EarthMines.at("IronMine").setCount(EarthMines.at("IronMine").getCount() + 1);
        Player.setMoney(Player.getMoney() - EarthMines.at("IronMine").getPrice());
        
        // ОБНОВЛЯЕМ ИНТЕРФЕЙС ПОСЛЕ ИЗМЕНЕНИЯ
        MinesWindowEarth* win = (MinesWindowEarth*)data;
        win->refreshAll();
    }
}

void MinesWindowEarth::buy_cooper_cb(Fl_Widget* w, void* data) {
    if (Player.getMoney() >= EarthMines.at("CooperMine").getPrice() && 
        EarthMines.at("CooperMine").getCount() < EarthMines.at("CooperMine").getMaxCountOfMines()) {
        EarthMines.at("CooperMine").setCount(EarthMines.at("CooperMine").getCount() + 1);
        Player.setMoney(Player.getMoney() - EarthMines.at("CooperMine").getPrice());
        
        // ОБНОВЛЯЕМ ИНТЕРФЕЙС ПОСЛЕ ИЗМЕНЕНИЯ
        MinesWindowEarth* win = (MinesWindowEarth*)data;
        win->refreshAll();
    }
}

void MinesWindowEarth::buy_titan_cb(Fl_Widget* w, void* data) {
    if (Player.getMoney() >= EarthMines.at("TitanMine").getPrice() && 
        EarthMines.at("TitanMine").getCount() < EarthMines.at("TitanMine").getMaxCountOfMines()) {
        EarthMines.at("TitanMine").setCount(EarthMines.at("TitanMine").getCount() + 1);
        Player.setMoney(Player.getMoney() - EarthMines.at("TitanMine").getPrice());
        
        // ОБНОВЛЯЕМ ИНТЕРФЕЙС ПОСЛЕ ИЗМЕНЕНИЯ
        MinesWindowEarth* win = (MinesWindowEarth*)data;
        win->refreshAll();
    }
}

void MinesWindowEarth::buy_aluminium_cb(Fl_Widget* w, void* data) {
    if (Player.getMoney() >= EarthMines.at("AluminiumMine").getPrice() && 
        EarthMines.at("AluminiumMine").getCount() < EarthMines.at("AluminiumMine").getMaxCountOfMines()) {
        EarthMines.at("AluminiumMine").setCount(EarthMines.at("AluminiumMine").getCount() + 1);
        Player.setMoney(Player.getMoney() - EarthMines.at("AluminiumMine").getPrice());
        
        // ОБНОВЛЯЕМ ИНТЕРФЕЙС ПОСЛЕ ИЗМЕНЕНИЯ
        MinesWindowEarth* win = (MinesWindowEarth*)data;
        win->refreshAll();
    }
}

void MinesWindowEarth::buy_magnesium_cb(Fl_Widget* w, void* data) {
    if (Player.getMoney() >= EarthMines.at("MagnesiumMine").getPrice() && 
        EarthMines.at("MagnesiumMine").getCount() < EarthMines.at("MagnesiumMine").getMaxCountOfMines()) {
        EarthMines.at("MagnesiumMine").setCount(EarthMines.at("MagnesiumMine").getCount() + 1);
        Player.setMoney(Player.getMoney() - EarthMines.at("MagnesiumMine").getPrice());
        
        // ОБНОВЛЯЕМ ИНТЕРФЕЙС ПОСЛЕ ИЗМЕНЕНИЯ
        MinesWindowEarth* win = (MinesWindowEarth*)data;
        win->refreshAll();
    }
}

void MinesWindowEarth::buy_oil_cb(Fl_Widget* w, void* data) {
    if (Player.getMoney() >= EarthMines.at("OilPumping").getPrice() && 
        EarthMines.at("OilPumping").getCount() < EarthMines.at("OilPumping").getMaxCountOfMines()) {
        EarthMines.at("OilPumping").setCount(EarthMines.at("OilPumping").getCount() + 1);
        Player.setMoney(Player.getMoney() - EarthMines.at("OilPumping").getPrice());
        
        // ОБНОВЛЯЕМ ИНТЕРФЕЙС ПОСЛЕ ИЗМЕНЕНИЯ
        MinesWindowEarth* win = (MinesWindowEarth*)data;
        win->refreshAll();
    }
}

MinesWindowEarth::MinesWindowEarth(MainWindow* mainWin) {
    mainWindow = mainWin;

    // Инициализируем указатели на nullptr
    buy_coal_mine = nullptr;
    buy_iron_mine = nullptr;
    buy_cooper_mine = nullptr;
    buy_titan_mine = nullptr;
    buy_aluminium_mine = nullptr;
    buy_magnesium_mine = nullptr;
    buy_oil_pumping = nullptr;

    window = new Fl_Window(1440, 820, "Планеты");
    window->position(10, 10);

    // ЗАГРУЖАЕМ ИЗОБРАЖЕНИЯ ТОЛЬКО ПРИ ПЕРВОМ СОЗДАНИИ
    if (!static_bg) {
        static_bg = new Fl_PNG_Image("C:/Users/Zenbook/Desktop/Graphproject/Pictures/ЗемнойФон.png");
        static_arrow = new Fl_PNG_Image("C:/Users/Zenbook/Desktop/Graphproject/Pictures/Cтрелка.png");
        static_coal_mine = new Fl_PNG_Image("C:/Users/Zenbook/Desktop/Graphproject/Pictures/УгольнаяШахта.png");
        static_iron_mine = new Fl_PNG_Image("C:/Users/Zenbook/Desktop/Graphproject/Pictures/ЖелезнаяШахта.png");
        static_cooper_mine = new Fl_PNG_Image("C:/Users/Zenbook/Desktop/Graphproject/Pictures/МеднаяШахта.png");
        static_titan_mine = new Fl_PNG_Image("C:/Users/Zenbook/Desktop/Graphproject/Pictures/ТитановаяШахта.png");
        static_magnesium_mine = new Fl_PNG_Image("C:/Users/Zenbook/Desktop/Graphproject/Pictures/МагниеваяШахта.png");
        static_aluminium_mine = new Fl_PNG_Image("C:/Users/Zenbook/Desktop/Graphproject/Pictures/АлюминиеваяШахта.png");
        static_oil_pumping = new Fl_PNG_Image("C:/Users/Zenbook/Desktop/Graphproject/Pictures/НефтянаяВышка.png");
    }
    bg = static_bg;
    background = new Fl_Box(0, 0, 1440, 820);
    background->image(bg);

    // ИСПОЛЬЗУЕМ УЖЕ ЗАГРУЖЕННЫЕ ИЗОБРАЖЕНИЯ
    back_Button = new PictureButton(0, 0, 96, 96, static_arrow);
    back_Button->getButton()->callback(back_cb, this);

    Fl_Box* coal_mine_box = new Fl_Box(100, 100, 96, 96);
    coal_mine_box->image(static_coal_mine);
    
    Fl_Box* iron_mine_box = new Fl_Box(100, 196, 96, 96);
    iron_mine_box->image(static_iron_mine);
    
    Fl_Box* cooper_mine_box = new Fl_Box(100, 292, 96, 96);
    cooper_mine_box->image(static_cooper_mine);

    Fl_Box* titan_mine_box = new Fl_Box(100, 388, 96, 96);
    titan_mine_box->image(static_titan_mine);
    
    Fl_Box* aluminium_mine_box = new Fl_Box(100, 484, 96, 96);
    aluminium_mine_box->image(static_aluminium_mine);
    
    Fl_Box* magnesium_mine_box = new Fl_Box(100, 580, 96, 96);
    magnesium_mine_box->image(static_magnesium_mine);

    Fl_Box* oil_pumping_box = new Fl_Box(100, 676, 96, 96);
    oil_pumping_box->image(static_oil_pumping);

    // СОЗДАЕМ КНОПКИ КАК ЧЛЕНЫ КЛАССА
    buy_coal_mine = new Button(196, 123, 200, 50, 20, "Купить шахту");
    buy_coal_mine->getButton()->callback(buy_coal_cb, this);

    buy_iron_mine = new Button(196, 219, 200, 50, 20, "Купить шахту");
    buy_iron_mine->getButton()->callback(buy_iron_cb, this);

    buy_cooper_mine = new Button(196, 315, 200, 50, 20, "Купить шахту");
    buy_cooper_mine->getButton()->callback(buy_cooper_cb, this);

    buy_titan_mine = new Button(196, 411, 200, 50, 20, "Купить шахту");
    buy_titan_mine->getButton()->callback(buy_titan_cb, this);

    buy_aluminium_mine = new Button(196, 507, 200, 50, 20, "Купить шахту");
    buy_aluminium_mine->getButton()->callback(buy_aluminium_cb, this);

    buy_magnesium_mine = new Button(196, 603, 200, 50, 20, "Купить шахту");
    buy_magnesium_mine->getButton()->callback(buy_magnesium_cb, this);

    buy_oil_pumping = new Button(196, 699, 200, 50, 20, "Купить вышку");
    buy_oil_pumping->getButton()->callback(buy_oil_cb, this);

    // Текстовые метки
    Text count_of_coal_mines(423, 123, 250, 50, 20, "Количество шахт:");
    Text count_of_iron_mines(423, 219, 250, 50, 20, "Количество шахт:");
    Text count_of_cooper_mines(423, 315, 250, 50, 20, "Количество шахт:");
    Text count_of_titan_mines(423, 411, 250, 50, 20, "Количество шахт:");
    Text count_of_aluminium_mines(423, 507, 250, 50, 20, "Количество шахт:");
    Text count_of_magnesium_mines(423, 603, 250, 50, 20, "Количество шахт:");
    Text count_of_oil_pumping(423, 699, 250, 50, 20, "Количество вышек:");

    // Счетчики шахт
    Count_of_coal_mines = new Fl_Box(675, 123, 100, 50, "0");
    Count_of_coal_mines->labelsize(20);
    Count_of_coal_mines->box(FL_BORDER_BOX);
    Count_of_coal_mines->align(FL_ALIGN_CENTER);
    Count_of_coal_mines->labelfont(FL_COURIER_BOLD);

    Count_of_iron_mines = new Fl_Box(675, 219, 100, 50, "0");
    Count_of_iron_mines->labelsize(20);
    Count_of_iron_mines->box(FL_BORDER_BOX);
    Count_of_iron_mines->align(FL_ALIGN_CENTER);
    Count_of_iron_mines->labelfont(FL_COURIER_BOLD);

    Count_of_cooper_mines = new Fl_Box(675, 315, 100, 50, "0");
    Count_of_cooper_mines->labelsize(20);
    Count_of_cooper_mines->box(FL_BORDER_BOX);
    Count_of_cooper_mines->align(FL_ALIGN_CENTER);
    Count_of_cooper_mines->labelfont(FL_COURIER_BOLD);

    Count_of_titan_mines = new Fl_Box(675, 411, 100, 50, "0");
    Count_of_titan_mines->labelsize(20);
    Count_of_titan_mines->box(FL_BORDER_BOX);
    Count_of_titan_mines->align(FL_ALIGN_CENTER);
    Count_of_titan_mines->labelfont(FL_COURIER_BOLD);

    Count_of_aluminium_mines = new Fl_Box(675, 507, 100, 50, "0");
    Count_of_aluminium_mines->labelsize(20);
    Count_of_aluminium_mines->box(FL_BORDER_BOX);
    Count_of_aluminium_mines->align(FL_ALIGN_CENTER);
    Count_of_aluminium_mines->labelfont(FL_COURIER_BOLD);

    Count_of_magnesium_mines = new Fl_Box(675, 603, 100, 50, "0");
    Count_of_magnesium_mines->labelsize(20);
    Count_of_magnesium_mines->box(FL_BORDER_BOX);
    Count_of_magnesium_mines->align(FL_ALIGN_CENTER);
    Count_of_magnesium_mines->labelfont(FL_COURIER_BOLD);

    Count_of_oil_pumping = new Fl_Box(675, 699, 100, 50, "0");
    Count_of_oil_pumping->labelsize(20);
    Count_of_oil_pumping->box(FL_BORDER_BOX);
    Count_of_oil_pumping->align(FL_ALIGN_CENTER);
    Count_of_oil_pumping->labelfont(FL_COURIER_BOLD);

    // Деньги
    Text money_Title(1129, 330, 250, 50, 20, "Баланс");
    Money_Mines_Earth = new Fl_Box(1129, 382, 250, 50, "0 M");
    Money_Mines_Earth->labelsize(20);
    Money_Mines_Earth->box(FL_BORDER_BOX);
    Money_Mines_Earth->align(FL_ALIGN_CENTER);
    Money_Mines_Earth->labelfont(FL_COURIER_BOLD);

    // Первоначальное обновление данных
    refreshAll();
}

MinesWindowEarth::~MinesWindowEarth() {
    // ТАЙМЕР УБРАН - НИЧЕГО НЕ УДАЛЯЕМ
    
    // Освобождаем память
    delete buy_coal_mine;
    delete buy_iron_mine;
    delete buy_cooper_mine;
    delete buy_titan_mine;
    delete buy_aluminium_mine;
    delete buy_magnesium_mine;
    delete buy_oil_pumping;
}

void MinesWindowEarth::refreshAll() {
    // Обновляем счетчики шахт
    std::string ColonInfoCoalMines = std::to_string(EarthMines.at("CoalMine").getCount());
    Count_of_coal_mines->copy_label(ColonInfoCoalMines.c_str());

    std::string ColonInfoIronMines = std::to_string(EarthMines.at("IronMine").getCount());
    Count_of_iron_mines->copy_label(ColonInfoIronMines.c_str());

    std::string ColonInfoCooperMines = std::to_string(EarthMines.at("CooperMine").getCount());
    Count_of_cooper_mines->copy_label(ColonInfoCooperMines.c_str());

    std::string ColonInfoTitanMines = std::to_string(EarthMines.at("TitanMine").getCount());
    Count_of_titan_mines->copy_label(ColonInfoTitanMines.c_str());

    std::string ColonInfoAluminiumMines = std::to_string(EarthMines.at("AluminiumMine").getCount());
    Count_of_aluminium_mines->copy_label(ColonInfoAluminiumMines.c_str());

    std::string ColonInfoMagnesiumMines = std::to_string(EarthMines.at("MagnesiumMine").getCount());
    Count_of_magnesium_mines->copy_label(ColonInfoMagnesiumMines.c_str());

    std::string ColonInfoOilPumping = std::to_string(EarthMines.at("OilPumping").getCount());
    Count_of_oil_pumping->copy_label(ColonInfoOilPumping.c_str());

    // Обновляем деньги
    std::string newText = std::to_string(Player.getMoney()) + " M";
    Money_Mines_Earth->copy_label(newText.c_str());

    // Обновляем состояние кнопок
    updateButtonsState();

    // Перерисовываем окно
    if (window->visible()) {
        window->redraw();
    }
}

void MinesWindowEarth::updateButtonsState() {
    // Угольная шахта
    if (Player.getMoney() >= EarthMines.at("CoalMine").getPrice() && 
        EarthMines.at("CoalMine").getCount() < EarthMines.at("CoalMine").getMaxCountOfMines()) {
        buy_coal_mine->activate();
        buy_coal_mine->setColor(FL_GREEN);
    } else {
        buy_coal_mine->deactivate();
        buy_coal_mine->setColor(FL_RED);
    }

    // Железная шахта
    if (Player.getMoney() >= EarthMines.at("IronMine").getPrice() && 
        EarthMines.at("IronMine").getCount() < EarthMines.at("IronMine").getMaxCountOfMines()) {
        buy_iron_mine->activate();
        buy_iron_mine->setColor(FL_GREEN);
    } else {
        buy_iron_mine->deactivate();
        buy_iron_mine->setColor(FL_RED);
    }

    // Медная шахта
    if (Player.getMoney() >= EarthMines.at("CooperMine").getPrice() && 
        EarthMines.at("CooperMine").getCount() < EarthMines.at("CooperMine").getMaxCountOfMines()) {
        buy_cooper_mine->activate();
        buy_cooper_mine->setColor(FL_GREEN);
    } else {
        buy_cooper_mine->deactivate();
        buy_cooper_mine->setColor(FL_RED);
    }

    // Титановая шахта
    if (Player.getMoney() >= EarthMines.at("TitanMine").getPrice() && 
        EarthMines.at("TitanMine").getCount() < EarthMines.at("TitanMine").getMaxCountOfMines()) {
        buy_titan_mine->activate();
        buy_titan_mine->setColor(FL_GREEN);
    } else {
        buy_titan_mine->deactivate();
        buy_titan_mine->setColor(FL_RED);
    }

    // Алюминиевая шахта
    if (Player.getMoney() >= EarthMines.at("AluminiumMine").getPrice() && 
        EarthMines.at("AluminiumMine").getCount() < EarthMines.at("AluminiumMine").getMaxCountOfMines()) {
        buy_aluminium_mine->activate();
        buy_aluminium_mine->setColor(FL_GREEN);
    } else {
        buy_aluminium_mine->deactivate();
        buy_aluminium_mine->setColor(FL_RED);
    }

    // Магниевая шахта
    if (Player.getMoney() >= EarthMines.at("MagnesiumMine").getPrice() && 
        EarthMines.at("MagnesiumMine").getCount() < EarthMines.at("MagnesiumMine").getMaxCountOfMines()) {
        buy_magnesium_mine->activate();
        buy_magnesium_mine->setColor(FL_GREEN);
    } else {
        buy_magnesium_mine->deactivate();
        buy_magnesium_mine->setColor(FL_RED);
    }

    // Нефтяная вышка
    if (Player.getMoney() >= EarthMines.at("OilPumping").getPrice() && 
        EarthMines.at("OilPumping").getCount() < EarthMines.at("OilPumping").getMaxCountOfMines()) {
        buy_oil_pumping->activate();
        buy_oil_pumping->setColor(FL_GREEN);
    } else {
        buy_oil_pumping->deactivate();
        buy_oil_pumping->setColor(FL_RED);
    }
}

// ФУНКЦИЯ ДЛЯ ТАЙМЕРА - УБИРАЕМ ВОВСЕ
// void MinesWindowEarth::updateData(void* data) {
//     // ЭТУ ФУНКЦИЮ УДАЛЯЕМ
// }

void MinesWindowEarth::show() {
    window->show();
    // НЕ ЗАПУСКАЕМ ТАЙМЕР - обновляем только при действиях
    refreshAll(); // однократное обновление при показе
}

void MinesWindowEarth::hide() {
    // НЕ ОСТАНАВЛИВАЕМ ТАЙМЕР - его нет
    window->hide();
}

void MinesWindowEarth::back_cb(Fl_Widget* w, void* data) {
    MinesWindowEarth* minesWin = (MinesWindowEarth*)data;
    minesWin->return_to_main();
}

void MinesWindowEarth::return_to_main() {
    mainWindow->show();
    this->hide();
}