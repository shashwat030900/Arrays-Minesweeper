#ifndef IMAGE_H
#define IMAGE_H

#include <SFML/Graphics.hpp>
#include <string>

class Image {
private:
    sf::Texture texture;
    sf::Sprite sprite;

public:
    Image() = default;
    ~Image() = default;

    bool Initialize(const std::string& texturePath, float width, float height, const sf::Vector2f& position);
    void Render(sf::RenderWindow& window);
    void SetTextureRect(const sf::IntRect& rect);
    void SetPosition(const sf::Vector2f& position);
    void SetScale(float width, float height);
    void SetImageAlpha(float alpha);
    sf::FloatRect GetGlobalBounds() const;
    void SetCentreAlinged(const sf::RenderWindow& window);
};

#endif // IMAGE_H
