#ifndef BEAM_H
#define BEAM_H
#include <SFML/Graphics.hpp>
#include<string.h>
using namespace sf;

class Beam
{
    public:

	Texture tex;
	Sprite sprite;
	float speed = 250;
    bool flag = 0, flag2 = 0;
    bool alive = 1;
	int x,y;
    int count = 0;
    Clock clock;
    float duration = 2;


    Beam(std::string png_path)
    {
        tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		x=10000;y=10000;
		sprite.setPosition(x,y);
		sprite.setScale(4,10);
    }

    void setAlive(bool a)
    {
        alive = a;
    }

    bool isAlive()
    {
        return alive;
    }


    int fired(float p_x, float p_y, float& timer)
    {
        if (clock.getElapsedTime().asSeconds() >= duration)
        {
            flag2 = !flag2;
            if (flag2 == 1)
                count++;
            clock.restart();
        }

        if (!flag && flag2 && !alive)
        {
            sprite.setPosition(p_x - sprite.getGlobalBounds().width / 2, p_y - sprite.getGlobalBounds().height / 2);
            flag = true;
        }
        
        return count;
    }

    bool beam_flag() 
    {
        return flag;
    }

    void move_beam()
    {
        sprite.move(0, speed);

        if (sprite.getPosition().y > 780)
        {
            flag = false;
        }
    }

    ~Beam(){}
};

#endif