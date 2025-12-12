#include "GameSave.h"
#include "Mines.h"
#include "Planet.h"
#include "Person.h"
#include "PartsOfRocket.h"
#include "alloys.h"
#include <fstream>
#include <iostream>
#include <string>

GameSave::GameSave() : savePath("savegame.dat") {}

GameSave& GameSave::getInstance() {
    static GameSave instance;
    return instance;
}

// Вспомогательная функция для записи строк
void writeString(std::ofstream& file, const std::string& str) {
    size_t length = str.size();
    file.write(reinterpret_cast<char*>(&length), sizeof(length));
    file.write(str.c_str(), length);
}

// Вспомогательная функция для чтения строк
std::string readString(std::ifstream& file) {
    size_t length;
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    
    if (length > 0 && length < 10000) {
        std::string str(length, '\0');
        file.read(&str[0], length);
        return str;
    }
    return "";
}

bool GameSave::saveGame() {
    try {
        std::ofstream file(savePath, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }
        
        // Заголовок и версия
        const char* header = "RKTSAVE";
        file.write(header, 7);
        int version = 1;
        file.write(reinterpret_cast<char*>(&version), sizeof(version));
        
        // 1. Игрок
        long money = Player.getMoney();
        file.write(reinterpret_cast<char*>(&money), sizeof(money));
        
        std::string planetName = Player.getPlanet()->getName();
        writeString(file, planetName);
        
        int rocketLevel = (Player.getRocket() != nullptr) ? Player.getRocket()->getLevel() : 0;
        file.write(reinterpret_cast<char*>(&rocketLevel), sizeof(rocketLevel));
        
        // 2. Ресурсы
        file.write(reinterpret_cast<char*>(&iron), sizeof(iron));
        file.write(reinterpret_cast<char*>(&coal), sizeof(coal));
        file.write(reinterpret_cast<char*>(&copper), sizeof(copper));
        file.write(reinterpret_cast<char*>(&aluminium), sizeof(aluminium));
        file.write(reinterpret_cast<char*>(&titanium), sizeof(titanium));
        file.write(reinterpret_cast<char*>(&magnesium), sizeof(magnesium));
        file.write(reinterpret_cast<char*>(&oil), sizeof(oil));
        file.write(reinterpret_cast<char*>(&nickel), sizeof(nickel));
        file.write(reinterpret_cast<char*>(&cobalt), sizeof(cobalt));
        
        // 3. Колонизация
        int earthCol = Earth.getPercentColonization();
        int moonCol = Moon.getPercentColonization();
        int marsCol = Mars.getPercentColonization();
        file.write(reinterpret_cast<char*>(&earthCol), sizeof(earthCol));
        file.write(reinterpret_cast<char*>(&moonCol), sizeof(moonCol));
        file.write(reinterpret_cast<char*>(&marsCol), sizeof(marsCol));
        
        // 4. Шахты Земли
        for (auto& [name, mine] : EarthMines) {
            int count = mine.getCount();
            writeString(file, name);
            file.write(reinterpret_cast<char*>(&count), sizeof(count));
        }
        writeString(file, "END_EARTH_MINES");
        
        // 5. Шахты Луны
        for (auto& [name, mine] : MoonMines) {
            int count = mine.getCount();
            writeString(file, name);
            file.write(reinterpret_cast<char*>(&count), sizeof(count));
        }
        writeString(file, "END_MOON_MINES");
        
        // 6. Шахты Марса
        for (auto& [name, mine] : MarsMines) {
            int count = mine.getCount();
            writeString(file, name);
            file.write(reinterpret_cast<char*>(&count), sizeof(count));
        }
        writeString(file, "END_MARS_MINES");
        
        // 7. Части ракет
        for (auto& [name, part] : Rockets_parts) {
            writeString(file, name);
            bool unlocked = part.getIsUnlocked();
            int count = part.getCount();
            file.write(reinterpret_cast<char*>(&unlocked), sizeof(unlocked));
            file.write(reinterpret_cast<char*>(&count), sizeof(count));
        }
        writeString(file, "END_ROCKET_PARTS");
        
        // 8. Сплавы
        for (auto& [name, alloy] : alloys) {
            writeString(file, name);
            int count = alloy.getCount();
            file.write(reinterpret_cast<char*>(&count), sizeof(count));
        }
        writeString(file, "END_ALLOYS");
        
        file.close();
        return true;
        
    } catch (const std::exception& e) {
        return false;
    }
}

