/*
    ISPPV1 2023
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the definition of the class World.
*/

#include <Settings.hpp>
#include <src/World.hpp>

World::World(bool _generate_logs) noexcept
    : generate_logs{_generate_logs}, background{Settings::textures["background"]}, ground{Settings::textures["ground"]},
      logs{}, rng{std::default_random_engine{}()}
{
    ground.setPosition(0, Settings::VIRTUAL_HEIGHT - Settings::GROUND_HEIGHT);
    std::uniform_int_distribution<int> dist(0, 80);
    last_log_y = -Settings::LOG_HEIGHT + dist(rng) + 20;
}

void World::reset(bool _generate_logs) noexcept
{
    generate_logs = _generate_logs;

    for (auto log_pair: logs)
    {
        log_factory.remove(log_pair);
    }
    logs.clear();

    for (auto power_up: power_ups)
    {
        power_up_factory.remove(power_up);
    }
    power_ups.clear();
}

bool World::collides(const sf::FloatRect& rect) const noexcept
{
    if (rect.top + rect.height >= Settings::VIRTUAL_HEIGHT)
    {
        return true;
    }
    
    for (auto log_pair: logs)
    {
        if (log_pair->collides(rect))
        {
            return true;
        }
    }

    return false;
}

bool World::update_scored(const sf::FloatRect& rect) noexcept
{
    for (auto log_pair: logs)
    {
        if (log_pair->update_scored(rect))
        {
            return true;
        }
    }

    return false;
}

void World::update(float dt) noexcept
{
    if (generate_logs)
    {
        logs_spawn_timer += dt;

        if (logs_spawn_timer >= game_mode->get_timer_spawn_log())
        {
            game_mode->spawn_entity(logs_spawn_timer, rng, last_log_y, logs, log_factory, power_up_factory, power_ups);
        }
    }   

    background_x += -Settings::BACK_SCROLL_SPEED * dt;

    if (background_x <= -Settings::BACKGROUND_LOOPING_POINT)
    {
        background_x = 0;
    }

    background.setPosition(background_x, 0);

    ground_x += -Settings::MAIN_SCROLL_SPEED * dt;

    if (ground_x <= -Settings::VIRTUAL_WIDTH)
    {
        ground_x = 0;
    }

    ground.setPosition(ground_x, Settings::VIRTUAL_HEIGHT - Settings::GROUND_HEIGHT);

    for (auto it = logs.begin(); it != logs.end(); )
    {
        if ((*it)->is_out_of_game())
        {
            auto log_pair = *it;
            log_factory.remove(log_pair);
            it = logs.erase(it);
            
        }
        else
        {
            (*it)->update(dt);
            ++it;
        }
    }

    for (auto it = power_ups.begin(); it != power_ups.end(); )
    {
        if ((*it)->is_out_of_game())
        {
            auto power_up = *it;
            power_up->reset();
            power_up_factory.remove(power_up);
            it = power_ups.erase(it);
        }
        else
        {
            (*it)->update(dt);
            ++it;
        }
    }
}

void World::render(sf::RenderTarget& target) const noexcept
{
    target.draw(background);

    for (const auto& log_pair: logs)
    {
        log_pair->render(target);
    }
    
    if (!power_ups.empty()) 
    {
        for (const auto& power_up: power_ups)
        {
            power_up->render(target);
        }
    }
    
    target.draw(ground);
}

void World::set_game_mode(std::shared_ptr<BaseStrategy> _game_mode) noexcept
{
    if (game_mode == nullptr)
    {
        game_mode = _game_mode;
    }
}

bool World::activate_power_up(const sf::FloatRect& rect) noexcept
{
    for (auto power_up: power_ups)
    {
        if (power_up->collides(rect))
        {
            power_up->disappear();
            power_up_factory.remove(power_up);
            return true;
        }
    }

    return false;
}