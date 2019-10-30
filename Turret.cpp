#include "Turret.h"

Turret::Turret(size_t gridID,std::vector<sf::RectangleShape> &gridsVector)
{
    shape.setSize(gridsVector[gridID].getSize());
    shape.setPosition(gridsVector[gridID].getPosition());

    tempBullet.bulletShape.setSize(sf::Vector2f(10.f,10.f));
    tempBullet.bulletShape.setFillColor(sf::Color::Red);
    tempBullet.bulletShape.setPosition(sf::Vector2f(shape.getPosition().x+shape.getSize().x/2.f,shape.getPosition().y+shape.getSize().y/2.f));

    shootCooldown=30;
    shootTimer=0;
    shootRange=300.0;
    bulletSpeed=20.f;

    upgradeStage=0;

    rangeShape.setRadius(shootRange);
    rangeShape.setOrigin(sf::Vector2f(rangeShape.getRadius(),rangeShape.getRadius()));
    rangeShape.setFillColor(sf::Color::Transparent);
    rangeShape.setOutlineThickness(3.f);
    rangeShape.setOutlineColor(sf::Color::Red);
    drawRange = false;
    drawTemp = false;
}

Turret::~Turret()
{

}

void Turret::update(std::vector<Enemy> &enemiesVector)
{
    shootTimer+=1;

    for(size_t i=0; i<enemiesVector.size(); i++)
    {
        if(vectorLength(sf::Vector2f(shape.getPosition().x - enemiesVector[i].getPosition().x, shape.getPosition().y - enemiesVector[i].getPosition().y)) < shootRange)
            if(shootTimer > shootCooldown)
            {
                shootTimer=0;
                tempBullet.focusedEnemy=i;
                bullets.push_back(tempBullet);
                break;
            }

        for(size_t j=0; j<bullets.size(); j++)
            if(enemiesVector[i].getGlobalBounds().intersects(bullets[j].bulletShape.getGlobalBounds()))
            {
                enemiesVector[i].setHP(enemiesVector[i].getHP() - 1);
                bullets.erase(bullets.begin() + j);
            }
    }

    for(size_t i=0; i<bullets.size(); i++)
    {
        if(enemiesVector.size() == 0)
            bullets.erase(bullets.begin() + i);

        sf::Vector2f direction=sf::Vector2f(enemiesVector[bullets[i].focusedEnemy].getPosition().x + enemiesVector[bullets[i].focusedEnemy].getSize().x/2.f - bullets[i].bulletShape.getPosition().x, enemiesVector[bullets[i].focusedEnemy].getPosition().y + enemiesVector[bullets[i].focusedEnemy].getSize().y/2.f - bullets[i].bulletShape.getPosition().y);
        double len=vectorLength(direction);

        direction.x/=len;
        direction.x*=bulletSpeed;

        direction.y/=len;
        direction.y*=bulletSpeed;

        bullets[i].bulletShape.move(direction);
    }


}

void Turret::upgrade()
{
    bullets.clear();

    upgradeStage++;
    shootCooldown-=5;
    shootRange+=30.0;
    rangeShape.setRadius(shootRange);
    rangeShape.setOrigin(sf::Vector2f(rangeShape.getRadius(),rangeShape.getRadius()));
}

void Turret::render(sf::RenderTarget &window)
{
    window.draw(shape);

    if(drawRange)
        window.draw(rangeShape);

    for(size_t i=0; i < bullets.size(); i++)
        window.draw(bullets[i].bulletShape);
}

double Turret::vectorLength(const sf::Vector2f &vec)
{
    return sqrt(vec.x*vec.x + vec.y*vec.y);
}

void Turret::setTexture(sf::Texture *texture)
{
    shape.setTexture(texture);
}
