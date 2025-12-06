#ifndef ALLOYS_H
#define ALLOYS_H
#pragma once
#include <map>
#include <FL/Fl.H>
#include <string>

class Alloy{
private:
    int count_of_alloy;
    std::map<std::string, int> recipe; // ресурс -> количество
    
public:
    Alloy(); 
    Alloy(const std::map<std::string, int>& recipe);
    
    // Сеттер
    void setCount(int new_count) { count_of_alloy = new_count; }
    
    // Геттеры
    int getCount() const { return count_of_alloy; }
    const std::map<std::string, int>& getRecipe() const { return recipe; }

};

// Глобальные переменные сплавов
extern std::map<std::string, Alloy> alloys;



#endif