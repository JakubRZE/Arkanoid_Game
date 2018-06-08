#include "ResourceManager.h"

//Textures

void ResourceManager::LoadTexture(std::string name, std::string filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	if (!texture->loadFromFile(filename))
	{
		throw std::runtime_error("ResourceManager::LoadTexture - Failed to load " + filename);
	}

	TextureMap.insert(std::make_pair(name, std::move(texture)));
}

sf::Texture &ResourceManager::GetTexture(std::string name)
{
	auto found = TextureMap.find(name);
	return *found->second;
}

const sf::Texture &ResourceManager::GetTexture(std::string name) const
{
	auto found = TextureMap.find(name);
	return *found->second;
}

// Fonts

void ResourceManager::LoadFont(std::string name, std::string filename)
{
	std::unique_ptr<sf::Font> font(new sf::Font());
	if (!font->loadFromFile(filename))
	{
		throw std::runtime_error("ResourceManager::LoadFont - Failed to load " + filename);
	}

	FontMap.insert(std::make_pair(name, std::move(font)));
}

sf::Font &ResourceManager::GetFont(std::string name)
{
	auto found = FontMap.find(name);
	return *found->second;
}

const sf::Font &ResourceManager::GetFont(std::string name) const
{
	auto found = FontMap.find(name);
	return *found->second;
}

// Audio

void ResourceManager::LoadAudio(std::string name, std::string filename)
{
	std::unique_ptr<sf::SoundBuffer> audio(new sf::SoundBuffer());
	if (!audio->loadFromFile(filename))
	{
		throw std::runtime_error("ResourceManager::LoadAudio - Failed to load " + filename);
	}

	soundBufferMap.emplace(std::make_pair(name, std::move(audio)));

	std::unique_ptr<sf::Sound> sound = std::make_unique<sf::Sound>
		(std::move(*soundBufferMap[name]));

	AudioMap.emplace(std::make_pair(name, std::move(sound)));
}

void ResourceManager::Play(const std::string name)
{
	auto found = AudioMap.find(name);

	if (found == AudioMap.end())
	{ 
		throw std::runtime_error("empty sound vec");
	}

	found->second->play();
}