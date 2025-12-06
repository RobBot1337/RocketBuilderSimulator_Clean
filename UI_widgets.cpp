#include "UI_widgets.h"
#include <cstring>
#include <string>

// Реализация класса Text
Text::Text(int x, int y, int w, int h, int s, const std::string& t) {
    textBox = new Fl_Box(x, y, w, h);
    textBox->copy_label(t.c_str());
    textBox->labelsize(s);
    textBox->box(FL_BORDER_BOX);
    textBox->align(FL_ALIGN_CENTER);
    textBox->labelfont(FL_COURIER_BOLD);
}

// Реализация класс Picture
Picture::Picture(int x, int y, int w, int h, const std::string& p){
    pictureBox = new Fl_Box(x, y, w, h);
    picture = new Fl_PNG_Image(p.c_str());
    pictureBox->image(picture);
}

// Конструктор для загрузки изображения по пути
PictureButton::PictureButton(int x, int y, int w, int h, const std::string& p) {
    buttonImage = new Fl_PNG_Image(p.c_str());
    buttonBox = new Fl_Button(x, y, w, h);
    buttonBox->image(buttonImage);
}

// НОВЫЙ конструктор для готового изображения
PictureButton::PictureButton(int x, int y, int w, int h, Fl_PNG_Image* existing_image) {
    buttonImage = existing_image;  // Используем уже загруженное изображение
    buttonBox = new Fl_Button(x, y, w, h);
    buttonBox->image(buttonImage);
}

Fl_Button* PictureButton::getButton() {
    return buttonBox;
}

void PictureButton::updateImage(const char* newImagePath) {
    delete buttonImage;
    buttonImage = new Fl_PNG_Image(newImagePath);
    buttonBox->image(buttonImage);
}

// НОВЫЕ МЕТОДЫ ДЛЯ PictureButton
void PictureButton::activate() {
    if (buttonBox) buttonBox->activate();
}

void PictureButton::deactivate() {
    if (buttonBox) buttonBox->deactivate();
}

bool PictureButton::isActive() const {
    return buttonBox ? buttonBox->active() : false;
}

// Реализация класса Button
Button::Button(int x, int y, int w, int h, int s, const std::string& t) {
    buttonBox = new Fl_Button(x, y, w, h);
    buttonBox->copy_label(t.c_str());
    buttonBox->labelsize(s);
    buttonBox->align(FL_ALIGN_CENTER);
    buttonBox->labelfont(FL_COURIER_BOLD);
}

Fl_Button* Button::getButton(){
    return buttonBox;
}

// НОВЫЕ МЕТОДЫ ДЛЯ Button
void Button::activate() {
    if (buttonBox) buttonBox->activate();
}

void Button::deactivate() {
    if (buttonBox) buttonBox->deactivate();
}

bool Button::isActive() const {
    return buttonBox ? buttonBox->active() : false;
}

void Button::setLabel(const std::string& newLabel) {
    if (buttonBox) buttonBox->copy_label(newLabel.c_str());
}

void Button::setColor(Fl_Color color) {
    if (buttonBox) buttonBox->color(color);
}