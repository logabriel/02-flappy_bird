#pragma once

#include <SFML/Graphics.hpp>

class PowerUp
{
public:
    PowerUp(float _x, float _y) noexcept;

    bool collides(const sf::FloatRect& rect) const noexcept;

    bool is_out_of_game() const noexcept;

    sf::FloatRect get_collision_rect() const noexcept;

    void reset(float _x, float _y) noexcept;

    void update(float dt) noexcept;

    void render(sf::RenderTarget& target) const noexcept;

    void disappear() noexcept;

    void reset() noexcept;

private:
    float x;
    float y;
    float width;
    float height;
    sf::Sprite sprite;
    bool consumed;
};