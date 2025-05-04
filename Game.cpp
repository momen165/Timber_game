#include "Game.h"

Game::Game() : window(sf::VideoMode(1920, 1080), "Timber Game", sf::Style::Fullscreen), 
               timeBarStartWidth(400), timeBarHeight(80), timeRemaining(6.0f), 
               timeBarWidthPerSecond(timeBarStartWidth / timeRemaining), score(0), paused(true), acceptInput(false) {
    // Load textures
    textureBackground.loadFromFile("graphics/background.png");
    textureCloud.loadFromFile("graphics/cloud.png");

    // Set up sprites
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);

    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 250);
    spriteCloud3.setPosition(0, 500);

    // Set up time bar
    timeBar.setSize(sf::Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(sf::Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

    // Load font and set up text
    font.loadFromFile("fonts/KOMIKAP_.ttf");
    messageText.setFont(font);
    scoreText.setFont(font);

    messageText.setString("Press Enter to start");
    scoreText.setString("Score = 0");

    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);

    messageText.setFillColor(sf::Color::White);
    scoreText.setFillColor(sf::Color::White);

    sf::FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
    scoreText.setPosition(20, 20);

    // Load sounds
    chopBuffer.loadFromFile("sound/chop.wav");
    chop.setBuffer(chopBuffer);

    deathBuffer.loadFromFile("sound/death.wav");
    death.setBuffer(deathBuffer);

    ootBuffer.loadFromFile("sound/out_of_time.wav");
    outOfTime.setBuffer(ootBuffer);
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        processEvents();
        if (!paused) {
            sf::Time dt = clock.restart();
            update(dt);
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::KeyReleased && !paused) {
            acceptInput = true;
        }
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
        paused = false;
        score = 0;
        timeRemaining = 6.0f;
        for (int i = 1; i < 6; i++) {
            branches[i].setSide(i, Branch::Side::NONE);
        }
        acceptInput = true;
    }

    if (acceptInput) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.moveRight();
            score++;
            timeRemaining += (2 / score) + .15;
            acceptInput = false;
            chop.play();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.moveLeft();
            score++;
            timeRemaining += (2 / score) + .15;
            acceptInput = false;
            chop.play();
        }
    }
}

void Game::update(sf::Time dt) {
    timeRemaining -= dt.asSeconds();
    timeBar.setSize(sf::Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

    if (timeRemaining <= 0.0f) {
        paused = true;
        messageText.setString("Out of time!!");
        sf::FloatRect textRect = messageText.getLocalBounds();
        messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
        outOfTime.play();
    }

    if (!bee.isActive()) {
        bee.setSpeed((rand() % 200) + 200);
        float height = (rand() % 500) + 500;
        bee.setPosition(2000, height);
        bee.setActive(true);
    } else {
        bee.move(dt.asSeconds());
        if (bee.getPosition().x < -100) {
            bee.setActive(false);
        }
    }

    for (int i = 0; i < 3; i++) {
        if (!clouds[i].isActive()) {
            clouds[i].setSpeed((rand() % 200));
            float height = (rand() % 150);
            clouds[i].setPosition(-200, height);
            clouds[i].setActive(true);
        } else {
            clouds[i].move(dt.asSeconds());
            if (clouds[i].getPosition().x > 1920) {
                clouds[i].setActive(false);
            }
        }
    }

    std::stringstream ss;
    ss << "Score = " << score;
    scoreText.setString(ss.str());

    for (int i = 0; i < 6; i++) {
        float height = i * 150;
        if (branches[i].getSide(i) == Branch::Side::Left) {
            branches[i].getSprite().setPosition(610, height);
            branches[i].getSprite().setRotation(180);
        } else if (branches[i].getSide(i) == Branch::Side::Right) {
            branches[i].getSprite().setPosition(1330, height);
            branches[i].getSprite().setRotation(0);
        } else {
            branches[i].getSprite().setPosition(3000, height);
        }
    }

    if (log.isActive()) {
        log.move(dt.asSeconds());
        if (log.getPosition().x < -100 || log.getPosition().x > 2000) {
            log.setActive(false);
            log.setPosition(810, 720);
        }
    }

    if (branches[5].getSide(5) == player.getSide()) {
        paused = true;
        acceptInput = false;
        player.setPosition(2000, 660);
        messageText.setString("SQUISHED!!");
        sf::FloatRect textRect = messageText.getLocalBounds();
        messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
        death.play();
    }
}

void Game::render() {
    window.clear();
    window.draw(spriteBackground);
    window.draw(spriteCloud1);
    window.draw(spriteCloud2);
    window.draw(spriteCloud3);
    for (int i = 0; i < 6; i++) {
        window.draw(branches[i].getSprite());
    }
    window.draw(tree.getSprite());
    window.draw(player.getSprite());
    window.draw(bee.getSprite());
    window.draw(scoreText);
    window.draw(timeBar);
    if (paused) {
        window.draw(messageText);
    }
    window.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Right) {
        player.moveRight();
    } else if (key == sf::Keyboard::Left) {
        player.moveLeft();
    }
}
