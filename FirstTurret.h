#ifndef FIRSTTURRET_H
#define FIRSTTURRET_H

#include"Turret.h"

class FirstTurret : public Turret
{
    public:
        FirstTurret(size_t gridID,std::vector<sf::RectangleShape> &gridsVector) : Turret(gridID,gridsVector)
        {
            shootCooldown=60;
            shootRange=200.0;
            rangeShape.setRadius(shootRange);
            rangeShape.setOrigin(sf::Vector2f(rangeShape.getRadius(),rangeShape.getRadius()));
            upgradeCost[0] = 100;
            upgradeCost[1] = 200;

        }


        ~FirstTurret(){}



};

#endif // FIRSTTURRET_H
