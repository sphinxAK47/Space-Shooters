#include <SFML/Graphics.hpp>
#include<string.h>
#include "Enemy.h"
#include "Fire.h"
using namespace sf;

class Dragon : public Enemy
{
    public:

    Fire *f;

    Dragon(std::string png_path, Fire* fire) : Enemy()
    {
        //srand(time(0));
        tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		sprite.setPosition(220,0);
		sprite.setScale(1.5,1.5);
        f = fire;
    }

    void destroy() override
    {
        alive = 1;
        sprite.setPosition(10000,10000); 
        total = 50;
        flag5 = 0;
    }

    ~Dragon()
    {
        delete f;
    }
};
