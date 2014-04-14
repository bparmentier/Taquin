/*!
 * \file Direction.h
 * \brief Définition de la classe d'énumération Direction.
 */

#ifndef DIRECTION_H
#define DIRECTION_H

//! Classe d'énumération Direction.
/*!
 * \brief Définit différentes directions : NONE, UP, RIGHT, DOWN, LEFT.
 * \author Bruno Parmentier
 */

enum class Direction {
    NONE,   /*!< Énumération NONE. */
    UP,     /*!< Énumération UP. */
    RIGHT,  /*!< Énumération RIGHT. */
    DOWN,   /*!< Énumération DOWN. */
    LEFT    /*!< Énumération LEFT. */
};

#endif // DIRECTION_H
