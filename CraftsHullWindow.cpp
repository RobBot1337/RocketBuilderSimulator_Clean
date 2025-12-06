#include "CraftsHullWindow.h"
#include "CraftsWindow.h"
#include "Mines.h"
#include "PartsOfRocket.h"
#include "Alloys.h"  // Для работы со сплавами
#include "Config.h"  // Для путей
#include <windows.h>
#include <mmsystem.h>

static Fl_PNG_Image* static_bg = nullptr;
static Fl_PNG_Image* static_arrow = nullptr;

Fl_Box* Hull1_count;
Fl_Box* Hull2_count;

// Вспомогательные функции для получения ресурсов
bool hasEnoughResourcesForHull1() {
    const auto& recipe = Rockets_parts.at("Hull1").getRecipe();
    
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

bool hasEnoughResourcesForHull2() {
    const auto& recipe = Rockets_parts.at("Hull2").getRecipe();
    
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
void CraftsHullWindow::craft_hull1_cb(Fl_Widget* w, void* data){
    if(Rockets_parts.at("Hull1").getIsUnlocked() == true && hasEnoughResourcesForHull1()){
        const auto& recipe = Rockets_parts.at("Hull1").getRecipe();
        
        // Вычитаем все ресурсы из рецепта
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
        
        Rockets_parts.at("Hull1").setCount(Rockets_parts.at("Hull1").getCount() + 1);

        CraftsHullWindow* win = (CraftsHullWindow*)data;
        win->refreshAll();
        win->updateButtonsState();
    }
}

void CraftsHullWindow::craft_hull2_cb(Fl_Widget* w, void* data){
    if(Rockets_parts.at("Hull2").getIsUnlocked() == true && hasEnoughResourcesForHull2()){
        const auto& recipe = Rockets_parts.at("Hull2").getRecipe();
        
        // Вычитаем все ресурсы из рецепта
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
        
        Rockets_parts.at("Hull2").setCount(Rockets_parts.at("Hull2").getCount() + 1);

        CraftsHullWindow* win = (CraftsHullWindow*)data;
        win->refreshAll();
        win->updateButtonsState();
    }
}

void CraftsHullWindow::back_cb(Fl_Widget* w, void* data) {
    CraftsHullWindow* allWin = (CraftsHullWindow*)data;
    allWin->return_to_main();
}

CraftsHullWindow::CraftsHullWindow(CraftsWindow* mainWin){
    crWindow = mainWin;

    window = new Fl_Window(1440, 820, "Крафт корпусов");
    window->position(10, 10);

    Config& config = Config::getInstance();
    
    // ЗАГРУЖАЕМ ИЗОБРАЖЕНИЯ С ИСПОЛЬЗОВАНИЕМ КОНФИГА
    if (!static_bg) {
        std::string bgPath = config.getPicturePath("Небо.png");
        std::string arrowPath = config.getPicturePath("Cтрелка.png");
        
        static_bg = new Fl_PNG_Image(bgPath.c_str());
        static_arrow = new Fl_PNG_Image(arrowPath.c_str());
    }

    bg = static_bg;
    background = new Fl_Box(0, 0, 1440, 820);
    background->image(bg);

    // ИСПОЛЬЗУЕМ УЖЕ ЗАГРУЖЕННЫЕ ИЗОБРАЖЕНИЯ
    back_Button = new PictureButton(0, 0, 96, 96, static_arrow);
    back_Button->getButton()->callback(back_cb, this);

    // Корпус 1
    std::string hull1Path = config.getPicturePath("Корпус1.png");
    Picture hull1(100, 100, 96, 96, hull1Path.c_str());
    
    craft_hull1 = new Button(196, 123, 450, 50, 20, "Создать корпус 1-го уровня");
    craft_hull1->getButton()->callback(craft_hull1_cb, this);
    craft_hull1->getButton()->tooltip("Stl:60, AlMg:40, Coal:150, Fe:200, Mg:80, Al:100");
    
    Text Hull1_Title(696, 123, 150, 50, 20, "Количество");

    Hull1_count = new Fl_Box(846, 123, 120, 50, "0");
    Hull1_count->labelsize(20);
    Hull1_count->box(FL_BORDER_BOX);
    Hull1_count->align(FL_ALIGN_CENTER);
    Hull1_count->labelfont(FL_COURIER_BOLD);

    // Корпус 2
    std::string hull2Path = config.getPicturePath("Корпус2.png");
    Picture hull2(100, 196, 96, 96, hull2Path.c_str());
    
    craft_hull2 = new Button(196, 219, 450, 50, 20, "Создать корпус 2-го уровня");
    craft_hull2->getButton()->callback(craft_hull2_cb, this);
    craft_hull2->getButton()->tooltip("TiAlFe:50, Dural:40, CuTi:35, AlMg:30, Stl:25, Ti:100, Cu:150");
    
    Text Hull2_Title(696, 219, 150, 50, 20, "Количество");

    Hull2_count = new Fl_Box(846, 219, 120, 50, "0");
    Hull2_count->labelsize(20);
    Hull2_count->box(FL_BORDER_BOX);
    Hull2_count->align(FL_ALIGN_CENTER);
    Hull2_count->labelfont(FL_COURIER_BOLD);

    updateButtonsState();
}

CraftsHullWindow::~CraftsHullWindow() {
    // Деструктор
}

void CraftsHullWindow::show() {
    window->show();
    refreshAll();
}

void CraftsHullWindow::hide() {
    window->hide();
}

void CraftsHullWindow::return_to_main() {
    crWindow->show();
    this->hide();
}

void CraftsHullWindow::refreshAll(){
    std::string hull1Text = std::to_string(Rockets_parts.at("Hull1").getCount());
    Hull1_count->copy_label(hull1Text.c_str());

    std::string hull2Text = std::to_string(Rockets_parts.at("Hull2").getCount());
    Hull2_count->copy_label(hull2Text.c_str());
}

void CraftsHullWindow::updateButtonsState(){
    // Корпус 1
    if (Rockets_parts.at("Hull1").getIsUnlocked() == true && hasEnoughResourcesForHull1()){
        craft_hull1->activate();
        craft_hull1->setColor(FL_GREEN);
        craft_hull1->getButton()->tooltip("Stl:60, AlMg:40, Coal:150, Fe:200, Mg:80, Al:100");
    } else {
        craft_hull1->deactivate();
        craft_hull1->setColor(FL_RED);
        craft_hull1->getButton()->tooltip("Stl:60, AlMg:40, Coal:150, Fe:200, Mg:80, Al:100");
    }

    // Корпус 2
    if (Rockets_parts.at("Hull2").getIsUnlocked() == true && hasEnoughResourcesForHull2()){
        craft_hull2->activate();
        craft_hull2->setColor(FL_GREEN);
        craft_hull2->getButton()->tooltip("TiAlFe:50, Dural:40, CuTi:35, AlMg:30, Stl:25, Ti:100, Cu:150");
    } else {
        craft_hull2->deactivate();
        craft_hull2->setColor(FL_RED);
        craft_hull2->getButton()->tooltip("TiAlFe:50, Dural:40, CuTi:35, AlMg:30, Stl:25, Ti:100, Cu:150");
    }
}

void CraftsHullWindow::updateData(void* data) {
    // Метод для обновления данных
}