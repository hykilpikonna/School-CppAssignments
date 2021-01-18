//
// Created by Hykilpikonna on 1/18/21.
//

#ifndef HOMEWORKS_WINDOW_H
#define HOMEWORKS_WINDOW_H

#include "gtkmm.h"
#include "macros.h"
#include "constants.h"
#include "GameState.h"

using namespace Gtk;

/**
 * Drawing area for GUI
 */
class MyArea: public DrawingArea
{
public:
    GameState game;

    /**
     * Constructor
     */
    MyArea()
    {
        // Set draw callback function
        set_draw_func(sigc::mem_fun(*this, &MyArea::on_draw));

        // Mouse
        val controller = GestureClick::create();
        controller->signal_released().connect(sigc::bind(sigc::mem_fun(*this, &MyArea::pressed)), false);
        add_controller(controller);

    }
    ~MyArea() override = default;

    /**
     * Called whenever the mouse clicks the drawing area
     *
     * @param n_press What is this?
     * @param x Horizontal pixels from the left
     * @param y Vertical pixels from the top
     */
    void pressed(int n_press, double x, double y)
    {
        log("Pressed: " << x << ", " << y);

        // Calculate which cell did the user press
        if (x < gPadding || y < gPadding) return; // Out of bounds
        val cellX = (int) (x - gPadding) / gFullCellLen;
        val cellY = (int) (y - gPadding) / gFullCellLen;
        if (cellX >= rows || cellY >= rows) return; // Out of bounds
        val loc = xyToLoc(cellX, cellY);

        log("Pressed cell is: " << loc);

        // Click for player
        game.movePlayer(cellX, cellY);
    }

    /**
     * Draw GUI
     */
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
    {
        // Calculate values
        val xStart = gPadding;
        val yStart = gPadding;
        val fullWidth = gFullCellLen * rows;
        val xEnd = xStart + fullWidth;
        val yEnd = yStart + fullWidth;

        // Draw boarder lines
        cr->set_line_width(gBorderLen);
        cr->set_source_rgb(0.8, 0.0, 0.0);
        for (int row = 0; row < rows + 1; ++row)
        {
            // Draw vertical
            val xPos = xStart + gFullCellLen * row;
            cr->move_to(xPos, yStart);
            cr->line_to(xPos, yEnd);

            // Draw horizontal
            val yPos = yStart + gFullCellLen * row;
            cr->move_to(xStart, yPos);
            cr->line_to(xEnd, yPos);
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
        set_default_size(gWindowLen, gWindowLen);

        // Add drawing area
        set_child(drawingArea);
    }
    ~MyWindow() override = default;
};

#endif //HOMEWORKS_WINDOW_H
