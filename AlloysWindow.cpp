#include "AlloysWindow.h"
#include "RecourcesMainWindow.h" 
#include "Mines.h"
#include "Alloys.h"
#include "Config.h"
#include <windows.h>
#include <mmsystem.h>

static Fl_PNG_Image* static_bg = nullptr;
static Fl_PNG_Image* static_arrow = nullptr;

Fl_Box* Steel_Count;
Fl_Box* Duraluminium_Count;
Fl_Box* Aluminium_Magnesium_Count;
Fl_Box* Copper_Titanium_Count;
Fl_Box* Titanium_Aluminium_Iron_Count;

void AlloysWindow::craft_steel_cb(Fl_Widget* w, void* data) {
    if (iron >= alloys.at("Steel").getRecipe().at("iron") && coal >= alloys.at("Steel").getRecipe().at("coal")) {
        alloys.at("Steel").setCount(alloys.at("Steel").getCount() + 10);  // +10 за крафт
        iron -= alloys.at("Steel").getRecipe().at("iron");
        coal -= alloys.at("Steel").getRecipe().at("coal");
        
        AlloysWindow* win = (AlloysWindow*)data;
        win->refreshAll();
    }
}

void AlloysWindow::craft_duraluminium_cb(Fl_Widget* w, void* data) {
    if (aluminium >= alloys.at("Duraluminium").getRecipe().at("aluminium") && 
        copper >= alloys.at("Duraluminium").getRecipe().at("copper")){
        
        alloys.at("Duraluminium").setCount(alloys.at("Duraluminium").getCount() + 10);  // +10 за крафт
        aluminium -= alloys.at("Duraluminium").getRecipe().at("aluminium");
        copper -= alloys.at("Duraluminium").getRecipe().at("copper");
        
        AlloysWindow* win = (AlloysWindow*)data;
        win->refreshAll();
    }
}

void AlloysWindow::craft_aluminium_magnesium_cb(Fl_Widget* w, void* data) {
    if (aluminium >= alloys.at("AluminiumMagnesium").getRecipe().at("aluminium") && 
        magnesium >= alloys.at("AluminiumMagnesium").getRecipe().at("magnesium")) {
        
        alloys.at("AluminiumMagnesium").setCount(alloys.at("AluminiumMagnesium").getCount() + 10);  // +10 за крафт
        aluminium -= alloys.at("AluminiumMagnesium").getRecipe().at("aluminium");
        magnesium -= alloys.at("AluminiumMagnesium").getRecipe().at("magnesium");
        
        AlloysWindow* win = (AlloysWindow*)data;
        win->refreshAll();
    }
}

void AlloysWindow::craft_copper_titanium_cb(Fl_Widget* w, void* data) {
    if (copper >= alloys.at("CopperTitanium").getRecipe().at("copper") && 
        titanium >= alloys.at("CopperTitanium").getRecipe().at("titanium")) {
        
        alloys.at("CopperTitanium").setCount(alloys.at("CopperTitanium").getCount() + 10);  // +10 за крафт
        copper -= alloys.at("CopperTitanium").getRecipe().at("copper");
        titanium -= alloys.at("CopperTitanium").getRecipe().at("titanium");
        
        AlloysWindow* win = (AlloysWindow*)data;
        win->refreshAll();
    }
}

void AlloysWindow::craft_titanium_aluminium_iron_cb(Fl_Widget* w, void* data) {
    if (titanium >= alloys.at("TitaniumAluminiumIron").getRecipe().at("titanium") && 
        aluminium >= alloys.at("TitaniumAluminiumIron").getRecipe().at("aluminium") &&
        iron >= alloys.at("TitaniumAluminiumIron").getRecipe().at("iron")) {
        
        alloys.at("TitaniumAluminiumIron").setCount(alloys.at("TitaniumAluminiumIron").getCount() + 10);  // +10 за крафт
        titanium -= alloys.at("TitaniumAluminiumIron").getRecipe().at("titanium");
        aluminium -= alloys.at("TitaniumAluminiumIron").getRecipe().at("aluminium");
        iron -= alloys.at("TitaniumAluminiumIron").getRecipe().at("iron");
        
        AlloysWindow* win = (AlloysWindow*)data;
        win->refreshAll();
    }
}

