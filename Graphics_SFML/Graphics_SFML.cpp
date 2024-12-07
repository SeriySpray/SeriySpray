#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace sf;
Sprite playerSprite;
RenderWindow window;

int main()
{

    //------------------ INITIALIZE ------------------

    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(1920, 1080), "RPG Game", Style::Default, settings);

    //------------------ LOAD AREA (Arrow) ------------------
    RectangleShape arrow(Vector2f(20, 5));
    Vector2f arrowHidden(playerSprite.getPosition());
    Vector2f HiddenPos(200, 200);


    //------------------ LOAD AREA (Player) ------------------

    Texture playerTexture;
    Sprite playerSprite;

    if (playerTexture.loadFromFile("./sprites/player/Solider1.png"))
    {
        playerSprite.setTexture(playerTexture);
        playerSprite.setTextureRect(IntRect(0, 100, 100, 100));
        playerSprite.scale(Vector2f(4, 4));
        playerSprite.setPosition(Vector2f(800, 750));
    }
    //------------------ LOAD AREA (ENEMY) ------------------
    Texture enemyTexture;
    Sprite enemySprite;

    if (enemyTexture.loadFromFile("./sprites/player/Solider1.png"))
    {
        enemySprite.setTexture(enemyTexture);
        enemySprite.setTextureRect(IntRect(0, 0, 100, 100));
        enemySprite.scale(Vector2f(4, 4));
        enemySprite.setPosition(Vector2f(2000, 750));
    }


    //------------------ LOAD AREA (BACKGROUND) ------------------

    Texture BackTexture;
    Sprite BackSprite;
    BackTexture.loadFromFile("./sprites/background/back.png");
    BackSprite.setTexture(BackTexture);
    BackSprite.scale(Vector2f(7.5, 7.5));
    BackSprite.setPosition(Vector2f(0, 0));

    Texture FrontTexture;
    Sprite FrontSprite;
    FrontTexture.loadFromFile("./sprites/background/front.png");
    FrontSprite.setTexture(FrontTexture);
    FrontSprite.scale(Vector2f(7.5, 7.5));
    FrontSprite.setPosition(Vector2f(0, 0));

    Texture MiddleTexture;
    Sprite MiddleSprite;
    MiddleTexture.loadFromFile("./sprites/background/middle.png");
    MiddleSprite.setTexture(MiddleTexture);
    MiddleSprite.scale(Vector2f(7.5, 7.5));
    MiddleSprite.setPosition(Vector2f(0, 0));

        

    //------------------ VARIABLES ------------------

    int frame = 0;
    const int frameWidth = 100;    // Ширина кадру
    const int totalFrames = 8;     // Загальна кількість кадрів у анімації
    Clock frameClock;              // Таймер
    float frameDuration = 0.1f;


    //------------------ MAIN GAME LOOP ------------------

    window.setFramerateLimit(100);
    while (window.isOpen())
    {

        //------------------ UPDATE ------------------

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        Vector2f positionEnemy = (enemySprite.getPosition());
        Vector2f position = playerSprite.getPosition();
        Vector2f arrowPosition = arrow.getPosition();

        //------------------ ARROW -----------------

        Vector2f arrowHidden(playerSprite.getPosition());
        Vector2f arrowToPlayer(200, 200);
        Vector2f ReadyToShoot = (arrowHidden + arrowToPlayer);
        arrow.setPosition(ReadyToShoot);

        //------------------ MOVEMENT -----------------

        if (Keyboard::isKeyPressed(Keyboard::A))
        {


            playerSprite.setPosition(position + Vector2f(-5, 0));
            //Таймер

            if (frameClock.getElapsedTime().asSeconds() >= frameDuration)
            {

                frame = (frame + 1) % totalFrames; //Кадри
                playerSprite.setTextureRect(IntRect(frame * frameWidth, 800, 100, 100));
                frameClock.restart();

            }

        }

        if (Keyboard::isKeyPressed(Keyboard::D))
        {


            playerSprite.setPosition(position + Vector2f(5, 0));
            //Таймер
            if (frameClock.getElapsedTime().asSeconds() >= frameDuration)
            {
                frame = (frame + 1) % (totalFrames); //Кадри
                playerSprite.setTextureRect(IntRect(frame * frameWidth, 100, 100, 100));
                frameClock.restart();
            }
        }

        //------------------ ATTACK -----------------

        if (Keyboard::isKeyPressed(Keyboard::Period))
        {

            //Таймер
            if (frameClock.getElapsedTime().asSeconds() >= frameDuration)
            {

                frame = (frame + 1) % (totalFrames - 2); //Кадри
                playerSprite.setTextureRect(IntRect((frame)*frameWidth, 200, 100, 100));
                frameClock.restart();
            }


        }


        if (Keyboard::isKeyPressed(Keyboard::Comma))
        {

            //Таймер     
            if (frameClock.getElapsedTime().asSeconds() >= frameDuration)
            {
                frame += 6;
                frame = (frame - 1) % (totalFrames - 2); //Кадри
                playerSprite.setTextureRect(IntRect((frame)*frameWidth, 900, 100, 100));
                frameClock.restart();
            }

        }
        if (Keyboard::isKeyPressed(Keyboard::RShift))
        {
            arrow.setPosition(ReadyToShoot);
            arrow.setPosition(arrowPosition + Vector2f(15, 0)); //вистрєл
            //Таймер
            if (frameClock.getElapsedTime().asSeconds() >= frameDuration)
            {

                frame = (frame + 1) % totalFrames; //Кадри
                playerSprite.setTextureRect(IntRect((frame)*frameWidth, 400, 100, 100));
                frameClock.restart();
                if (frame == 0)
                    arrow.setPosition(ReadyToShoot);
            }

            if (positionEnemy + Vector2f(200, 200) == arrowPosition)
            {
                enemySprite.setPosition(2000, 750);
            }

        }

        if (Keyboard::isKeyPressed(Keyboard::Slash))
        {
            arrow.setPosition(ReadyToShoot);
            arrow.setPosition(arrowPosition + Vector2f(-15, 0));
            //Таймер
            if (frameClock.getElapsedTime().asSeconds() >= frameDuration)
            {
                frame += 8;
                frame = (frame - 1) % totalFrames; //Кадри
                playerSprite.setTextureRect(IntRect((frame)*frameWidth, 1100, 100, 100));
                frameClock.restart();
                if (frame == 0)
                    arrow.setPosition(ReadyToShoot);
            }
        }
        //------------------ ENEMY MOVEMENT -----------------


        enemySprite.setPosition(positionEnemy + Vector2f(-5, 0));
        if (frameClock.getElapsedTime().asSeconds() >= frameDuration)
        {
            frame += 8;
            frame = (frame - 1) % totalFrames; //Кадри
            enemySprite.setTextureRect(IntRect(frame * frameWidth, 800, 100, 100));
            frameClock.restart();

        }

        //------------------ ENEMY RESPAWN -----------------

        if (positionEnemy == Vector2f(-300, 750))
        {
            enemySprite.setPosition(2000, 750);
        }
        if (positionEnemy + Vector2f(200, 200) == arrowPosition)
        {
            enemySprite.setPosition(2000, 750);
        }


        //------------------ DRAW ------------------
        window.clear(Color::Black);
        window.draw(BackSprite);
        window.draw(MiddleSprite);
        window.draw(arrow);
        window.draw(enemySprite);
        window.draw(playerSprite);
        window.draw(FrontSprite);
        window.display();



    }


}