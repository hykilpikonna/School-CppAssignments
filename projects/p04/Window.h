//
// Created by Hykilpikonna on 1/18/21.
//

#ifndef HOMEWORKS_WINDOW_H
#define HOMEWORKS_WINDOW_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include "macros.h"

class Window: public Gtk::Window
{
public:
    Gtk::Button button;

    Window();
    ~Window() override = default;

    void onButtonClick();

};

#endif //HOMEWORKS_WINDOW_H
