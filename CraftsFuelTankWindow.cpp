#include "CraftsFuelTankWindow.h"  // Должен быть СВОЙ заголовочный файл!
#include "CraftsWindow.h"
#include "Mines.h"
#include "PartsOfRocket.h"
#include "Alloys.h"
#include "Config.h"
#include <windows.h>
#include <mmsystem.h>

static Fl_PNG_Image* static_bg = nullptr;
static Fl_PNG_Image* static_arrow = nullptr;

// ВАЖНО: должны быть СВОИ переменные для топливных баков!
Fl_Box* FuelTank1_count;
Fl_Box* FuelTank2_count;

// Вспомогательные функции для получения ресурсов (ДЛЯ ТОПЛИВНЫХ БАКОВ!)
bool hasEnoughResourcesForFuelTank1() {
    const auto& recipe = Rockets_parts.at("FuelTank1").getRecipe();
    
    for (const auto& [resource, amount] : recipe) {
        if (resource == "Steel" && alloys.at("Steel").getCount() < amount) return false;
        else if (resource == "Duraluminium" && alloys.at("Duraluminium").getCount() < amount) return false;
        else if (resource == "CopperTitanium" && alloys.at("CopperTitanium").getCount() < amount) return false;
        else if (resource == "AluminiumMagnesium" && alloys.at("AluminiumMagnesium").getCount() < amount) return false;
        else if (resource == "TitaniumAluminiumIron" && alloys.at("TitaniumAluminiumIron").getCount() < amount) return false;
        else if (resource == "iron" && iron < amount) return false;
        else if (resource == "aluminium" && aluminium < amount) return false;
        else if (resource == "copper" && copper < amount) return false;
        else if (resource == "titanium" && titanium < amount) return false;
        else if (resource == "magnesium" && magnesium < amount) return false;
        else if (resource == "coal" && coal < amount) return false;
        else if (resource == "oil" && oil < amount) return false;
    }
    
    return true;
}

bool hasEnoughResourcesForFuelTank2() {
    const auto& recipe = Rockets_parts.at("FuelTank2").getRecipe();
    
    for (const auto& [resource, amount] : recipe) {
        if (resource == "Steel" && alloys.at("Steel").getCount() < amount) return false;
        else if (resource == "Duraluminium" && alloys.at("Duraluminium").getCount() < amount) return false;
        else if (resource == "CopperTitanium" && alloys.at("CopperTitanium").getCount() < amount) return false;
        else if (resource == "AluminiumMagnesium" && alloys.at("AluminiumMagnesium").getCount() < amount) return false;
        else if (resource == "TitaniumAluminiumIron" && alloys.at("TitaniumAluminiumIron").getCount() < amount) return false;
        else if (resource == "iron" && iron < amount) return false;
        else if (resource == "aluminium" && aluminium < amount) return false;
        else if (resource == "copper" && copper < amount) return false;
        else if (resource == "titanium" && titanium < amount) return false;
        else if (resource == "magnesium" && magnesium < amount) return false;
        else if (resource == "coal" && coal < amount) return false;
        else if (resource == "oil" && oil < amount) return false;
    }
    
    return true;
}

