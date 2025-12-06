#ifndef PARTSOFROCKET_H
#define PARTSOFROCKET_H
#pragma once
#include <map>
#include <FL/Fl.H>
#include <string>

class Parts_of_Rocket{
private:
    int count;
    int price_to_research;
    bool isUnlocked;
    std::map<std::string, int> recipe;
    
public:
    Parts_of_Rocket(); 
    Parts_of_Rocket(const std::map<std::string, int>& recipe, int price_to_research, bool isUnlocked, int count);
    
    // Сеттер
    void changeUnlocked(bool Unlocked) { isUnlocked = Unlocked; }
    void setCount(int new_count) { count = new_count; }
    
    // Геттеры
    const std::map<std::string, int>& getRecipe() const { return recipe; }
    bool getIsUnlocked() const { return isUnlocked; }  // Изменили имя метода
    int getPrice() const { return price_to_research; }
    int getCount() const { return count; }
};
class Rocket{
private:
    int power;
    int level_of_rocket;
public:
    Rocket();
    Rocket(int level_of_rocket, int power);

    int getLevel() const { return level_of_rocket; }
    int getPower() const { return power; }
};
// Глобальные переменные сплавов
extern std::map<std::string, Parts_of_Rocket> Rockets_parts;
extern Rocket Rocket1;
extern Rocket Rocket2;



#endif