#ifndef Text_fast_h
#define Text_fast_h
#include <SFML/Graphics.hpp>
#include "v2f.h"
class Text_fast {
public:
    Text_fast(const std::string& str = "", const sf::Font& font = sf::Font(), unsigned int size = 30)
        : m_text(str, font, size) {}

    void setString(const std::string& str) { m_text.setString(str); }
    void setFont(const sf::Font& font) { m_text.setFont(font); }
    void setCharacterSize(unsigned int size) { m_text.setCharacterSize(size); }
    void setPosition(float x, float y) { m_text.setPosition(x, y); }
    void setPosition(v2f xy) { m_text.setPosition(xy.x, xy.y); }
    void setFillColor(const sf::Color& color) { m_text.setFillColor(color); }
    void setOutlineColor(const sf::Color& color) { m_text.setOutlineColor(color); }
    void setOutlineThickness(float thickness) { m_text.setOutlineThickness(thickness); }

    const std::string& getString() const { return m_text.getString(); }
    const sf::Font* getFont() const { return m_text.getFont(); }
    unsigned int getCharacterSize() const { return m_text.getCharacterSize(); }
    const sf::Vector2f& getPosition() const { return m_text.getPosition(); }
    const sf::Color& getFillColor() const { return m_text.getFillColor(); }
    const sf::Color& getOutlineColor() const { return m_text.getOutlineColor(); }
    float getOutlineThickness() const { return m_text.getOutlineThickness(); }

    sf::FloatRect getGlobalBounds() const { return m_text.getGlobalBounds(); }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(m_text, states); }

private:
    sf::Text m_text;
};
#endif