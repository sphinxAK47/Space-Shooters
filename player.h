#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include<string.h>
#include "Bullet.h"
#include "Bomb.h"
#include "Beam.h"
#include "Fire.h"
using namespace sf;


class Player
{
	public:

	Texture tex;
	Sprite sprite;
	float speed=1.3;
	int x,y;
	Bullet* b1;
	float centre_x = sprite.getGlobalBounds().width / 2;
	float centre_y = sprite.getGlobalBounds().height / 2;
	int lives = 3;


	Player(std::string png_path, Bullet *b)
	{
		tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		x=340;y=700;
		sprite.setPosition(x,y);
		sprite.setScale(0.75,0.75);

		b1 = b;	
	}

	void fire()
	{

	}

	void move(std::string s)
	{
		float delta_x=0,delta_y=0;

		if(s=="l")
			delta_x = -1;
		else if(s=="r")
			delta_x = 1;
		if(s=="u")
			delta_y=-1;
		else if(s=="d")
			delta_y=1;

		delta_x*=speed;
		delta_y*=speed;

		sprite.move(delta_x, delta_y);
		//b1->sprite.move(delta_x, delta_y);
	}

	void wrap()
	{
		if (sprite.getPosition().x < -100)
			sprite.setPosition(780, sprite.getPosition().y);
		if (sprite.getPosition().x > 780)
			sprite.setPosition(0, sprite.getPosition().y);
		if (sprite.getPosition().y < -100)
			sprite.setPosition(sprite.getPosition().x, 780);
		if (sprite.getPosition().y > 780)
			sprite.setPosition(sprite.getPosition().x, 0);
	}

	// void rotate()
	// {
	// 	float angle = 0.717;
	// 	float temp_x, temp_y;

	// 	temp_x = ((sprite.getPosition().x - centre_x) * angle) - ((sprite.getPosition().y - centre_y) * angle) + centre_x;
	// 	temp_y = angle * (sprite.getPosition().y - centre_y + sprite.getPosition().x - centre_x) + centre_y;

	// 	float rot_x = temp_x - sprite.getPosition().x;
	// 	float rot_y = temp_y - sprite.getPosition().y;

	// 	sprite.setPosition(rot_x, rot_y);
	// }

	void destroy()
    {
		lives--;
        sprite.setPosition(340,700);
    }

	void live()
	{
		lives++;
	}

bool collision(Bomb* bomb)
{
    float centre_px = sprite.getPosition().x + sprite.getGlobalBounds().width / 2;
    float centre_py = sprite.getPosition().y + sprite.getGlobalBounds().height / 2;
    float centre_bx = bomb->sprite.getPosition().x + bomb->sprite.getGlobalBounds().width / 2;
    float centre_by = bomb->sprite.getPosition().y + bomb->sprite.getGlobalBounds().height / 2;

    if (centre_px < centre_bx + bomb->sprite.getGlobalBounds().width / 2 &&
        centre_px + sprite.getGlobalBounds().width > centre_bx - bomb->sprite.getGlobalBounds().width / 2 &&
        centre_py < centre_by + bomb->sprite.getGlobalBounds().height / 2 &&
        centre_py + sprite.getGlobalBounds().height > centre_by - bomb->sprite.getGlobalBounds().height / 2)
    {
        return true;
    }

    return false;
}

bool collision(Beam* bomb)
{
    float centre_px = sprite.getPosition().x + sprite.getGlobalBounds().width / 2;
    float centre_py = sprite.getPosition().y + sprite.getGlobalBounds().height / 2;
    float centre_bx = bomb->sprite.getPosition().x + bomb->sprite.getGlobalBounds().width / 2;
    float centre_by = bomb->sprite.getPosition().y + bomb->sprite.getGlobalBounds().height / 2;

    if (centre_px < centre_bx + bomb->sprite.getGlobalBounds().width / 2 &&
        centre_px + sprite.getGlobalBounds().width > centre_bx - bomb->sprite.getGlobalBounds().width / 2 &&
        centre_py < centre_by + bomb->sprite.getGlobalBounds().height / 2 &&
        centre_py + sprite.getGlobalBounds().height > centre_by - bomb->sprite.getGlobalBounds().height / 2)
    {
        return true;
    }

    return false;
}

bool collision(Fire* bomb)
{
    float centre_px = sprite.getPosition().x + sprite.getGlobalBounds().width / 2;
    float centre_py = sprite.getPosition().y + sprite.getGlobalBounds().height / 2;
    float centre_bx = bomb->sprite.getPosition().x + bomb->sprite.getGlobalBounds().width / 2;
    float centre_by = bomb->sprite.getPosition().y + bomb->sprite.getGlobalBounds().height / 2;

    if (centre_px < centre_bx + bomb->sprite.getGlobalBounds().width / 2 &&
        centre_px + sprite.getGlobalBounds().width > centre_bx - bomb->sprite.getGlobalBounds().width / 2 &&
        centre_py < centre_by + bomb->sprite.getGlobalBounds().height / 2 &&
        centre_py + sprite.getGlobalBounds().height > centre_by - bomb->sprite.getGlobalBounds().height / 2)
    {
        return true;
    }

    return false;
}

~Player()
{
	delete b1;
}
};

#endif