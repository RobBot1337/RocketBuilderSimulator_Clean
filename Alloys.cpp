#include "alloys.h"
#include "Mines.h"
#include <map>

// Инициализация сплавов с рецептами
std::map<std::string, Alloy> alloys = {
    {"Steel", Alloy({{"iron", 10}, {"coal", 5}})},
    {"Duraluminium", Alloy({{"aluminium", 10}, {"copper", 5}})},
    {"AluminiumMagnesium", Alloy({{"aluminium", 8}, {"magnesium", 4}})},
    {"CopperTitanium", Alloy({{"copper", 6}, {"titanium", 3}})},
    {"TitaniumAluminiumIron", Alloy({{"titanium", 4}, {"aluminium", 6}, {"iron", 5}})}
};

// Конструктор по умолчанию
Alloy::Alloy() 
    : count_of_alloy(0), recipe() {
}

// Конструктор с рецептом
Alloy::Alloy(const std::map<std::string, int>& recipe) 
    : count_of_alloy(0), recipe(recipe) {
}