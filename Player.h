#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player();

    // Moves the player to the left
    void moveLeft();

    // Moves the player to the right
    void moveRight();

    // Returns the current position of the player
    sf::Vector2f getPosition();

    // Returns the sprite of the player
    sf::Sprite getSprite();

private:
    // The sprite representing the player
    sf::Sprite sprite;

    // The texture of the player sprite
    sf::Texture texture;

    // Indicates whether the player is on the left side
    bool isLeft;
};

#endif // PLAYER_H
