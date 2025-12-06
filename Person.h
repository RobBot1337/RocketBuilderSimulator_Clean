#ifndef PERSON_H
#define PERSON_H
#include <string>
#include "Planet.h"
#include "PartsOfRocket.h"

// Создаем класс персонажа
class Person{
    private:
        long int money;
        Planet* Chosen_Planet;
        Rocket* playerRocket;
    public:
        Person(Planet* planet, long int cash, Rocket* playerRocket);

        // Сеттеры
        void setMoney(long int new_money) { money = new_money; }
        void setPlanet(Planet* new_planet) { Chosen_Planet = new_planet; }
        void setRocket(Rocket* new_rocket) { playerRocket = new_rocket; }
        
        // Геттеры
        long int getMoney() const { return money; }
        Planet* getPlanet() const { return Chosen_Planet; }
        Rocket* getRocket() const { return playerRocket; }
};

// Объявляем глобальную переменную
extern Person Player;

#endif