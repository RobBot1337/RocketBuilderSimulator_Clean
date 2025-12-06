#ifndef UI_WIDGETS_H
#define UI_WIDGETS_H

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_PNG_Image.H>
#include <string>

class Text {
private:
    Fl_Box* textBox;
    
public:
    Text(int x, int y, int w, int h, int s, const std::string& t);
};

class Picture {
private:
    Fl_Box* pictureBox;
    Fl_PNG_Image* picture;
    
public:
    Picture(int x, int y, int w, int h, const std::string& p);
};

class PictureButton {
private:
    Fl_Button* buttonBox;
    Fl_PNG_Image* buttonImage;
    
public:
    PictureButton(int x, int y, int w, int h, const std::string& p);
    PictureButton(int x, int y, int w, int h, Fl_PNG_Image* existing_image);
    Fl_Button* getButton();
    void updateImage(const char* newImagePath);
    
    // НОВЫЕ МЕТОДЫ ДЛЯ АКТИВАЦИИ/ДЕАКТИВАЦИИ
    void activate();
    void deactivate();
    bool isActive() const;
};

class Button {
private:
    Fl_Button* buttonBox;
    
public:
    Button(int x, int y, int w, int h, int s, const std::string& t);
    Fl_Button* getButton();
    
    // НОВЫЕ МЕТОДЫ ДЛЯ АКТИВАЦИИ/ДЕАКТИВАЦИИ
    void activate();
    void deactivate();
    bool isActive() const;
    
    // ДОПОЛНИТЕЛЬНЫЕ МЕТОДЫ ДЛЯ УДОБСТВА
    void setLabel(const std::string& newLabel);
    void setColor(Fl_Color color);
};

#endif