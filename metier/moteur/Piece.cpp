#include "Piece.h"

Piece::Piece() {}

Piece::Piece(Position position, bool estVide) {
    this->positionCorrecte = position;
    this->positionActuelle = position;
    this->caseVide = estVide;
}

void Piece::setPosition(Position position) {
    this->positionActuelle = position;
}

Position Piece::getPositionActuelle() {
    return this->positionActuelle;
}

Position Piece::getPositionCorrecte() {
    return this->positionCorrecte;
}

bool Piece::estCaseVide() {
    return this->caseVide;
}

std::ostream &operator<<(std::ostream &out, Piece in) {
    if (in.estCaseVide()) {
        out << "(___)";
    } else {
        out << "(" << in.getPositionCorrecte().ligne << "," << in.getPositionCorrecte().colonne << ")";
    }

    return out;
}
