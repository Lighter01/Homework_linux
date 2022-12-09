#ifndef PREPARATION_PARAMETERS_H
#define PREPARATION_PARAMETERS_H

#include "defines.h"

/*!
 * \brief wrapValue - функция, проверяющая выход клетки за границу поля
 *
 * Закольцовывает игровое поле во время перемещения клеток.
 * \param v - координата клетки (по одной из координат)
 * \param vMax - граничное положение, возможное на поле (по одной из координат)
 * \return обновленное значение координаты, если клетка вышла за пределы игрового поля, иначе возвращает значение без изменений
 */
int wrapValue(int v, int vMax) // function for map cycling
{
    if (v == -1) return vMax - 1;
    if (v == vMax) return 0;
    return v;
}

/** \brief CELL_SIZE - размер одной клетки */
const int CELL_SIZE = 15;
/** \brief CELL_VECTOR - вектор, представляющий собой одну игровую клетку */
const sf::Vector2f CELL_VECTOR(CELL_SIZE, CELL_SIZE);
/** \brief GRID_WIDTH - ширина сетки в клетках */
const int GRID_WIDTH = 106;
/** \brief GRID_HEIGHT - высота сетки в клетках */
const int GRID_HEIGHT = 60;
/** \brief N_CELLS - количество клеток в сетке */
const int N_CELLS = GRID_WIDTH * GRID_HEIGHT;
/** \brief grid - массив живых клеток на поле */
int grid[N_CELLS] = {  };
/** \brief gridNext - массив клеток, которые должны быть живы на следующем шаге игры */
int gridNext[N_CELLS];

/*!
 * \brief generateStartGrid - функция, генерирующая начальное состояние игрового поля
 * \param grid - массив живых клеток на поле
 */
void generateStartGrid(int grid[N_CELLS])
{
    for (int i = 0; i < N_CELLS; i++)
        grid[i] = (static_cast<double>(std::uniform_int_distribution<std::size_t>(1, RAND_MAX)(random_device))/RAND_MAX < 0.1) ? 1 : 0;
    //     grid[0 + 0 * GRID_WIDTH] = 1;
    //     grid[1 + 1 * GRID_WIDTH] = 1;
    //     grid[2 + 1 * GRID_WIDTH] = 1;
    //     grid[0 + 2 * GRID_WIDTH] = 1;
    //     grid[1 + 2 * GRID_WIDTH] = 1;
}

/** \brief DELAY_INC - переменная, хранящая значение изменения задержки по нажатию на кнопки стрелочек вправо и влево */
const int DELAY_INC = 50;

/** \brief delay - переменная, хоанящая значение задержки */
int delay = 200;

/** \brief isPlaying - переменная, хранящая нынешнее состояние игрока */
bool isPlaying = true;



#endif // PREPARATION_PARAMETERS_H
