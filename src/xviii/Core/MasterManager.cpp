#include "xviii/Headers/stdafx.h"
#include "xviii/Core/MasterManager.h"

#include "xviii/Core/FactionLoader.h"
#include "xviii/Core/UnitLoader.h"
#include "xviii/Core/TerrainLoader.h"

/*
The only warning I was unable to eliminate was the vague "required from here"
warning on line 26. It has something to do with...

xviii\src\xviii\Core\MasterManager.cpp:19:66:   required from here
     BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(mersenne_twister_engine,
                                                ^
     explicit Self(const T& x)
*/

MasterManager::MasterManager():
randevice{},
randomEngine{randevice()},
mapSeedEngine{randevice()},
fontManager{std::unique_ptr<FontManager>(new FontManager())},
textureManager{std::unique_ptr<TextureManager>(new TextureManager(randomEngine))},
factionLoader{std::unique_ptr<FactionLoader>(new FactionLoader(*(textureManager.get())))},
unitLoader{std::unique_ptr<UnitLoader>(new UnitLoader(*(textureManager.get())))},
terrainLoader{std::unique_ptr<TerrainLoader>(new TerrainLoader())}
{
}

MasterManager::~MasterManager()
{
}
