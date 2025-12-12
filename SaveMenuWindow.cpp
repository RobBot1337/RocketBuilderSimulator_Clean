#include "SaveMenuWindow.h"
#include "MainWindow.h"
#include "Config.h"
#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <iostream>
#include <fstream>
#include <sys/stat.h>

static Fl_PNG_Image* static_bg = nullptr;
static Fl_PNG_Image* static_arrow = nullptr;
static Fl_PNG_Image* static_save_icon = nullptr;
static Fl_PNG_Image* static_load_icon = nullptr;
static Fl_PNG_Image* static_new_icon = nullptr;
static Fl_PNG_Image* static_exit_icon = nullptr;

std::string getSaveFileTime() {
    std::ifstream file("savegame.dat", std::ios::binary);
    if (!file.is_open()) {
        return "Сохранение не найдено";
    }
    
    struct stat fileInfo;
    if (stat("savegame.dat", &fileInfo) == 0) {
        std::time_t time = fileInfo.st_mtime;
        std::tm* tm = std::localtime(&time);
        
        std::stringstream ss;
        ss << std::put_time(tm, "%d.%m.%Y %H:%M:%S");
        return "Последнее сохранение: " + ss.str();
    }
    
    return "Время сохранения неизвестно";
}

SaveMenuWindow::SaveMenuWindow(MainWindow* mainWin) {
    mainWindow = mainWin;

    window = new Fl_Window(1440, 820, "Меню сохранения");
    window->position(10, 10);

    Config& config = Config::getInstance();
    
    if (!static_bg) {
        static_bg = new Fl_PNG_Image(config.getPicturePath("Небо.png").c_str());
        static_arrow = new Fl_PNG_Image(config.getPicturePath("Cтрелка.png").c_str());
        static_save_icon = new Fl_PNG_Image(config.getPicturePath("Сохранить.png").c_str());
        static_load_icon = new Fl_PNG_Image(config.getPicturePath("Загрузить.png").c_str());
        static_new_icon = new Fl_PNG_Image(config.getPicturePath("НоваяИгра.png").c_str());
        static_exit_icon = new Fl_PNG_Image(config.getPicturePath("Выход.png").c_str());
    }

    // Фон
    Fl_Box* background = new Fl_Box(0, 0, 1440, 820);
    background->image(static_bg);

    // Кнопка назад - PictureButton
    backButton = new PictureButton(0, 0, 96, 96, static_arrow);
    backButton->getButton()->callback(back_cb, this);

    // Просто картинка Сохранить (Picture)
    savePicture = new Fl_Box(320, 240, 96, 96);
    savePicture->image(static_save_icon);

    // Просто картинка Загрузить (Picture)
    loadPicture = new Fl_Box(320, 366, 96, 96);
    loadPicture->image(static_load_icon);

    // Просто картинка Новая игра (Picture)
    newPicture = new Fl_Box(320, 492, 96, 96);
    newPicture->image(static_new_icon);

    // Просто картинка Выход (Picture)
    exitPicture = new Fl_Box(320, 618, 96, 96);
    exitPicture->image(static_exit_icon);

    // ТАКОЙ ЖЕ ШРИФТ КАК В MAINWINDOW
    const int BUTTON_FONT_SIZE = 20;  // ТАКОЙ ЖЕ РАЗМЕР КАК У Money (20)
    
    // Кнопка Сохранить игру (Button)
    saveGameButton = new Button(436, 240, 684, 96, BUTTON_FONT_SIZE, "Сохранить игру");
    saveGameButton->getButton()->callback(saveGame_cb, this);
    saveGameButton->getButton()->labelfont(FL_COURIER_BOLD);  // ТАКОЙ ЖЕ ШРИФТ КАК У Money

    // Кнопка Загрузить игру (Button)
    loadGameButton = new Button(436, 366, 684, 96, BUTTON_FONT_SIZE, "Загрузить игру");
    loadGameButton->getButton()->callback(loadGame_cb, this);
    loadGameButton->getButton()->labelfont(FL_COURIER_BOLD);

    // Кнопка Новая игра (Button)
    newGameButton = new Button(436, 492, 684, 96, BUTTON_FONT_SIZE, "Новая игра");
    newGameButton->getButton()->callback(newGame_cb, this);
    newGameButton->getButton()->labelfont(FL_COURIER_BOLD);

    // Кнопка Выйти из игры (Button)
    exitGameButton = new Button(436, 618, 684, 96, BUTTON_FONT_SIZE, "Выйти из игры");
    exitGameButton->getButton()->callback(exitGame_cb, this);
    exitGameButton->getButton()->labelfont(FL_COURIER_BOLD);

    window->end();
}

SaveMenuWindow::~SaveMenuWindow() {
    delete saveGameButton;
    delete loadGameButton;
    delete newGameButton;
    delete exitGameButton;
    delete backButton;
    delete window;
}

void SaveMenuWindow::back_cb(Fl_Widget* w, void* data) {
    SaveMenuWindow* win = (SaveMenuWindow*)data;
    win->returnToMain();
}

void SaveMenuWindow::saveGame_cb(Fl_Widget* w, void* data) {
    SaveMenuWindow* win = (SaveMenuWindow*)data;
    
    if (GameSave::getInstance().saveGame()) {
        fl_alert("Игра успешно сохранена!");
    }
}

void SaveMenuWindow::loadGame_cb(Fl_Widget* w, void* data) {
    SaveMenuWindow* win = (SaveMenuWindow*)data;
    
    if (GameSave::getInstance().loadGame()) {
        fl_alert("Игра успешно загружена!");
        win->returnToMain();
    }
}

void SaveMenuWindow::newGame_cb(Fl_Widget* w, void* data) {
    SaveMenuWindow* win = (SaveMenuWindow*)data;
    
    int choice = fl_choice("Начать новую игру?", "Отмена", "Начать", NULL);
    if (choice == 1) {
        // Используем GameSave::newGame() вместо ручного сброса
        if (GameSave::getInstance().newGame()) {
            fl_alert("Новая игра начата!");
            win->returnToMain();
        } else {
            fl_alert("Ошибка при создании новой игры!");
        }
    }
}

void SaveMenuWindow::exitGame_cb(Fl_Widget* w, void* data) {
    int choice = fl_choice("Выйти из игры?", "Отмена", "Выйти", NULL);
    if (choice == 1) {
        exit(0);
    }
}

void SaveMenuWindow::show() {
    window->show();
}

void SaveMenuWindow::hide() {
    window->hide();
}

void SaveMenuWindow::returnToMain() {
    if (mainWindow) {
        mainWindow->show();
    }
    this->hide();
}

void SaveMenuWindow::updateSaveInfo() {
    // Если не используешь, можно оставить пустым
}