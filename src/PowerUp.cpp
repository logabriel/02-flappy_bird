#include <Settings.hpp>
#include <src/PowerUp.hpp>

PowerUp::PowerUp(float _x, float _y) noexcept
    : x{_x}, y{_y}, width{Settings::BERRIE_WIDTH}, height{Settings::BERRIE_HEIGHT}, sprite{Settings::textures["berrie"]}, consumed{false}
{
    sprite.setPosition(x, y);
}

bool PowerUp::collides(const sf::FloatRect& rect) const noexcept
{
    return get_collision_rect().intersects(rect);
}

sf::FloatRect PowerUp::get_collision_rect() const noexcept
{
    return sf::FloatRect{x, y, width, height};
}

void PowerUp::reset(float _x, float _y) noexcept
{
    x = _x;
    y = _y;
}

bool PowerUp::is_out_of_game() const noexcept
{
    return (x + Settings::BERRIE_WIDTH) < 0;
}

void PowerUp::update(float dt) noexcept
{
    x += -Settings::MAIN_SCROLL_SPEED * dt;
    sprite.setPosition(x, y);
}

void PowerUp::render(sf::RenderTarget& target) const noexcept
{
    if(!consumed)
        target.draw(sprite);
}

void PowerUp::disappear() noexcept
{
    consumed = true;
}

void PowerUp::reset() noexcept
{
    consumed = false;
}
