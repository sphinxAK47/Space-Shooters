#include "game.h"
int main()
{
    
//    Menu m;
//    m.display_menu(); 
    Game g;
 //   g.start_menu();
    if (g.start_menu() == 1)
        g.start_game();
    return 0;
}
