#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Tree.h"
#include "Bee.h"
#include "Branch.h"

/**
 * @class Game
 * @brief Manages the game state and entities, and handles the game loop.
 */
class Game {
public:
    /**
     * @brief Constructs the Game object and initializes the game state and entities.
     */
    Game();

    /**
     * @brief Starts the game loop.
     */
    void run();

private:
    /**
     * @brief Processes user input events.
     */
    void processEvents();

    /**
     * @brief Updates the game state based on the elapsed time.
     * @param dt The elapsed time since the last update.
     */
    void update(sf::Time dt);

    /**
     * @brief Renders the game entities and UI elements.
     */
    void render();

    /**
     * @brief Handles player input for movement.
     * @param key The key that was pressed or released.
     * @param isPressed Indicates whether the key was pressed or released.
     */
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    // The game window
    sf::RenderWindow window;

    // The player entity
    Player player;

    // The tree entity
    Tree tree;

    // The bee entity
    Bee bee;

    // The branch entities
    Branch branches[6];

    // The background texture and sprite
    sf::Texture textureBackground;
    sf::Sprite spriteBackground;

    // The cloud texture and sprites
    sf::Texture textureCloud;
    sf::Sprite spriteCloud1;
    sf::Sprite spriteCloud2;
    sf::Sprite spriteCloud3;

    // The time bar UI element
    sf::RectangleShape timeBar;
    sf::Time getTimeTotal;
    float timeRemaining;
    float timeBarWidthPerSecond;

    // The message and score text UI elements
    sf::Text messageText;
    sf::Text scoreText;
    sf::Font font;

    // The game score
    int score;

    // Indicates whether the game is paused
    bool paused;

    // Indicates whether player input is accepted
    bool acceptInput;

    // Sound buffers and sounds for game events
    sf::SoundBuffer chopBuffer;
    sf::Sound chop;
    sf::SoundBuffer deathBuffer;
    sf::Sound death;
    sf::SoundBuffer ootBuffer;
    sf::Sound outOfTime;
};

#endif // GAME_H
