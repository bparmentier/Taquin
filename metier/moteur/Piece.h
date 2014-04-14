/*!
 * \file Piece.h
 * \brief Définition de la classe Piece.
 */

#ifndef PIECE_H
#define PIECE_H

#include "Position.h"
#include <iostream>

//! Classe Piece
/*!
 * \brief Représente une pièce du puzzle ou <em>le vide</em>.
 * \author Bruno Parmentier
 */
class Piece {
private:
    Position positionActuelle;
    Position positionCorrecte;
    bool caseVide;

public:
    //! Constructeur par défaut de Pièce
    Piece();

    //! Constructeur de Pièce
    /*!
     * \brief Construit une pièce du puzzle.
     * \param positionActuelle la position de la pièce
     * \param estVide si la pièce représente la case vide
     */
    Piece(Position positionActuelle, bool estVide);

    /*!
     * \brief Définit la position de la pièce.
     * \param position la position de la pièce
     */
    void setPosition(Position position);

    /*!
     * \brief Retourne la position actuelle de la pièce.
     * \return la position actuelle de la pièce
     */
    Position getPositionActuelle();

    /*!
     * \brief Retourne la position correcte de la pièce.
     * \return la position correcte de la pièce
     */
    Position getPositionCorrecte();

    /*!
     * \brief Vérifie si la pièce est une case vide ou non.
     * \return <code>true</code> si la pièce est une case vide,
     * <code>false</code> sinon
     */
    bool estCaseVide();
};

std::ostream &operator<< (std::ostream &out, Piece in);

#endif // PIECE_H
