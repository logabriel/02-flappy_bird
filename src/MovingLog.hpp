#pragma once

#include<src/Log.hpp>

class MovingLog: public Log
{
public:
    MovingLog(float _x, float _y, bool _inverted) noexcept;

    void update(float _x, float _y) noexcept override;

    void change_direction() noexcept override;

    float speed_y() const noexcept override;

    bool is_at_initial_y() const noexcept override;

private:
    float Yspeed;
    float initialY;
};
