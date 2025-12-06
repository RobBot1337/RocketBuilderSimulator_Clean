#ifndef MINES_H
#define MINES_H
#pragma once
#include <map>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <string>
#include "UI_widgets.h"
#include "Person.h"
#include "Planet.h"


class Mine{
    private:
        int count_of_mines;
        int profit_for_one;
        int max_count_of_mines;
        int price_of_mine;
    public:
        Mine(); 
        Mine(int count, int profit, int max_count, int price);
        //Сеттер
        void setCount(long int new_count) { count_of_mines = new_count; }
        //Геттеры
        int getRecources() const { return count_of_mines*profit_for_one; }
        int getMaxCountOfMines() const { return max_count_of_mines; }
        int getPrice() const { return price_of_mine; }
        int getCount() const { return count_of_mines; }
};

extern std::map<std::string, Mine> EarthMines;
extern std::map<std::string, Mine> MoonMines;
extern std::map<std::string, Mine> MarsMines;

extern int iron;
extern int coal;
extern int copper;
extern int aluminium;
extern int titanium;
extern int magnesium;
extern int oil;
extern int nickel;
extern int cobalt;

#endif