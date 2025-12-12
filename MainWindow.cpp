#include "MainWindow.h"
#include "PlanetsWindow.h"
#include "MinesWindowEarth.h"
#include "MinesWindowMoon.h"
#include "MinesWindowMars.h"
#include "RecourcesMainWindow.h"
#include "ResearchesWindow.h"
#include "CraftsWindow.h"
#include "SaveMenuWindow.h"  // Добавляем заголовок
#include "Config.h"
#include <windows.h>
#include <mmsystem.h>

// Глобальные переменные (как было)
Fl_Box* Money;

// СТАТИЧЕСКИЕ ИЗОБРАЖЕНИЯ (как было + добавляем для сохранения)
static Fl_PNG_Image* static_bg = nullptr;
static Fl_PNG_Image* static_bur_img = nullptr;
static Fl_PNG_Image* static_rudy_img = nullptr;
static Fl_PNG_Image* static_lupa_img = nullptr;
static Fl_PNG_Image* static_raketa_img = nullptr;
static Fl_PNG_Image* static_save_menu_img = nullptr;  // Добавляем

class MainWindowText : public Text {
private:
    static const int width = 250;
    static const int height = 50;
    static const int size = 20;

public:
    MainWindowText(int x, int y, const std::string& content) 
        : Text(x, y, width, height, size, content){}
};

// Callback для планеты (как было, обычная функция)
void ButtonPlanetCallback(Fl_Widget* widget, void* data){
    Player.setMoney(Player.getMoney() + Player.getPlanet()->getProfit());
    std::string newText = std::to_string(Player.getMoney()) + " M";
    Money->copy_label(newText.c_str());
}

// СТАТИЧЕСКИЕ CALLBACK ФУНКЦИИ (как было + добавляем для сохранения)
void MainWindow::open_planets_cb(Fl_Widget* w, void* data) {
    MainWindow* mainWin = (MainWindow*)data;
    mainWin->open_planets_window();
}

void MainWindow::open_recources_main_cb(Fl_Widget* w, void* data) {
    MainWindow* mainWin = (MainWindow*)data;
    mainWin->open_recources_main_window();
}

void MainWindow::open_researches_cb(Fl_Widget* w, void* data) {
    MainWindow* mainWin = (MainWindow*)data;
    mainWin->open_researches_window();
}

void MainWindow::open_crafts_cb(Fl_Widget* w, void* data) {
    MainWindow* mainWin = (MainWindow*)data;
    mainWin->open_crafts_window();
}

void MainWindow::open_mines_earth_cb(Fl_Widget* w, void* data) {
    MainWindow* mainWin = (MainWindow*)data;
    mainWin->open_mines_window_earth();
}

void MainWindow::open_mines_moon_cb(Fl_Widget* w, void* data) {
    MainWindow* mainWin = (MainWindow*)data;
    mainWin->open_mines_window_moon();
}

void MainWindow::open_mines_mars_cb(Fl_Widget* w, void* data) {
    MainWindow* mainWin = (MainWindow*)data;
    mainWin->open_mines_window_mars();
}

// Добавляем callback для кнопки сохранения
void MainWindow::open_save_menu_cb(Fl_Widget* w, void* data) {
    MainWindow* mainWin = (MainWindow*)data;
    mainWin->open_save_menu_window();
}

