/*
    ISPPV1 2023
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the declaration of the class Bird.
*/

#pragma once

#include <SFML/Graphics.hpp>

class Bird
{
public:
    Bird(float _x, float _y, float w, float h) noexcept;

    Bird(const Bird&) = delete;

    Bird& operator = (Bird) = delete;

    sf::FloatRect get_collision_rect() const noexcept;

    void jump() noexcept;

    void update(float dt) noexcept;

    void render(sf::RenderTarget& target) const noexcept;
    
    void add_point() noexcept;

    int get_score() const noexcept;

    void move_right() noexcept;

    void move_left() noexcept;

    void stop_move() noexcept;

    void moving(float dt) noexcept;

    void activate_power_up() noexcept;

    void deactivate_power_up() noexcept;

    bool get_intangible() const noexcept;
    
private:
    float x;
    float y;
    float width;
    float height;
    float vy;
    float vx; 
    bool jumping{false};
    int score{0}; 
    bool intangible;
    float timer_intangible{0};
    sf::Sprite sprite;
    
};
