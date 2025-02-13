#include <Settings.hpp>
#include <src/text_utilities.hpp>
#include <src/states/StateMachine.hpp>
#include <src/states/PlayingState.hpp>
#include <src/strategy/HardMode.hpp>

HardMode::HardMode(StateMachine* sm, std::shared_ptr<World> _world, std::shared_ptr<Bird> _bird) noexcept
    : BaseStrategy{sm}
{
    world = _world;
    bird = _bird;
}

void HardMode::handle_inputs(const sf::Event& event) noexcept
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        bird->jump();
    } 
    else if (event.type == sf::Event::KeyPressed &&  sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        state_machine->change_state("pause", world, bird); //pauso el juego
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
    {
        bird->move_left();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
    {
        bird->move_right();
    }
    else if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left)) 
    {
        bird->stop_move();
    }
}

void HardMode::update(float dt) noexcept
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

void HardMode::render(sf::RenderTarget& target) const noexcept
{
    world->render(target);
    bird->render(target);
    render_text(target, 20, 10, "Score: " + std::to_string(bird->get_score()), Settings::FLAPPY_TEXT_SIZE, "flappy", sf::Color::White);
}

void HardMode::spawn_entity(float& logs_spawn_timer, std::mt19937 &rng, float &last_log_y, std::list<std::shared_ptr<LogPair>>& logs, Factory<LogPair>& log_factory) noexcept
{
    logs_spawn_timer = 0.f;

    std::uniform_real_distribution<float> dist_timer{1.f, 2.f};
    timer_spawn_log = dist_timer(rng);

    std::uniform_int_distribution<int> dist{-20, 20};
    float y = std::max(-Settings::LOG_HEIGHT + 10, std::min(last_log_y + dist(rng), Settings::VIRTUAL_HEIGHT + 90 - Settings::LOG_HEIGHT));
    last_log_y = y;

    std::uniform_int_distribution<int> dist_gap{56, 90};
    std::shared_ptr<Log> _top;
    std::shared_ptr<Log> _bottom;

    if (dist(rng) % 2 == 0) 
    {
        _top = std::make_shared<MovingLog>((float)Settings::VIRTUAL_WIDTH, y + Settings::LOG_HEIGHT, true);
        _bottom = std::make_shared<MovingLog>((float)Settings::VIRTUAL_WIDTH, y + (float)dist_gap(rng) + Settings::LOG_HEIGHT, false);
    }
    else 
    {
        _top = std::make_shared<StaticLog>((float)Settings::VIRTUAL_WIDTH, y + Settings::LOG_HEIGHT, true);
        _bottom = std::make_shared<StaticLog>((float)Settings::VIRTUAL_WIDTH, y + (float)dist_gap(rng) + Settings::LOG_HEIGHT, false);
    }

    logs.push_back(log_factory.create((float)Settings::VIRTUAL_WIDTH, y, _top, _bottom));
}

float HardMode::get_timer_spawn_log() noexcept
{
    return timer_spawn_log;
}