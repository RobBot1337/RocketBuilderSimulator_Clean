#include "Planet.h"
#include <string>

// Конструктор
Planet::Planet(
    const std::string& planetName,
    const std::string& Path_to_Big, const std::string& Path_to_Small,
    int per_of_colon, int protect, int profit): 
name(planetName), PathBigPlanetPNG(Path_to_Big), PathSmallPlanetPNG(Path_to_Small), 
percent_of_colonization(per_of_colon), protection(protect), max_profit(profit)
{}

// Инициализируем планеты
Planet Earth("Земля", "C:/Users/Zenbook/Desktop/Graphproject/Pictures/Земля.png", "C:/Users/Zenbook/Desktop/Graphproject/Pictures/ЗемляМини.png", 100, 1, 1);
Planet Moon("Луна", "C:/Users/Zenbook/Desktop/Graphproject/Pictures/Луна.png", "C:/Users/Zenbook/Desktop/Graphproject/Pictures/ЛунаМини.png", 0, 1, 2);
Planet Mars("Марс", "C:/Users/Zenbook/Desktop/Graphproject/Pictures/Марс.png", "C:/Users/Zenbook/Desktop/Graphproject/Pictures/МарсМини.png", 0, 2, 5);