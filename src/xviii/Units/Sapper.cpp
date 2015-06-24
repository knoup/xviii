#include "xviii/Headers/stdafx.h"
#include "xviii/Units/Sapper.h"

#include "xviii/Terrain/TerrainTile.h"

Sapper::Sapper(UnitLoader& _unitLoader, World& _world, boost::random::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& _tm, FontManager& _fm, TextureManager::Unit _texture, std::string _name, UnitType _type, UnitFamily _familyType, Direction _dir) :
Infantry(_unitLoader, _world, _mt19937, _belongsToPlayer, _tm, _fm, _texture, _name, _type, _familyType, _dir)
{
}
