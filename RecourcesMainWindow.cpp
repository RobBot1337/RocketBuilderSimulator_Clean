#include "RecourcesMainWindow.h"
#include "RecourcesWindow.h"
#include "AlloysWindow.h"
#include "MainWindow.h" 
#include "Config.h"
#include <windows.h>
#include <mmsystem.h>

static Fl_PNG_Image* static_bg = nullptr;
static Fl_PNG_Image* static_arrow = nullptr;
static Fl_PNG_Image* static_simple_recources = nullptr;
static Fl_PNG_Image* static_alloys = nullptr;

void RecourcesMainWindow::open_recources_cb(Fl_Widget* w, void* data) {
    RecourcesMainWindow* resMainWin = (RecourcesMainWindow*)data;
    resMainWin->open_recources_window();
}
void RecourcesMainWindow::open_alloys_cb(Fl_Widget* w, void* data) {
    RecourcesMainWindow* resMainWin = (RecourcesMainWindow*)data;
    resMainWin->open_alloys_window();
}

RecourcesMainWindow::RecourcesMainWindow(MainWindow* mainWin){
    mainWindow = mainWin;

    window = new Fl_Window(1440, 820, "Ресурсы");
    window->position(10, 10);

    Config& config = Config::getInstance();
    
    // ЗАГРУЖАЕМ ИЗОБРАЖЕНИЯ ТОЛЬКО ПРИ ПЕРВОМ СОЗДАНИИ
    if (!static_bg) {
        static_bg = new Fl_PNG_Image(config.getPicturePath("Небо.png").c_str());
        static_arrow = new Fl_PNG_Image(config.getPicturePath("Cтрелка.png").c_str());
        static_simple_recources = new Fl_PNG_Image(config.getPicturePath("Руды.png").c_str());
        static_alloys = new Fl_PNG_Image(config.getPicturePath("Сталь.png").c_str());
    }

    bg = static_bg;
    background = new Fl_Box(0, 0, 1440, 820);
    background->image(bg);

    // ИСПОЛЬЗУЕМ УЖЕ ЗАГРУЖЕННЫЕ ИЗОБРАЖЕНИЯ
    back_Button = new PictureButton(0, 0, 96, 96, static_arrow);
    back_Button->getButton()->callback(back_cb, this);

    Text simple_resources_title(400, 300, 300, 60, 28, "Ресурсы");
    Text alloys_title(740, 300, 300, 60, 28, "Сплавы"); 

    simple_recources_Button = new PictureButton(502, 380, 96, 96, static_simple_recources);
    simple_recources_Button->getButton()->callback(open_recources_cb, this);
    simple_recources_Button->getButton()->tooltip("Просмотреть базовые ресурсы");

    alloys_Button = new PictureButton(842, 380, 96, 96, static_alloys);
    alloys_Button->getButton()->callback(open_alloys_cb, this);
    alloys_Button->getButton()->tooltip("Просмотреть сплавы и созданные материалы");
}

void RecourcesMainWindow::show() {
    window->show();
}

void RecourcesMainWindow::hide() {
    window->hide();
}

void RecourcesMainWindow::back_cb(Fl_Widget* w, void* data) {
    RecourcesMainWindow* planetsWin = (RecourcesMainWindow*)data;
    planetsWin->return_to_main();
}

void RecourcesMainWindow::return_to_main() {
    mainWindow->show();
    this->hide();
}

void RecourcesMainWindow::open_recources_window() {
    RecourcesWindow* recWin = new RecourcesWindow(this);
    recWin->show();
    this->hide();
}

void RecourcesMainWindow::open_alloys_window() {
    AlloysWindow* allWin = new AlloysWindow(this);
    allWin->show();
    this->hide();
}