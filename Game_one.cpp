#include <iostream>
#include "Game.h" //all sfml files moved here just to ensure including everything once
int main()
{   
    //inti srand
    std::srand(static_cast<unsigned>(time(NULL)));
    Game game;

    while (game.running() && !game.getEndGame()) //checks if window is open
    {
        //updating is just event polling and then , acting on the events polled
        game.update();

        //render
        game.render();

        //end of application
    }
    return 0;
}