// СТАТИЧЕСКИЕ CALLBACK ФУНКЦИИ - ДОЛЖНЫ БЫТЬ CraftsFuelTankWindow:: а не CraftsHullWindow::
void CraftsFuelTankWindow::craft_fueltank1_cb(Fl_Widget* w, void* data){
    if(Rockets_parts.at("FuelTank1").getIsUnlocked() == true && hasEnoughResourcesForFuelTank1()){
        const auto& recipe = Rockets_parts.at("FuelTank1").getRecipe();
        
        for (const auto& [resource, amount] : recipe) {
            if (resource == "Steel") {
                alloys.at("Steel").setCount(alloys.at("Steel").getCount() - amount);
            }
            else if (resource == "Duraluminium") {
                alloys.at("Duraluminium").setCount(alloys.at("Duraluminium").getCount() - amount);
            }
            else if (resource == "CopperTitanium") {
                alloys.at("CopperTitanium").setCount(alloys.at("CopperTitanium").getCount() - amount);
            }
            else if (resource == "AluminiumMagnesium") {
                alloys.at("AluminiumMagnesium").setCount(alloys.at("AluminiumMagnesium").getCount() - amount);
            }
            else if (resource == "TitaniumAluminiumIron") {
                alloys.at("TitaniumAluminiumIron").setCount(alloys.at("TitaniumAluminiumIron").getCount() - amount);
            }
            else if (resource == "iron") {
                iron -= amount;
            }
            else if (resource == "aluminium") {
                aluminium -= amount;
            }
            else if (resource == "copper") {
                copper -= amount;
            }
            else if (resource == "titanium") {
                titanium -= amount;
            }
            else if (resource == "magnesium") {
                magnesium -= amount;
            }
            else if (resource == "coal") {
                coal -= amount;
            }
            else if (resource == "oil") {
                oil -= amount;
            }
        }
        
        Rockets_parts.at("FuelTank1").setCount(Rockets_parts.at("FuelTank1").getCount() + 1);

        CraftsFuelTankWindow* win = (CraftsFuelTankWindow*)data;
        win->refreshAll();
        win->updateButtonsState();
    }
}

void CraftsFuelTankWindow::craft_fueltank2_cb(Fl_Widget* w, void* data){
    if(Rockets_parts.at("FuelTank2").getIsUnlocked() == true && hasEnoughResourcesForFuelTank2()){
        const auto& recipe = Rockets_parts.at("FuelTank2").getRecipe();
        
        for (const auto& [resource, amount] : recipe) {
            if (resource == "Steel") {
                alloys.at("Steel").setCount(alloys.at("Steel").getCount() - amount);
            }
            else if (resource == "Duraluminium") {
                alloys.at("Duraluminium").setCount(alloys.at("Duraluminium").getCount() - amount);
            }
            else if (resource == "CopperTitanium") {
                alloys.at("CopperTitanium").setCount(alloys.at("CopperTitanium").getCount() - amount);
            }
            else if (resource == "AluminiumMagnesium") {
                alloys.at("AluminiumMagnesium").setCount(alloys.at("AluminiumMagnesium").getCount() - amount);
            }
            else if (resource == "TitaniumAluminiumIron") {
                alloys.at("TitaniumAluminiumIron").setCount(alloys.at("TitaniumAluminiumIron").getCount() - amount);
            }
            else if (resource == "iron") {
                iron -= amount;
            }
            else if (resource == "aluminium") {
                aluminium -= amount;
            }
            else if (resource == "copper") {
                copper -= amount;
            }
            else if (resource == "titanium") {
                titanium -= amount;
            }
            else if (resource == "magnesium") {
                magnesium -= amount;
            }
            else if (resource == "coal") {
                coal -= amount;
            }
            else if (resource == "oil") {
                oil -= amount;
            }
        }
        
        Rockets_parts.at("FuelTank2").setCount(Rockets_parts.at("FuelTank2").getCount() + 1);

        CraftsFuelTankWindow* win = (CraftsFuelTankWindow*)data;
        win->refreshAll();
        win->updateButtonsState();
    }
}

void CraftsFuelTankWindow::back_cb(Fl_Widget* w, void* data) {
    CraftsFuelTankWindow* allWin = (CraftsFuelTankWindow*)data;
    allWin->return_to_main();
}