bool GameSave::loadGame() {
    try {
        std::ifstream file(savePath, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }
        
        // Проверяем заголовок
        char header[8] = {0};
        file.read(header, 7);
        if (std::string(header) != "RKTSAVE") {
            return false;
        }
        
        int version;
        file.read(reinterpret_cast<char*>(&version), sizeof(version));
        if (version != 1) {
            return false;
        }
        
        // 1. Игрок
        long money;
        file.read(reinterpret_cast<char*>(&money), sizeof(money));
        Player.setMoney(money);
        
        std::string planetName = readString(file);
        if (planetName == "Земля") Player.setPlanet(&Earth);
        else if (planetName == "Луна" && Moon.getPercentColonization() > 0) Player.setPlanet(&Moon);
        else if (planetName == "Марс" && Mars.getPercentColonization() > 0) Player.setPlanet(&Mars);
        else Player.setPlanet(&Earth);
        
        int rocketLevel;
        file.read(reinterpret_cast<char*>(&rocketLevel), sizeof(rocketLevel));
        if (rocketLevel == 1) Player.setRocket(&Rocket1);
        else if (rocketLevel == 2) Player.setRocket(&Rocket2);
        else Player.setRocket(nullptr);
        
        // 2. Ресурсы
        file.read(reinterpret_cast<char*>(&iron), sizeof(iron));
        file.read(reinterpret_cast<char*>(&coal), sizeof(coal));
        file.read(reinterpret_cast<char*>(&copper), sizeof(copper));
        file.read(reinterpret_cast<char*>(&aluminium), sizeof(aluminium));
        file.read(reinterpret_cast<char*>(&titanium), sizeof(titanium));
        file.read(reinterpret_cast<char*>(&magnesium), sizeof(magnesium));
        file.read(reinterpret_cast<char*>(&oil), sizeof(oil));
        file.read(reinterpret_cast<char*>(&nickel), sizeof(nickel));
        file.read(reinterpret_cast<char*>(&cobalt), sizeof(cobalt));
        
        // 3. Колонизация
        int earthCol, moonCol, marsCol;
        file.read(reinterpret_cast<char*>(&earthCol), sizeof(earthCol));
        file.read(reinterpret_cast<char*>(&moonCol), sizeof(moonCol));
        file.read(reinterpret_cast<char*>(&marsCol), sizeof(marsCol));
        Earth.setPercentColonization(earthCol);
        Moon.setPercentColonization(moonCol);
        Mars.setPercentColonization(marsCol);
        
        // 4. Шахты Земли
        std::string mineName;
        while ((mineName = readString(file)) != "END_EARTH_MINES") {
            int count;
            file.read(reinterpret_cast<char*>(&count), sizeof(count));
            if (EarthMines.find(mineName) != EarthMines.end()) {
                EarthMines[mineName].setCount(count);
            }
        }
        
        // 5. Шахты Луны
        while ((mineName = readString(file)) != "END_MOON_MINES") {
            int count;
            file.read(reinterpret_cast<char*>(&count), sizeof(count));
            if (MoonMines.find(mineName) != MoonMines.end()) {
                MoonMines[mineName].setCount(count);
            }
        }
        
        // 6. Шахты Марса
        while ((mineName = readString(file)) != "END_MARS_MINES") {
            int count;
            file.read(reinterpret_cast<char*>(&count), sizeof(count));
            if (MarsMines.find(mineName) != MarsMines.end()) {
                MarsMines[mineName].setCount(count);
            }
        }
        
        // 7. Части ракет
        std::string partName;
        while ((partName = readString(file)) != "END_ROCKET_PARTS") {
            bool unlocked;
            int count;
            file.read(reinterpret_cast<char*>(&unlocked), sizeof(unlocked));
            file.read(reinterpret_cast<char*>(&count), sizeof(count));
            if (Rockets_parts.find(partName) != Rockets_parts.end()) {
                Rockets_parts[partName].changeUnlocked(unlocked);
                Rockets_parts[partName].setCount(count);
            }
        }
        
        // 8. Сплавы
        std::string alloyName;
        while ((alloyName = readString(file)) != "END_ALLOYS") {
            int count;
            file.read(reinterpret_cast<char*>(&count), sizeof(count));
            if (alloys.find(alloyName) != alloys.end()) {
                alloys[alloyName].setCount(count);
            }
        }
        
        file.close();
        return true;
        
    } catch (const std::exception& e) {
        return false;
    }
}

// Метод для создания новой игры
bool GameSave::newGame() {
    try {
        // 1. Сбрасываем планеты к начальным значениям
        Earth.setPercentColonization(100);
        Moon.setPercentColonization(0);
        Mars.setPercentColonization(0);
        
        // 2. Сбрасываем игрока
        Player.setMoney(0);
        Player.setPlanet(&Earth);
        Player.setRocket(nullptr);
        
        // 3. Сбрасываем все ресурсы
        iron = 0;
        coal = 0;
        copper = 0;
        aluminium = 0;
        titanium = 0;
        magnesium = 0;
        oil = 0;
        nickel = 0;
        cobalt = 0;
        
        // 4. Сбрасываем все шахты
        for (auto& [name, mine] : EarthMines) {
            mine.setCount(0);
        }
        for (auto& [name, mine] : MoonMines) {
            mine.setCount(0);
        }
        for (auto& [name, mine] : MarsMines) {
            mine.setCount(0);
        }
        
        // 5. Сбрасываем части ракет
        for (auto& [name, part] : Rockets_parts) {
            part.changeUnlocked(false);
            part.setCount(0);
        }
        
        // 6. Сбрасываем сплавы
        for (auto& [name, alloy] : alloys) {
            alloy.setCount(0);
        }
        
        // 7. Удаляем старый файл сохранения
        std::remove(savePath.c_str());
        
        // 8. Создаем новое сохранение с начальными значениями
        return saveGame();
        
    } catch (const std::exception& e) {
        return false;
    }
}