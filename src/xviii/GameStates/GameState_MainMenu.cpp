#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_MainMenu.h"

#include "xviii/Core/Game.h"

GameState_MainMenu::GameState_MainMenu(Game* game) :
GameState_MenuState{game}
{
	std::vector<std::string> quotes;

	/*

    quotes.push_back("\"Cavalry is useful before, during, and after the battle.\" - Napoleon");
    quotes.push_back("\"Don't forget your great guns, which are the most respectable arguments of the rights of kings.\" - Frederick II");
    quotes.push_back("\"Do not fire until you see the white of their eyes!\" - Joseph Warren");
    quotes.push_back("\"Soldiers usually win the battles and generals get the credit for them.\" - Napoleon");
    quotes.push_back("\"Discipline is the soul of an army. It makes small numbers formidable; procures success to the weak, and esteem to all.\" - George Washington");
    quotes.push_back("\"The backbone of surprise is fusing speed with secrecy.\" - Carl von Clausewitz");
    quotes.push_back("\"It is even better to act quickly and err than to hesitate until the time of action is past.\" - Carl von Clausewitz");
    quotes.push_back("\"Men are always more inclined to pitch their estimate of the enemy's strength too high than too low, such is human nature.\" - Carl von Clausewitz");
    quotes.push_back("\"Everything in war is simple, but the simplest thing is difficult.\" - Carl von Clausewitz");
    quotes.push_back("\"There are times when the utmost daring is the height of wisdom.\" - Carl von Clausewitz");
    */

    quotes.push_back("\"War is not merely a political act but a real political instrument, a continuation of political intercourse, a carrying out of the same by other means.\" - Carl von Clausewitz");

	//Select a random quote:
	boost::random::uniform_int_distribution<int> quoteDistribution(0, quotes.size() - 1);
	int randQuote{quoteDistribution(game->mManager.randomEngine)};

    quoteText.setCharacterSize(23);
	quoteText.setFont(game->mManager.fontManager->getFont(FontManager::Type::TCMT));
    quoteText.setStyle(2);
	quoteText.setString(quotes.at(randQuote));

	if(quoteText.getGlobalBounds().width > backgroundView.getSize().x - backgroundView.getSize().x * 0.5){

        std::string quoteStr = quoteText.getString();
        size_t breakPos{quoteStr.find_last_of(" ", quoteStr.length() * 0.65)};

		if (breakPos == std::string::npos) {
			breakPos = quoteStr.length() / 2;
			quoteStr.insert(breakPos, "-\n");
		}
		else {
			quoteStr.insert(breakPos, "\n");
		}

		if(quoteStr.length() - breakPos < breakPos){
            int blankSpacesToInsert{int((2 * breakPos) - quoteStr.length()) / 2};
            std::string blankString{""};


            for(int i{0}; i < blankSpacesToInsert; ++i){
				blankString += " ";
            }

            std::cout << "inserting " << blankSpacesToInsert << " spaces:" << std::endl;

            quoteStr.insert(breakPos + 2, blankString);
		}

		quoteText.setString(quoteStr);
	}

    quoteText.setOrigin(quoteText.getGlobalBounds().width / 2, quoteText.getGlobalBounds().height / 2);
	quoteText.setPosition(game->mWindow.getSize().x / 2, titleText.getPosition().y + titleText.getGlobalBounds().height * 2);

}

void GameState_MainMenu::init(){
    //menuList.push_back({{"[New Campaign]"}, true, nullptr, Action::NONE});
	//menuList.push_back({{"[Load Campaign]"}, true, nullptr, Action::NONE});
	menuList.push_back({std::string("Battle Menu"), true, game->CustomBattleMenuState.get(), Action::NONE});
	menuList.push_back({std::string("Options"), true, nullptr, Action::NONE});
	menuList.push_back({std::string("Credits"), true, game->CreditMenuState.get(), Action::NONE});
	menuList.push_back({std::string(""), false, nullptr, Action::NONE});
	menuList.push_back({std::string("Exit"), true, nullptr, Action::EXIT});

	lineUpObjects();
}
