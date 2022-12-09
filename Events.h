#ifndef EVENTS_H
#define EVENTS_H

#include "preparation_parameters.h"
#include "display_grid.h"

/*!
 * \brief gameEvents - функция, проверяющая наличие игровых событий и отвечающая за их вызов
 * \param window        - окно для 2D-рисования, объект SFML
 * \param event         - объект SFML, хранящий информацию о действии, совершенном пользователем
 * \param textSpeed     - переменная, хранящая текст интсрукции по изменению скорости игры, который надо вывести на экран игрового поля
 * \param textPause     - переменная, хранящая текст интсрукции по остановке игры, который надо вывести на экран игрового поля
 * \param textPlay      - переменная, хранящая текст интсрукции по продолжению игры, который надо вывести на экран игрового поля
 * \param textToggle    - переменная, хранящая текст интсрукции по взаимодействию с клетками в игре, который надо вывести на экран игрового поля
 */
void gameEvents(sf::RenderWindow& window, sf::Event& event,
                const sf::Text& textSpeed, const sf::Text& textPause, const sf::Text& textPlay, const sf::Text& textToggle) {
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::P)
                isPlaying = !isPlaying;
            else if (event.key.code == sf::Keyboard::Right)
                delay = std::max(delay - DELAY_INC, 0); // 0 to prevent negative numbers
            else if (event.key.code == sf::Keyboard::Left)
                delay += DELAY_INC;
            else if (event.key.code == sf::Keyboard::Z)
            {
                while (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        int x = double(sf::Mouse::getPosition(window).x) / CELL_SIZE;
                        int y = double(sf::Mouse::getPosition(window).y) / CELL_SIZE;
                        if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT)
                            grid[x + y * GRID_WIDTH] = 1;
                        displayGrid(window, textSpeed, textPause, textPlay, textToggle); // really slow
                    }
                }
            }
            break;
        case sf::Event::MouseButtonPressed:
            int x = double(sf::Mouse::getPosition(window).x) / CELL_SIZE;
            int y = double(sf::Mouse::getPosition(window).y) / CELL_SIZE;
            if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT)
                grid[x + y * GRID_WIDTH] = !grid[x + y * GRID_WIDTH];
            break;
        }
    }
}

#endif // EVENTS_H
