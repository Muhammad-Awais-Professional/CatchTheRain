#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include <sstream>
#include <fstream>

using namespace sf;
using namespace std;

class Game
{

    // widnow
    RenderWindow *window;
    VideoMode videomode;
    Event ev;

    //Background
    Texture background;
    Sprite background_sprite;

    // Start screen
    Text start;
    bool toggle;
    bool update_screen;

    // Mouse Position
    Vector2i mouseposwindow;
    Vector2f mouseposview;
    bool mouseHeld;

    // Resources
    Font fonts;

    // Text
    Text uiText;

    // Game stuff

    fstream file;

    string highestscore;

    bool endgame;

    int health;

    unsigned int points;

    float enemyspawntimer;

    float enemyspawntimermax;

    int maxenemies;

    // Game Objects
    vector<Sprite> enemies;
    Sprite enemy;
    Texture enemy_tex;

    void initText()
    {

        uiText.setFont(fonts);
        uiText.setCharacterSize(24);
        uiText.setFillColor(Color::White);
        uiText.setString("Nothing in here!");

        // Start Screen
        start.setString("Start");
        start.setFont(fonts);
        start.setFillColor(Color::White);
        start.setPosition(350, 275);
        start.setOutlineThickness(50);
        start.setOutlineColor(Color::Cyan);
    }

    void initenemy()
    {

        //this->enemy.setPosition(10.f, 10.f);

        //this->enemy.setSize(Vector2f(100.f, 100.f));

        this->enemy.setScale(Vector2f(0.5f, 0.5f));

        //this->enemy.setFillColor(Color::Red);

        //this->enemy.setOutlineColor(Color::Black);

        //this->enemy.setOutlineThickness(2.f);
    }

    void initfonts()
    {

        fonts.loadFromFile("Fonts/ZandaLover.otf");
    }

    void initTextures(){

        //background
        background.loadFromFile("sky.jpeg");

        background_sprite.setTexture(background);

        //background_sprite.setScale(2.285715,0.917);

        //enemy
        enemy_tex.loadFromFile("drop.png");

        enemy.setTexture(enemy_tex);

    }

    void initvariables()
    {

        // Start Screen
        toggle = true;

        update_screen = false;
        // Start Screen

        file.open("highest_score.txt", ios::in);

        if (!file.is_open())
        {
            cout << "Error opening file! " << endl;
        }

        file >> highestscore;
        // cout << "highest score " << highestscore << endl;
        file.close();
        health = 20;

        this->window = NULL;

        points = 0;

        enemyspawntimermax = 20.f;

        enemyspawntimer = enemyspawntimermax;

        maxenemies = 5;

        mouseHeld = false;

        endgame = false;
    }

    void initwindow()
    {

        this->videomode.height = 600;

        this->videomode.width = 800;

        // window->setFramerateLimit(60);

        window = new RenderWindow(this->videomode, "Catch The Rain", Style::Titlebar | Style::Close);
    }

public:
    void settoggle(bool b)
    {
        toggle = b;
    }

    bool gettoggle()
    {
        return toggle;
    }

    bool getwindowisOpen()
    {

        return window->isOpen();
    }

    bool getEndgame()
    {

        return endgame;
    }

    Game()
    {

        this->initvariables();

        this->initwindow();

        this->initfonts();

        this->initText();

        this->initenemy();

        this->initTextures(); 
    }

    void pollEvents()
    {

        while (window->pollEvent(ev))
        {

            switch (ev.type)
            {
            case Event::Closed:
                window->close();
                break;

            case Event::KeyPressed:

                if (ev.key.code == Keyboard::Escape)
                    window->close();

                break;

            default:
                break;
            }
        }
    }

    void update()
    {

        // Relative to Screen
        // cout << " Mouse Pos: " << Mouse::getPosition().x<<" " << Mouse::getPosition().y << endl;

        // Relative to Window
        // cout << " Mouse Pos: " << Mouse::getPosition(*this->window).x<<" " << Mouse::getPosition(*this->window).y << endl;

        this->pollEvents();

        this->updateMousePosition();

        if (update_screen)
        {
            if (!endgame)
            {

                updateText();

                this->updateenemies();
            }
            else
            {
                updateText();
            }

            if (health <= 0)
                endgame = true;
        }
    }

    void render()
    {

        //window->clear(Color(165, 190, 205));

        window->draw(background_sprite);

        // Draw

        if (!StartButtonPressed() && toggle)
        {

            renderStartScreen(*window);
        }
        else
        {

            update_screen = true;

            this->renderenemies(*window);

            if (endgame){

                window->clear(Color(165, 190, 205));
                window->draw(background_sprite);
            }
            
            this->renderText(*window);
        }

        window->display();
    }

    void updateMousePosition()
    {

        mouseposwindow = Mouse::getPosition(*this->window);
        //cout<<"Mouse pos window "<<mouseposwindow.x<<" ,  "<< mouseposwindow.y<<endl;
        mouseposview = window->mapPixelToCoords(mouseposwindow);
        //cout<<"Mouse pos view "<<mouseposview<<endl;
    }

