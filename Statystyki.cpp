#include "Statystyki.h"

template<class T>
std::string toString(T var) {
    std::ostringstream oss;
    oss << var;
    return oss.str();
}

Statystyki::Statystyki(Statek & x, sf::Font *pFont) : life(x.zycie())
{
     font = pFont;
     LiczbaStraconychStatkow = 0;
     level = 1;
}

void Statystyki::Rysuj(Statek & ship, sf::RenderWindow & app)
{
    life = ship.zycie();
    sf::Text wyswietl_zycie;
    std::string zycie = toString(life);

    wyswietl_zycie.setString(zycie);
    wyswietl_zycie.setPosition(Width-150,Height-100);
    wyswietl_zycie.setFont(*font);

    if ( life <= 100 && life >= 75){
        wyswietl_zycie.setColor(sf::Color::Green);
        wyswietl_zycie.setCharacterSize(20);
    }
    else if ( life < 75 && life >= 50){
        wyswietl_zycie.setColor(sf::Color::Blue);
        wyswietl_zycie.setCharacterSize(30);
    }
    else if (life < 50 && life >= 25 ){
        wyswietl_zycie.setColor(sf::Color::Yellow);
        wyswietl_zycie.setCharacterSize(40);
    }
    else{
        wyswietl_zycie.setColor(sf::Color::Red);
        wyswietl_zycie.setCharacterSize(50);
    }
    sf::Text punkty;
    std::string Point = toString(ship.punkty());

    punkty.setString(Point);
    punkty.setCharacterSize(30);
    punkty.setColor(sf::Color::Yellow);
    punkty.setPosition(50, Height-100);
    punkty.setFont(*font);

    app.draw(wyswietl_zycie);
    app.draw(punkty);
}
