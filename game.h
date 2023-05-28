
#include <SFML/Graphics.hpp>
#include <time.h>
#include "player.h"
#include "menu.h"
#include "Enemy.h"
#include "Alpha.h"
#include "Beta.h"
#include "Gamma.h"
#include "Monster.h"
#include "Beam.h"
#include "Dragon.h"
#include "Fire.h"
#include "Add_on.h"
#include "Danger.h"
#include "Live.h"
#include "Add_Fire.h"
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;
using namespace std;
#include<iostream>

class Game
{
public:
Sprite background; //Game background sprite
Texture bg_texture;
Player* p; //player 
Bullet *b;
Menu *m;
static const int max_a = 3;
int count_a = 0, count_b = 0, count_c = 0, total = 0, count_d = 0;
int count_health = 0;
int num_a = rand()%max_a;
Enemy *e;
Enemy *a[max_a];
Enemy *beta[max_a];
Enemy *g[max_a];
Bomb *bomb[max_a*3];
Enemy *monster;
Beam *beam;
Enemy *dragon;
Fire *fire[max_a];
bool fireflag[3];
Add_on* add[4];
Add_on* danger;
Add_on* live;
Add_on* add_fire;
int total_score;




Game()
{
b = new Bullet("img/PNG/Lasers/laserGreen09.png");
for (int i=0; i<4; i++)
{
    add[i] = new Add_on("img/PNG/Power-ups/bolt_bronze.png");
    add[i]->sprite.setPosition(rand() % 600 + 100, 0);
}

danger = new Danger("img/PNG/Power-ups/bolt_bronze.png");
live = new Live("img/PNG/Power-ups/pill_blue.png");
add_fire = new Add_Fire("img/PNG/Power-ups/powerupGreen_star.png");
p = new Player("img/player_ship.png", b);
m = new Menu;
for (int i=0; i<max_a; i++)
{
    bomb[i] = new Bomb("img/PNG/Lasers/laserBlue10.png");
    e = new Enemy(bomb[i]);
}
for (int i=0; i<max_a; i++)
{
    a[i] = new Alpha("img/PNG/Enemies/enemyBlue1.png");
    a[i]->sprite.setPosition(rand() % 600 + 100, rand() % 300);
    beta[i] = new Beta("img/PNG/Enemies/enemyBlue4.png");
    beta[i]->sprite.setPosition(rand() % 600 + 100, rand() % 300);
    g[i] = new Gamma("img/PNG/Enemies/enemyBlue5.png");
    g[i]->sprite.setPosition(rand() % 600 + 100, rand() % 300);    
}
beam = new Beam("img/PNG/Lasers/laserRed14.png");
monster = new Monster("img/monster1.png", beam);
for (int i=0; i<max_a; i++)
{    
    fire[i] = new Fire("img/PNG/Lasers/laserGreen16.png");
    dragon = new Dragon("img/dragon1.png", fire[i]);
}
bg_texture.loadFromFile("img/background.jpg");
background.setTexture(bg_texture);
background.setScale(2.15, 1.5);
for (int i=0; i<max_a; i++)
    fireflag[i] = 0;

total_score = 0;
}

bool start_menu()
{
   return m->display_menu();
}

void start_game()
{
    srand(time(0));
    RenderWindow window(VideoMode(780, 780), title);
    Clock clock;
    float timer=0;
    float timer2 = 0;
    float timer3 = 0;
    float timer4 = 0;
    float add_timer1 = 0;
    float add_timer2 = 0;
    float add_timer3 = 0;
    float add_timer4 = 0;
    bool flag4 = 0;
    float add_timer5 = 0;
    

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds(); 
        clock.restart();
        timer += time; 
        timer2 += time; 
        timer3 += time;
        timer4 += time;
        add_timer1 += time; 
        add_timer2 += time; 
        add_timer3 += time; 
        add_timer4 += time; 
        add_timer5 += time; 

 	Event e;
        while (window.pollEvent(e))
        {  
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game                        	    
        }
          
	if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
            p->move("l");    // Player will move to left
	if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
            p->move("r");  //player will move to right
	if (Keyboard::isKeyPressed(Keyboard::Up)) //If up key is pressed
            p->move("u");    //playet will move upwards
	if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
            p->move("d");  //player will move downwards
    if (Keyboard::isKeyPressed(Keyboard::Space)) //If spacebar key is pressed
            b->fired(p->sprite.getPosition().x + p->sprite.getGlobalBounds().width / 2, p->sprite.getPosition().y + p->sprite.getGlobalBounds().height / 2, timer);    // Bullet will shoot  
	if (Keyboard::isKeyPressed(Keyboard::J)) 
        m->display_menu();
    

    ////////////////////////////////////////////////
	/////  Call your functions here            ////


    p->wrap(); //Function to make player wrap around

    if (b->shoot_flag() == 1)
        b->move_bullet();  //Function to move bullet
  
    for (int i=0; i<max_a; i++)
    {
        a[i]->setAlive(0);
        beta[i]->setAlive(0);
        g[i]->setAlive(0);
        a[i]->move();
        a[i]->direction();
        beta[i]->move();
        beta[i]->direction();
        g[i]->move();
        g[i]->direction();
    }

    for (int i=0; i<4; i++)
    {
        add[i]->move();
        add[i]->direction();
    }
    for (int i = 0; i < max_a; i++)
    {
        if (a[i]->player_hit(p))
        {
            p->destroy();
        }

        if (beta[i]->player_hit(p))
        {
            p->destroy();
        }

        if (g[i]->player_hit(p))
        {
            p->destroy();
        }

        if (a[i]->collision(b))
        {
                a[i]->destroy();
                b->bullet_destroy();
                total++;
                total_score += 10;
                break;
        }

        if (beta[i]->collision(b))
        {
                beta[i]->destroy();
                b->bullet_destroy();
                total++;
                total_score += 20;
                break;
        }

        if (g[i]->collision(b))
        {
                g[i]->destroy();
                b->bullet_destroy();
                total++;
                total_score += 30;
                break;
        }
    }

    for (int i=0; i<max_a; i++)
    {
        if (timer2 >= 5)
        {
            bomb[i]->fired_b(a[i]->sprite.getPosition().x + a[i]->sprite.getGlobalBounds().width / 2, a[i]->sprite.getPosition().y + a[i]->sprite.getGlobalBounds().height / 2, timer);
        }

        if (timer3 >= 3)
        {
            bomb[i]->fired_b(beta[i]->sprite.getPosition().x + beta[i]->sprite.getGlobalBounds().width / 2, beta[i]->sprite.getPosition().y + beta[i]->sprite.getGlobalBounds().height / 2, timer);
        }

        if (timer4 >= 2)
        {
        //    beam->fired(monster->sprite.getPosition().x + monster->sprite.getGlobalBounds().width / 2, monster->sprite.getPosition().y + monster->sprite.getGlobalBounds().height / 2, timer);
            bomb[i]->fired_b(g[i]->sprite.getPosition().x + g[i]->sprite.getGlobalBounds().width / 2, g[i]->sprite.getPosition().y + g[i]->sprite.getGlobalBounds().height / 2, timer);
        }
    }

    if (add_timer1 >= 7)
        danger->fired_add(add[0]->sprite.getPosition().x, add[0]->sprite.getPosition().y, timer);
    
    if (danger->add_flag() == 1)
    {
        danger->move_add(); 
        danger->flag3 = 0;
    }

    if (danger->collision(p))
    {
        p->destroy();
        danger->sprite.setPosition(1000,1000);
    }

    if (danger->sprite.getPosition().y >= 780 && !danger->flag3)
    {
        total_score += 5;
        danger->flag3 = 1;
    }

    if (add_timer2 >= 13)
        live->fired_add(add[1]->sprite.getPosition().x, add[1]->sprite.getPosition().y, timer);
    
    if (live->add_flag() == 1)
        live->move_add(); 

    if (live->collision(p))
    {
        p->live();
        live->sprite.setPosition(1000,1000);
    }

    if (add_timer3 >= 10)
        add_fire->fired_add(add[2]->sprite.getPosition().x, add[2]->sprite.getPosition().y, timer);
    
    if (add_fire->add_flag() == 1)
        add_fire->move_add(); 

    if (add_fire->collision(p))
    {
        if (add_fire->activate(b))  
        {
            flag4 = 1;
            add_timer5 = 0;
        }
        add_fire->sprite.setPosition(1000,1000);
    }

    if (flag4 == 1 && add_timer5 >= 5)
    {
        flag4 = 0;
        add_fire->activate(b);
        add_timer5 = 0;
    }
    for (int i=0; i<max_a; i++)
    {
        if (p->collision(bomb[i]))
        {
            p->destroy();
            bomb[i]->sprite.setPosition(10000,10000);
            break;
        }
    }

    

    if (timer2 >= 5)
        timer2 = 0;

    if (timer3 >= 3)
        timer3 = 0;

    if (timer4 >= 2)
        timer4 = 0;

    if (add_timer1 >= 7)
        add_timer1 = 0;
    
    if (add_timer2 >= 13)
        add_timer2 = 0;

    if (add_timer3 >= 10)
        add_timer3 = 0;

               
    for (int i=0; i<max_a; i++)
    {
        if (bomb[i]->bomb_flag() == 1)
            bomb[i]->move_bomb(); 
    }
    
    monster->direction();
    monster->move();
    if (monster->collision(b))
    {
        b->bullet_destroy();
    }

    if (monster->player_hit(p))
        p->destroy();

    if (p->collision(beam))
    {
        p->destroy();
    }

    if (dragon->collision(b))
    {
        b->bullet_destroy();
    }

    if (dragon->player_hit(p))
        p->destroy();


    if (p->lives == 0)
    {   
        m->gameover(total_score);
        window.close();
    }

    fireflag[0] = 1;

    if (p->sprite.getPosition().x >= 340)
    {
        fireflag[1] = 1;
        fireflag[2] = 0;
    }

    if (p->sprite.getPosition().x <= 340)
    {
        fireflag[1] = 0;
        fireflag[2] = 1;
    }

    for (int i=0; i<max_a; i++)
    {
        if (p->collision(fire[i]))
        {
            p->destroy();
        }
    }

	//////////////////////////////////////////////

	window.clear(Color::Black); //clears the screen
	window.draw(background);  // setting background
	window.draw(p->sprite);   // setting player on screen
    window.draw(danger->sprite);
    window.draw(live->sprite);
    window.draw(add_fire->sprite);
//    window.draw(add[0]->sprite);
    for (int i=0; i<max_a; i++)
    {    
        window.draw(a[i]->sprite);
        window.draw(beta[i]->sprite);
        window.draw(g[i]->sprite);
        window.draw(bomb[i]->sprite);
    }
    if (b->shoot_flag() == 1)
        window.draw(b->sprite);  //setting bullet on screen

    if (total == 9)
    {
        if (beam->fired(monster->sprite.getPosition().x + monster->sprite.getGlobalBounds().width / 2, monster->sprite.getPosition().y + monster->sprite.getGlobalBounds().height / 2, timer) >= 5)
        {
            
            if (monster->alive == 0 && !monster->flag5 && monster->sprite.getPosition().y <= 780)
            {
                total_score += 50;
                monster->flag5 = 1;
            }
            monster->destroy();
            window.draw(dragon->sprite);
            dragon->setAlive(0);
            for (int i=0; i<max_a; i++)
            {
                if (fireflag[i] == 1)
                {
                    if(fire[i]->fired(dragon->sprite.getPosition().x + dragon->sprite.getGlobalBounds().width / 2, dragon->sprite.getPosition().y + dragon->sprite.getGlobalBounds().height / 2, timer, fireflag[i]) >= 2)
                    {
                        dragon->destroy();
                        total_score += dragon->total;
                        window.close();
                        m->gameover(total_score);
                        break;
                    }
                    
                    if (fire[0]->fire_flag() == 1)
                        fire[0]->move_fire(0, 1);
                    if (fire[1]->fire_flag() == 1)
                        fire[1]->move_fire(1, 1);
                    if (fire[2]->fire_flag() == 1)
                        fire[2]->move_fire(-1, 1);
                             

                    fire[i]->setAlive(0);
                    window.draw(fire[i]->sprite);
                }
            }
        }

        if (beam->beam_flag() == 1)
            beam->move_beam(); 

        monster->setAlive(0);
        beam->setAlive(0);
        window.draw(monster->sprite);
        window.draw(beam->sprite);
    }
    Font font;
    font.loadFromFile("font2.ttf");

    Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
    text.setPosition(10, 10); 
    text.setString("Lives: " + to_string(p->lives));

    Text text2;
    text2.setFont(font);
    text2.setCharacterSize(24);
    text2.setFillColor(Color::White);
    text2.setPosition(10, 30); 
    text2.setString("Score: " + to_string(total_score));
    
    window.draw(text);
    window.draw(text2);


	window.display();  //Displying all the sprites
    }


}

~Game()
{
    delete p;
    delete b;
    delete m;
    delete monster;
    delete beam;
    delete dragon;
    delete danger;
    delete live;
    delete add_fire;
    for (int i=0; i<max_a; i++)
    {
        delete a[i];
        delete beta[i];
        delete g[i];
        delete bomb[i];
        delete fire[i];
    }
    delete e;

    for (int i=0; i<4; i++)
        delete add[i];
}

};

