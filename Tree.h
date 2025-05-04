#ifndef TREE_H
#define TREE_H

#include <SFML/Graphics.hpp>

class Tree {
public:
    Tree();

    // Sets the position of the tree
    void setPosition(float x, float y);

    // Sets the scale of the tree
    void setScale(float factorX, float factorY);

    // Returns the current position of the tree
    sf::Vector2f getPosition();

    // Returns the sprite of the tree
    sf::Sprite getSprite();

private:
    // The sprite representing the tree
    sf::Sprite sprite;

    // The texture of the tree sprite
    sf::Texture texture;
};

#endif // TREE_H
