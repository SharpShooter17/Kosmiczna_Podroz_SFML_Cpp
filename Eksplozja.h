#ifndef EKSPLOZJA_H_INCLUDED
#define EKSPLOZJA_H_INCLUDED

#include "space.h"

class Explozja
{
private:
    float x,y;
    sf::Texture *explo;
    sf::Sprite *tmp;
    sf::Clock cBom;
    sf::Time tBom = sf::seconds(Dlugosc_Eksplozji); /// ile sekund trwa eksplozja?
    sf::Time tBomEnd;
public:
    Explozja(float a, float b, sf::Texture *pExplo );
    ~Explozja() {}
    void Rysuj(sf::RenderWindow & app);
    bool bCzyWybuchTrwa();
};

#endif // EKSPLOZJA_H_INCLUDED
