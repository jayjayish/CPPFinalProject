#include "Precompiled.h"
#include "FontManager.h"

sf::Font FontManager::m_Font = sf::Font();

void FontManager::Initialize()
{

}

sf::Font FontManager::GetFont()
{
	return m_Font;
}
