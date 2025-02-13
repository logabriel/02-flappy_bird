/*
    ISPPV1 2023
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the declaration of the class LogPair.
*/

#pragma once

#include <memory>

#include <src/Bird.hpp>
#include <src/Log.hpp>
#include <src/StaticLog.hpp>
#include <src/MovingLog.hpp>

class LogPair
{
public:
    LogPair(float _x, float _y, std::shared_ptr<Log> _top, std::shared_ptr<Log> _bottom) noexcept;

    bool collides(const sf::FloatRect& rect) const noexcept;

    void update(float dt) noexcept;

    void render(sf::RenderTarget& target) const noexcept;

    bool is_out_of_game() const noexcept;

    bool update_scored(const sf::FloatRect& rect) noexcept;

    void reset(float _x, float _y, std::shared_ptr<Log> _top, std::shared_ptr<Log> _bottom) noexcept;

    void move_limiter() noexcept;

    bool is_gap_closed() const noexcept;
private:
    float x;
    float y;
    std::shared_ptr<Log> top;
    std::shared_ptr<Log> bottom;

    bool scored{false};
};