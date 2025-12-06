#include "PartsOfRocket.h"
#include <map>

std::map<std::string, Parts_of_Rocket> Rockets_parts = {
    {"Engine1", Parts_of_Rocket({{"iron", 10}, {"coal", 5}}, 150, false, 0)},
    {"Engine2", Parts_of_Rocket({{"iron", 10}, {"coal", 5}}, 300, false, 0)},
    {"Hull1", Parts_of_Rocket({{"iron", 10}, {"coal", 5}}, 200, false, 0)},
    {"Hull2", Parts_of_Rocket({{"iron", 10}, {"coal", 5}}, 400, false, 0)},
    {"FuelTank1", Parts_of_Rocket({{"iron", 10}, {"coal", 5}}, 125, false, 0)},
    {"FuelTank2", Parts_of_Rocket({{"iron", 10}, {"coal", 5}}, 250, false, 0)}
};

// Конструктор по умолчанию
Parts_of_Rocket::Parts_of_Rocket() 
    : isUnlocked(false), recipe(), price_to_research(0), count(0) {
}

// Конструктор с рецептом
Parts_of_Rocket::Parts_of_Rocket(const std::map<std::string, int>& recipe, int price_to_research, bool isUnlocked, int count) 
    : isUnlocked(isUnlocked), recipe(recipe), price_to_research(price_to_research) , count(count){
}

Rocket::Rocket()
    : power(0), level_of_rocket(1){}

Rocket::Rocket(int power, int level_of_rocket)
    : power(power), level_of_rocket(level_of_rocket){    
}

Rocket Rocket1(25, 1);
Rocket Rocket2(50, 2);