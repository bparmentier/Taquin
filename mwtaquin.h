#ifndef MWTAQUIN_H
#define MWTAQUIN_H

#include <QMainWindow>
#include "metier/moteur/Taquin.h"
#include "TexteObservateur.h"
#include "GraphiqueObservateur.h"
#include "ImageObservateur.h"
#include <sstream>
#include <QVBoxLayout>
#include <QTimer>

namespace Ui {
class MWTaquin;
}

class MWTaquin : public QMainWindow
{
    Q_OBJECT

public:
    explicit MWTaquin(QWidget *parent = 0);
    ~MWTaquin();

private:
    Ui::MWTaquin *ui;
    Taquin *taquin;
    TexteObservateur *obsTexte;
    GraphiqueObservateur *obsGraph;
    ImageObservateur *obsImage;
    QVBoxLayout *vbLayoutGrille;
    QVBoxLayout *vbLayoutGraph;
    int temps;
    QTimer *timer;

    void connexion();
    void majMouvements();
    bool jeuResolu();

private slots:
    void nouveauJeu();
    void resoudreJeu();
    void melangerJeu();
    void observateurTexte(bool actif);
    void observateurGraphique(bool actif);
    void observateurImage();
    void deplacerHaut();
    void deplacerDroite();
    void deplacerBas();
    void deplacerGauche();
    void deplacerPosition();
    void majTimer();
};

#endif // MWTAQUIN_H