CraftsFuelTankWindow::CraftsFuelTankWindow(CraftsWindow* mainWin){
    crWindow = mainWin;

    window = new Fl_Window(1440, 820, "Крафт топливных баков");
    window->position(10, 10);

    Config& config = Config::getInstance();
    
    if (!static_bg) {
        std::string bgPath = config.getPicturePath("Небо.png");
        std::string arrowPath = config.getPicturePath("Cтрелка.png");
        
        static_bg = new Fl_PNG_Image(bgPath.c_str());
        static_arrow = new Fl_PNG_Image(arrowPath.c_str());
    }

    bg = static_bg;
    background = new Fl_Box(0, 0, 1440, 820);
    background->image(bg);

    back_Button = new PictureButton(0, 0, 96, 96, static_arrow);
    back_Button->getButton()->callback(back_cb, this);

    // Топливный бак 1
    std::string fueltank1Path = config.getPicturePath("Топливный1.png");
    Picture fueltank1(100, 100, 96, 96, fueltank1Path.c_str());
    
    craft_fueltank1 = new Button(196, 123, 450, 50, 20, "Создать топливный бак 1");
    craft_fueltank1->getButton()->callback(craft_fueltank1_cb, this);
    craft_fueltank1->getButton()->tooltip("Stl:35, Oil:120, Cu:200, AlMg:25, CuTi:15, Fe:150");
    
    Text FuelTank1_Title(696, 123, 150, 50, 20, "Количество");

    FuelTank1_count = new Fl_Box(846, 123, 120, 50, "0");
    FuelTank1_count->labelsize(20);
    FuelTank1_count->box(FL_BORDER_BOX);
    FuelTank1_count->align(FL_ALIGN_CENTER);
    FuelTank1_count->labelfont(FL_COURIER_BOLD);

    // Топливный бак 2
    std::string fueltank2Path = config.getPicturePath("Топливный2.png");
    Picture fueltank2(100, 196, 96, 96, fueltank2Path.c_str());
    
    craft_fueltank2 = new Button(196, 219, 450, 50, 20, "Создать топливный бак 2");
    craft_fueltank2->getButton()->callback(craft_fueltank2_cb, this);
    craft_fueltank2->getButton()->tooltip("CuTi:50, Oil:200, AlMg:40, Mg:120, Dural:30, Ti:80, Stl:20");
    
    Text FuelTank2_Title(696, 219, 150, 50, 20, "Количество");

    FuelTank2_count = new Fl_Box(846, 219, 120, 50, "0");
    FuelTank2_count->labelsize(20);
    FuelTank2_count->box(FL_BORDER_BOX);
    FuelTank2_count->align(FL_ALIGN_CENTER);
    FuelTank2_count->labelfont(FL_COURIER_BOLD);

    updateButtonsState();
}

CraftsFuelTankWindow::~CraftsFuelTankWindow() {
    // Деструктор
}

void CraftsFuelTankWindow::show() {
    window->show();
    refreshAll();
}

void CraftsFuelTankWindow::hide() {
    window->hide();
}

void CraftsFuelTankWindow::return_to_main() {
    crWindow->show();
    this->hide();
}

void CraftsFuelTankWindow::refreshAll(){
    std::string fueltank1Text = std::to_string(Rockets_parts.at("FuelTank1").getCount());
    FuelTank1_count->copy_label(fueltank1Text.c_str());

    std::string fueltank2Text = std::to_string(Rockets_parts.at("FuelTank2").getCount());
    FuelTank2_count->copy_label(fueltank2Text.c_str());
}

void CraftsFuelTankWindow::updateButtonsState(){
    // Топливный бак 1
    if (Rockets_parts.at("FuelTank1").getIsUnlocked() == true && hasEnoughResourcesForFuelTank1()){
        craft_fueltank1->activate();
        craft_fueltank1->setColor(FL_GREEN);
        craft_fueltank1->getButton()->tooltip("Stl:35, Oil:120, Cu:200, AlMg:25, CuTi:15, Fe:150");
    } else {
        craft_fueltank1->deactivate();
        craft_fueltank1->setColor(FL_RED);
        craft_fueltank1->getButton()->tooltip("Stl:35, Oil:120, Cu:200, AlMg:25, CuTi:15, Fe:150");
    }

    // Топливный бак 2
    if (Rockets_parts.at("FuelTank2").getIsUnlocked() == true && hasEnoughResourcesForFuelTank2()){
        craft_fueltank2->activate();
        craft_fueltank2->setColor(FL_GREEN);
        craft_fueltank2->getButton()->tooltip("CuTi:50, Oil:200, AlMg:40, Mg:120, Dural:30, Ti:80, Stl:20");
    } else {
        craft_fueltank2->deactivate();
        craft_fueltank2->setColor(FL_RED);
        craft_fueltank2->getButton()->tooltip("CuTi:50, Oil:200, AlMg:40, Mg:120, Dural:30, Ti:80, Stl:20");
    }
}

void CraftsFuelTankWindow::updateData(void* data) {
    // Метод для обновления данных
}