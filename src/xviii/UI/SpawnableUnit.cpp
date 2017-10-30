#include "xviii/Headers/stdafx.h"
#include "xviii/UI/SpawnableUnit.h"

SpawnableUnit::SpawnableUnit(Player* _player, std::string _unitID, sf::Vector2i _coords) :
unitID{_unitID},
unitName{},
unitSprite{},
player{_player},
type{}
{
    unitName.setFont(player->masterManager.fontManager->getFont(FontManager::Type::TCMT));
    unitName.setFillColor(sf::Color::White);
    unitName.setCharacterSize(12);

    unitName.setString(player->masterManager.unitLoader->customClasses.at(_unitID).shortDisplayName);

    std::string textureID = player->masterManager.unitLoader->customClasses.at(_unitID).textureID;
    unitSprite = player->masterManager.textureManager->getUnitSprite(textureID);

    unitSprite.setOrigin(unitSprite.getGlobalBounds().width / 2, unitSprite.getGlobalBounds().height / 2);
    unitName.setOrigin(unitName.getLocalBounds().width / 2, unitName.getLocalBounds().height / 2);
    unitSprite.setPosition(getSelectablePos(_coords));
    unitName.setPosition({unitSprite.getPosition().x, unitSprite.getPosition().y - 30});
}

//Copy constructor
SpawnableUnit::SpawnableUnit(const SpawnableUnit& _spawnableUnit):
unitID{_spawnableUnit.unitID},
unitName{_spawnableUnit.unitName},
unitSprite{_spawnableUnit.unitSprite},
player{_spawnableUnit.player},
type{_spawnableUnit.type}
{
}
//Operator=
SpawnableUnit & SpawnableUnit::operator=(const SpawnableUnit& _spawnableUnit){
    unitID = _spawnableUnit.unitID;
    unitName = _spawnableUnit.unitName;
    unitSprite = _spawnableUnit.unitSprite;
    player = _spawnableUnit.player;
    type = _spawnableUnit.type;

    return *this;
}
