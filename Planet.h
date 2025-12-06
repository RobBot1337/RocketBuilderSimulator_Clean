#ifndef PLANET_H
#define PLANET_H

#include <string>

// Создаем класс планет
class Planet{
    private:
        std::string name;
        std::string PathBigPlanetPNG;
        std::string PathSmallPlanetPNG;
        int percent_of_colonization;
        int protection;
        int max_profit;
    public:
        Planet(const std::string& planetName, const std::string& Path_to_Big, const std::string& Path_to_Small, int per_of_colon, const int protect, const int profit);
        int getProfit() const { return max_profit; }
        int getProtection() const {return protection;}
        short int getPercentColonization() const { return percent_of_colonization; }
        std::string getPathToSmallPNG() const { return PathSmallPlanetPNG; }
        std::string getPathToBigPNG() const { return PathBigPlanetPNG; }
        std::string getName() const { return name; }
        void setPercentColonization(int new_percent_of_colonization) {percent_of_colonization = new_percent_of_colonization; }

};

// Объявляем глобальные перменные
extern Planet Earth;
extern Planet Moon; 
extern Planet Mars;

#endif