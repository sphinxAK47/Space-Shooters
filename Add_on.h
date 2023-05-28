#ifndef ADD_ON_H
#define ADD_ON_H
#include <SFML/Graphics.hpp>
#include<string.h>
#include "player.h"
using namespace sf;

class Add_on
{
    public:

	Texture tex;
	Sprite sprite;
	float speed;
    bool flag;
	bool flag2;
	int x,y;
	Clock clock;
	float duration;
	int total = 0;
	bool flag3 = 0;

	Add_on()
	{
		speed = 1.1;
		flag = 1;
		flag2 = 0;
	    sprite.setPosition(0,0);
		sprite.setScale(0.5,0.5);
    }

    Add_on(std::string png_path)
    {
	    tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		speed = 0.1;
		flag = 1;
		flag2 = 0;
	    sprite.setPosition(0,0);
		sprite.setScale(0.5,0.5);
    }

    void direction()
    {
        if (sprite.getPosition().x >= 740 || sprite.getPosition().x <= 0)
            flag = !flag;
    }

    void move()
    {
        if (flag == 1)
            sprite.move(speed, 0);
        else
            sprite.move(-speed, 0);
    }

    virtual void fired_add(float p_x, float p_y, float& timer)
    {
        if (!flag2 && timer > 0.5)
        {
            sprite.setPosition(p_x - sprite.getGlobalBounds().width / 2, p_y - sprite.getGlobalBounds().height / 2);
            flag2 = true;
        }
    }

    virtual bool add_flag() 
    {
        return flag2;
    }

    virtual void move_add()
    {
        sprite.move(0, speed);

        if (sprite.getPosition().y > 780)
        {
            flag2 = false;
        }
    }

    virtual bool collision(Player *b)
    {     
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

    virtual bool activate(Bullet* b)
    {}

	virtual void score()
    {
        if (flag3)
        {
            total += 5;
            flag3 = false;
        }
    }

    ~Add_on(){}

};

#endif