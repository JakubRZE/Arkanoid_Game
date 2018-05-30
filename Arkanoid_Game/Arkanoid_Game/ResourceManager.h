#pragma once

#include<map>
#include<memory>
#include<SFML\Graphics.hpp>


class ResourceManager
{
public:
	ResourceManager() {}
	~ResourceManager() {}

	void LoadTexture(std::string name, std::string fileName);
	sf::Texture& GetTexture(std::string name);
	const sf::Texture& GetTexture(std::string name) const;

	void LoadFont(std::string name, std::string fileName);
	sf::Font& GetFont(std::string name);
	const sf::Font& GetFont(std::string name) const;


private:
	std::map<std::string, std::unique_ptr<sf::Texture>> TextureMap;
	std::map<std::string, std::unique_ptr<sf::Font>> FontMap;
};
