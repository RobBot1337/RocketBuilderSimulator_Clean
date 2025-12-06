#ifndef PLANET_H
#define PLANET_H

#include <string>

// Создаем класс планет
class Planet {
private:
    std::string name;
    std::string pathBigPNG;
    std::string pathSmallPNG;
    short unsigned int percentColonization;
    short unsigned int protection;
    short unsigned int maxProfit;
    
public:
    Planet(const std::string& planetName, 
           const std::string& pathToBig, 
           const std::string& pathToSmall, 
           short unsigned int percentColon, 
           short unsigned int protect, 
           short unsigned int profit);
    
    double getProfit() const { return maxProfit * percentColonization / 100; }
    int getProtection() const { return protection; }
    int getPercentColonization() const { return percentColonization; }
    std::string getPathToSmallPNG() const { return pathSmallPNG; }
    std::string getPathToBigPNG() const { return pathBigPNG; }
    std::string getName() const { return name; }
    
    void setPercentColonization(int newPercentColonization) { 
        percentColonization = newPercentColonization; 
    }
};

// Объявляем глобальные переменные
extern Planet Earth;
extern Planet Moon; 
extern Planet Mars;

#endif