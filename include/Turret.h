#ifndef TURRET_H
#define TURRET_H

#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include<math.h>
#include"Enemy.h"

class Turret
{
    public:
        Turret(size_t gridID,std::vector<sf::RectangleShape> &gridsVector);
        virtual ~Turret() = default;

        void update(std::vector<Enemy> &enemiesVector);
        void upgrade();
        void render(sf::RenderTarget &window);

        double vectorLength(const sf::Vector2f &vec);
        void setTexture(sf::Texture *texture);

        enum Prices{first=100, second=250, third=600, fourth=1000};

        sf::RectangleShape shape;

        sf::CircleShape rangeShape;
        bool drawRange;
        bool drawTemp;

        struct Bullet
        {
            sf::RectangleShape bulletShape;
            size_t focusedEnemy;
        }tempBullet;

        std::vector<Bullet> bullets;
        int shootCooldown;
        int shootTimer;
        double shootRange;
        float bulletSpeed;

        int upgradeStage;
        int upgradeCost[2];



};

#endif // TURRET_H