// КОНСТРУКТОР (добавляем кнопку сохранения)
MainWindow::MainWindow() {
    window = new Fl_Window(1440, 820, "Главное меню");
    window->position(10, 10);

    Config& config = Config::getInstance();
    
    // ЗАГРУЖАЕМ ИЗОБРАЖЕНИЯ (как было + добавляем для сохранения)
    if (!static_bg) {
        static_bg = new Fl_PNG_Image(config.getPicturePath("Небо.png").c_str());
        static_bur_img = new Fl_PNG_Image(config.getPicturePath("Бур.png").c_str());
        static_rudy_img = new Fl_PNG_Image(config.getPicturePath("Руды.png").c_str());
        static_lupa_img = new Fl_PNG_Image(config.getPicturePath("Лупа.png").c_str());
        static_raketa_img = new Fl_PNG_Image(config.getPicturePath("Ракета2.png").c_str());
        static_save_menu_img = new Fl_PNG_Image(config.getPicturePath("МенюСохранения.png").c_str());  // Добавляем
    }

    bg = static_bg;
    background = new Fl_Box(0, 0, 1440, 820);
    background->image(bg);
    
    // Текстовые заголовки (как было + добавляем для сохранения)
    MainWindowText recource_extraction_Title(30, 30, "Добыча ресурсов");
    MainWindowText recources_Title(30, 180, "Ресурсы");
    MainWindowText researches_Title(30, 330, "Исследования");
    MainWindowText crafts_Title(30, 480, "Создание ракет");
    MainWindowText choose_other_planet_Title(30, 630, "Поменять планету");
    MainWindowText money_Title(1129, 330, "Баланс");
    MainWindowText save_menu_Title(1160, 30, "Сохранение игры");  // Добавляем

    // Отображение денег (как было)
    Money = new Fl_Box(1129, 382, 250, 50, "0 M");
    Money->labelsize(20);
    Money->box(FL_BORDER_BOX);
    Money->align(FL_ALIGN_CENTER);
    Money->labelfont(FL_COURIER_BOLD);

    // Первоначальное обновление денег
    updateMoneyDisplay();

    // Инициализируем указатель на окно сохранения
    saveMenuWin = nullptr;

    // Кнопки (как было)
    recources_Button = new PictureButton(105, 232, 96, 96, static_rudy_img);
    recources_Button->getButton()->callback(open_recources_main_cb, this);

    researches_Button = new PictureButton(105, 382, 96, 96, static_lupa_img);
    researches_Button->getButton()->callback(open_researches_cb, this);
    
    crafts_Button = new PictureButton(105, 532, 96, 96, static_raketa_img);
    crafts_Button->getButton()->callback(open_crafts_cb, this);
    
    // ПЛАНЕТЫ (как было)
    planet_Button = new PictureButton(300, 30, 768, 768, Player.getPlanet()->getPathToBigPNG().c_str());
    planet_Button->getButton()->callback(ButtonPlanetCallback);  // Как было

    // Кнопка шахт (как было)
    mines_Button = new PictureButton(105, 82, 96, 96, static_bur_img);

    choose_other_planet_Button = new PictureButton(105, 682, 96, 96, Player.getPlanet()->getPathToSmallPNG().c_str());
    choose_other_planet_Button->getButton()->callback(open_planets_cb, this);

    // Кнопка меню сохранения (добавляем в правый верхний угол)
    // mines_Button: x=105, y=82 (левая сторона)
    // saveMenuButton: x=1440-105-96=1239, y=82 (правая сторона, симметрично)
    saveMenuButton = new PictureButton(1239, 82, 96, 96, static_save_menu_img);
    saveMenuButton->getButton()->callback(open_save_menu_cb, this);
    saveMenuButton->getButton()->tooltip("Открыть меню сохранения игры");

    window->end();
}

// ДЕСТРУКТОР (добавляем очистку для кнопки сохранения)
MainWindow::~MainWindow() {
    // Удаляем кнопку сохранения
    if (saveMenuButton) {
        delete saveMenuButton;
    }
    
    // Удаляем окно сохранения, если оно было создано
    if (saveMenuWin) {
        delete saveMenuWin;
    }
}

// Метод show (как было)
void MainWindow::show() {
    updatePlanetDisplay();
    updateMoneyDisplay();
    updateMinesButton();
    window->show();
}

void MainWindow::hide() {
    window->hide();
}

void MainWindow::updatePlanetDisplay() {
    planet_Button->updateImage(Player.getPlanet()->getPathToBigPNG().c_str());
    choose_other_planet_Button->updateImage(Player.getPlanet()->getPathToSmallPNG().c_str());
}

void MainWindow::updateMoneyDisplay() {
    std::string newText = std::to_string(Player.getMoney()) + " M";
    Money->copy_label(newText.c_str());
    
    if (window->visible()) {
        window->redraw();
    }
}

void MainWindow::updateMinesButton() {
    // ЯВНОЕ ПРИВЕДЕНИЕ ТИПА (как было)
    mines_Button->getButton()->callback((Fl_Callback*)0);
    
    if(Player.getPlanet()->getName() == "Земля") {
        mines_Button->getButton()->callback(open_mines_earth_cb, this);
    }
    else if(Player.getPlanet()->getName() == "Луна") {
        mines_Button->getButton()->callback(open_mines_moon_cb, this);
    }
    else if(Player.getPlanet()->getName() == "Марс") {
        mines_Button->getButton()->callback(open_mines_mars_cb, this);
    }
    
    mines_Button->getButton()->redraw();
}

// Методы открытия окон (как было)
void MainWindow::open_planets_window() {
    PlanetsWindow* planetsWin = new PlanetsWindow(this);
    planetsWin->show();
    this->hide();
}

void MainWindow::open_recources_main_window() {
    RecourcesMainWindow* recourcesWin = new RecourcesMainWindow(this);
    recourcesWin->show();
    this->hide();
}

void MainWindow::open_researches_window() {
    ResearchesWindow* recearchesWin = new ResearchesWindow(this);
    recearchesWin->show();
    this->hide();
}

void MainWindow::open_crafts_window() {
    CraftsWindow* craftsWin = new CraftsWindow(this);
    craftsWin->show();
    this->hide();
}

void MainWindow::open_mines_window_earth() {
    MinesWindowEarth* minesWin = new MinesWindowEarth(this);
    minesWin->show();
    this->hide();
}

void MainWindow::open_mines_window_moon() {
    MinesWindowMoon* minesWin = new MinesWindowMoon(this);
    minesWin->show();
    this->hide();
}

void MainWindow::open_mines_window_mars() {
    MinesWindowMars* minesWin = new MinesWindowMars(this);
    minesWin->show();
    this->hide();
}

// Добавляем метод для открытия окна сохранения
void MainWindow::open_save_menu_window() {
    // Создаем окно сохранения только при первом вызове
    if (!saveMenuWin) {
        saveMenuWin = new SaveMenuWindow(this);
    }
    saveMenuWin->show();
    this->hide();
}