    // Enemies
    void spawnenemies()
    {

        bool push = true;

        enemy.setPosition(static_cast<float>(rand() % static_cast<int>(window->getSize().x - enemy.getGlobalBounds().width)), 0.f);

        int type = rand() % 5;

        switch (type)
        {

        case 0:
            this->enemy.setScale(Vector2f(0.1f, 0.1f));
            //this->enemy.setFillColor(Color::Magenta);
            break;
        case 1:
            this->enemy.setScale(Vector2f(0.2f, 0.2f));
            //this->enemy.setFillColor(Color::Red);
            break;
        case 2:
            this->enemy.setScale(Vector2f(0.3f, 0.3f));
            //this->enemy.setFillColor(Color::Yellow);
            break;
        case 3:
            this->enemy.setScale(Vector2f(0.4f, 0.4f));
            //this->enemy.setFillColor(Color::Cyan);
            break;
        case 4:
            this->enemy.setScale(Vector2f(0.5f, 0.5f));
            //this->enemy.setFillColor(Color::Green);
            break;
        default:
            this->enemy.setScale(Vector2f(1.f, 1.f));
            //this->enemy.setFillColor(Color::Yellow);
            break;
        }

        // this->enemy.setFillColor(Color::Red);

        for (int i = 0; i < enemies.size(); i++)
        {

            if (enemies[i].getGlobalBounds().intersects(enemy.getGlobalBounds()))
            {
                push = false;
                break;
            }
        }

        if (push)
            enemies.push_back(enemy);
    }

    void updateenemies()
    {

        if (enemies.size() < maxenemies)
        {

            if (enemyspawntimer >= enemyspawntimermax)
            {

                spawnenemies();

                enemyspawntimer = 0.f;
            }

            else
                enemyspawntimer += 1.f;
        }

        for (int i = 0; i < enemies.size(); i++)
        {

            enemies[i].move(0.f, 1.f);

            // Helpful. Might help with deleting stuff that reach the end of the screen bottem.
            if (enemies[i].getPosition().y > window->getSize().y || enemies[i].getPosition().x > window->getSize().x)
            {
                enemies.erase(enemies.begin() + i);
                health -= 1;
            }
        }

        // Important example!! Deletes enemies with a mouse click. Might help with the start screen of project.
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (mouseHeld == false)
            {
                mouseHeld = true;
                bool deleted = false;

                for (int i = 0; i < enemies.size() && deleted == false; i++)
                {

                    if (enemies[i].getGlobalBounds().contains(mouseposview))
                    {
                        if (enemies[i].getScale().x == 0.1f)
                        {
                            points += 20;
                        }
                        else if (enemies[i].getScale().x == 0.2f)
                        {
                            points += 15;
                        }
                        else if (enemies[i].getScale().x == 0.3f)
                        {
                            points += 10;
                        }
                        else if (enemies[i].getScale().x == 0.4f)
                        {
                            points += 5;
                        }
                        else if (enemies[i].getScale().x == 0.5f)
                        {
                            points += 1;
                        }

                        // points += 1;
                        deleted = true;
                        enemies.erase(enemies.begin() + i);
                    }
                }
            }
        }
        else
            mouseHeld = false;
    }

    void renderenemies(RenderTarget &target)
    {

        for (auto &e : enemies)
        {
            target.draw(e);
        }
    }

    // Enemeis

    // Text

    void updateText()
    {

        stringstream ss;

        ss << " Points: " << points << "\n Health: " << health << "\n";

        string highscore = "0";

        highscore = to_string(points);

        if (endgame == true && stoi(highscore) > stoi(highestscore))
        {

            file.open("highest_score.txt", ios::out);

            highestscore = highscore;
            // string check;
            // cout<<"highestscore: "<<highestscore<<endl;
            // cout << "Writing to file " << highestscore << endl;

            file.write(highscore.c_str(), highscore.length());

            // cout << "Closing file" << endl;
            file.close();

            // getline(file,check);
            // cout<<"check : "<<check<<endl;
        }

        if (endgame == true)
        {

            ss << "Highest Score: " << highestscore << endl;

            ss << " Game Over!" << endl;

            uiText.setFillColor(Color::Red);

            uiText.setOutlineColor(Color::Cyan);

            uiText.setOutlineThickness(50);

            uiText.setPosition(325, 250);
        }
        uiText.setString(ss.str());
    }

    void renderText(RenderTarget &target)
    {

        target.draw(uiText);
    }

    void renderStartScreen(RenderTarget &target)
    {

        target.draw(start);
    }

    bool StartButtonPressed()
    {

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (start.getGlobalBounds().contains(mouseposview))
            {

                toggle = false;

                return true;
            }
        }

        return false;
    }

    ~Game()
    {

        delete this->window;
    }
};