#include "Person.h"

// Конструктор
Person::Person(Planet* planet, long double cash, Rocket* rocket) 
    : chosenPlanet(planet), money(cash), playerRocket(rocket) 
{}

// Инициализация
Person Player(&Earth, 10000, nullptr);