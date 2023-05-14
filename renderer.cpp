#include "renderer.h"

const float timeStep = 0.001f;

const float n = 0.05;
const float h = 0.45;
const float r = 0.1;
const float offset_y = 200;

void render(sf::RenderWindow* window, Level* level) {

    sf::View view = window->getDefaultView();

    while (window->isOpen())
    {
        sf::Event event{};
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window->close();
        }
        window->clear(sf::Color::White);

        for (GameObject* object : *level->objects) {
            object->update();
            window->draw(*object->shape);
            window->draw(*object->animator->sprite);
        }
        window->setView(view);
        window->display();

        movePlayerCamera(view, level->player, window);

        level->world->Step(timeStep * 100, 10, 10);
        std::this_thread::sleep_for(std::chrono::milliseconds((long long)(timeStep * 1000)));
    }
}

void movePlayerCamera(sf::View &view, Player *player, sf::Window *window) {
    b2Vec2 pos = player->body->GetPosition();
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
    float x = ((mousePos.x - window->getSize().x * 0.5f) * h + pos.x * zoom - view.getCenter().x);
    float y = ((mousePos.y - window->getSize().y * 0.5f) * h + pos.y * zoom - offset_y - view.getCenter().y);
    view.move(pow(x * n * r, 3), y * n);
}