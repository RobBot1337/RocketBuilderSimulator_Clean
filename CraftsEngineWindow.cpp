#include "CraftsEngineWindow.h"
#include "CraftsWindow.h"
#include "Mines.h"
#include "PartsOfRocket.h"
#include "Alloys.h"
#include "Config.h"
#include <windows.h>
#include <mmsystem.h>

static Fl_PNG_Image* static_bg = nullptr;
static Fl_PNG_Image* static_arrow = nullptr;

Fl_Box* Engine1_count;
Fl_Box* Engine2_count;

// Вспомогательные функции для получения ресурсов
bool hasEnoughResourcesForEngine1() {
    const auto& recipe = Rockets_parts.at("Engine1").getRecipe();
    
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

bool hasEnoughResourcesForEngine2() {
    const auto& recipe = Rockets_parts.at("Engine2").getRecipe();
    
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

// СТАТИЧЕСКИЕ CALLBACK ФУНКЦИИ
void CraftsEngineWindow::craft_engine1_cb(Fl_Widget* w, void* data){
    if(Rockets_parts.at("Engine1").getIsUnlocked() == true && hasEnoughResourcesForEngine1()){
        const auto& recipe = Rockets_parts.at("Engine1").getRecipe();
        
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
        
        Rockets_parts.at("Engine1").setCount(Rockets_parts.at("Engine1").getCount() + 1);

        CraftsEngineWindow* win = (CraftsEngineWindow*)data;
        win->refreshAll();
        win->updateButtonsState();
    }
}

void CraftsEngineWindow::craft_engine2_cb(Fl_Widget* w, void* data){
    if(Rockets_parts.at("Engine2").getIsUnlocked() == true && hasEnoughResourcesForEngine2()){
        const auto& recipe = Rockets_parts.at("Engine2").getRecipe();
        
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
        
        Rockets_parts.at("Engine2").setCount(Rockets_parts.at("Engine2").getCount() + 1);

        CraftsEngineWindow* win = (CraftsEngineWindow*)data;
        win->refreshAll();
        win->updateButtonsState();
    }
}

void CraftsEngineWindow::back_cb(Fl_Widget* w, void* data) {
    CraftsEngineWindow* allWin = (CraftsEngineWindow*)data;
    allWin->return_to_main();
}

CraftsEngineWindow::CraftsEngineWindow(CraftsWindow* mainWin){
    crWindow = mainWin;

    window = new Fl_Window(1440, 820, "Исследовать двигатели");
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

    // Двигатель 1
    std::string engine1Path = config.getPicturePath("Двигатель1.png");
    Picture engine1(100, 100, 96, 96, engine1Path.c_str());
    
    craft_engine1 = new Button(196, 123, 450, 50, 20, "Создать двигатель 1-го уровня");
    craft_engine1->getButton()->callback(craft_engine1_cb, this);
    craft_engine1->getButton()->tooltip("Stl:45, Dural:35, CuTi:20, Fe:120, Al:85");
    
    Text Engine1_Title(696, 123, 150, 50, 20, "Количество");

    Engine1_count = new Fl_Box(846, 123, 120, 50, "0");
    Engine1_count->labelsize(20);
    Engine1_count->box(FL_BORDER_BOX);
    Engine1_count->align(FL_ALIGN_CENTER);
    Engine1_count->labelfont(FL_COURIER_BOLD);

    // Двигатель 2
    std::string engine2Path = config.getPicturePath("Двигатель2.png");
    Picture engine2(100, 196, 96, 96, engine2Path.c_str());
    
    craft_engine2 = new Button(196, 219, 450, 50, 20, "Создать двигатель 2-го уровня");
    craft_engine2->getButton()->callback(craft_engine2_cb, this);
    craft_engine2->getButton()->tooltip("TiAlFe:40, CuTi:35, AlMg:30, Dural:25, Ti:75, Mg:50");
    
    Text Engine2_Title(696, 219, 150, 50, 20, "Количество");

    Engine2_count = new Fl_Box(846, 219, 120, 50, "0");
    Engine2_count->labelsize(20);
    Engine2_count->box(FL_BORDER_BOX);
    Engine2_count->align(FL_ALIGN_CENTER);
    Engine2_count->labelfont(FL_COURIER_BOLD);

    updateButtonsState();
}

CraftsEngineWindow::~CraftsEngineWindow() {
    // Деструктор
}

void CraftsEngineWindow::show() {
    window->show();
    refreshAll();
}

void CraftsEngineWindow::hide() {
    window->hide();
}

void CraftsEngineWindow::return_to_main() {
    crWindow->show();
    this->hide();
}

void CraftsEngineWindow::refreshAll(){
    std::string engine1Text = std::to_string(Rockets_parts.at("Engine1").getCount());
    Engine1_count->copy_label(engine1Text.c_str());

    std::string engine2Text = std::to_string(Rockets_parts.at("Engine2").getCount());
    Engine2_count->copy_label(engine2Text.c_str());
}

void CraftsEngineWindow::updateButtonsState(){
    // Двигатель 1
    if (Rockets_parts.at("Engine1").getIsUnlocked() == true && hasEnoughResourcesForEngine1()){
        craft_engine1->activate();
        craft_engine1->setColor(FL_GREEN);
        // Просто рецепт
        craft_engine1->getButton()->tooltip("Stl:45, Dural:35, CuTi:20, Fe:120, Al:85");
    } else {
        craft_engine1->deactivate();
        craft_engine1->setColor(FL_RED);
        // Просто рецепт
        craft_engine1->getButton()->tooltip("Stl:45, Dural:35, CuTi:20, Fe:120, Al:85");
    }

    // Двигатель 2
    if (Rockets_parts.at("Engine2").getIsUnlocked() == true && hasEnoughResourcesForEngine2()){
        craft_engine2->activate();
        craft_engine2->setColor(FL_GREEN);
        craft_engine2->getButton()->tooltip("TiAlFe:40, CuTi:35, AlMg:30, Dural:25, Ti:75, Mg:50");
    } else {
        craft_engine2->deactivate();
        craft_engine2->setColor(FL_RED);
        craft_engine2->getButton()->tooltip("TiAlFe:40, CuTi:35, AlMg:30, Dural:25, Ti:75, Mg:50");
    }
}