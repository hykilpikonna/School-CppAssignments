//
// Created by Hykilpikonna on 1/18/21.
//

#include "gui.h"

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create("org.hydev.cpp.p04");
    return app->make_window_and_run<MyWindow>(argc, argv);
}