#ifndef GAMESAVE_H
#define GAMESAVE_H

#include <string>

class GameSave {
private:
    std::string savePath;
    GameSave();  // Приватный конструктор
    
public:
    // Удаляем копирование
    GameSave(const GameSave&) = delete;
    GameSave& operator=(const GameSave&) = delete;
    
    // Получение экземпляра
    static GameSave& getInstance();
    
    // Методы сохранения/загрузки
    bool saveGame();
    bool loadGame();
    bool newGame();  // Новый метод для создания новой игры
};

#endif // GAMESAVE_H