AlloysWindow::AlloysWindow(RecourcesMainWindow* mainWin){
    resWindow = mainWin;

    window = new Fl_Window(1440, 820, "Сплавы");
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

    // СТАЛЬ - верные рецепты из alloys.h
    std::string steelPath = config.getPicturePath("Сталь.png");
    Picture steel_picture(100, 100, 96, 96, steelPath.c_str());
    
    craft_steel = new Button(196, 123, 300, 60, 20, "Создать сталь");
    craft_steel->getButton()->callback(craft_steel_cb, this);
    craft_steel->getButton()->tooltip("Сталь: 10 железа + 5 угля");

    Text steel_count_Title(506, 123, 300, 60, 20, "Количество стали: ");
    Steel_Count = new Fl_Box(806, 123, 120, 60, "0");
    Steel_Count->labelsize(20);
    Steel_Count->box(FL_BORDER_BOX);
    Steel_Count->align(FL_ALIGN_CENTER);
    Steel_Count->labelfont(FL_COURIER_BOLD);

    // ДЮРАЛЮМИНИЙ
    std::string duralPath = config.getPicturePath("Дюраллюминий.png");
    Picture duraluminium_picture(100, 196, 96, 96, duralPath.c_str());
    craft_duraluminium = new Button(196, 219, 300, 60, 20, "Создать дюралюминий");
    craft_duraluminium->getButton()->callback(craft_duraluminium_cb, this);
    craft_duraluminium->getButton()->tooltip("Дюралюминий: 10 алюминия + 5 меди");

    Text duraluminium_count_Title(506, 219, 300, 60, 20, "Количество дюралюминия: ");
    Duraluminium_Count = new Fl_Box(806, 219, 120, 60, "0");
    Duraluminium_Count->labelsize(20);
    Duraluminium_Count->box(FL_BORDER_BOX);
    Duraluminium_Count->align(FL_ALIGN_CENTER);
    Duraluminium_Count->labelfont(FL_COURIER_BOLD);

    // АЛЮМИНИЙ+МАГНИЙ
    std::string almgPath = config.getPicturePath("АлюминийМагний.png");
    Picture aluminium_magnesium_picture(100, 292, 96, 96, almgPath.c_str());
    craft_aluminium_magnesium = new Button(196, 315, 300, 60, 20, "Создать Al+Mg сплав");
    craft_aluminium_magnesium->getButton()->callback(craft_aluminium_magnesium_cb, this);
    craft_aluminium_magnesium->getButton()->tooltip("Al+Mg сплав: 8 алюминия + 4 магния");

    Text aluminium_magnesium_count_Title(506, 315, 300, 60, 20, "Количество Al+Mg: ");
    Aluminium_Magnesium_Count = new Fl_Box(806, 315, 120, 60, "0");
    Aluminium_Magnesium_Count->labelsize(20);
    Aluminium_Magnesium_Count->box(FL_BORDER_BOX);
    Aluminium_Magnesium_Count->align(FL_ALIGN_CENTER);
    Aluminium_Magnesium_Count->labelfont(FL_COURIER_BOLD);

    // МЕДЬ+ТИТАН
    std::string cutiPath = config.getPicturePath("МедьТитан.png");
    Picture copper_titanium_picture(100, 388, 96, 96, cutiPath.c_str());
    craft_copper_titanium = new Button(196, 411, 300, 60, 20, "Создать Cu+Ti сплав");
    craft_copper_titanium->getButton()->callback(craft_copper_titanium_cb, this);
    craft_copper_titanium->getButton()->tooltip("Cu+Ti сплав: 6 меди + 3 титана");

    Text copper_titanium_count_Title(506, 411, 300, 60, 20, "Количество Cu+Ti: ");
    Copper_Titanium_Count = new Fl_Box(806, 411, 120, 60, "0");
    Copper_Titanium_Count->labelsize(20);
    Copper_Titanium_Count->box(FL_BORDER_BOX);
    Copper_Titanium_Count->align(FL_ALIGN_CENTER);
    Copper_Titanium_Count->labelfont(FL_COURIER_BOLD);

    // ТИТАН+АЛЮМИНИЙ+ЖЕЛЕЗО
    std::string tiaifePath = config.getPicturePath("ТитанАлюминийЖелезо.png");
    Picture titanium_aluminium_iron_picture(100, 484, 96, 96, tiaifePath.c_str());
    craft_titanium_aluminium_iron = new Button(196, 507, 300, 60, 20, "Создать Ti+Al+Fe сплав");
    craft_titanium_aluminium_iron->getButton()->callback(craft_titanium_aluminium_iron_cb, this);
    craft_titanium_aluminium_iron->getButton()->tooltip("Ti+Al+Fe сплав: 4 титана + 6 алюминия + 5 железа");

    Text titanium_aluminium_iron_count_Title(506, 507, 300, 60, 20, "Количество Ti+Al+Fe: ");
    Titanium_Aluminium_Iron_Count = new Fl_Box(806, 507, 120, 60, "0");
    Titanium_Aluminium_Iron_Count->labelsize(20);
    Titanium_Aluminium_Iron_Count->box(FL_BORDER_BOX);
    Titanium_Aluminium_Iron_Count->align(FL_ALIGN_CENTER);
    Titanium_Aluminium_Iron_Count->labelfont(FL_COURIER_BOLD);

    refreshAll();
}

AlloysWindow::~AlloysWindow() {
    // ТАЙМЕР УБРАН - НИЧЕГО НЕ УДАЛЯЕМ
}

