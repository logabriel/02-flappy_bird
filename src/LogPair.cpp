/*
    ISPPV1 2023
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the definition of the class LogPair.
*/

#include <Settings.hpp>
#include <src/Log.hpp>
#include <src/LogPair.hpp>

/*top{x, y + Settings::LOG_HEIGHT, true},
      bottom{x, y + Settings::LOGS_GAP + Settings::LOG_HEIGHT, false}*/

LogPair::LogPair(float _x, float _y, std::shared_ptr<Log> _top, std::shared_ptr<Log> _bottom) noexcept
    : x{_x}, y{_y},
    top{_top},
    bottom{_bottom}
{
    
}

bool LogPair::collides(const sf::FloatRect& rect) const noexcept
{
    return top->get_collision_rect().intersects(rect) || bottom->get_collision_rect().intersects(rect);
}

void LogPair::update(float dt) noexcept
{
    x += -Settings::MAIN_SCROLL_SPEED * dt;
    
    move_limiter();
    
    const float top_dy = top->speed_y() * dt;
    const float bottom_dy = bottom->speed_y() * dt;
    
    top->update(x, top_dy);
    bottom->update(x, bottom_dy);
}

void LogPair::render(sf::RenderTarget& target) const noexcept
{
    top->render(target);
    bottom->render(target);
}

bool LogPair::is_out_of_game() const noexcept
{
    return x < -Settings::LOG_WIDTH;
}

bool LogPair::update_scored(const sf::FloatRect& rect) noexcept
{
    if (scored)
    {
        return false;
    }

    if (rect.left > x + Settings::LOG_WIDTH)
    {
        scored = true;
        return true;
    }

    return false;
}

void LogPair::reset(float _x, float _y, std::shared_ptr<Log> _top, std::shared_ptr<Log> _bottom) noexcept
{
    x = _x;
    y = _y;
    top = _top;
    bottom = _bottom;
    scored = false;
}

void LogPair::move_limiter() noexcept
{
    bool IsGapClosed = is_gap_closed();
    
    if(IsGapClosed || top->is_at_initial_y())
        top->change_direction();
    if(IsGapClosed || bottom->is_at_initial_y())
        bottom->change_direction();

    if (IsGapClosed)
    {
        Settings::sounds["wood_crash"].stop();
        Settings::sounds["wood_crash"].play();
    }
}

bool LogPair::is_gap_closed() const noexcept
{
    return top->get_collision_rect().intersects(bottom->get_collision_rect());
}