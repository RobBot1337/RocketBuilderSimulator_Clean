#ifndef SAVEMENUWINDOW_H
#define SAVEMENUWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include "UI_widgets.h"      // Здесь уже есть Button и PictureButton
#include "GameSave.h"

class MainWindow;

class SaveMenuWindow {
private:
    Fl_Window* window;
    MainWindow* mainWindow;
    
    PictureButton* backButton;          // PictureButton для назад
    Button* saveGameButton;             // Button для сохранения
    Button* loadGameButton;             // Button для загрузки
    Button* newGameButton;              // Button для новой игры
    Button* exitGameButton;             // Button для выхода
    
    Fl_Box* savePicture;                // Picture (просто картинка)
    Fl_Box* loadPicture;                // Picture (просто картинка)
    Fl_Box* newPicture;                 // Picture (просто картинка)
    Fl_Box* exitPicture;                // Picture (просто картинка)
    
    // Добавляем текстовое поле для информации о сохранении
    Fl_Box* saveInfoText;
    
public:
    SaveMenuWindow(MainWindow* mainWin);
    ~SaveMenuWindow();
    
    void show();
    void hide();
    
    static void back_cb(Fl_Widget* w, void* data);
    static void saveGame_cb(Fl_Widget* w, void* data);
    static void loadGame_cb(Fl_Widget* w, void* data);
    static void newGame_cb(Fl_Widget* w, void* data);
    static void exitGame_cb(Fl_Widget* w, void* data);
    
    void returnToMain();
    void updateSaveInfo();  // Метод для обновления информации о сохранении
};

#endif