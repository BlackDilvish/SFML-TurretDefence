#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


class Animation
{
    public:
        Animation(char *path,size_t numberOfFrames,sf::Vector2f sizeOfFrame,sf::Vector2f sizeOfPlayer,float cooldown,bool repeatFlag);
        virtual ~Animation();

        void update(float time);
        void setPosition(sf::Vector2f pos);
        void setScale(sf::Vector2f scale);
        void render(sf::RenderTarget &window);

        bool isEnabled;
        bool isRecurrent;

    protected:

    private:
        std::vector<sf::IntRect> frames;
        sf::RectangleShape animation;
        sf::Texture framesPic;

        float speed;
        float timer;
        size_t currentFrame;
};

#endif // ANIMATION_H
