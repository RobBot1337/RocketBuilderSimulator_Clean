#ifndef ALLOYS_H
#define ALLOYS_H
#pragma once
#include <map>
#include <FL/Fl.H>
#include <string>

class Alloy {
private:
    int count;
    std::map<std::string, int> recipe; // ресурс -> количество
    
public:
    Alloy(); 
    Alloy(const std::map<std::string, int>& recipe);
    
    // Сеттер
    void setCount(int newCount) { count = newCount; }
    
    // Геттеры
    int getCount() const { return count; }
    const std::map<std::string, int>& getRecipe() const { return recipe; }
};

// Глобальные переменные сплавов
extern std::map<std::string, Alloy> alloys;

#endif