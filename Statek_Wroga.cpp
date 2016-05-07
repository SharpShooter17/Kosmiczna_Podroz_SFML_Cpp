#include "Statek_Wroga.h"

Statek_Wroga::Statek_Wroga(float speed, sf::Texture *pwrog)
{
    wrog = pwrog;
    srand(time(NULL));
    int i = rand() % 9 + 1;
    X_WROG = i * ((Width-wrog->getSize().x)/10);
    Y_WROG = -yWrogTekstura();
    life = 50;
    SzybkoscRuchu = speed;

    bCzyZbalokowany = false;
}

void Statek_Wroga::Automatyczny_ruch(Statek & atakuj, std::deque < Asteroida > & Tablica)
{
    sf::Sprite tmp;
    tmp.setTexture(*wrog);
    tmp.setPosition(X_WROG,Y_WROG);

    for (int i = 0; i < Tablica.size(); i++){

        sf::Sprite PrzedeMna = Tablica[i].Zwroc_Sprite();

        tmp.setPosition(X_WROG+1,Y_WROG);
        if (Collision::BoundingBoxTest(tmp, PrzedeMna )){
            X_WROG -=SzybkoscRuchu;
            bCzyZbalokowany = true;
        }

        tmp.setPosition(X_WROG-1,Y_WROG);
        if (Collision::BoundingBoxTest(tmp, PrzedeMna ) ){
             X_WROG +=SzybkoscRuchu;
             bCzyZbalokowany = true;
        }

        tmp.setPosition(X_WROG,Y_WROG+1);
        if (Collision::BoundingBoxTest(tmp, PrzedeMna ) ){
             Y_WROG -=SzybkoscRuchu;
             bCzyZbalokowany = true;
        }

        tmp.setPosition(X_WROG,Y_WROG-1);
        if (Collision::BoundingBoxTest(tmp, PrzedeMna ) ) {
            Y_WROG +=SzybkoscRuchu;
             bCzyZbalokowany = true;
            }

    }

    if (X_WROG > atakuj.x_rakiety()){
        X_WROG -=SzybkoscRuchu;
        bCzyZbalokowany = false;
    }
    else if (X_WROG < atakuj.x_rakiety()){
        X_WROG +=SzybkoscRuchu;
        bCzyZbalokowany = false;
    }
        Y_WROG +=Ruch_w_dol_wroga;

}

bool Statek_Wroga::bAutomatyczne_strzelanie(Statek & atakuj)
{
    if ( (X_WROG >= atakuj.x_rakiety() && X_WROG <= atakuj.x_rakiety() + atakuj.X_statek_tekstura()) ||
        ( X_WROG+xWrogTekstura() >= atakuj.x_rakiety() && X_WROG <= atakuj.x_rakiety()+xWrogTekstura() ) )
       return true;
       else
        return false;
}

void Statek_Wroga::Rysuj(sf::RenderWindow & app)
{
    sf::Sprite tmp;
    tmp.setTexture(*wrog);
    tmp.setPosition(X_WROG,Y_WROG);
    app.draw(tmp);
}

bool Statek_Wroga::bPozaOknem()
{
    if ( Y_WROG > Height )
        return true;
    else
        return false;
}
bool Statek_Wroga::bCzyMogeStrzelic()
{
    if ( tWrogFire < tWrog ){
        tWrogFire +=cWrog.restart();
        return false;
    }
    else {
        tWrogFire = sf::Time::Zero;
        return true;
    }
}

sf::Sprite Statek_Wroga::Zwroc_Sprite()
{
    sf::Sprite tmp;
    tmp.setTexture(*wrog);
    tmp.setPosition(X_WROG,Y_WROG);
    return tmp;
}
