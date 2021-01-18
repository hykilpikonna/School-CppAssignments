//
// Created by Hykilpikonna on 1/18/21.
//

#ifndef HOMEWORKS_WINDOW_H
#define HOMEWORKS_WINDOW_H

#include "gtkmm.h"

using namespace Gtk;

class MyWindow: public Window
{
public:
    MyWindow()
    {
        // Window
        set_title("GUI");
        set_default_size(200, 200);
    }

    ~MyWindow() override = default;
};

#endif //HOMEWORKS_WINDOW_H
