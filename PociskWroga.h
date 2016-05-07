#ifndef POCISKWROGA_H_INCLUDED
#define POCISKWROGA_H_INCLUDED

#include "space.h"

class PociskWroga
{
private:
    float X_POCISK;
    float Y_POCISK;

    float SzybkoscPocisku;

    sf::Texture *Pocisk;
public:
    PociskWroga(float x, float y,float width, float speed, sf::Texture *pPocisk);
    ~PociskWroga() {}
    inline void Fly() {Y_POCISK+=SzybkoscPocisku;}
    bool bPozaOknem();
    inline float XPOCISK() {return X_POCISK;}
    inline float YPOCISK() {return Y_POCISK;}
    inline float XPOCISKTEKSTURA() {return Pocisk->getSize().x;}
    inline float YPOCISKTEKSTURA() {return Pocisk->getSize().y;}
    void Rysuj( sf::RenderWindow & app);
    sf::Sprite Zwroc_Sprite();
};

#endif // POCISKWROGA_H_INCLUDED
