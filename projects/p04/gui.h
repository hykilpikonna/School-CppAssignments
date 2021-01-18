//
// Created by Hykilpikonna on 1/18/21.
//

#ifndef HOMEWORKS_WINDOW_H
#define HOMEWORKS_WINDOW_H

#include "gtkmm.h"
#include "macros.h"

using namespace Gtk;

// GUI Constants
val rows = 3;
val padding = 50;
val cellLen = 50;
val borderWidth = 2;
val length = padding * 2 + cellLen * rows + borderWidth * (rows + 1);

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
        // Calculate values
        val xStart = padding;
        val yStart = padding;
        val fullWidth = (borderWidth + cellLen) * rows;
        val xEnd = xStart + fullWidth;
        val yEnd = yStart + fullWidth;

        // Line settings
        cr->set_line_width(borderWidth);

        // Draw vertical
        cr->set_source_rgb(0.8, 0.0, 0.0);
        for (int row = 0; row < rows + 1; ++row)
        {
            val xPos = xStart + (borderWidth + cellLen) * row;
            cr->move_to(xPos, yStart);
            cr->line_to(xPos, yEnd);
        }
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
