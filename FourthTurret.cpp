#ifndef FOURTHTURRET_H
#define FOURTHTURRET_H

#include"Turret.h"

class FourthTurret : public Turret
{
    public:
        FourthTurret(size_t gridID,std::vector<sf::RectangleShape> &gridsVector) : Turret(gridID,gridsVector)
        {
            shootCooldown=15;
            shootRange=400.0;
            rangeShape.setRadius(shootRange);
            rangeShape.setOrigin(sf::Vector2f(rangeShape.getRadius(),rangeShape.getRadius()));
            upgradeCost[0] = 700;
            upgradeCost[1] = 1000;
        }

        ~FourthTurret(){}

};

#endif // FourthTURRET_H


