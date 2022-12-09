#ifndef DISPLAY_GRID_H
#define DISPLAY_GRID_H

#include "preparation_parameters.h"

// display grid and prepare gridNext
/*!
 * \brief displayGrid   - функция, создающая следующий кадр игровой сетки
 * \param window        - окно для 2D-рисования, объект SFML
 * \param textSpeed     - переменная, хранящая текст интсрукции по изменению скорости игры, который надо вывести на экран игрового поля
 * \param textPause     - переменная, хранящая текст интсрукции по остановке игры, который надо вывести на экран игрового поля
 * \param textPlay      - переменная, хранящая текст интсрукции по продолжению игры, который надо вывести на экран игрового поля
 * \param textToggle    - переменная, хранящая текст интсрукции по взаимодействию с клетками в игре, который надо вывести на экран игрового поля
 */
void displayGrid(sf::RenderWindow& window, const sf::Text& textSpeed, const sf::Text& textPause, const sf::Text& textPlay, const sf::Text& textToggle) {
//    window.clear(WHITE);
    for (int x = 0; x < GRID_WIDTH; x++)
    {
        for (int y = 0; y < GRID_HEIGHT; y++)
        {
            // draw cell
            sf::RectangleShape cell;
            cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
            cell.setSize(CELL_VECTOR);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(GRAY);
            if (grid[x + y * GRID_WIDTH] == 1)
                cell.setFillColor(GREEN);
            else
                cell.setFillColor(WHITE);
            window.draw(cell);

            // prepare gridNext
            if (isPlaying)
            {
                int neighborSum = 0;
                for (int i = -1; i < 2; i++)
                    for (int j = -1; j < 2; j++)
                    {
                        /// \ref wrapValue() \copybrief wrapValue()
                        int xi = wrapValue(x + i, GRID_WIDTH);
                        int yj = wrapValue(y + j, GRID_HEIGHT);
                        neighborSum += grid[xi + yj * GRID_WIDTH];
                    }

                int current = x + y * GRID_WIDTH;
                neighborSum -= grid[current];
                gridNext[current] = grid[current];
                if (grid[current] == 1 && (neighborSum < 2 || neighborSum > 3))
                    gridNext[current] = 0;
                else if (neighborSum == 3)
                    gridNext[current] = 1;
            }
        }
    }

    // move gridNext to grid
    if (isPlaying)
        for (int i = 0; i < N_CELLS; i++)
            grid[i] = gridNext[i];

    // Additional info
    window.draw(textSpeed);
    if (isPlaying)
        window.draw(textPause);
    else
    {
        window.draw(textPlay);
        window.draw(textToggle);
    }

    window.display();
    sf::sleep(sf::milliseconds(delay));

}

#endif // DISPLAY_GRID_H
