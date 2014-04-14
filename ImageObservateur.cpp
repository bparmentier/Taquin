#include "ImageObservateur.h"
#include <sstream>
#include <QCoreApplication>

ImageObservateur::ImageObservateur(SujetDObservation *sdo, QWidget *parent) :
    QWidget(parent),
    image(QPixmap(":resources/images/evolution.jpg")),
    centralWidget(new QWidget),
    vLayout(new QVBoxLayout),
    gLayout(new QGridLayout) {

    jeu = static_cast<Taquin *> (sdo);
    jeu->attacher(this);

    this->setWindowTitle("Vue image");

    traitementImage();

    this->setLayout(vLayout);
    vLayout->addWidget(centralWidget);
    centralWidget->setLayout(gLayout);
    gLayout->setHorizontalSpacing(1);
    gLayout->setVerticalSpacing(1);

    creerMenu();

    for (unsigned i = 0; i < jeu->getTaille(); i++) { // lignes
        std::vector<QPushButton *> lignePieces;
        grille.push_back(lignePieces);
        for (unsigned j = 0; j < jeu->getTaille(); j++) { // colonnes
            auto piece = new QPushButton;
            piece->setFlat(true);
            piece->setCursor(QCursor(Qt::PointingHandCursor));
            piece->setFixedSize(image.width() / jeu->getTaille(),
                                image.height() / jeu->getTaille());

            grille[i].push_back(piece);
            gLayout->addWidget(grille[i][j], i, j);

            connect(piece, &QPushButton::released, [=]{
                handleClick(i, j);
            });
        }
    }

    this->rafraichir(sdo);
}

ImageObservateur::~ImageObservateur() noexcept {
    jeu->detacher(this);
}

void ImageObservateur::rafraichir(SujetDObservation *sdo) {
    if (sdo != jeu) {
        return;
    }

    unsigned ligne;
    unsigned colonne;
    int largeur;
    int hauteur;

    for (unsigned i = 0; i < jeu->getTaille(); i++) {
        for (unsigned j = 0; j < jeu->getTaille(); j++) {
            if (jeu->getPiece({i, j}).estCaseVide()) {
                grille[i][j]->setIcon(QIcon());
            } else {
                ligne = jeu->getPiece({i, j}).getPositionCorrecte().ligne;
                colonne = jeu->getPiece({i, j}).getPositionCorrecte().colonne;
                largeur = image.width() / jeu->getTaille();
                hauteur = image.height() / jeu->getTaille();
                QPixmap pixmap = image.copy(
                            colonne * largeur,
                            ligne * hauteur,
                            largeur,
                            hauteur);
                QIcon buttonIcon(pixmap);
                grille[i][j]->setIcon(buttonIcon);
                grille[i][j]->setIconSize(pixmap.rect().size());
            }
        }
    }
    this->adjustSize();
}

void ImageObservateur::handleClick(unsigned i, unsigned j) {
    jeu->deplacerPiece({i, j});
}

void ImageObservateur::naviguer() {
    QFileInfo image
            = QFileDialog::getOpenFileName(this,
                                           "Choisir une image",
                                           QDir::currentPath(),
                                           "Images (*.png *.jpg *.bmp)");
    if (image.filePath() != NULL) {
        this->image.load(image.filePath());
        traitementImage();
        for (unsigned i = 0; i < jeu->getTaille(); i++) { // lignes
            for (unsigned j = 0; j < jeu->getTaille(); j++) { // colonnes
                grille[i][j]->setFixedSize(
                            this->image.width() / jeu->getTaille(),
                            this->image.height() / jeu->getTaille());
            }
        }
        this->rafraichir(jeu);
    }

}

void ImageObservateur::traitementImage() { // FIXME
    if (image.height() > 500 || image.width() > 500) {
        image = image.scaled(500, 500, Qt::KeepAspectRatio);
    }
}

void ImageObservateur::creerMenu() {
    menuBar = new QMenuBar;
    menuImage = new QMenu("&Image");

    choisirImage = new QAction("&Choisir une image", this);
    choisirImage->setShortcut(QKeySequence::Open);
    connect(choisirImage, SIGNAL(triggered()), this, SLOT(naviguer()));

    fermer = new QAction("&Fermer", this);
    fermer->setShortcut(QKeySequence::Close);
    connect(fermer, SIGNAL(triggered()), SLOT(fermerFenetre()));

    menuImage->addAction(choisirImage);
    menuImage->addAction(fermer);
    menuBar->addMenu(menuImage);
    vLayout->setMenuBar(menuBar);

}

void ImageObservateur::fermerFenetre() {
    this->hide();
}
