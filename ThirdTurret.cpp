#ifndef THIRDTURRET_H
#define THIRDTURRET_H

#include"Turret.h"

class ThirdTurret : public Turret
{
    public:
        ThirdTurret(size_t gridID,std::vector<sf::RectangleShape> &gridsVector) : Turret(gridID,gridsVector)
        {
            shootCooldown=30;
            shootRange=300.0;
            rangeShape.setRadius(shootRange);
            rangeShape.setOrigin(sf::Vector2f(rangeShape.getRadius(),rangeShape.getRadius()));
            upgradeCost[0] = 400;
            upgradeCost[1] = 500;
        }

        ~ThirdTurret(){}

};

#endif // ThirdTURRET_H

