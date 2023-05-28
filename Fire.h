#ifndef FIRE_H
#define FIRE_H
#include <SFML/Graphics.hpp>
#include<string.h>
using namespace sf;

class Fire
{
    public:

	Texture tex;
	Sprite sprite;
	float speed = 1.1;
    bool flag = 0, flag2 = 0;
    bool alive = 1;
	int x,y;
    int count = 0;
    Clock clock;
    float duration = 5;
    bool flag3 = 0;


    Fire(std::string png_path)
    {
        tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		x=10000;y=10000;
		sprite.setPosition(x,y);
		sprite.setScale(0.75,0.75);
    }

    void setAlive(bool a)
    {
        alive = a;
    }

    bool isAlive()
    {
        return alive;
    }


    int fired(float p_x, float p_y, float& timer, bool fireflag)
    {
        if (clock.getElapsedTime().asSeconds() >= duration)
        {
            flag2 = !flag2;
            if (flag2 == 1)
                count++;
            if (flag2 == 0)
                count++;
            clock.restart();
        }

        if (!flag && flag2 && !alive)
        {
            sprite.setPosition(p_x - sprite.getGlobalBounds().width / 2, (p_y - sprite.getGlobalBounds().height / 2) + 100);
            flag = true;
        }
        return count;
    }

    bool fire_flag() 
    {
        return flag;
    }

    void move_fire(float x, float y)
    {
        float temp_x = x*speed; 
        float temp_y = y*speed;
        sprite.move(temp_x, temp_y);

        if (sprite.getPosition().y > 780)
        {
            flag = false;
        }
    }

    ~Fire(){}
};

#endif