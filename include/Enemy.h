#ifndef ENEMY_H
#define ENEMY_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<sstream>
#include "Animation.h"

class Enemy
{
    public:
        Enemy(std::vector<sf::RectangleShape> &gridsVector,std::vector<int> &gridsTypeVector,int b_HP,int b_PRIZE);
        virtual ~Enemy();

        void update(std::vector<sf::RectangleShape> &gridsVector,std::vector<int> &gridsTypeVector,size_t rows,size_t collumns);
        void render(sf::RenderTarget &window);

        bool isInBase();
        bool isAlive();
        sf::Vector2f getPosition();
        sf::Vector2f getSize();
        sf::FloatRect getGlobalBounds();
        int getHP();
        void setBaseHP(int newHP);
        void setHP(int newHP);
        int getPrize();
        void setPrize(int newPrize);
        void setTexture(const sf::Texture *texture);
        void initText(sf::Font &font);

    private:

        sf::RectangleShape shape;
        sf::Texture enemyTex;

        sf::Vector2i velocity;
        int maxSpeed;

        size_t currentGrid;
        size_t baseGrid;
        int prize;
        bool inBase;
        bool alive;

        sf::RectangleShape redHealthBar;
        sf::RectangleShape greenHealthBar;
        int maxhealthPoints;
        int currenthealthPoints;

        sf::Text HPtext;

};

#endif // ENEMY_H
