#include "display_grid.h"
#include "preparation_parameters.h"
#include "Events.h"


/*!
 * \brief main - главная функция, вызывающая сам процесс игры
 * \return
 */
int main()
{
    generateStartGrid(grid);

    sf::Font font;
    font.loadFromFile("./fonts/arial.ttf");

    sf::Text textPause("Press 'p' to pause.", font);
    textPause.setCharacterSize(15);
    textPause.setPosition(10, CELL_SIZE * GRID_HEIGHT + 5);
    textPause.setFillColor(BLACK);

    sf::Text textPlay("Press 'p' to play.", font);
    textPlay.setCharacterSize(15);
    textPlay.setPosition(10, CELL_SIZE * GRID_HEIGHT + 5);
    textPlay.setFillColor(BLACK);

    sf::Text textToggle("Click on cell to toggle live/dead cell.", font);
    textToggle.setCharacterSize(15);
    textToggle.setPosition(10, CELL_SIZE * GRID_HEIGHT + 25);
    textToggle.setFillColor(BLACK);

    sf::Text textSpeed("Use left/right arrow keys to change speed.", font);
    textSpeed.setCharacterSize(15);
    textSpeed.setPosition(300, CELL_SIZE * GRID_HEIGHT + 5);
    textSpeed.setFillColor(BLACK);

    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * GRID_WIDTH, CELL_SIZE * GRID_HEIGHT + 50), "Game of Life");
    while (window.isOpen())
    {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window); //позиция мышки относительно окны
        sf::Vector2f pos = window.mapPixelToCoords(pixelPos);
        sf::Event event;
        gameEvents(window, event, textSpeed, textPause, textPlay, textToggle);

        displayGrid(window, textSpeed, textPause, textPlay, textToggle);
    }
}
