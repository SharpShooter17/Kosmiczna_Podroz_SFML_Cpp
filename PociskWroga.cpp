#include "PociskWroga.h"

///konstrukror dla pocisku wroga
PociskWroga::PociskWroga(float x, float y, float width, float speed, sf::Texture *pPocisk)
{
    Pocisk = pPocisk;
    X_POCISK = x + width*0.5 - XPOCISKTEKSTURA()/2;
    Y_POCISK =  y + YPOCISKTEKSTURA();
    SzybkoscPocisku = speed;
}

bool PociskWroga::bPozaOknem()
{
    if ( Y_POCISK < -YPOCISKTEKSTURA() || Y_POCISK > Height )
        return true;
    else
        return false;
}

void PociskWroga::Rysuj( sf::RenderWindow & app)
{
    sf::Sprite tmp;
    tmp.setTexture(*Pocisk);
    tmp.setPosition(X_POCISK,Y_POCISK);
    app.draw(tmp);
}
sf::Sprite PociskWroga::Zwroc_Sprite()
{
    sf::Sprite tmp;
    tmp.setTexture(*Pocisk);
    tmp.setPosition(X_POCISK,Y_POCISK);
    return tmp;
}
