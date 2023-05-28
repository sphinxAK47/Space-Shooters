#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include<string.h>
#include "Bomb.h"
using namespace sf;

class Enemy
{
    public:

	Texture tex;
	Sprite sprite;
    float speed1;
	bool alive;
    bool right;
    int x, y;
    Bomb* bomb1;
    int health;
    int total = 0;
    bool flag5 = 0;



    Enemy()
    {
        alive = 1;
        right = 1;
        speed1 = 0.3;
        health = 0;
    }

    Enemy(Bomb *bomb)
    {
        alive = 1;
        right = 1;
        speed1 = 0.05;
        bomb1 = bomb;
    }

    virtual void direction()
    {
        if (sprite.getPosition().x >= 740 || sprite.getPosition().x <= 0)
            right = !right;
    }

    virtual void move()
    {
        if (right == 1)
            sprite.move(speed1, 0);
        else
            sprite.move(-speed1, 0);
    }

    virtual void destroy()
    {
        alive = 1;
        sprite.setPosition(10000,10000);
    }
    
    virtual void setAlive(bool a)
    {
        alive = a;
    }

    virtual bool isAlive()
    {
        return alive;
    }

    virtual bool collision(Bullet *b)
    {
        if(isAlive())
            return 0;
        
        float centre_ax = sprite.getPosition().x + sprite.getGlobalBounds().width / 2;
        float centre_ay = sprite.getPosition().y + sprite.getGlobalBounds().height / 2;
        float centre_bx = b->sprite.getPosition().x - b->sprite.getGlobalBounds().width / 2;
        float centre_by = b->sprite.getPosition().y - b->sprite.getGlobalBounds().height / 2;

        if (centre_bx < centre_ax + sprite.getGlobalBounds().width / 2 &&
        centre_bx + b->sprite.getGlobalBounds().width > centre_ax - sprite.getGlobalBounds().width / 2 &&
        centre_by < centre_ay + sprite.getGlobalBounds().height / 2 &&
        centre_by + b->sprite.getGlobalBounds().height > centre_ay - sprite.getGlobalBounds().height / 2)
        {
            return 1;
        }
        return 0;
    }

    virtual void inc_health() 
    {
        health++;
    }

    virtual bool player_hit(Player *p)
    {
        if(isAlive())
            return 0;
        
        float centre_ax = sprite.getPosition().x + sprite.getGlobalBounds().width / 2;
        float centre_ay = sprite.getPosition().y + sprite.getGlobalBounds().height / 2;
        float centre_bx = p->sprite.getPosition().x - p->sprite.getGlobalBounds().width / 2;
        float centre_by = p->sprite.getPosition().y - p->sprite.getGlobalBounds().height / 2;

        if (centre_bx < centre_ax + sprite.getGlobalBounds().width / 2 &&
        centre_bx + p->sprite.getGlobalBounds().width > centre_ax - sprite.getGlobalBounds().width / 2 &&
        centre_by < centre_ay + sprite.getGlobalBounds().height / 2 &&
        centre_by + p->sprite.getGlobalBounds().height > centre_ay - sprite.getGlobalBounds().height / 2)
        {
            return 1;
        }
        return 0;
    }

    virtual bool time() 
    {
        Clock clock;
        if (clock.getElapsedTime().asSeconds() >= 15)
            return 1;
    }

    ~Enemy()
    {
        delete bomb1;
    }
};

#endif

