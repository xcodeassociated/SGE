//
//  main.cpp
//  ZombieGame
//
//  Created by Hamashy on 13.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#include <SGE.hpp>
#include "ZombieScene.hpp"
#include "IntroScene.hpp"

int main(int argc, char * argv[])
{
    std::cout.setf(std::ios::boolalpha);
    std::cout.sync_with_stdio(true);

	SGE::Director* director = SGE::Director::getDirector(1024, 768);
	SGE::Game* game = SGE::Game::getGame();
	game->bindDirector(director);
	game->init(60);

	ZombieScene* S1 = new ZombieScene(game, PATH"ZombieGame/Levels/level1.txt");
	SGE::Scene* S0 = new IntroScene(S1, PATH"ZombieGame/Resources/Textures/zombie-game.png");
	SGE::Scene* S2 = new EndScene(S1, PATH"ZombieGame/Resources/Textures/end-game.png");
	
	S1->endScene = S2;

	director->addScene(S0);
	director->addScene(S1);
	director->addScene(S2);

	director->setNextScene(S0);
	
	game->run();

	director->deleteScene(S0);
	director->deleteScene(S1);
	director->deleteScene(S2);
	
	game->finalize();
	director->finalize();

    return 0;
}
