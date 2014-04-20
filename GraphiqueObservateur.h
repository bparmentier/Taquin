#ifndef GRAPHIQUEOBSERVATEUR_H
#define GRAPHIQUEOBSERVATEUR_H

#include <vector>
#include <sstream>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include "metier/moteur/Taquin.h"
#include "metier/O_SDO/observateur.h"

class Taquin;

/* Observateur graphique du jeu de taquin */
class GraphiqueObservateur : public QWidget, public Observateur {
private:
    Taquin *jeu;
    std::vector< std::vector<QPushButton *> > grille;
    QGridLayout *layout;
    void handleClick(unsigned i, unsigned j);

public:
    GraphiqueObservateur(SujetDObservation *sdo);
    ~GraphiqueObservateur() noexcept;
    void rafraichir(SujetDObservation *sdo);
};

#endif // GRAPHIQUEOBSERVATEUR_H
