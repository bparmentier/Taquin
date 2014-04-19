/*!
 * \file ImageObservateur.h
 * \brief Définition de la classe ImageObservateur.
 */

#ifndef IMAGEOBSERVATEUR_H
#define IMAGEOBSERVATEUR_H

#include "metier/moteur/Taquin.h"
#include "metier/O_SDO/observateur.h"
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QPushButton>
#include <QFileDialog>
#include <QMenuBar>
#include <QAction>

class Taquin;

//! Classe ImageObservateur
/*!
 * \brief Observateur image du jeu de taquin
 * \see Observateur
 * \author Bruno Parmentier
 */
class ImageObservateur : public QWidget, public Observateur {
    Q_OBJECT

private:
    Taquin *jeu;
    std::vector< std::vector<QPushButton *> > grille;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuImage;
    QAction *choisirImage;
    QAction *fermer;
    QVBoxLayout *vLayout;
    QGridLayout *gLayout;
    QPixmap image;

    void handleClick(unsigned i, unsigned j);
    void creerMenu();
    void traitementImage();

private slots:
    void naviguer();
    void fermerFenetre();

public:
    ImageObservateur(SujetDObservation *sdo, QWidget *parent = 0);
    ~ImageObservateur() noexcept;
    void rafraichir(SujetDObservation *sdo);
};

#endif // IMAGEOBSERVATEUR_H
