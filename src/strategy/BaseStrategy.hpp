/*
    Assignment: Flappy Bird

    This file contains the declaration of the class BaseStrategy.
*/

#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

class StateMachine;
class World;
class Bird;

class BaseStrategy
{
public:
    BaseStrategy(StateMachine* sm) : state_machine(sm) {}

    virtual ~BaseStrategy() {}

    virtual void handle_inputs(const sf::Event& event) noexcept {}

    virtual void update(float dt) noexcept {}

    virtual void render(sf::RenderTarget& target) const noexcept {}

    virtual void spawn_entity(float &logs_spawn_timer, std::mt19937 &rng, float &last_log_y, std::list<std::shared_ptr<LogPair>> &logs, Factory<LogPair> &log_factory, Factory<PowerUp> &power_up_factory, std::list<std::shared_ptr<PowerUp> > &power_ups) noexcept {}

    virtual float get_timer_spawn_log() noexcept {return 0.f;}
protected:
    StateMachine* state_machine;
    std::shared_ptr<Bird> bird;
    std::shared_ptr<World> world;
};

