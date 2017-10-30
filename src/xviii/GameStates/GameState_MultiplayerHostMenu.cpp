#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_MultiplayerHostMenu.h"

#include "xviii/Core/Game.h"

GameState_MultiplayerHostMenu::GameState_MultiplayerHostMenu(Game* game) :
GameState_MenuState{game},
tcpListener{},
waitText{}
{

}

void GameState_MultiplayerHostMenu::init(){
	menuList.push_back({std::string("Back"), true, game->MultiplayerMenuState.get(), Action::NONE});
	lineUpObjects();

    waitText.setCharacterSize(40);
	waitText.setFont(game->mManager.fontManager->getFont(FontManager::Type::TCMT));
	waitText.setString("Waiting for an incoming connection...");
	waitText.setFillColor(sf::Color::Red);
	waitText.setOrigin(waitText.getLocalBounds().width / 2, waitText.getLocalBounds().height / 2);
	waitText.setPosition(xResolution / 2, -(yResolution / 3.5f));

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
    game->mWindow.clear(sf::Color::Black);
	game->mWindow.setView(backgroundView);
	game->mWindow.draw(backgroundSprite);

	game->mWindow.setView(menuSelectView);
	game->mWindow.draw(waitText);

	for (auto& item : menuList){
		game->mWindow.draw(item.text);
	}
}
