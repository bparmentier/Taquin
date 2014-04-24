#include "GraphiqueObservateur.h"
#include <sstream>

GraphiqueObservateur::GraphiqueObservateur(SujetDObservation *sdo) :
    layout(new QGridLayout) {

    jeu = static_cast<Taquin *> (sdo);
    jeu->attacher(this);

    QFont font("Monospace");
    font.setStyleHint(QFont::TypeWriter);
    font.setBold(true);
    font.setPointSize(12);
    this->setFont(font);

    this->setLayout(layout);

    for (unsigned i = 0; i < jeu->getTaille(); i++) { // lignes
        std::vector<QPushButton *> lignePieces;
        grille.push_back(lignePieces);
        for (unsigned j = 0; j < jeu->getTaille(); j++) { // colonnes
            auto piece = new QPushButton;

            grille[i].push_back(piece);
            layout->addWidget(grille[i][j], i, j);

            connect(piece, &QPushButton::released, [=]{
                handleClick(i, j);
            });
        }
    }

    this->rafraichir(sdo);
}

GraphiqueObservateur::~GraphiqueObservateur() noexcept {
    jeu->detacher(this);
}

void GraphiqueObservateur::rafraichir(SujetDObservation *sdo) {
    if (sdo != jeu) {
        return;
    }
    std::ostringstream oss;

    for (unsigned i = 0; i < jeu->getTaille(); i++) {
        for (unsigned j = 0; j < jeu->getTaille(); j++) {
            oss.str("");
            oss.flush();
            oss << jeu->getPiece({i, j});
            grille[i][j]->setText(oss.str().c_str());
        }
    }
}

void GraphiqueObservateur::handleClick(unsigned i, unsigned j) {
    jeu->deplacerPiece({i, j});
}

