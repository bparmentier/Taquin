/*!
 * \file Taquin.h
 * \brief Définition de la classe Taquin.
 */

#ifndef TAQUIN_H
#define TAQUIN_H

#include <iostream>
#include <vector>
#include "Position.h"
#include "Piece.h"
#include "Direction.h"
#include "../O_SDO/sujetDObservation.h"

//! Classe Taquin
/*!
 * \brief Jeu de taquin
 * \see SujetDObservation
 * \author Bruno Parmentier
 */
class Taquin : public SujetDObservation {
private:
    unsigned nbLignes;
    std::vector< std::vector<Piece> > grille;
    bool melange;
    Position positionVide;
    unsigned nbMouvements;

    bool verifierDeplacement(Position positionPiece);
    //void setPositionPiece(Position position);

public:
    //! Constructeur par défaut de Taquin
    Taquin();

    //! Constructeur de Taquin
    /*!
     * \brief Construit un jeu de taquin.
     * \param lignes le nombre de lignes/colonnes
     * \param posVide la position de l'emplacement vide dans la grille de
     * jeu <em>résolue</em>
     * \param melange si le puzzle est initialement mélangé ou non
     */
    Taquin(unsigned lignes, Position posVide, bool melange);

    /*!
     * \brief Retourne le nombre de lignes/colonnes de la grille de jeu.
     * \return le nombre de lignes/colonnes de la grille de jeu
     */
    unsigned getTaille();

    /*!
     * \brief Retourne la grille de pièces.
     * \return la grille de pièces
     */
    std::vector< std::vector<Piece> > getGrille();

    /*!
     * \brief Retourne la pièce à la position donnée.
     * \param p la position de la pièce
     * \return la pièce à la position donnée
     * \throw TaquinException si les positions sont hors limites
     */
    Piece getPiece(Position p);

    /*!
     * \brief Retourne la position de l'emplacement vide.
     * \return la position de l'emplacement vide
     */
    Position getPositionVide();

    /*!
     * \brief Met toutes les pièces à leur emplacement correct.
     * \todo Tri incomplet.
     */
    void setPiecesCorrectes();

    /*!
     * \brief Mélange les pièces.
     */
    void melangerPieces();

    /*!
     * \brief Déplace la pièce dont la position est donnée par positionPiece.
     * \param positionPiece la position de la pièce à déplacer
     * \return <code>true</code> si la pièce a été déplacée,
     * <code>false</code> sinon
     */
    bool deplacerPiece(Position positionPiece);

    /*!
     * \brief Déplace la pièce dans la direction donnée.
     * \param direction la direction vers laquelle la pièce doit être déplacée
     * \return <code>true</code> si la pièce a été déplacée,
     * <code>false</code> sinon
     */
    bool deplacerPiece(Direction direction);

    /*!
     * \brief Retourne le nombre de mouvements effectués depuis le début de la
     * partie.
     * \return le nombre de mouvements effectués depuis le début de la partie
     */
    int getNombreMouvements();

    /*!
     * \brief Vérifie si la partie est résolue ou non
     * \return <code>true</code> si la partie est résolue,
     * <code>false</code> sinon
     */
    bool estResolu();
};

std::ostream &operator<<(std::ostream &out, Taquin in);

#endif // TAQUIN_H
