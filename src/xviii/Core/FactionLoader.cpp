#include "xviii/Headers/stdafx.h"
#include "xviii/Core/FactionLoader.h"

FactionLoader::FactionLoader(TextureManager& _tm) :
tm(_tm)
{
    load();
}

void FactionLoader::load(){
	boost::filesystem::recursive_directory_iterator end;

	for (boost::filesystem::recursive_directory_iterator it("assets/factions"); it != end; ++it){
		parse(it->path());
	}
}

void FactionLoader::parse(boost::filesystem::path path){
	//Create a new FactionClassData; initialise its name as "temp" while we get it from the file itself
	std::unique_ptr<FactionClassData> newClass = std::move(std::unique_ptr<FactionClassData>(new FactionClassData("temp", path)));

	std::ifstream factionData;
	factionData.open(path.string());

	std::string currentLine;

	#define AFTERCOLON currentLine.substr(currentLine.find(":") + 1, currentLine.size() - 1)
	#define EXISTS != std::string::npos

	std::getline(factionData, currentLine);
	if (!(currentLine.find("FACTION DEFINITION") EXISTS)){
		return;
	}

	while (factionData && std::getline(factionData, currentLine)){

        if (currentLine.find("NAME:") EXISTS){
			newClass->name = AFTERCOLON;
		}

        else if (currentLine.find("SPRITE:") EXISTS){
			newClass->textureID = AFTERCOLON;
		}

		else if (currentLine.find("LANGUAGE:") EXISTS){
			newClass->languageID = AFTERCOLON;
		}

	}

	customFactions.emplace(newClass->name, std::move(*newClass));

}
