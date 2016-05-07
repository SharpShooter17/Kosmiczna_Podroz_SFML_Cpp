#ifndef ASTEORIDA_H_INCLUDED
#define ASTEORIDA_H_INCLUDED

#include "space.h"

class Asteroida
{
private:
    float X_Asteroida, Y_Asteroida;
    int oslabienie;
    sf::Texture *Asteroid;
public:

    Asteroida(sf::Texture *pAsteroida);
    ~Asteroida() {}
    ///wspolrzedne asteroidy
    inline float X_Skala() { return X_Asteroida; }
    inline float Y_Skala() { return Y_Asteroida; }
    ///poruszanie asteroidy
    inline void Fly() { Y_Asteroida+=Ruch_asteroidy; }
    inline void Asteroida_dostala_pociskiem() { ++oslabienie; }
    ///stan asteroidy
    inline int Oslabiebie_asteroidy() { return oslabienie; }
    ///Rozmiar tekstury asteroidy!
    inline int X_Asteroida_tekstura() { return Asteroid->getSize().x; }
    inline int Y_Asteroida_tekstura() { return Asteroid->getSize().y; }
    ///Rysuje asteroide
    void Rysuj(sf::RenderWindow & app);
    ///ateorida poza ekranem?
    bool bPozaOknem();
    sf::Sprite Zwroc_Sprite();
    void Ustaw_Asteroide(Asteroida & przede_mna);
};

#endif // ASTEORIDA_H_INCLUDED
