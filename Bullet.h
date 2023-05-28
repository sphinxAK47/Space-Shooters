#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include<string.h>
using namespace sf;

class Bullet
{
    public:

	Texture tex;
	Sprite sprite;
	float speed = -7;
    bool flag = 0;
	int x,y;


    Bullet(std::string png_path)
    {
        tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		x=370;y=700;
		sprite.setPosition(x,y);
		sprite.setScale(0.9,0.9);
    }

    void fired(float p_x, float p_y, float& timer)
    {
        if (!flag && timer > 0.5)
        {
            sprite.setPosition(p_x - sprite.getGlobalBounds().width / 2, p_y - sprite.getGlobalBounds().height / 2);
            flag = true;
        }
    }

    bool shoot_flag() 
    {
        return flag;
    }

    void move_bullet()
    {
        sprite.move(0, speed);

        if (sprite.getPosition().y < 0)
        {
            flag = false;
        }
    }

    void bullet_destroy()
    {
        flag = false;
    }

    ~Bullet(){}
};

#endif