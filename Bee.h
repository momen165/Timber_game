#ifndef BEE_H
#define BEE_H

#include <SFML/Graphics.hpp>

class Bee {
public:
    Bee();

    // Sets the position of the bee
    void setPosition(float x, float y);

    // Sets the speed of the bee
    void setSpeed(float speed);

    // Moves the bee based on the elapsed time
    void move(float dt);

    // Returns the current position of the bee
    sf::Vector2f getPosition();

    // Returns the sprite of the bee
    sf::Sprite getSprite();

private:
    // The sprite representing the bee
    sf::Sprite sprite;

    // The texture of the bee sprite
    sf::Texture texture;

    // The speed of the bee
    float speed;

    // Indicates whether the bee is active
    bool isActive;
};

#endif // BEE_H
