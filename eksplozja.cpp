#include "Eksplozja.h"
static sf::Sprite PlikTymczasowy;

Explozja:: Explozja(float a, float b, sf::Texture *pExplo)
{
    explo = pExplo;
    x = a;
    y = b;
}

void Explozja::Rysuj(sf::RenderWindow & app)
{
    PlikTymczasowy.setTexture(*explo);
    PlikTymczasowy.setPosition(x,y);
    PlikTymczasowy.setOrigin(explo->getSize().x/2,explo->getSize().y/2);
    app.draw(PlikTymczasowy);
}

bool Explozja::bCzyWybuchTrwa()
{
    if ( tBomEnd < tBom ){
        tBomEnd +=cBom.restart();
        return false;
    }
    else {
        tBomEnd = sf::Time::Zero;
        return true;
    }


}
