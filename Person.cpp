#include "Person.h"
// Конструктор
Person::Person(Planet* planet, long int cash, Rocket* playerRocket):Chosen_Planet(planet), money(cash), playerRocket(playerRocket){}
// Инициализация
Person Player(&Earth, 0, nullptr);