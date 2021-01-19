//
// Created by Hykilpikonna on 1/18/21.
//

#ifndef HOMEWORKS_WINDOW_H
#define HOMEWORKS_WINDOW_H

#include <utility>

#include "gtkmm.h"
#include "macros.h"
#include "constants.h"
#include "GameState.h"

#define CContext const Cairo::RefPtr<Cairo::Context>&

using namespace Gtk;

/**
 * Drawing area for GUI
 */
class MyRenderer: public DrawingArea
{
public:
    GameState* game;

    // Update callback function (https://stackoverflow.com/questions/2298242/callback-functions-in-c)
    function<void()> updateCallback;

    /**
     * Constructor
     */
    explicit MyRenderer(GameState* game, function<void()> updateCallback): game(game), updateCallback(std::move(updateCallback))
    {
        set_size_request(gWindowLen, gWindowLen);

        // Set draw callback function
        set_draw_func(sigc::mem_fun(*this, &MyRenderer::draw));

        // Mouse
        val controller = GestureClick::create();
        controller->signal_released().connect(sigc::bind(sigc::mem_fun(*this, &MyRenderer::pressed)), false);
        add_controller(controller);
    }

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
        if (game->grid[loc] != NO_CELL) return;

        // Click for player
        game->movePlayer(cellX, cellY);

        // Refresh UI
        queue_draw();
        updateCallback();
    }

    /**
     * Draw GUI
     */
    void draw(CContext cr, int width, int height) const
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
                val v = game->grid[xyToLoc(x, y)];

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
                    // https://developer.gnome.org/gtkmm-tutorial/stable/sec-cairo-drawing-arcs.html.en
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
    // Game
    GameState game;

    // UI Components
    Box box;
    MyRenderer renderer;
    Label lStatus;
    Button bNewGame;

    /**
     * Constructor
     */
    MyWindow(): box(Orientation::VERTICAL, 10),
                // Update window when game updates (Lambda: https://docs.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp)
                renderer(&game, [this](){ updateStats(); }),
                bNewGame("New Game vs Player")
    {
        // Window
        set_title("GUI");
        set_default_size(gWindowLen, gWindowLen);

        // Layout container box
        set_child(box);

        // Add Components
        box.append(renderer);
        box.append(lStatus);
        box.append(bNewGame);

        // Register events
        bNewGame.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &MyWindow::onClickNewGame)));

        updateStats();
    }
    ~MyWindow() override = default;

    /**
     * Called when new game button is clicked
     */
    void onClickNewGame()
    {
        game = GameState();
        renderer.queue_draw();
        updateStats();
    }

    /**
     * Update status text
     */
    void updateStats()
    {
        String texts[]{"Now it's player " + str(game.currentPlayer + 1) + "'s turn!",
                       "Game ended, player 1 won!",
                       "Game ended, player 2 won!",
                       "Game ended, it's a draw!"};

        val result = game.checkResult();
        lStatus.set_label(texts[result + 1]);
    }
};

#endif //HOMEWORKS_WINDOW_H
