/*!
 * \file TexteObservateur.h
 * \brief Définition de la classe TexteObservateur.
 */

#ifndef TEXTEOBSERVATEUR_H
#define TEXTEOBSERVATEUR_H

#include <sstream>
#include <QLabel>
#include "metier/moteur/Taquin.h"
#include "metier/O_SDO/observateur.h"

class Taquin;

/* Observateur texte du jeu de taquin */
class TexteObservateur : public QLabel, public Observateur {
private:
    Taquin *jeu;
    //QLabel *grilleTexte;
    std::ostringstream oss;

public:
    TexteObservateur(SujetDObservation *sdo);
    ~TexteObservateur() noexcept;
    void rafraichir(SujetDObservation *sdo);
};

#endif // TEXTEOBSERVATEUR_H
