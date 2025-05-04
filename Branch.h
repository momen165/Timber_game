#ifndef BRANCH_H
#define BRANCH_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

class Branch {
public:
    // Enum class representing the side of the branch
    enum class Side { Left, Right, NONE };

    // Constructor to initialize the branch
    Branch();

    // Updates the branches based on the given seed
    void updateBranches(int seed);

    // Returns the sprite of the branch
    sf::Sprite getSprite();

    // Returns the side of the branch at the given index
    Side getSide(int index);

    // Sets the side of the branch at the given index
    void setSide(int index, Side side);

private:
    // The sprite representing the branch
    sf::Sprite sprite;

    // The texture of the branch sprite
    sf::Texture texture;

    // The number of branches
    static const int NUM_BRANCHES = 6;

    // The positions of the branches
    Side branchPosition[NUM_BRANCHES];
};

#endif // BRANCH_H
