#include "renderer.h"

const float n = 0.05;
const float h = 0.45;
const float r = 0.1;
const float offset_y = 200;

void render(Level* level) {

    while (level->window->isOpen())
    {
        sf::Event event{};
        while (level->window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                level->window->close();
        }
        level->window->clear(sf::Color::White);

        for (PhysicalObject* object : *level->objects) {
            object->update();
            level->window->draw(*object->shape);
            level->window->draw(*object->animator->sprite);
        }

        level->update();

        level->window->setView(*level->view);

        level->window->display();

        movePlayerCamera(*level->view, *level->player, *level->window);
    }
}

void movePlayerCamera(sf::View& view, Player& player, sf::Window& window) {
    b2Vec2 pos = player.body->GetPosition();
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    float x = ((mousePos.x - window.getSize().x * 0.5f) * h + pos.x * zoom - view.getCenter().x);
    float y = ((mousePos.y - window.getSize().y * 0.5f) * h + pos.y * zoom - offset_y - view.getCenter().y);
    view.move(pow(x * n * r, 3), y * n * 0.6);
}