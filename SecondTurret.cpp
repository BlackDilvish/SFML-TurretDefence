#ifndef SECONDTURRET_H
#define SECONDTURRET_H

#include"Turret.h"

class SecondTurret : public Turret
{
    public:
        SecondTurret(size_t gridID,std::vector<sf::RectangleShape> &gridsVector) : Turret(gridID,gridsVector)
        {
            shootCooldown=30;
            shootRange=150.0;
            rangeShape.setRadius(shootRange);
            rangeShape.setOrigin(sf::Vector2f(rangeShape.getRadius(),rangeShape.getRadius()));
            upgradeCost[0] = 200;
            upgradeCost[1] = 300;
        }

        ~SecondTurret(){}

};

#endif // SecondTURRET_H

