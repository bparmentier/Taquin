#include <iostream>
#include <algorithm>
#include "Taquin.h"
#include "Piece.h"
#include "TaquinException.h"
#include "Direction.h"

Taquin::Taquin() {}

Taquin::Taquin(unsigned lignes = 3,
               Position posVide = {0, 0},
               bool estMelange = false)
    : nbLignes(lignes),
      positionVide(posVide),
      melange(estMelange),
      nbMouvements(0) {
    if ((lignes < 3) || (lignes > 5)) {
        throw TaquinException("La taille doit être comprise entre 3 et 5.");
    }
    for (unsigned i = 0; i < lignes; i++) { // lignes
        vector<Piece> lignePieces;
        grille.push_back(lignePieces);
        for (unsigned j = 0; j < lignes; j++) { // colonnes
            Piece piece;
            Position position;
            position.ligne = i;
            position.colonne = j;
            if ((positionVide.ligne == i) && (positionVide.colonne == j)) {
                piece = Piece(position, true); // pièce vide
            } else {
                piece = Piece(position, false);
            }
            this->grille[i].push_back(piece);
        }
    }
    if (estMelange) {
        melangerPieces();
    }

    notifierChangement();
}

Position Taquin::getPositionVide() {
    return this->positionVide;
}

unsigned Taquin::getTaille() {
    return this->nbLignes;
}

std::vector< std::vector<Piece> > Taquin::getGrille() {
    return this->grille;
}

Piece Taquin::getPiece(Position p) {
    if ((p.ligne > this->getTaille()) || (p.colonne > this->getTaille())) {
        throw TaquinException("Position hors limites.");
    } else {
        return this->grille[p.ligne][p.colonne];
    }
}

void Taquin::setPiecesCorrectes() {
    for (unsigned i = 0; i < nbLignes; i++) {
        for (unsigned j = 0; j < nbLignes; j++) {
            //Piece piece = this->getPiece({i, j});
            Position posCorrecte = grille.at(i).at(j).getPositionCorrecte();
            if (posCorrecte.ligne != i
                    || posCorrecte.colonne != j) {
                std::swap(grille.at(i).at(j),
                      grille.at(posCorrecte.ligne).at(posCorrecte.colonne));
                // TODO

            }
        }
    }
}

void Taquin::melangerPieces() {
    //unsigned sauvNbMouv = nbMouvements;
    for (int i = 0; i < 1000; i++) {
        deplacerPiece(static_cast<Direction> (rand() % 5));
    }
    nbMouvements = 0;
    this->notifierChangement();
}

bool Taquin::deplacerPiece(Position positionPiece) {
    bool deplace = false; // a été déplacé

    if (verifierDeplacement(positionPiece)) {
        Piece pieceADeplacer;
        Piece pieceVide;
        try {
            pieceADeplacer = this->getPiece(positionPiece);
            pieceVide = this->getPiece(positionVide);
        } catch (TaquinException te) {
            std::cerr << te.what();
        }

        if (positionPiece.ligne == (positionVide.ligne - 1)) {
            this->positionVide.ligne--;
        } else if (positionPiece.ligne == (positionVide.ligne + 1)) {
            this->positionVide.ligne++;
        } else if (positionPiece.colonne == (positionVide.colonne - 1)) {
            this->positionVide.colonne--;
        } else if (positionPiece.colonne == (positionVide.colonne + 1)) {
            this->positionVide.colonne++;
        }

        /* nouvelles positions */
        Position nouvPosPiece = pieceVide.getPositionActuelle();
        Position nouvPosVide = pieceADeplacer.getPositionActuelle();

        /* déplacement des pièces dans la grille */
        grille[nouvPosVide.ligne][nouvPosVide.colonne] = pieceVide;
        grille[nouvPosPiece.ligne][nouvPosPiece.colonne] = pieceADeplacer;

        /* mise à jour des attributs des pièces */
        grille[nouvPosVide.ligne][nouvPosVide.colonne]
                .setPosition(nouvPosVide);
        grille[nouvPosPiece.ligne][nouvPosPiece.colonne]
                .setPosition(nouvPosPiece);

        this->nbMouvements++;
        deplace = true;
    }

    this->notifierChangement();

    return deplace;
}

bool Taquin::verifierDeplacement(Position positionPiece) {
    bool horsLimites = ((positionPiece.ligne > nbLignes - 1)
                        || (positionPiece.colonne > nbLignes - 1));

    /* le déplacement doit être égal à 1 pour que la pièce soit adjacente à la
     * case vide */
    int deplacement = abs(static_cast<int> (positionPiece.ligne)
                          - static_cast<int> (positionVide.ligne))
            + abs(static_cast<int> (positionPiece.colonne)
                  - static_cast<int> (positionVide.colonne));

    return (!horsLimites && (deplacement == 1));
}

bool Taquin::deplacerPiece(Direction direction) {
    bool deplace = false;
    switch (direction) {
    case Direction::UP:
        if (positionVide.ligne > 0) {
            deplace = deplacerPiece({positionVide.ligne - 1,
                                     positionVide.colonne});
        }
        break;
    case Direction::RIGHT:
        if (positionVide.colonne < nbLignes) {
            deplace = deplacerPiece({positionVide.ligne,
                                     positionVide.colonne + 1});
        }
        break;
    case Direction::DOWN:
        if (positionVide.ligne < nbLignes) {
            deplace = deplacerPiece({positionVide.ligne + 1,
                                     positionVide.colonne});
        }
        break;
    case Direction::LEFT:
        if (positionVide.colonne > 0) {
            deplace = deplacerPiece({positionVide.ligne,
                                     positionVide.colonne - 1});
        }
        break;
    case Direction::NONE:
        //deplacerPiece({positionVide.ligne, positionVide.colonne});
        break;
    default:
        throw TaquinException("Direction invalide.");
        break;
    }

    return deplace;
}

int Taquin::getNombreMouvements() {
    return this->nbMouvements;
}

bool Taquin::estResolu() {
    unsigned i = 0; // indice ligne
    unsigned j = 0; // indice colonne

    bool resolu = true; // on considère le jeu résolu
    while (resolu && (i < nbLignes)) {
        j = 0;
        while (resolu && (j < nbLignes)) {
            if ((grille[i][j].getPositionCorrecte().ligne != i)
                    || (grille[i][j].getPositionCorrecte().colonne != j)) {
                resolu = false;
            }
            j++;
        }
        i++;
    }

    return resolu;
}

std::ostream &operator<<(std::ostream &out, Taquin in) {
    for (unsigned i = 0; i < in.getTaille(); i++) { // ligne
        for (unsigned j = 0; j < in.getTaille(); j++) { // colonne
            out << in.getPiece({i, j});
        }
        out << "<br />";
    }

    return out;
}