void AlloysWindow::refreshAll() {
    std::string steelText = std::to_string(alloys.at("Steel").getCount());
    Steel_Count->copy_label(steelText.c_str());

    std::string duraluminiumText = std::to_string(alloys.at("Duraluminium").getCount());
    Duraluminium_Count->copy_label(duraluminiumText.c_str());

    std::string aluminiumMagnesiumText = std::to_string(alloys.at("AluminiumMagnesium").getCount());
    Aluminium_Magnesium_Count->copy_label(aluminiumMagnesiumText.c_str());

    std::string copperTitaniumText = std::to_string(alloys.at("CopperTitanium").getCount());
    Copper_Titanium_Count->copy_label(copperTitaniumText.c_str());

    std::string titaniumAluminiumIronText = std::to_string(alloys.at("TitaniumAluminiumIron").getCount());
    Titanium_Aluminium_Iron_Count->copy_label(titaniumAluminiumIronText.c_str());
    
    updateButtonsState();
    
    if (window->visible()) {
        window->redraw();
    }
}

void AlloysWindow::updateButtonsState() {
    // Сталь
    if (iron >= alloys.at("Steel").getRecipe().at("iron") && coal >= alloys.at("Steel").getRecipe().at("coal")){
        craft_steel->activate();
        craft_steel->setColor(FL_GREEN);
        craft_steel->getButton()->tooltip("Создать сталь");
    } else {
        craft_steel->deactivate();
        craft_steel->setColor(FL_RED);
        craft_steel->getButton()->tooltip("Недостаточно ресурсов\nРецепт: 10 железа + 5 угля");
    }

    // Дюралюминий
    if (aluminium >= alloys.at("Duraluminium").getRecipe().at("aluminium") && 
        copper >= alloys.at("Duraluminium").getRecipe().at("copper")) {
        craft_duraluminium->activate();
        craft_duraluminium->setColor(FL_GREEN);
        craft_duraluminium->getButton()->tooltip("Создать дюралюминий");
    } else {
        craft_duraluminium->deactivate();
        craft_duraluminium->setColor(FL_RED);
        craft_duraluminium->getButton()->tooltip("Недостаточно ресурсов\nРецепт: 10 алюминия + 5 меди");
    }

    // Алюминий+Магний
    if (aluminium >= alloys.at("AluminiumMagnesium").getRecipe().at("aluminium") && 
        magnesium >= alloys.at("AluminiumMagnesium").getRecipe().at("magnesium")) {
        craft_aluminium_magnesium->activate();
        craft_aluminium_magnesium->setColor(FL_GREEN);
        craft_aluminium_magnesium->getButton()->tooltip("Создать Al+Mg сплав");
    } else {
        craft_aluminium_magnesium->deactivate();
        craft_aluminium_magnesium->setColor(FL_RED);
        craft_aluminium_magnesium->getButton()->tooltip("Недостаточно ресурсов\nРецепт: 8 алюминия + 4 магния");
    }

    // Медь+Титан
    if (copper >= alloys.at("CopperTitanium").getRecipe().at("copper") && 
        titanium >= alloys.at("CopperTitanium").getRecipe().at("titanium")) {
        craft_copper_titanium->activate();
        craft_copper_titanium->setColor(FL_GREEN);
        craft_copper_titanium->getButton()->tooltip("Создать Cu+Ti сплав");
    } else {
        craft_copper_titanium->deactivate();
        craft_copper_titanium->setColor(FL_RED);
        craft_copper_titanium->getButton()->tooltip("Недостаточно ресурсов\nРецепт: 6 меди + 3 титана");
    }

    // Титан+Алюминий+Железо
    if (titanium >= alloys.at("TitaniumAluminiumIron").getRecipe().at("titanium") && 
        aluminium >= alloys.at("TitaniumAluminiumIron").getRecipe().at("aluminium") &&
        iron >= alloys.at("TitaniumAluminiumIron").getRecipe().at("iron")) {
        craft_titanium_aluminium_iron->activate();
        craft_titanium_aluminium_iron->setColor(FL_GREEN);
        craft_titanium_aluminium_iron->getButton()->tooltip("Создать Ti+Al+Fe сплав");
    } else {
        craft_titanium_aluminium_iron->deactivate();
        craft_titanium_aluminium_iron->setColor(FL_RED);
        craft_titanium_aluminium_iron->getButton()->tooltip("Недостаточно ресурсов\nРецепт: 4 титана + 6 алюминия + 5 железа");
    }
}

void AlloysWindow::show() {
    window->show();
    refreshAll();
}

void AlloysWindow::hide() {
    window->hide();
}

void AlloysWindow::back_cb(Fl_Widget* w, void* data) {
    AlloysWindow* allWin = (AlloysWindow*)data;
    allWin->return_to_main();
}

void AlloysWindow::return_to_main() {
    resWindow->show();
    this->hide();
}