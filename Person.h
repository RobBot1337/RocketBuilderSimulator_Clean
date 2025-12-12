#ifndef PERSON_H
#define PERSON_H
#include <string>
#include "Planet.h"
#include "PartsOfRocket.h"

// Создаем класс персонажа
class Person {
private:
    long double money;
    Planet* chosenPlanet;
    Rocket* playerRocket;
    
public:
    Person(Planet* planet, long double cash, Rocket* rocket);

    // Сеттеры
    void setMoney(long double newMoney) { money = newMoney; }
    void setPlanet(Planet* newPlanet) { chosenPlanet = newPlanet; }
    void setRocket(Rocket* newRocket) { playerRocket = newRocket; }
    
    // Геттеры
    long double getMoney() const { return money; }
    Planet* getPlanet() const { return chosenPlanet; }
    Rocket* getRocket() const { return playerRocket; }
};

// Объявляем глобальную переменную
extern Person Player;

#endif