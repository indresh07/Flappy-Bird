#include"mainGame.h"
#include<vector>
#include<iostream>

int main(int argc, char** argv){

    mainGame game;
    game.run();

    char tmp;
    std::cout<<"\nEnter any key to exit...";
    std::cin>>tmp;

    return 0;
}
