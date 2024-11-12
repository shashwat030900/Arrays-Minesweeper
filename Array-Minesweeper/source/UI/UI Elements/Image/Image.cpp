#include "../../header/UI/UI Elements/Image/Image.h"
#include <iostream>

namespace UI {
    namespace UIElement {

        void Image::Initialize(const std::string& texturePath, float width, float height, const sf::Vector2f& position) {
            if (!texture.loadFromFile(texturePath)) {
                std::cerr << "Failed to load image texture: " << texturePath << std::endl;
            }
            sprite.setTexture(texture);
            sprite.setPosition(position);
            SetScale(width, height);
        }

        void Image::Render(sf::RenderWindow& window) {
            window.draw(sprite);
        }

        void Image::SetTextureRect(const sf::IntRect& rect) {
            sprite.setTextureRect(rect);
        }

        void Image::SetPosition(const sf::Vector2f& position) {
            sprite.setPosition(position);
        }

        void Image::SetScale(float width, float height) {
            float scale_x = width / texture.getSize().x;
            float scale_y = height / texture.getSize().y;
            sprite.setScale(scale_x, scale_y);
        }

        sf::FloatRect Image::GetGlobalBounds() const {
            return sprite.getGlobalBounds();
        }

    }
}
