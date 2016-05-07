#ifndef STATEK_H_INCLUDED
#define STATEK_H_INCLUDED

#include "space.h"

class Statek
{
    private:
        float X_rakieta, Y_rakieta;
        int life; //tylko co ja z tym robie? NIC :D
        int Scores;
        sf::Texture *rakieta;

    public:
        Statek(sf::Texture *pShipPlayer);
        ///Ruch statku
        inline void Right() {if ( X_rakieta < Width - X_statek_tekstura()) X_rakieta+=Przeskocz_O_pixeli;}
        inline void Left() {if ( X_rakieta > 0) X_rakieta-=Przeskocz_O_pixeli;}
        inline void Up() {if ( Y_rakieta > 0) Y_rakieta-=Przeskocz_O_pixeli;}
        inline void Down() {if ( Y_rakieta < Height - X_statek_tekstura()) Y_rakieta+=Przeskocz_O_pixeli;}

        void Rysuj(sf::RenderWindow & app);
        ///Pozycja XY
        inline float x_rakiety() { return X_rakieta; }
        inline float y_rakiety() { return Y_rakieta; }
        inline void ResetXY() { X_rakieta = Width/2-64; Y_rakieta = Height*0.8; }
        ///Rozmiar tekstury statku!
        inline float X_statek_tekstura() { return rakieta->getSize().x; }
        inline float Y_statek_tekstura() { return rakieta->getSize().y; }
        inline void change_life(int x) { life +=x; }
        inline int zycie() { return life; }
        inline void scores(int x) { Scores+=x; }
        inline void ResetScores() { Scores = 0; }
        inline void ResetLife() { life = 100; }
        inline int punkty() {return Scores;}
        sf::Sprite Zwroc_Sprite();
};


#endif // STATEK_H_INCLUDED
