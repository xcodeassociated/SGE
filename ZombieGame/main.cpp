//
//  main.cpp
//  ZombieGame
//
//  Created by Hamashy on 13.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#include <SGE.hpp>
#include "ZombieScene.hpp"

int main(int argc, char * argv[])
{
    std::cout.setf(std::ios::boolalpha);
    std::cout.sync_with_stdio(true);

	SGE::Director* director = SGE::Director::getDirector(1024, 768);
	SGE::Game* game = SGE::Game::getGame();
	game->bindDirector(director);
	game->init(60);

	SGE::Scene* S1 = director->addScene(new ZombieScene(game,PATH"ZombieGame/Levels/level1.txt"));

	director->showScene(S1);

    //...

	director->deleteScene(S1);
	
	game->finalize();
	director->finalize();

    return 0;
}
