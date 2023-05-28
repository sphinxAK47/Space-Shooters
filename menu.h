
#include <SFML/Graphics.hpp>
#include<time.h>
#include<iostream>
//#include<string>
#include<fstream>
using namespace sf;
//using namespace std;
const char title2[] = "Menu Screen";

class Menu
{

public:

Sprite background; //Game background sprite
Texture bg_texture;
std::fstream scores;


Menu()
{
    bg_texture.loadFromFile("img/background.jpg");
    background.setTexture(bg_texture);
    background.setScale(2.15, 1.5);
    scores.open("scores.txt", std::ios::app);
}

bool display_menu()

{
    int help = 0;

    Font font;
    font.loadFromFile("font2.ttf");
    Text text;												//Text to be used in menu window
    text.setFont(font);
    text.setCharacterSize(30);
    text.setString("Space Shooters\nNew Game: Press Enter\nQuit: Press Escape\nHelp: Press H\nHigh Scores: Press S");
    text.setPosition(10.f, 10.f);
    
    Text text2;												//Text to be used in menu window
    text2.setFont(font);
    text2.setCharacterSize(30);
    text2.setString("Our galaxy is attacked by enemies.\n The enemy invaders beat our squad,\n they destroyed all of galactica.\n Space team is waiting for your order.\n Please command the ship to protect the\n galaxy and the surrounding asteroids.\n\nBack to Menu: Press G\nPause Game: Press J");
    text2.setPosition(10.f, 10.f);

    const int max = 10;
    std::string player_names[max];
    int record[max];
    std::string names2;
    int temp;
    int num = 0;

    std::ifstream scores("scores.txt");
    if (scores.is_open()) 
    {
        while (num < max && scores >> player_names[num] >> record[num])
            num++;
    
    scores.close();

    for (int i=0; i<num-1; i++) 
    {
        for (int j=i+1; j<num; j++) 
        {
            if (record[i] < record[j]) 
            {
                temp = record[i];
                record[i] = record[j];
                record[j] = temp;
                names2 = player_names[i];
                player_names[i] = player_names[j];
                player_names[j] = names2;
            }
        }
    }

    Text scores_text("High Scores", font, 40);
    scores_text.setPosition(300, 100);
    Texture gold_tex;
    Texture silver_tex;
    Texture bronze_tex;

    if (!gold_tex.loadFromFile("img/gold.png")) 
    {
        std::cerr<<"Error loading texture"<<std::endl;
    }

    if (!silver_tex.loadFromFile("img/silver2.png"))
    {
        std::cerr<<"Error loading texture."<<std::endl;
    }

    if (!bronze_tex.loadFromFile("img/bronze.png")) 
    {
        std::cerr<<"Error loading texture."<<std::endl;
    }

    Sprite gold(gold_tex);
    Sprite silver(silver_tex);
    Sprite bronze(bronze_tex);
    gold.setTexture(gold_tex);
    silver.setTexture(silver_tex);
    bronze.setTexture(bronze_tex);

    int y = 200;

    srand(time(0));

    RenderWindow window(VideoMode(780, 780), title2);								
    	while (window.isOpen())
        {
           	Event e;
           	while (window.pollEvent(e))
           	{ 
           		if (e.type == Event::Closed)                  
               		window.close();  
               				
               	else if (e.key.code == Keyboard::Escape)
               		window.close(); 
               		
               	else if (e.key.code == Keyboard::H)
               	{
                    help = 1;
               	}

                else if (e.key.code == Keyboard::G)
                    help = 0;

                else if (e.key.code == Keyboard::S)
                    help = 2;

          		else if (e.key.code == Keyboard::Enter)
          		{
                    return 1;
    				window.close();
                }
            }
            window.clear();
            window.draw(background);

            if (help == 0)  // Draw the menu only if help is not being displayed
            {
                window.draw(text);
            }
            else if (help == 1)
            {
                window.draw(text2);
            }

            else if (help == 2)
            {
                int y2 = 200;
                for (int i = 0; i < num; i++) 
                {
                    Text scores_text2(player_names[i] + "   " + std::to_string(record[i]), font, 30);
                    scores_text2.setPosition(250, y2);
                    y2 += 50;
                    window.draw(scores_text2);

                    if (i == 0)
                    {
                        gold.setPosition(200, 200);
                        gold.setScale(0.05,0.05);
                        window.draw(gold);
                    } 

                    else if (i == 1)
                    {
                        silver.setPosition(200, 250);
                        silver.setScale(0.05,0.05);
                        window.draw(silver);
                    } 

                    else if (i == 2) 
                    {
                        bronze.setPosition(200, 300);
                        bronze.setScale(0.03,0.03);
                        window.draw(bronze);
                    }

                  //  y += 10;
                }
            }

            window.display();
        }
    scores.close();
    }
    return 0;	
}

void gameover(int score)
{
    Font font;
    font.loadFromFile("font2.ttf");
    Text text;											
    text.setFont(font);
    text.setCharacterSize(50);
    text.setString("Game Over");
    text.setPosition(10.f, 10.f);

    Text text2;
    text2.setFont(font);
    text2.setCharacterSize(50);
    text2.setFillColor(Color::White);
    text2.setPosition(10.f, 70.f); 
    text2.setString("Score: " + std::to_string(score));  

    Text text3;
    text3.setFont(font);
    text3.setCharacterSize(50);
    text3.setFillColor(Color::White);
    text3.setPosition(10.f, 120.f); 
    text3.setString("Restart Game: Press 1");  

    srand(time(0));

    Text nameText;
    nameText.setFont(font);
    nameText.setCharacterSize(50);
    nameText.setFillColor(Color::White);
    nameText.setPosition(10.f, 170.f);

    std::string player_name;
    bool input_finished = false;
    RenderWindow window2(VideoMode(780, 780), "Game Over");
    while (window2.isOpen())
    {
        Event e;
        while (window2.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window2.close();
            else if (e.key.code == Keyboard::Escape)
                window2.close();
            else if (e.key.code == Keyboard::Num1)
            {
                window2.close();
                display_menu();
            }
            else if (e.type == Event::TextEntered && !input_finished)
            {
                if (e.text.unicode >= 32 && e.text.unicode <= 126) 
                {
                    player_name += static_cast<char>(e.text.unicode);
                    nameText.setString("Player Name: " + player_name);
                }
                else if (e.text.unicode == '\b' && player_name.size() > 0) 
                {
                    player_name.pop_back();
                    nameText.setString("Player Name: " + player_name);
                }
                else if (e.text.unicode == '\r' || e.text.unicode == '\n') 
                {
                    input_finished = true;
                    std::ofstream scores("scores.txt", std::ios::app);
                    if (scores.is_open())
                    {
                        scores << player_name << " " << score << std::endl;
                        scores.close();
                    }
                }
            }
        }
        window2.clear();
        window2.draw(background);
        window2.draw(text);
        window2.draw(text2);
        window2.draw(text3);
        window2.draw(nameText);
        window2.display();

        if (input_finished)
            break; 
    } 
}

~Menu(){}
};
