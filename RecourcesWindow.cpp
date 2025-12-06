#include "RecourcesWindow.h"
#include "RecourcesMainWindow.h" 
#include "Mines.h"
#include "Config.h"
#include <windows.h>
#include <mmsystem.h>

static Fl_PNG_Image* static_bg = nullptr;
static Fl_PNG_Image* static_arrow = nullptr;

// ГЛОБАЛЬНЫЙ УКАЗАТЕЛЬ НА ТЕКУЩЕЕ ОКНО РЕСУРСОВ
static RecourcesWindow* currentResourcesWindow = nullptr;

RecourcesWindow::RecourcesWindow(RecourcesMainWindow* mainWin){
    resWindow = mainWin;
    
    // СОХРАНЯЕМ СЕБЯ В ГЛОБАЛЬНЫЙ УКАЗАТЕЛЬ
    currentResourcesWindow = this;

    window = new Fl_Window(1440, 820, "Ресурсы");
    window->position(10, 10);

    Config& config = Config::getInstance();
    
    // ЗАГРУЖАЕМ ИЗОБРАЖЕНИЯ ТОЛЬКО ПРИ ПЕРВОМ СОЗДАНИИ
    if (!static_bg) {
        static_bg = new Fl_PNG_Image(config.getPicturePath("Небо.png").c_str());
        static_arrow = new Fl_PNG_Image(config.getPicturePath("Cтрелка.png").c_str());
    }

    bg = static_bg;
    background = new Fl_Box(0, 0, 1440, 820);
    background->image(bg);

    // ИСПОЛЬЗУЕМ УЖЕ ЗАГРУЖЕННЫЕ ИЗОБРАЖЕНИЯ
    back_Button = new PictureButton(0, 0, 96, 96, static_arrow);
    back_Button->getButton()->callback(back_cb, this);

    // ЖЕЛЕЗО
    std::string ironPath = config.getPicturePath("Железо.png");
    Picture iron_picture(100, 100, 96, 96, ironPath.c_str());
    Text iron_count_Title(196, 123, 250, 50, 20, "Количество железа");
    Iron_Count = new Fl_Box(448, 123, 100, 50, "0");
    Iron_Count->labelsize(20);
    Iron_Count->box(FL_BORDER_BOX);
    Iron_Count->align(FL_ALIGN_CENTER);
    Iron_Count->labelfont(FL_COURIER_BOLD);

    // УГОЛЬ
    std::string coalPath = config.getPicturePath("Уголь.png");
    Picture coal_picture(100, 196, 96, 96, coalPath.c_str());
    Text coal_count_Title(196, 219, 250, 50, 20, "Количество угля");
    Coal_Count = new Fl_Box(448, 219, 100, 50, "0");
    Coal_Count->labelsize(20);
    Coal_Count->box(FL_BORDER_BOX);
    Coal_Count->align(FL_ALIGN_CENTER);
    Coal_Count->labelfont(FL_COURIER_BOLD);

    // МЕДЬ
    std::string copperPath = config.getPicturePath("Медь.png");
    Picture copper_picture(100, 292, 96, 96, copperPath.c_str());
    Text copper_count_Title(196, 315, 250, 50, 20, "Количество меди");
    Copper_Count = new Fl_Box(448, 315, 100, 50, "0");
    Copper_Count->labelsize(20);
    Copper_Count->box(FL_BORDER_BOX);
    Copper_Count->align(FL_ALIGN_CENTER);
    Copper_Count->labelfont(FL_COURIER_BOLD);

    // АЛЮМИНИЙ
    std::string aluminiumPath = config.getPicturePath("Алюминий.png");
    Picture aluminium_picture(100, 388, 96, 96, aluminiumPath.c_str());
    Text aluminium_count_Title(196, 411, 250, 50, 20, "Количество алюминия");
    Aluminium_Count = new Fl_Box(448, 411, 100, 50, "0");
    Aluminium_Count->labelsize(20);
    Aluminium_Count->box(FL_BORDER_BOX);
    Aluminium_Count->align(FL_ALIGN_CENTER);
    Aluminium_Count->labelfont(FL_COURIER_BOLD);

    // ТИТАН
    std::string titaniumPath = config.getPicturePath("Титан.png");
    Picture titanium_picture(100, 484, 96, 96, titaniumPath.c_str());
    Text titanium_count_Title(196, 507, 250, 50, 20, "Количество титана");
    Titanium_Count = new Fl_Box(448, 507, 100, 50, "0");
    Titanium_Count->labelsize(20);
    Titanium_Count->box(FL_BORDER_BOX);
    Titanium_Count->align(FL_ALIGN_CENTER);
    Titanium_Count->labelfont(FL_COURIER_BOLD);

    // МАГНИЙ
    std::string magnesiumPath = config.getPicturePath("Магний.png");
    Picture magnesium_picture(100, 580, 96, 96, magnesiumPath.c_str());
    Text magnesium_count_Title(196, 603, 250, 50, 20, "Количество магния");
    Magnesium_Count = new Fl_Box(448, 603, 100, 50, "0");
    Magnesium_Count->labelsize(20);
    Magnesium_Count->box(FL_BORDER_BOX);
    Magnesium_Count->align(FL_ALIGN_CENTER);
    Magnesium_Count->labelfont(FL_COURIER_BOLD);

    // НЕФТЬ
    std::string oilPath = config.getPicturePath("Нефть.png");
    Picture oil_picture(100, 676, 96, 96, oilPath.c_str());
    Text oil_count_Title(196, 699, 250, 50, 20, "Количество нефти");
    Oil_Count = new Fl_Box(448, 699, 100, 50, "0");
    Oil_Count->labelsize(20);
    Oil_Count->box(FL_BORDER_BOX);
    Oil_Count->align(FL_ALIGN_CENTER);
    Oil_Count->labelfont(FL_COURIER_BOLD);

    // НИКЕЛЬ
    std::string nickelPath = config.getPicturePath("Никель.png");
    Picture nickel_picture(600, 100, 96, 96, nickelPath.c_str());
    Text nickel_count_Title(696, 123, 250, 50, 20, "Количество никеля");
    Nickel_Count = new Fl_Box(948, 123, 100, 50, "0");
    Nickel_Count->labelsize(20);
    Nickel_Count->box(FL_BORDER_BOX);
    Nickel_Count->align(FL_ALIGN_CENTER);
    Nickel_Count->labelfont(FL_COURIER_BOLD);

    // КОБАЛЬТ
    std::string cobaltPath = config.getPicturePath("Кобальт.png");
    Picture cobalt_picture(600, 196, 96, 96, cobaltPath.c_str());
    Text cobalt_count_Title(696, 219, 250, 50, 20, "Количество кобальта");
    Cobalt_Count = new Fl_Box(948, 219, 100, 50, "0");
    Cobalt_Count->labelsize(20);
    Cobalt_Count->box(FL_BORDER_BOX);
    Cobalt_Count->align(FL_ALIGN_CENTER);
    Cobalt_Count->labelfont(FL_COURIER_BOLD);

    // Первоначальное обновление
    refreshAll();
}

