#ifndef LIVE_H
#define LIVE_H
#include <SFML/Graphics.hpp>
#include<string.h>
#include "Add_on.h"
using namespace sf;

class Live: public Add_on
{
    public:

	// Texture tex;
	// Sprite sprite;
	float speed = 1.2;
    bool flag2 = 0;
	int x,y;

    Live(std::string png_path)
    {
        tex.loadFromFile(png_path);
		sprite.setTexture(tex);
        sprite.setPosition(1000,1000);
		sprite.setScale(1.5,1.5);
    }

    void fired_add(float p_x, float p_y, float& timer) override
    {
        if (!flag2 && timer > 0.5)
        {
            sprite.setPosition(p_x, p_y);
            flag2 = true;
        }
    }

    bool add_flag() override
    {
        return flag2;
    }

    void move_add() override
    {
        sprite.move(0, speed);

        if (sprite.getPosition().y > 780)
        {
            flag2 = false;
        }
    }

    bool collision(Player *b) override
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

    ~Live(){}
};

#endif