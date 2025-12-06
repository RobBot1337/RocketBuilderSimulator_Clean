#include "Person.h"

// Конструктор
Person::Person(Planet* planet, long int cash, Rocket* rocket) 
    : chosenPlanet(planet), money(cash), playerRocket(rocket) 
{}

// Инициализация
Person Player(&Earth, 0, nullptr);