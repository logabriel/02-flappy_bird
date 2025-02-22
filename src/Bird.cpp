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
    : x{_x}, y{_y}, width{w}, height{h}, vy{0.f}, sprite{Settings::textures["bird"]}, intangible{false}
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

    if (intangible)
    {   
        if(timer_intangible >= Settings::power_up_duration) 
        {
            deactivate_power_up();
            timer_intangible = 0.f;
        }
        timer_intangible += dt;
    }
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

void Bird::activate_power_up() noexcept
{
    intangible = true;
    sprite.setTexture(Settings::textures["bird_ghost"]);
}

void Bird::deactivate_power_up() noexcept
{
    intangible = false;
    Settings::music_power_up.stop();
    Settings::music.play();
    sprite.setTexture(Settings::textures["bird"]);
}

bool Bird::get_intangible() const noexcept
{
    return intangible;
}