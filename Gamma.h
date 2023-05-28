#include <SFML/Graphics.hpp>
#include<string.h>
#include "Enemy.h"
using namespace sf;

class Gamma : public Enemy
{
    public:

    Gamma(std::string png_path)
    {
        tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		sprite.setScale(0.75,0.75);
    }

    void move() override
    {
        speed1 = 0.5;
        if (right == 1)
            sprite.move(speed1, 0);
        else
            sprite.move(-speed1, 0);
    }

    void destroy() override
    {
        alive = 1;
        sprite.setPosition(1000,1000);
    }

    ~Gamma(){}
};



