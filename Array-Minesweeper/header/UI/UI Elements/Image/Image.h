#ifndef IMAGE_H
#define IMAGE_H

#include <SFML/Graphics.hpp>
#include <string>

namespace UI {
    namespace UIElement {

        class Image {
        private:
            sf::Texture texture;
            sf::Sprite sprite;

        public:
            Image() = default;
            ~Image() = default;

            void Initialize(const std::string& texturePath, float width, float height, const sf::Vector2f& position);
            void Render(sf::RenderWindow& window);
            void SetTextureRect(const sf::IntRect& rect);
            void SetPosition(const sf::Vector2f& position);
            void SetScale(float width, float height);
            sf::FloatRect GetGlobalBounds() const;
        };

    }
}

#endif // IMAGE_H
