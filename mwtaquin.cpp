#include "mwtaquin.h"
#include "ui_mwtaquin.h"
#include "dialogdimensions.h"
#include "metier/moteur/TaquinException.h"
#include <QMessageBox>
#include <iostream>
#include <sstream>

MWTaquin::MWTaquin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MWTaquin),
    vbLayoutGrille(new QVBoxLayout),
    vbLayoutGraph(new QVBoxLayout),
    obsTexte(nullptr),
    obsGraph(nullptr),
    obsImage(nullptr),
    taquin(nullptr),
    timer(new QTimer(0))
{
    ui->setupUi(this);

    ui->wGrilleTexte->setLayout(vbLayoutGrille);
    vbLayoutGrille->setAlignment(Qt::AlignCenter);

    ui->wGrilleGraphique->setLayout(vbLayoutGraph);
    vbLayoutGraph->setAlignment(Qt::AlignCenter);

    ui->pbHaut->setDisabled(true);
    ui->pbDroite->setDisabled(true);
    ui->pbBas->setDisabled(true);
    ui->pbGauche->setDisabled(true);
    ui->pbValiderPosition->setDisabled(true);

    ui->sbLigne->setDisabled(true);
    ui->sbColonne->setDisabled(true);
    ui->lbLigne->setDisabled(true);
    ui->lbColonne->setDisabled(true);

    temps = 0;

    connexion();
}

MWTaquin::~MWTaquin()
{
    delete ui;
    //delete taquin;
    vbLayoutGrille->removeWidget(obsTexte);
    vbLayoutGraph->removeWidget(obsGraph);
    obsTexte = nullptr;
    obsGraph = nullptr;
    delete vbLayoutGrille;
    delete vbLayoutGraph;
}

void MWTaquin::connexion() {
    /* menus */
    connect(ui->action_Quitter, &QAction::triggered,
            &QCoreApplication::quit);
    connect(ui->action_Nouveau, &QAction::triggered, this,
            &MWTaquin::nouveauJeu);
    connect(ui->action_Resoudre, &QAction::triggered, this,
            &MWTaquin::resoudreJeu);
    connect(ui->action_Melanger, &QAction::triggered, this,
            &MWTaquin::melangerJeu);
    connect(ui->action_Texte, &QAction::toggled, this,
            &MWTaquin::observateurTexte);
    connect(ui->action_Graphique, &QAction::toggled, this,
            &MWTaquin::observateurGraphique);
    connect(ui->action_Image, &QAction::triggered, this,
            &MWTaquin::observateurImage);

    /* boutons de déplacement */
    connect(ui->pbHaut, &QAbstractButton::released, this,
            &MWTaquin::deplacerHaut);
    connect(ui->pbDroite, &QAbstractButton::released, this,
            &MWTaquin::deplacerDroite);
    connect(ui->pbBas, &QAbstractButton::released, this,
            &MWTaquin::deplacerBas);
    connect(ui->pbGauche, &QAbstractButton::released, this,
            &MWTaquin::deplacerGauche);

    /* bouton validation position */
    connect(ui->pbValiderPosition, &QAbstractButton::released, this,
            &MWTaquin::deplacerPosition);

    /* timer */
    connect(timer, SIGNAL(timeout()), SLOT(majTimer()));

}

