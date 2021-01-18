//
// Created by Hykilpikonna on 1/18/21.
//

#ifndef HOMEWORKS_WINDOW_H
#define HOMEWORKS_WINDOW_H

#include "gtkmm.h"

using namespace Gtk;

/**
 * Drawing area for GUI
 */
class MyArea: public DrawingArea
{
public:
    /**
     * Constructor
     */
    MyArea()
    {
        // Set draw callback function
        set_draw_func(sigc::mem_fun(*this, &MyArea::on_draw));
    }
    ~MyArea() override = default;

    /**
     * Draw GUI
     */
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
    {
        // coordinates for the center of the window
        int xc, yc;
        xc = width / 2;
        yc = height / 2;

        cr->set_line_width(10.0);

        // draw red lines out from the center of the window
        cr->set_source_rgb(0.8, 0.0, 0.0);
        cr->move_to(0, 0);
        cr->line_to(xc, yc);
        cr->line_to(0, height);
        cr->move_to(xc, yc);
        cr->line_to(width, yc);
        cr->stroke();
    }
};

/**
 * GUI Window
 */
class MyWindow: public Window
{
public:
    // Initialize drawing area
    MyArea drawingArea;

    /**
     * Constructor
     */
    MyWindow()
    {
        // Window
        set_title("GUI");
        set_default_size(length, length);

        // Add drawing area
        set_child(drawingArea);
    }
    ~MyWindow() override = default;
};

#endif //HOMEWORKS_WINDOW_H
