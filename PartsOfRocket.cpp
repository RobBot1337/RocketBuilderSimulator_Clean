#include "PartsOfRocket.h"
#include <map>

std::map<std::string, PartsOfRocket> Rockets_parts = {
    // Двигатель 1: МАСШТАБНЫЙ крафт
    {"Engine1", PartsOfRocket({
        {"Steel", 45},                 // 45 сталей = 450 железа + 225 угля
        {"Duraluminium", 35},          // 35 дюралюминия = 350 алюминия + 175 меди
        {"iron", 120},                 // 120 железа дополнительно
        {"CopperTitanium", 20},        // 20 Cu+Ti сплавов = 120 меди + 60 титана
        {"aluminium", 85}              // 85 алюминия
        // ИТОГО: ~570 железа, 225 угля, 435 алюминия, 295 меди, 60 титана
    }, 150, false, 0)},
    
    // Двигатель 2: МЕГА-КРАФТ 
    {"Engine2", PartsOfRocket({
        {"TitaniumAluminiumIron", 40}, // 40 Ti+Al+Fe = 160 титана + 240 алюминия + 200 железа
        {"CopperTitanium", 35},        // 35 Cu+Ti = 210 меди + 105 титана
        {"AluminiumMagnesium", 30},    // 30 Al+Mg = 240 алюминия + 120 магния
        {"Duraluminium", 25},          // 25 дюралюминия = 250 алюминия + 125 меди
        {"titanium", 75},              // 75 титана дополнительно
        {"magnesium", 50}              // 50 магния
        // ИТОГО: ~265 титана, 730 алюминия, 335 меди, 170 магния, 200 железа
    }, 300, false, 0)},
    
    // Корпус 1: ТЯЖЕЛЫЙ крафт
    {"Hull1", PartsOfRocket({
        {"Steel", 60},                 // 60 сталей = 600 железа + 300 угля
        {"AluminiumMagnesium", 40},    // 40 Al+Mg = 320 алюминия + 160 магния
        {"coal", 150},                 // 150 угля
        {"iron", 200},                 // 200 железа
        {"magnesium", 80},             // 80 магния
        {"aluminium", 100}             // 100 алюминия
        // ИТОГО: ~800 железа, 450 угля, 420 алюминия, 240 магния
    }, 300, false, 0)},
    
    // Корпус 2: УЛЬТРА-КРАФТ
    {"Hull2", PartsOfRocket({
        {"TitaniumAluminiumIron", 50}, // 50 Ti+Al+Fe = 200 титана + 300 алюминия + 250 железа
        {"Duraluminium", 40},          // 40 дюралюминия = 400 алюминия + 200 меди
        {"CopperTitanium", 35},        // 35 Cu+Ti = 210 меди + 105 титана
        {"AluminiumMagnesium", 30},    // 30 Al+Mg = 240 алюминия + 120 магния
        {"Steel", 25},                 // 25 сталей = 250 железа + 125 угля
        {"titanium", 100},             // 100 титана
        {"copper", 150}                // 150 меди
        // ИТОГО: ~305 титана, 940 алюминия, 560 меди, 120 магния, 500 железа, 125 угля
    }, 600, false, 0)},
    
    // Топливный бак 1: НЕФТЯНОЙ МОНСТР
    {"FuelTank1", PartsOfRocket({
        {"Steel", 35},                 // 35 сталей = 350 железа + 175 угля
        {"oil", 120},                  // 120 нефти
        {"copper", 200},               // 200 меди
        {"AluminiumMagnesium", 25},    // 25 Al+Mg = 200 алюминия + 100 магния
        {"CopperTitanium", 15},        // 15 Cu+Ti = 90 меди + 45 титана
        {"iron", 150}                  // 150 железа
        // ИТОГО: ~500 железа, 175 угля, 290 меди, 200 алюминия, 100 магния, 45 титана, 120 нефти
    }, 200, false, 0)},
    
    // Топливный бак 2: КОСМИЧЕСКИЙ РЕЗЕРВУАР
    {"FuelTank2", PartsOfRocket({
        {"CopperTitanium", 50},        // 50 Cu+Ti = 300 меди + 150 титана
        {"oil", 200},                  // 200 нефти
        {"AluminiumMagnesium", 40},    // 40 Al+Mg = 320 алюминия + 160 магния
        {"magnesium", 120},            // 120 магния
        {"Duraluminium", 30},          // 30 дюралюминия = 300 алюминия + 150 меди
        {"titanium", 80},              // 80 титана
        {"Steel", 20}                  // 20 сталей = 200 железа + 100 угля
        // ИТОГО: ~450 меди, 230 титана, 620 алюминия, 280 магния, 200 железа, 100 угля, 200 нефти
    }, 400, false, 0)}
};

// Конструктор по умолчанию
PartsOfRocket::PartsOfRocket() 
    : isUnlocked(false), recipe(), priceToResearch(0), count(0) {
}

// Конструктор с рецептом
PartsOfRocket::PartsOfRocket(const std::map<std::string, int>& recipe, int priceToResearch, bool isUnlocked, int count) 
    : isUnlocked(isUnlocked), recipe(recipe), priceToResearch(priceToResearch), count(count){
}

// Конструктор Rocket по умолчанию
Rocket::Rocket()
    : power(0), level(1) {}

// Конструктор Rocket с параметрами
Rocket::Rocket(int level, int power)
    : level(level), power(power) {    
}

Rocket Rocket1(1, 25);  // Уровень 1, мощность 25
Rocket Rocket2(2, 50);  // Уровень 2, мощность 50