void MWTaquin::nouveauJeu() {

    DialogDimensions dd { this };
    if (dd.exec() == QDialog::Rejected) return;
    unsigned dimensions = dd.getDimensions();
    try {
        if (taquin != nullptr) {
            /* observateur texte */
            delete obsTexte;
            obsTexte = nullptr;

            /* observateur graphique */
            delete obsGraph;
            obsGraph = nullptr;

            /* observateur image */
            delete obsImage;
            obsImage = nullptr;

            /* timer */
            temps = 0;

            /* taquin */
            taquin = nullptr;
        }
        Position position = {0, 0};
        taquin = new Taquin(dimensions, position, false);


    } catch (TaquinException te) {
        QMessageBox qmbErr;
        qmbErr.warning(this, "Erreur", QString::fromStdString(te.what()));
    }

    observateurTexte(true);
    observateurGraphique(true);

    /* menu */
    ui->action_Melanger->setEnabled(true);
    ui->action_Resoudre->setEnabled(true);
    ui->menuVues->setEnabled(true);
    ui->menuChiffres->setEnabled(true);
    ui->action_Texte->setEnabled(true);
    ui->action_Graphique->setEnabled(true);
    ui->action_Image->setEnabled(true);

    /* directions */
    ui->pbHaut->setEnabled(true);
    ui->pbDroite->setEnabled(true);
    ui->pbBas->setEnabled(true);
    ui->pbGauche->setEnabled(true);

    /* positions */
    ui->sbLigne->setEnabled(true);
    ui->sbColonne->setEnabled(true);
    ui->lbLigne->setEnabled(true);
    ui->lbColonne->setEnabled(true);
    ui->pbValiderPosition->setEnabled(true);

    ui->sbLigne->setMaximum(dimensions - 1);
    ui->sbColonne->setMaximum(dimensions - 1);

    ui->lbMouvementsVal->setNum(0);

    timer->start(1000);

}

void MWTaquin::resoudreJeu() {
    taquin->setPiecesCorrectes();
}

void MWTaquin::melangerJeu() {
    taquin->melangerPieces();
    majMouvements();
}

void MWTaquin::observateurTexte(bool actif) {
    if (actif) {
        if (obsTexte == nullptr) {
            obsTexte = new TexteObservateur(taquin);
            vbLayoutGrille->addWidget(obsTexte);
        }
        obsTexte->show();
    } else {
        if (obsTexte != nullptr) {
            obsTexte->hide();
        }
    }
}

void MWTaquin::observateurGraphique(bool actif) {
    if (actif) {
        if (obsGraph == nullptr) {
            obsGraph = new GraphiqueObservateur(taquin);
            vbLayoutGraph->addWidget(obsGraph);
        }
        obsGraph->show();
    } else {
        if (obsGraph != nullptr) {
            obsGraph->hide();
        }
    }
}

void MWTaquin::observateurImage() {
    if (obsImage == nullptr) {
        obsImage = new ImageObservateur(taquin);
    }
    obsImage->show();
}

void MWTaquin::deplacerHaut() {
    taquin->deplacerPiece(Direction::UP);
    majMouvements();
    jeuResolu();
}

void MWTaquin::deplacerDroite() {
    taquin->deplacerPiece(Direction::RIGHT);
    majMouvements();
    jeuResolu();
}

void MWTaquin::deplacerBas() {
    taquin->deplacerPiece(Direction::DOWN);
    majMouvements();
    jeuResolu();
}

void MWTaquin::deplacerGauche() {
    taquin->deplacerPiece(Direction::LEFT);
    majMouvements();
    jeuResolu();
}

void MWTaquin::deplacerPosition() {
    try {
        Position position;
        position.ligne = ui->sbLigne->value();
        position.colonne = ui->sbColonne->value();
        //cout << "taquin->deplacerPiece({" << position.ligne << "," << position.colonne << "})" << endl;
        taquin->deplacerPiece(position);

        majMouvements();
        jeuResolu();
    } catch (TaquinException te) {
        QMessageBox qmbErr;
        qmbErr.warning(this, "Erreur", QString::fromStdString(te.what()));
    }
}

void MWTaquin::majMouvements() {
    ui->lbMouvementsVal->setNum(taquin->getNombreMouvements());
    ui->sbLigne->setValue(taquin->getPositionVide().ligne);
    ui->sbColonne->setValue(taquin->getPositionVide().colonne);
}

void MWTaquin::majTimer() {
    temps++;
    ui->lcdNumber->display(temps);
}

bool MWTaquin::jeuResolu() {
    bool resolu = false;
    if (taquin->estResolu()) {
        timer->stop();
        resolu = true;
        QString msg = QString("Bravo ! Vous avez fini le jeu en %1 mouvements et %2 secondes").arg(taquin->getNombreMouvements()).arg(temps);

        QMessageBox msgBox;
        msgBox.setWindowTitle("Jeu résolu");
        msgBox.setText(msg);
        msgBox.exec();
    }

    return resolu;
}
