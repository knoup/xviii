#pragma once

class FontManager
{
public:
	enum Type{Lucon, Arial, Eighteen};
	FontManager();

	const sf::Font& getFont(Type _type) const;
private:
	sf::Font lucon;
	sf::Font arial;
	sf::Font eighteen;
};

