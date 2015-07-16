#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Bridge.h"

#include "xviii/Core/World.h"


Bridge::Bridge(TerrainLoader& _terrainLoader, World& _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_terrainLoader, _world, tm, TextureManager::Terrain::BLANK, TerrainType::BRIDGE, _pos),
hp{5},
orientation{Orientation::VERTICAL}
{
    hpText.setFont(world.fm.getFont(FontManager::Type::Arial));
    hpText.setCharacterSize(18);
    hpText.setColor(sf::Color::Black);
    hpText.setString(std::to_string(hp));

    hpText.setPosition(sprite.getPosition());
}

void Bridge::setHp(int _hp){
    hp = _hp;
    hpText.setString(std::to_string(hp));
}

void Bridge::takeDamage(int dmg){
    hp -= dmg;
    hpText.setString(std::to_string(hp));

    if(hp < 0.9){
        //When "untoggling" a bridge, the second argument doesn't really matter
        world.toggleBridge(this, orientation);
    }
};

void Bridge::flip(Orientation _or){
    if(_or == Orientation::HORIZONTAL){
        orientation = Orientation::HORIZONTAL;
        sprite.setTextureRect(world.tm.getSprite(TextureManager::Terrain::BRIDGE_HOR).getTextureRect());
    }
    else if(_or == Orientation::VERTICAL){
        orientation = Orientation::VERTICAL;
        sprite.setTextureRect(world.tm.getSprite(TextureManager::Terrain::BRIDGE_VER).getTextureRect());
    }

    refreshVertexArray();
}

std::string Bridge::callTerrainAttack(UnitTile* unit, int distance){
    return(unit->terrainAttack(this, distance));
}

void Bridge::connect(){
    sf::Vector2i currentPos = this->getCartesianPos();

    sf::Vector2i northIndex = currentPos;
    northIndex.y -= 1;
    TerrainTile* northTile = world.terrainAtCartesianPos(northIndex);

    sf::Vector2i southIndex = currentPos;
    southIndex.y += 1;
    TerrainTile* southTile = world.terrainAtCartesianPos(southIndex);

    sf::Vector2i eastIndex = currentPos;
    eastIndex.x += 1;
    TerrainTile* eastTile = world.terrainAtCartesianPos(eastIndex);

    sf::Vector2i westIndex = currentPos;
    westIndex.x -= 1;
    TerrainTile* westTile = world.terrainAtCartesianPos(westIndex);

    if(northTile != nullptr){
         if(northTile->getTerrainType() == TerrainTile::TerrainType::BRIDGE || northTile->getTerrainType() == TerrainTile::TerrainType::TBRIDGE){
            Bridge* p = static_cast<Bridge*>(northTile);

            if(p->getOrientation() == orientation){
                northernConnection = true;
                p->southernConnection = true;
            }
        }

        else if(northTile->getTerrainType() != TerrainTile::TerrainType::WATER && orientation == TerrainTile::Orientation::VERTICAL){
            northernConnection = true;
        }
    }

    if(southTile != nullptr){
        if(southTile->getTerrainType() == TerrainTile::TerrainType::BRIDGE || southTile->getTerrainType() == TerrainTile::TerrainType::TBRIDGE){
            Bridge* p = static_cast<Bridge*>(southTile);

            if(p->getOrientation() == orientation){
                southernConnection = true;
                p->northernConnection = true;
            }
        }

        else if(southTile->getTerrainType() != TerrainTile::TerrainType::WATER && orientation == TerrainTile::Orientation::VERTICAL){
            southernConnection = true;
        }
    }

    if(eastTile != nullptr){
        if(eastTile->getTerrainType() == TerrainTile::TerrainType::BRIDGE || eastTile->getTerrainType() == TerrainTile::TerrainType::TBRIDGE){
            Bridge* p = static_cast<Bridge*>(eastTile);

            if(p->getOrientation() == orientation){
                easternConnection = true;
                p->westernConnection = true;
            }
        }

        else if(eastTile->getTerrainType() != TerrainTile::TerrainType::WATER && orientation == TerrainTile::Orientation::HORIZONTAL){
            easternConnection = true;
        }
    }

    if(westTile != nullptr){
        if(westTile->getTerrainType() == TerrainTile::TerrainType::BRIDGE || westTile->getTerrainType() == TerrainTile::TerrainType::TBRIDGE){
            Bridge* p = static_cast<Bridge*>(westTile);

            if(p->getOrientation() == orientation){
                westernConnection = true;
                p->easternConnection = true;
            }
        }

        else if(westTile->getTerrainType() != TerrainTile::TerrainType::WATER && orientation == TerrainTile::Orientation::HORIZONTAL){
            westernConnection = true;
        }
    }
}

void Bridge::disconnect(){
    sf::Vector2i currentPos = this->getCartesianPos();

    sf::Vector2i northIndex = currentPos;
    northIndex.y -= 1;
    TerrainTile* northTile = world.terrainAtCartesianPos(northIndex);

    sf::Vector2i southIndex = currentPos;
    southIndex.y += 1;
    TerrainTile* southTile = world.terrainAtCartesianPos(southIndex);

    sf::Vector2i eastIndex = currentPos;
    eastIndex.x += 1;
    TerrainTile* eastTile = world.terrainAtCartesianPos(eastIndex);

    sf::Vector2i westIndex = currentPos;
    westIndex.x -= 1;
    TerrainTile* westTile = world.terrainAtCartesianPos(westIndex);

    //Since a connection does not specify whether the tile on the other end is a terrain tile or
    //another bridge, we will use dynamic cast to find that out for us.

    if(northernConnection){
        Bridge* n = dynamic_cast<Bridge*>(northTile);

        if(n != nullptr){
            n->southernConnection = false;
        }
    }
    if(southernConnection){
        Bridge* s = dynamic_cast<Bridge*>(southTile);

        if(s != nullptr){
            s->northernConnection = false;
        }
    }
    if(easternConnection){
        Bridge* e = dynamic_cast<Bridge*>(eastTile);

        if(e != nullptr){
            e->westernConnection = false;
        }
    }
    if(westernConnection){
        Bridge* w = dynamic_cast<Bridge*>(westTile);

        if(w != nullptr){
            w->easternConnection = false;
        }
    }

}
