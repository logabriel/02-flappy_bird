/*
    ISPPV1 2023
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the definition of the class Bird.
*/

#include <Settings.hpp>
#include <src/Bird.hpp>

Bird::Bird(float _x, float _y, float w, float h) noexcept
    : x{_x}, y{_y}, width{w}, height{h}, vy{0.f}, sprite{Settings::textures["bird"]}
{
    sprite.setPosition(x, y);
}

sf::FloatRect Bird::get_collision_rect() const noexcept
{
    return sf::FloatRect{x, y, width, height};
}

void Bird::jump() noexcept
{
    if (!jumping)
    {
        jumping = true;
    }
}

void Bird::update(float dt) noexcept
{
    moving(dt);
}

void Bird::render(sf::RenderTarget& target) const noexcept
{
    target.draw(sprite);
}

void Bird::add_point() noexcept 
{
    score++;
}

int Bird::get_score() const noexcept
{
    return score;
}

void Bird::move_right() noexcept
{
    vx = Settings::BIRD_SPEED_X;
}

void Bird::move_left() noexcept
{
    vx = -Settings::BIRD_SPEED_X;
}

void Bird::stop_move() noexcept
{
    vx = 0.f;
}

void Bird::moving(float dt) noexcept
{
    vy += Settings::GRAVITY * dt;

    if (jumping)
    {
        Settings::sounds["jump"].play();
        vy = -Settings::JUMP_TAKEOFF_SPEED;
        jumping = false;
    }

    y += vy * dt;
    x += vx * dt;

    sprite.setPosition(x, y);
}