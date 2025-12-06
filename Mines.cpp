#include "Mines.h"
#include <map>

std::map<std::string, Mine> EarthMines = {
    {"IronMine", Mine(0, 5, 5, 30)},
    {"CoalMine", Mine(0, 7, 5, 25)},
    {"CooperMine", Mine(0, 4, 4, 50)},
    {"AluminiumMine", Mine(0, 4, 6, 25)},
    {"TitanMine", Mine(0, 3, 1, 100)},
    {"MagnesiumMine", Mine(0, 4, 1, 70)},
    {"OilPumping", Mine(0, 1, 10, 75)}
};

std::map<std::string, Mine> MoonMines = {
    {"IronMine", Mine(0, 4, 4, 40)},
    {"TitanMine", Mine(0, 4, 2, 125)},
    {"AluminiumMine", Mine(0, 3, 2, 30)},
    {"NickelMine", Mine(0, 5, 5, 125)}
};

std::map<std::string, Mine> MarsMines = {
    {"IronMine", Mine(0, 4, 4, 50)},
    {"TitanMine", Mine(0, 4, 2, 150)},
    {"AluminiumMine", Mine(0, 3, 2, 50)},
    {"NickelMine", Mine(0, 3, 4, 150)},
    {"CobaltMine", Mine(0, 2, 2, 250)}
};

int iron = 0;
int coal = 0; 
int copper = 0;
int aluminium = 0;
int titanium = 0;
int magnesium = 0;
int oil = 0;
int nickel = 0;
int cobalt = 0;

Mine::Mine() 
    : count_of_mines(0), profit_for_one(0), max_count_of_mines(0), price_of_mine(0) {
}
// ИСПРАВЛЕННЫЙ конструктор - инициализируй поля!
Mine::Mine(int count, int profit, int max_count, int price) 
    : count_of_mines(count), 
      profit_for_one(profit), 
      max_count_of_mines(max_count), 
      price_of_mine(price) {
}
