#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_MultiplayerHostMenu.h"

#include "xviii/Core/Game.h"

GameState_MultiplayerHostMenu::GameState_MultiplayerHostMenu(Game* game) :
GameState_MenuState{game}
{

}

void GameState_MultiplayerHostMenu::init(){
	menuList.push_back({{"Back"}, true, game->MultiplayerMenuState.get(), Action::NONE});
	lineUpObjects();

	tcpListener.setBlocking(false);

	if (tcpListener.listen(53000) != sf::Socket::Done)
    {
        // error...
    }
}

void GameState_MultiplayerHostMenu::update(float mFT){
	GameState_MenuState::update(mFT);

	sf::TcpSocket client;
	//client.setBlocking(false);
    if (tcpListener.accept(client) != sf::Socket::Done)
    {
        // error...
    }
    else{
        std::cout << "Success!" << std::endl;
    }

}

void GameState_MultiplayerHostMenu::draw(){
	GameState_MenuState::draw();
}
