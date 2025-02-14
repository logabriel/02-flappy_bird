#include <Settings.hpp>
#include <src/text_utilities.hpp>
#include <src/states/StateMachine.hpp>
#include <src/states/PlayingState.hpp>
#include <src/strategy/NormalMode.hpp>

NormalMode::NormalMode(StateMachine* sm, std::shared_ptr<World> _world, std::shared_ptr<Bird> _bird) noexcept
    : BaseStrategy{sm}
{
    world = _world;
    bird = _bird;
}

void NormalMode::handle_inputs(const sf::Event& event) noexcept
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        bird->jump();
    } 
    else if (event.type == sf::Event::KeyPressed &&  sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        state_machine->change_state("pause", world, bird); //pauso el juego
    }
}

void NormalMode::update(float dt) noexcept
{
    bird->update(dt);
    world->update(dt);

    if (world->collides(bird->get_collision_rect()))
    {
        Settings::sounds["explosion"].play();
        Settings::sounds["hurt"].play();
        state_machine->change_state("count_down");
    }

    if (world->update_scored(bird->get_collision_rect()))
    {
        bird->add_point();
        Settings::sounds["score"].play();
    }
}

void NormalMode::render(sf::RenderTarget& target) const noexcept
{
    world->render(target);
    bird->render(target);
    render_text(target, 20, 10, "Score: " + std::to_string(bird->get_score()), Settings::FLAPPY_TEXT_SIZE, "flappy", sf::Color::White);
}

void NormalMode::spawn_entity(float& logs_spawn_timer, std::mt19937 &rng, float &last_log_y, std::list<std::shared_ptr<LogPair>>& logs, Factory<LogPair>& log_factory, Factory<PowerUp>& power_up_factory, std::list<std::shared_ptr<PowerUp> >& power_ups) noexcept
{
    logs_spawn_timer = 0.f;

    std::uniform_int_distribution<int> dist{-20, 20};
    
    float y = std::max(-Settings::LOG_HEIGHT + 10, std::min(last_log_y + dist(rng), Settings::VIRTUAL_HEIGHT + 90 - Settings::LOG_HEIGHT));
    
    last_log_y = y;

    std::shared_ptr<Log> _top = std::make_shared<StaticLog>((float)Settings::VIRTUAL_WIDTH, y + Settings::LOG_HEIGHT, true);
    std::shared_ptr<Log> _bottom = std::make_shared<StaticLog>((float)Settings::VIRTUAL_WIDTH, y + Settings::LOGS_GAP + Settings::LOG_HEIGHT, false);
    
    logs.push_back(log_factory.create((float)Settings::VIRTUAL_WIDTH, y, _top, _bottom));
}

float NormalMode::get_timer_spawn_log() noexcept 
{
    return Settings::TIME_TO_SPAWN_LOGS;
}