RecourcesWindow::~RecourcesWindow() {
    // ЕСЛИ ЭТО ТЕКУЩЕЕ ОКНО - ОБНУЛЯЕМ УКАЗАТЕЛЬ
    if (currentResourcesWindow == this) {
        currentResourcesWindow = nullptr;
    }
}

// СТАТИЧЕСКИЙ МЕТОД ДЛЯ ПОЛУЧЕНИЯ ТЕКУЩЕГО ОКНА
RecourcesWindow* RecourcesWindow::getCurrentWindow() {
    return currentResourcesWindow;
}

// МЕТОД ДЛЯ ОБНОВЛЕНИЯ ВСЕХ ДАННЫХ
void RecourcesWindow::refreshAll() {
    // Обновляем все ресурсы
    std::string ironText = std::to_string(iron);
    Iron_Count->copy_label(ironText.c_str());

    std::string coalText = std::to_string(coal);
    Coal_Count->copy_label(coalText.c_str());

    std::string copperText = std::to_string(copper);
    Copper_Count->copy_label(copperText.c_str());

    std::string aluminiumText = std::to_string(aluminium);
    Aluminium_Count->copy_label(aluminiumText.c_str());

    std::string titaniumText = std::to_string(titanium);
    Titanium_Count->copy_label(titaniumText.c_str());

    std::string magnesiumText = std::to_string(magnesium);
    Magnesium_Count->copy_label(magnesiumText.c_str());

    std::string oilText = std::to_string(oil);
    Oil_Count->copy_label(oilText.c_str());

    std::string nickelText = std::to_string(nickel);
    Nickel_Count->copy_label(nickelText.c_str());

    std::string cobaltText = std::to_string(cobalt);
    Cobalt_Count->copy_label(cobaltText.c_str());
    
    // Перерисовываем окно
    if (window->visible()) {
        window->redraw();
    }
}

// ПУБЛИЧНЫЙ МЕТОД ДЛЯ ВНЕШНЕГО ОБНОВЛЕНИЯ
void RecourcesWindow::refreshResources() {
    refreshAll();
}

void RecourcesWindow::show() {
    window->show();
    // ОБНОВЛЯЕМ ДАННЫЕ ПРИ ПОКАЗЕ
    refreshAll();
}

void RecourcesWindow::hide() {
    window->hide();
}

void RecourcesWindow::back_cb(Fl_Widget* w, void* data) {
    RecourcesWindow* resWin = (RecourcesWindow*)data;
    resWin->return_to_main();
}

void RecourcesWindow::return_to_main() {
    resWindow->show();
    this->hide();
}