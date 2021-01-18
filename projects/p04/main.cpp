//
// Created by Hykilpikonna on 1/18/21.
//

#include "main.h"
#include "Window.h"

int main(int argc, char *argv[])
{
    // Create GTK3 app
    auto app = Gtk::Application::create(argc, argv, "org.hydev.cpp.p04");

    // Create and run my window
    Window window;
    return app->run(window);
}