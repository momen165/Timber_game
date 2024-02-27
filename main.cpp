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

    while (window.isOpen()) {
        // Handle the players input
        
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            paused = false;

            //Reset the time and the score
            score = 0;
            timeRemaining = 6;
        }

        //Update the scene

        if(!paused) {
            // Measure time
            Time dt = clock.restart();

            //subtract from the amount of time remaining
            timeRemaining -= dt.asSeconds();
            //resize up the time bar
            timeBar.setSize(Vector2f(timeBarWidthPerSecond*timeRemaining,timeBarHeight));

            if(timeRemaining<=0.0f){
                //pause the game
                paused = true;
            //change the message shown to player
            messageText.setString("out of time Bitch!!");

            //reposition the text based on its new size
            FloatRect textRect = messageText.getLocalBounds();
            messageText.setOrigin(textRect.left+textRect.width/2.0f,
            textRect.top+
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
            ss<<"Score = " <<score;
            scoreText.setString(ss.str());

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
        // Draw the tree
        window.draw(spriteTree);
        // Draw the insect
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