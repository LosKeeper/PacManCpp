#ifndef GHOST_H
#define GHOST_H

#include "shortestpath.h"
#include <random>

#define GHOST_INIT_X 10
#define GHOST_INIT_Y 10

#define RED_GHOST_INIT_X 10
#define RED_GHOST_INIT_Y 10

#define PINK_GHOST_INIT_X 9
#define PINK_GHOST_INIT_Y 12

#define BLUE_GHOST_INIT_X 10
#define BLUE_GHOST_INIT_Y 13

#define ORANGE_GHOST_INIT_X 11
#define ORANGE_GHOST_INIT_Y 12

#define GHOST_CENTER_X 0
#define GHOST_CENTER_Y 4

#define GHOST_HOUSE_SPEED 1
#define GHOST_HOUSE_RANGE_CENTER GHOST_HOUSE_SPEED - 1
#define GHOST_FEAR_SPEED 1
#define GHOST_FEAR_RANGE_CENTER GHOST_FEAR_SPEED - 1
#define GHOST_SPEED 2
#define GHOST_RANGE_CENTER GHOST_SPEED - 1
#define GHOST_RETURN_SPEED 3
#define GHOST_RETURN_RANGE_CENTER GHOST_RETURN_SPEED - 1

enum color { RED, PINK, BLUE, ORANGE };

// macro for wait time in function of difficulty
#define RED_GHOST_WAIT_TIME (6 / DIFFICULTY)     // 6s for easy
#define PINK_GHOST_WAIT_TIME (12 / DIFFICULTY)   // 12s for easy
#define BLUE_GHOST_WAIT_TIME (18 / DIFFICULTY)   // 18s for easy
#define ORANGE_GHOST_WAIT_TIME (24 / DIFFICULTY) // 24s for easy

// swap for the blue ghost between chase mode of red and pink ghost
#define BLUE_GHOST_RED_TIME 20  // 20s
#define BLUE_GHOST_PINK_TIME 12 // 12s

#define CHASE_MODE 20  // 20s
#define SCATTER_MODE 7 // 7s

#define updateDirWithShortestPath(vecBoard, xPac, yPac) \
    updateDirRed(vecBoard, xPac, yPac)

enum mode { ANY, CHASE, SCATTER, FRIGHTENED };

class ghost {
  public:
    ghost();
    ~ghost();
    /**
     * @brief Set the timer object.
     *
     */
    void setTimer();
    /**
     * @brief Set the color of the ghost.
     *
     * @param c
     */
    void setGhost(color c);
    /**
     * @brief Get the color of the ghost.
     *
     * @return color
     */
    color getGhost();
    /**
     * @brief Check if the ghost is in the ghost house.
     *
     * @return true
     * @return false
     */
    bool isInHouse();
    /**
     * @brief Update the position of the ghost in the ghost house.
     */
    void updateInGhostHouse(
        std::vector<std::vector<std::shared_ptr<square>>> vecBoard);
    /**
     * @brief Ghost go back to the house.
     *
     */
    void setReturnHouse();
    /**
     * @brief Check if the ghost is returning in the ghost house.
     *
     * @return true
     * @return false
     */
    bool isReturnHouse();
    /**
     * @brief Make the ghost go to the ghost house.
     *
     * @param vecBoard
     */
    void
    returnHouse(std::vector<std::vector<std::shared_ptr<square>>> vecBoard);
    /**
     * @brief Set the frightened object.
     *
     * @param isFear
     */
    void setFrightened(bool isFear);
    /**
     * @brief Check if the ghost is frightened.
     *
     * @return true
     * @return false
     */
    bool isFrightened();
    /**
     * @brief Get the sprite position of the ghost.
     *
     * @return std::pair<size_t, size_t>
     */
    std::pair<size_t, size_t> getPos();
    /**
     * @brief Update the sprite position of the ghost.
     *
     * @param count - frame number
     * @note The sprite position represents the pixel position of the ghost.
     */
    void updatePos();
    /**
     * @brief Wait the ghost to be in the center of a square in function of the
     * ghost speed, of the direction and of the sprite position.
     *
     * @return true
     * @return false
     */
    bool waitSquareCenter();
    /**
     * @brief Get the last direction of the ghost.
     *
     * @return dir*
     */
    dir getLastDir();
    /**
     * @brief Update the direction of the ghost with a  valid random
     * direction and update the board position of the ghost.
     *
     * @param vecBoard
     */
    void updateDir(std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
                   std::pair<size_t, size_t> pacPos, dir dirPac);
    /**
     * @brief Update direction of red ghost. Red ghost is following the pacman.
     *
     * @param vecBoard
     * @param xPac
     * @param yPac
     */
    void
    updateDirRed(std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
                 size_t xPac, size_t yPac);
    /**
     * @brief Update direction of pink ghost. Pink ghost is anticipating the
     * pacman, it is going to the position of the pacman + 4.
     *
     * @param vecBoard
     * @param xPac
     * @param yPac
     * @param dirPac
     */
    void
    updateDirPink(std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
                  size_t xPac, size_t yPac, dir dirPac);
    /**
     * @brief Update direction of blue ghost. Swap between the chase mode of red
     * and pink ghost.
     *
     * @param vecBoard
     * @param xPac
     * @param yPac
     * @param dirPac
     */
    void
    updateDirBlue(std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
                  size_t xPac, size_t yPac, dir dirPac);
    /**
     * @brief Update direction of orange ghost. Orange ghost is following the
     * pacman if the distance between the pacman and the ghost is greater than
     * 8, else it is going to the ghost house.
     *
     * @param vecBoard
     * @param xPac
     * @param yPac
     * @param dirPac
     */
    void
    updateDirOrange(std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
                    size_t xPac, size_t yPac);
    /**
     * @brief Update of the orange ghost. Orange ghost takes a random
     * direction.
     *
     * @param vecBoard
     */
    void
    updateDirRandom(std::vector<std::vector<std::shared_ptr<square>>> vecBoard);
    /**
     * @brief Update the direction of the ghost in scatter mode.
     *
     * @param vecBoard
     * @param x
     * @param y
     */
    void updateDirScatterMode(
        std::vector<std::vector<std::shared_ptr<square>>> vecBoard, size_t x,
        size_t y);
    /**
     * @brief Update the direction in run away mode. Ghost is going to the
     * opposite direction of the pacman.
     *
     * @param vecBoard
     * @param xPac
     * @param yPac
     * @param dirPac
     */
    void updateDirRunAwayMode(
        std::vector<std::vector<std::shared_ptr<square>>> vecBoard, size_t xPac,
        size_t yPac);
    /**
     * @brief Swap between chase and scatter mode.
     *
     */
    void swapMode();

  private:
    color _color;
    // board coordinates corresponding to coordinates of the board vector
    // pixel coordinates corresponding to the sprite position
    size_t _xBoard, _yBoard, _xPixel, _yPixel;
    dir _lastDir;
    mode _mode;
    // mode of the ghost
    bool _chaseMode, _scatterMode, _frightenedMode;
    // state of the ghost
    bool _isInHouse, _isReturnHouse, _isFear;
    // blue ghost is following the red ghost during 20s and the pink ghost
    // during 12s
    bool _blueRed, _bluePink;
    // timer for house waiting
    time_t houseWaitTimer1;
    // timer for switching mode
    time_t modeTimer1;
    // timer orange ghost
    time_t blueTimer1;
    // random number generator
    std::mt19937 _rng;
};

#endif