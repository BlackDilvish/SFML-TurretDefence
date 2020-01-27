#include "Enemy.h"

Enemy::Enemy(std::vector<sf::RectangleShape> &gridsVector,std::vector<int> &gridsTypeVector,int b_HP,int b_PRIZE)
{
    size_t spawnPos;
    for(spawnPos=0; spawnPos < gridsTypeVector.size(); spawnPos++)
        if(gridsTypeVector[spawnPos] == 2)
            break;

    for(baseGrid=0; baseGrid < gridsTypeVector.size(); baseGrid++)
        if(gridsTypeVector[baseGrid] == 3)
            break;

    shape.setSize(gridsVector[spawnPos].getSize());
    shape.setPosition(gridsVector[spawnPos].getPosition());

    maxSpeed=2;
    velocity={maxSpeed,0};
    currentGrid=spawnPos;
    inBase=false;
    alive=true;
    prize=b_PRIZE;

    maxhealthPoints=b_HP;
    currenthealthPoints=maxhealthPoints;

    redHealthBar.setSize(sf::Vector2f(shape.getSize().x,10.f));
    redHealthBar.setFillColor(sf::Color::Red);
    redHealthBar.setPosition(sf::Vector2f(shape.getPosition().x,shape.getPosition().y - 2*redHealthBar.getSize().y));

    greenHealthBar.setSize(redHealthBar.getSize());
    greenHealthBar.setFillColor(sf::Color::Green);
    greenHealthBar.setPosition(redHealthBar.getPosition());
}

Enemy::~Enemy()
{

}

void Enemy::initText(sf::Font &font)
{
    std::stringstream ss;
    ss<<currenthealthPoints<<"\t/\t"<<maxhealthPoints;

    HPtext.setFont(font);
    HPtext.setString(ss.str());
    HPtext.setFillColor(sf::Color::Black);
    HPtext.setCharacterSize(10);
    HPtext.setPosition(redHealthBar.getPosition());
}

void Enemy::update(std::vector<sf::RectangleShape> &gridsVector,std::vector<int> &gridsTypeVector,size_t rows,size_t collumns)
{
    currentGrid = (int(shape.getPosition().y)/int(gridsVector[0].getSize().y))*collumns + (int(shape.getPosition().x)/int(gridsVector[0].getSize().x));

    if(currentGrid == baseGrid)
        inBase=true;


    if(velocity.x > 0 && velocity.y == 0) // moving right
    {
        if(gridsTypeVector[currentGrid+1] == 1 || gridsTypeVector[currentGrid+1] == 3) // right
            velocity={maxSpeed,0};
        else if(gridsTypeVector[currentGrid - collumns] == 1 || gridsTypeVector[currentGrid+1] == 3) //  up
            velocity={0,-maxSpeed};
        else if(gridsTypeVector[currentGrid + collumns] == 1 || gridsTypeVector[currentGrid+1] == 3) //down
            velocity={0,maxSpeed};
        else
            std::cout<<"ERROR::ENEMY.UPDATE()_RIGHT\n";
    }
    else if(velocity.x < 0 && velocity.y == 0) // moving left
    {
        if(gridsTypeVector[currentGrid-1] == 1 || gridsTypeVector[currentGrid+1] == 3) // left
            velocity={-maxSpeed,0};
        else if(gridsTypeVector[currentGrid - collumns] == 1 || gridsTypeVector[currentGrid+1] == 3) //  up
        {
            if(shape.getPosition().x > gridsVector[currentGrid].getPosition().x + 5.f)
                velocity={-maxSpeed,0};
            else
                velocity={0,-maxSpeed};
        }
        else if(gridsTypeVector[currentGrid + collumns] == 1 || gridsTypeVector[currentGrid+1] == 3) //down
        {
            if(shape.getPosition().x > gridsVector[currentGrid].getPosition().x + 5.f)
                velocity={-maxSpeed,0};
            else
                velocity={0,maxSpeed};
        }
        else
            std::cout<<"ERROR::ENEMY.UPDATE()_LEFT\n";
    }
    else if(velocity.x == 0 && velocity.y > 0) // moving down
    {
        if(gridsTypeVector[currentGrid + collumns] == 1 || gridsTypeVector[currentGrid+1] == 3) //down
            velocity={0,maxSpeed};
        else if(gridsTypeVector[currentGrid+1] == 1 || gridsTypeVector[currentGrid+1] == 3) //  right
            velocity={maxSpeed,0};
        else if(gridsTypeVector[currentGrid-1] == 1 || gridsTypeVector[currentGrid+1] == 3) // left
            velocity={-maxSpeed,0};
        else
            std::cout<<"ERROR::ENEMY.UPDATE()_DOWN\n";
    }
    else if(velocity.x == 0 && velocity.y < 0) // moving up
    {
        if(gridsTypeVector[currentGrid - collumns] == 1 || gridsTypeVector[currentGrid+1] == 3) //up
            velocity={0,-maxSpeed};
        else if(gridsTypeVector[currentGrid+1] == 1 || gridsTypeVector[currentGrid+1] == 3) //  right
        {
            if(shape.getPosition().y > gridsVector[currentGrid].getPosition().y + 5.f) //still too low...
                velocity={0,-maxSpeed};
            else
                velocity={maxSpeed,0};
        }
        else if(gridsTypeVector[currentGrid-1] == 1 || gridsTypeVector[currentGrid+1] == 3) // left
        {
            if(shape.getPosition().y > gridsVector[currentGrid].getPosition().y + 5.f) //still too low...
                velocity={0,-maxSpeed};
            else
                velocity={-maxSpeed,0};
        }
        else
            std::cout<<"ERROR::ENEMY.UPDATE()_UP\n";
    }
    else
        std::cout<<"ERROR::ENEMY.UPDATE()\n";

    shape.move(sf::Vector2f(velocity));

    redHealthBar.setPosition(sf::Vector2f(shape.getPosition().x,shape.getPosition().y - 2*redHealthBar.getSize().y));
    greenHealthBar.setPosition(redHealthBar.getPosition());
    HPtext.setPosition(redHealthBar.getPosition());

    if(currenthealthPoints <= 0)
        alive=false;
}

void Enemy::render(sf::RenderTarget &window)
{
    window.draw(shape);

    window.draw(redHealthBar);
    window.draw(greenHealthBar);
    window.draw(HPtext);
}

bool Enemy::isInBase()                          {    return inBase;                 }

sf::Vector2f Enemy::getPosition()               {    return shape.getPosition();    }

sf::Vector2f Enemy::getSize()                   {    return shape.getSize();        }

sf::FloatRect Enemy::getGlobalBounds()          {    return shape.getGlobalBounds();}

bool Enemy::isAlive()                           {    return alive;                  }

int Enemy::getHP()                              {    return currenthealthPoints;    }

int Enemy::getPrize()                           {    return prize;                  }

void Enemy::setBaseHP(int newHP)                {    maxhealthPoints = newHP;
                                                     setHP(maxhealthPoints);        }

void Enemy::setTexture(const sf::Texture *texture) { shape.setTexture(texture);     }

void Enemy::setHP(int newHP)
{
    currenthealthPoints=newHP;
    greenHealthBar.setSize(sf::Vector2f(redHealthBar.getSize().x * (currenthealthPoints/float(maxhealthPoints)), redHealthBar.getSize().y));

    std::stringstream ss;
    ss<<currenthealthPoints<<"\t/\t"<<maxhealthPoints;
    HPtext.setString(ss.str());
}
