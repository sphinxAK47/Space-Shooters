#ifndef BOMB_H
#define BOMB_H
#include <SFML/Graphics.hpp>
#include<string.h>
using namespace sf;

class Bomb
{
    public:

	Texture tex;
	Sprite sprite;
	float speed = 1.2;
    bool flag = 0;
	int x,y;


    Bomb(std::string png_path)
    {
        tex.loadFromFile(png_path);
		sprite.setTexture(tex);
        sprite.setPosition(1000,1000);
		sprite.setScale(0.5,0.5);
    }

    void fired_b(float p_x, float p_y, float& timer)
    {
        if (!flag && timer > 0.5)
        {
            sprite.setPosition(p_x - sprite.getGlobalBounds().width / 2, p_y - sprite.getGlobalBounds().height / 2);
            flag = true;
        }
    }

    bool bomb_flag() 
    {
        return flag;
    }

    void move_bomb()
    {
        sprite.move(0, speed);

        if (sprite.getPosition().y > 780)
        {
            flag = false;
        }
    }

    ~Bomb(){}
};

#endif