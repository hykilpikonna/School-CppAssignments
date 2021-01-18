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
     * @param x Horizontal pixels from the left
     * @param y Vertical pixels from the top
     */
    void pressed(int _, double x, double y)
    {
        log("Pressed: " << x << ", " << y);

        // Calculate which cell did the user press
        if (x < gPadding || y < gPadding) return; // Out of bounds
        val cellX = (int) (x - gPadding) / gFullCellLen;
        val cellY = (int) (y - gPadding) / gFullCellLen;
        if (cellX >= rows || cellY >= rows) return; // Out of bounds
        val loc = xyToLoc(cellX, cellY);

        log("Pressed cell is: " << loc);

        // Check if location already has something
        if (game.grid[loc] != -1) return

        // Click for player
        game.movePlayer(cellX, cellY);

        // Refresh UI
        queue_draw();
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

        // Draw players
        cr->set_source_rgb(0.1, 0.1, 0.1);
        for (int x = 0; x < rows; ++x)
        {
            for (int y = 0; y < rows; ++y)
            {
                val v = game.grid[xyToLoc(x, y)];

                // Calculate cell graphics location
                val gs = gPadding + gBorderLen;
                val gx = gs + gFullCellLen * x;
                val gy = gs + gFullCellLen * y;

                // Player 1 (X)
                if (v == 0)
                {
                    // Draw X
                    int gxs[]{gx + gP1Padding, gx + gCellLen - gP1Padding};
                    int gys[]{gy + gP1Padding, gy + gCellLen - gP1Padding};
                    // Top left to bottom right
                    cr->move_to(gxs[0], gys[0]);
                    cr->line_to(gxs[1], gys[1]);
                    // Top right to bottom left
                    cr->move_to(gxs[0], gys[1]);
                    cr->line_to(gxs[1], gys[0]);
                    cr->stroke();
                }

                // Player 2 (O)
                if (v == 1)
                {
                    // Draw circle
                    val half = gCellLen * 0.5;
                    cr->arc(gx + half, gy + half, gP2Radius, 0.0, 2.0 * M_PI);
                    cr->stroke();
                }
            }
        }
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
