//
// Created by Hykilpikonna on 1/18/21.
//

#include "Window.h"

Window::Window(): button("Test")
{
    set_border_width(10);
    button.signal_clicked().connect(sigc::mem_fun(*this, &Window::onButtonClick));
    add(button);
    button.show();
}

void Window::onButtonClick()
{
    log("Hi");
}
