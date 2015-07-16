#pragma once

#include "xviii/Core/FontManager.h"
#include "xviii/Core/TextureManager.h"

class UnitLoader;
class TerrainLoader;

//This class is simply a collection of all the managers and other globally
//required stuff.
//Instead of passing in references to each desired manager to whatever class
//needs it, we can pass just one (this) and access any manager we need.

//TODO: add the mt engine

class MasterManager
{
public:
    //Note: due to a GCC peculiarity, a destructor must be defined (TL;DR) in order for forward
    //declarations involving unique pointers. This should not be happening according to the
    //standard. See here for more information:
    //http://stackoverflow.com/a/25853985

    MasterManager();
    ~MasterManager();

    std::unique_ptr<FontManager> fontManager;
    std::unique_ptr<TextureManager> textureManager;

    //IMPORTANT:
    //Due to the fact that UnitLoader.h and TerrainLoader.h include lots of other headers,
    //they are not included in MasterManager.h by default, to prevent a ton of dependency
    //issues, since MasterManager.h is included in a lot of places. Classes that need to
    //make use of unitLoader or terrainLoader can include their respective class headers
    //as needed and everything will work splendidly.

    std::unique_ptr<UnitLoader> unitLoader;
    std::unique_ptr<TerrainLoader> terrainLoader;
};
