//
// Created by Hykilpikonna on 1/18/21.
//

#ifndef HOMEWORKS_WINDOW_H
#define HOMEWORKS_WINDOW_H

#include <memory>
#include <utility>

#include "gtkmm.h"
#include "macros.h"
#include "constants.h"
#include "GameState.h"

#define CContext const Cairo::RefPtr<Cairo::Context>&

using namespace Gtk;
using namespace sigc;

/**
 * Drawing area for GUI
 */
class MyRenderer: public DrawingArea
{
public:
    // Use pointers to sync it with the window's game object (https://www.cplusplus.com/doc/tutorial/pointers/)
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
        // Ignore if game ended (Tuple: https://en.cppreference.com/w/cpp/utility/tuple)
        if (get<0>(game->checkResult()) != -1) return;

        // Calculate which cell did the user press
        if (x < gPadding || y < gPadding) return; // Out of bounds
        val cellX = (int) (x - gPadding) / gFullCellLen;
        val cellY = (int) (y - gPadding) / gFullCellLen;
        if (cellX >= rows || cellY >= rows) return; // Out of bounds
        val loc = xyToLoc(cellX, cellY);

        // Debug log
        log("Pressed: " << x << ", " << y);
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

        // Draw win if game is won
        {
            val [result, combo] = game->checkResult();

            // If a player is won (not draw)
            if (result == 0 || result == 1)
            {
                // Calculate values
                val start = gPadding + gBorderLen;

                // Draw green squares
                cr->set_source_rgb(.76, 1, .44);
                for (Int loc: combo)
                {
                    val [x, y] = locToXy(loc);
                    cr->rectangle(start + gFullCellLen * x, start + gFullCellLen * y, gFullCellLen, gFullCellLen);
                    cr->fill();
                }
            }
        }

        // Draw boarder lines (https://developer.gnome.org/gtkmm-tutorial/stable/sec-cairo-drawing-lines.html.en)
        {
            // Calculate values
            val fullWidth = gFullCellLen * rows;
            val start = gPadding;
            val end = gPadding + fullWidth;

            cr->set_line_width(gBorderLen);
            cr->set_source_rgb(0.8, 0.0, 0.0);
            for (int row = 0; row < rows + 1; ++row)
            {
                // Draw vertical
                val xPos = start + gFullCellLen * row;
                cr->move_to(xPos, start);
                cr->line_to(xPos, end);

                // Draw horizontal
                val yPos = start + gFullCellLen * row;
                cr->move_to(start, yPos);
                cr->line_to(end, yPos);
            }
            cr->stroke();
        }

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
    Button bNewGameAI;
    Scale sAiDifficulty;
    std::unique_ptr<Gtk::MessageDialog> dialog;

    /**
     * Constructor
     */
    MyWindow(): box(Orientation::VERTICAL, 10),
                // Update window when game updates (Lambda: https://docs.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp)
                renderer(&game, [this](){ updateStats(); }),
                bNewGame("New Game vs Player"),
                bNewGameAI("New Game vs \"Ponkotsu AI\"")
    {
        // Window
        set_title("GUI");
        set_default_size(gWindowLen, gWindowLen);

        // Layout container box
        set_child(box);
        box.set_margin(20);

        // Add Components
        box.append(renderer);
        box.append(lStatus);
        box.append(bNewGame);
        box.append(bNewGameAI);
        box.append(sAiDifficulty);

        // Slider settings
        sAiDifficulty.set_range(0, 2);
        sAiDifficulty.set_round_digits(0);
        sAiDifficulty.set_increments(1, 1);

        // Register events
        bNewGame.signal_clicked().connect(sigc::bind(mem_fun(*this, &MyWindow::onClickNewGame)));
        bNewGameAI.signal_clicked().connect(sigc::bind(mem_fun(*this, &MyWindow::onClickNewGameAI)));
        sAiDifficulty.signal_value_changed().connect(sigc::bind(mem_fun(*this, &MyWindow::onAiDifficultySliderChange)));

        updateStats();
        onAiDifficultySliderChange();
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
     * Called when new game AI button is clicked
     */
    void onClickNewGameAI()
    {
        // Show dialog to let the player choose who goes first
        // https://developer.gnome.org/gtkmm-tutorial/stable/sec-dialogs-messagedialog.html.en
        dialog = std::make_unique<MessageDialog>(*this, "Who goes first?", false, MessageType::QUESTION, ButtonsType::NONE, true);
        dialog->set_secondary_text("And this is the secondary text that explains things.");
        dialog->add_button("Me", 0);
        dialog->add_button("AI", 1);
        dialog->signal_response().connect(sigc::bind(mem_fun(*this, &MyWindow::_onClickNewGameAI)));
        dialog->get_content_area()->set_margin(20);
        dialog->show();

        game = GameState(true);
        renderer.queue_draw();
        updateStats();
    }

    /**
     * Called when the user confirmed who would start the game.
     *
     * @param whoStart 0: Player, 1: AI
     */
    void _onClickNewGameAI(int whoStart)
    {
        if (!(whoStart == 1 || whoStart == 2)) return;

        dialog->hide();
        log("Dialog Clicked " << whoStart);
    }

    /**
     * Called when the AI difficulty slider change
     */
    void onAiDifficultySliderChange()
    {
        String difficulties[]{"Lv 0 - \"Ponkotsu AI\"",
                              "Lv 1 - Normal AI",
                              "Lv ∞ - Perfect AI"};

        bNewGameAI.set_label("New Game vs " + difficulties[(int) round(sAiDifficulty.get_value())]);
    }

    /**
     * Update status text
     */
    void updateStats()
    {
        String texts[]{"Now it's player " + str(game.currentPlayer + 1) + "'s turn!",
                       "Game ended, " + (game.aiMode && game.aiPlayer == 0 ? string("AI") : "player 1") + " won!",
                       "Game ended, " + (game.aiMode && game.aiPlayer == 1 ? string("AI") : "player 2") + " won!",
                       "Game ended, it's a draw!"};

        val result = get<0>(game.checkResult());
        lStatus.set_label(texts[result + 1]);
    }
};

#endif //HOMEWORKS_WINDOW_H
