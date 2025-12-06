#ifndef PARTSOFROCKET_H
#define PARTSOFROCKET_H
#pragma once
#include <map>
#include <FL/Fl.H>
#include <string>

class PartsOfRocket {
private:
    int count;
    int priceToResearch;
    bool isUnlocked;
    std::map<std::string, int> recipe;
    
public:
    PartsOfRocket(); 
    PartsOfRocket(const std::map<std::string, int>& recipe, int priceToResearch, bool isUnlocked, int count);
    
    // Сеттер
    void changeUnlocked(bool unlocked) { isUnlocked = unlocked; }
    void setCount(int newCount) { count = newCount; }
    
    // Геттеры
    const std::map<std::string, int>& getRecipe() const { return recipe; }
    bool getIsUnlocked() const { return isUnlocked; }
    int getPrice() const { return priceToResearch; }
    int getCount() const { return count; }
};

class Rocket {
private:
    int power;
    int level;
    
public:
    Rocket();
    Rocket(int level, int power);

    int getLevel() const { return level; }
    int getPower() const { return power; }
};

// Глобальные переменные сплавов
extern std::map<std::string, PartsOfRocket> Rockets_parts;
extern Rocket Rocket1;
extern Rocket Rocket2;

#endif