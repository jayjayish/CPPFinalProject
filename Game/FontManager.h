#pragma once
class FontManager
{
private:
	static sf::Font m_Font;
public:
	void Initialize();
	sf::Font GetFont();
};

