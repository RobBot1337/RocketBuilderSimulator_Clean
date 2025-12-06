#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <filesystem>

class Config {
private:
    std::string projectRoot;
    static Config* instance;
    
    Config();  // Приватный конструктор
    
public:
    static Config& getInstance();
    
    // Установить корневую папку проекта
    void setProjectRoot(const std::string& root);
    
    // Получить путь к картинке
    std::string getPicturePath(const std::string& filename);
    
    // Получить путь к музыке
    std::string getMusicPath(const std::string& filename);
    
    // Получить абсолютный путь
    std::string getAbsolutePath(const std::string& relativePath);
    
    // Проверить существование файла
    bool fileExists(const std::string& path);
    
private:
    // Найти корневую папку проекта автоматически
    std::string findProjectRoot();
};

#define CONFIG Config::getInstance()

#endif