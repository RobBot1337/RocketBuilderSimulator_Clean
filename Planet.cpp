#include "Planet.h"
#include "Config.h"
#include <string>

// Конструктор
Planet::Planet(
    const std::string& planetName,
    const std::string& pathToBig, 
    const std::string& pathToSmall,
    short unsigned int percentColon, 
    short unsigned int protect, 
    short unsigned int profit): 
    name(planetName), 
    pathBigPNG(pathToBig), 
    pathSmallPNG(pathToSmall), 
    percentColonization(percentColon), 
    protection(protect), 
    maxProfit(profit)
{}

Config& config = Config::getInstance();

// Инициализируем планеты с использованием Config
Planet Earth("Земля", 
             config.getPicturePath("Земля.png"), 
             config.getPicturePath("ЗемляМини.png"), 
             100, 1, 1);

Planet Moon("Луна", 
            config.getPicturePath("Луна.png"), 
            config.getPicturePath("ЛунаМини.png"), 
            0, 1, 2);

Planet Mars("Марс", 
            config.getPicturePath("Марс.png"), 
            config.getPicturePath("МарсМини.png"), 
            0, 2, 5);