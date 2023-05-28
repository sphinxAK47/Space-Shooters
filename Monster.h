#include <SFML/Graphics.hpp>
#include<string.h>
#include "Enemy.h"
#include "Beam.h"
using namespace sf;

class Monster : public Enemy
{
    public:

    Beam* b1;

    Monster(std::string png_path, Beam* beam) : Enemy()
    {
        //srand(time(0));
        tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		sprite.setPosition(220,0);
		sprite.setScale(0.5,0.5);
        b1 = beam;
    }

    void direction() override
    {
        if (sprite.getPosition().x >= 500 || sprite.getPosition().x <= -100)
            right = !right;
    }

    void inc_health() override
    {
        health++;
    }

    void destroy() override
    {
        alive = 1;
        sprite.setPosition(10000,10000); 
        total = 50;
        flag5 = 0;
    }

    ~Monster()
    {
        delete b1;
    }

};