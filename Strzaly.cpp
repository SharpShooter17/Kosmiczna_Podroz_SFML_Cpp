#include "Strzaly.h"
#include "Asteorida.h"

///konstruktor dla pocisku statku
Strzaly::Strzaly(float x, float y, sf::Texture *pBullet)
{
    Kula=pBullet;
    X_Bullet = x +59;
    Y_Bullet =  y - pBullet->getSize().y;
}

Strzaly::~Strzaly()
{
}

bool Strzaly::bPozaOknem()
{
    if ( Y_Bullet< -Y_Bullet_tekstura() || Y_Bullet > Height )
        return true;
    else
        return false;
}

void Strzaly::Rysuj( sf::RenderWindow & app)
{
    sf::Sprite tmp;
    tmp.setTexture(*Kula);
    tmp.setPosition(X_Bullet,Y_Bullet);
    app.draw(tmp);
}
sf::Sprite Strzaly::Zwroc_Sprite()
{
    sf::Sprite tmp;
    tmp.setTexture(*Kula);
    tmp.setPosition(X_Bullet,Y_Bullet);
    return tmp;
}
