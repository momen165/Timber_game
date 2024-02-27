#include <sstream>
#include <SFML/Graphics.hpp>
using namespace sf;

//update branches function
void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

//where is the player/branch?
//left or right
enum class side{Left,Right,NONE};
side branchPosition[NUM_BRANCHES];
// This is where our game starts from
int main()
{

    VideoMode vm(1920,1080);
    RenderWindow window(vm,"timber", Style::Fullscreen);

    // Create a texture to hold a graphic on the GPU
    Texture textureBackground;

    //Load a graphic into the texture
    textureBackground.loadFromFile("graphics/background.png");

    // Create a sprite
    Sprite spriteBackground;

    // Attach the texture to the sprite
    spriteBackground.setTexture(textureBackground);

    // Set the spriteBackground to cover the screen
    spriteBackground.setPosition(0,0);


    //make a tree sprite
    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");

    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);


    //prepare the bee
    Texture textureBee;
    textureBee.loadFromFile("graphics/insect.png");

    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);


    //is the bee currently moving
    bool beeActive = false;


    // bee speed
    float beeSpeed= 0.0f;


    // make 3 cloud sprites from 1 texture
    Texture textureCloud;

    //loading the cloud texture
    textureCloud.loadFromFile("graphics/cloud.png");

    // 3 New sprites with the same texture
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;

    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);

    spriteCloud1.setPosition(0,0);
    spriteCloud2.setPosition(0,250);
    spriteCloud3.setPosition(0,500);

    // Are the clouds currently on screen?
    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;

    // How fast is each cloud?
    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;
    
    // Variables to control time itself
    Clock clock;

    //time bar
    RectangleShape timeBar;
    float timeBarStartWidth=400;
    float timeBarHeight=80;
    timeBar.setSize(Vector2f(timeBarStartWidth,timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920/2)-timeBarStartWidth/2,980);

    Time getTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth/ timeRemaining;
    //Track whether the game is running
    bool paused = true;

    //draw some text
    int score = 0;

    Text messageText;
    Text scoreText;

    //we need to choose a font
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    // set the font to out message
    messageText.setFont(font);
    scoreText.setFont(font);


    //Assign the message
    messageText.setString("Press enter to start");
    scoreText.setString("Score = 0");

    //change the messages size
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);


    //Change the color of the messages
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    //position the text
    FloatRect textRect= messageText.getLocalBounds();

    messageText.setOrigin(textRect.left+textRect.width/2.0f,textRect.top+textRect.height/2.0f);

    messageText.setPosition(1920/2.0f,1080/2.0f);
    scoreText.setPosition(20,20);

    //prepare 6 branches
    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");

    //set the texture for each branch sprite
    for(int i = 0;i < NUM_BRANCHES;i++)
    {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000,-2000);
        branches[i].setOrigin(220,20);
    }

   // Prepare the player
   Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580,720);

    //The player starts on the left
    side playerSide= side::Left;

    //prepare the grave stone
    Texture textureRip;
    textureRip.loadFromFile("graphics/rip.png");
    Sprite spriteRip;
    spriteRip.setTexture(textureRip);
    spriteRip.setPosition(600,860);

    //prepare the axe
    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700,830);

    //line the axe up with the tree
    const float AXE_Position_LEFT=700;
    const float AXE_Position_RIGHT=1075;

    //prepare the flying log
    Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810,720);

    //log variables
    bool logActive= false;
    float logSpeedX=1000;
    float logSpeedY=-1500;

    //control the player input
    bool acceptInput = false;

    while (window.isOpen()) {
        // Handle the players input
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased && !paused) {
// Listen for key presses again
                acceptInput = true;
// hide the axe
                spriteAxe.setPosition(2000,
                                      spriteAxe.getPosition().y);
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = false;

            //Reset the time and the score
            score = 0;
            timeRemaining = 6;

            // Make all the branches disappear -
            // starting in the second position
            for (int i = 1; i < NUM_BRANCHES; i++) {
                branchPosition[i] = side::NONE;
            }
            // Make sure the gravestone is hidden
            spriteRip.setPosition(675, 2000);
            // Move the player into position
            spritePlayer.setPosition(580, 720);
            acceptInput = true;
        }

        // Wrap the player controls to
        // Make sure we are accepting input
        if (acceptInput) {
            // First handle pressing the right cursor key
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                // Make sure the player is on the right
                playerSide = side::Right;
                score++;
                // Add to the amount of time remaining
                timeRemaining += (2 / score) + .15;
                spriteAxe.setPosition(AXE_Position_RIGHT,
                                      spriteAxe.getPosition().y);
                spritePlayer.setPosition(1200, 720);
                // Update the branches
                updateBranches(score);
                // Set the log flying to the left
                spriteLog.setPosition(810, 720);
                logSpeedX = -5000;
                logActive = true;
                acceptInput = false;
            }
            // Handle the left cursor key
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                // Make sure the player is on the left
                playerSide = side::Left;
                score++;
                // Add to the amount of time remaining
                timeRemaining += (2 / score) + .15;
                spriteAxe.setPosition(AXE_Position_LEFT,
                                      spriteAxe.getPosition().y);
                spritePlayer.setPosition(580, 720);
                // update the branches
                updateBranches(score);
                // set the log flying
                spriteLog.setPosition(810, 720);
                logSpeedX = 5000;
                logActive = true;
                acceptInput = false;
            }
        }


        //Update the scene

        if (!paused) {
            // Measure time
            sf::Time dt = clock.restart();

            //subtract from the amount of time remaining
            timeRemaining -= dt.asSeconds();
            //resize up the time bar
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.0f) {
                //pause the game
                paused = true;
                //change the message shown to player
                messageText.setString("out of time Bitch!!");

                //reposition the text based on its new size
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                                      textRect.top +
                                      textRect.height / 2.0f);
                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
            }

            //setup the bee
            if (!beeActive) {
                //how fast is the bee
                beeSpeed = (rand() % 200) + 200;

                //how high is the bee
                srand((int) time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);
                beeActive = true;
            } else
                //move the bee
            {
                spriteBee.setPosition(
                        spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
                        spriteBee.getPosition().y);
                // Has the bee reached the left-hand edge of the screen?
                if (spriteBee.getPosition().x < -100) {
                    beeActive = false;
                }
            }


            // Manage the clouds
            // Cloud 1
            if (!cloud1Active) {
                // How fast is the cloud
                srand((int) time(0) * 10);
                cloud1Speed = (rand() % 200);
                // How high is the cloud
                srand((int) time(0) * 10);
                float height = (rand() % 150);
                spriteCloud1.setPosition(-200, height);
                cloud1Active = true;
            } else {
                spriteCloud1.setPosition(
                        spriteCloud1.getPosition().x +
                        (cloud1Speed * dt.asSeconds()),
                        spriteCloud1.getPosition().y);
                // Has the cloud reached the right hand edge of the screen?
                if (spriteCloud1.getPosition().x > 1920) {
                    // Set it up ready to be a whole new cloud next frame
                    cloud1Active = false;
                }
            }

            // Cloud 2
            if (!cloud2Active) {
                // How fast is the cloud
                srand((int) time(0) * 20);
                cloud2Speed = (rand() % 200);
                // How high is the cloud
                srand((int) time(0) * 20);
                float height = (rand() % 300) - 150;
                spriteCloud2.setPosition(-200, height);
                cloud2Active = true;
            } else {
                spriteCloud2.setPosition(
                        spriteCloud2.getPosition().x +
                        (cloud2Speed * dt.asSeconds()),
                        spriteCloud2.getPosition().y);
                // Has the cloud reached the right hand edge of the screen?
                if (spriteCloud2.getPosition().x > 1920) {
                    // Set it up ready to be a whole new cloud next frame
                    cloud2Active = false;
                }
            }
            if (!cloud3Active) {
                // How fast is the cloud
                srand((int) time(0) * 30);
                cloud3Speed = (rand() % 200);


                // How high is the cloud
                srand((int) time(0) * 30);
                float height = (rand() % 450) - 150;
                spriteCloud3.setPosition(-200, height);
                cloud3Active = true;
            } else {
                spriteCloud3.setPosition(
                        spriteCloud3.getPosition().x +
                        (cloud3Speed * dt.asSeconds()),
                        spriteCloud3.getPosition().y);
                // Has the cloud reached the right hand edge of the screen?
                if (spriteCloud3.getPosition().x > 1920) {
                    // Set it up ready to be a whole new cloud next frame
                    cloud3Active = false;
                }
            }
            //update the score text
            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());

        }

        //update the branch sprite
        // update the branch sprites
        for (int i = 0; i < NUM_BRANCHES; i++) {
            float height = i * 150;

            if (branchPosition[i] == side::Left) {
// Move the sprite to the left side
                branches[i].setPosition(610, height);
// Flip the sprite round the other way
                branches[i].setRotation(180);
            } else if (branchPosition[i] == side::Right) {
// Move the sprite to the right side
                branches[i].setPosition(1330, height);
// Set the sprite rotation to normal
                branches[i].setRotation(0);
            } else {
// Hide the branch
                branches[i].setPosition(3000, height);
            }
        }

        // Handle a flying log
        if (logActive) {

            spriteLog.setPosition(
                    spriteLog.getPosition().x +
                    (logSpeedX * dt.asSeconds()),
                    spriteLog.getPosition().y +
                    (logSpeedY * dt.asSeconds()));
            // Has the log reached the right hand edge?
            if (spriteLog.getPosition().x < -100 ||
                spriteLog.getPosition().x > 2000) {
                // Set it up ready to be a whole new log next frame
                logActive = false;
                spriteLog.setPosition(810, 720);
            }
        }

        //draw the scene






        //clear every thing from the last frame
        window.clear();


        //draw our game scene here
        window.draw(spriteBackground);

        // Draw the clouds
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        //draw the branches
        for(int i = 0; i<NUM_BRANCHES;i++){
            window.draw(branches[i]);
        }


        // Draw the tree
        window.draw(spriteTree);

        //draw the player
        window.draw(spritePlayer);

        //draw the axe
        window.draw(spriteAxe);

        //draw the log
        window.draw(spriteLog);

        //draw the grave stone
        window.draw(spriteRip);



        // Draw the bee
        window.draw(spriteBee);

        //draw the score
        window.draw(scoreText);

        //draw the time bar
        window.draw(timeBar);

        if(paused){
            //draw message
            window.draw(messageText);
        }


        //show every thing we just draw
        window.display();
        


    }

    return 0;


}

void updateBranches(int seed){
    for(int j = NUM_BRANCHES-1;j>0;j--)
    {
        branchPosition[j] = branchPosition[j-1];
    }
    //spawn a new branch at position 0
    //left , right or none
    srand((int)time(0)+seed);
    int r = (rand() % 5);
    switch (r) {
        case 0:
            branchPosition[0] = side::Left;
            break;
        case 1:
            branchPosition[0]= side::Right;
            break;
        default:
            branchPosition[0] = side::NONE;
            break;
    }
}