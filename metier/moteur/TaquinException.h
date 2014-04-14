/*!
 * \file TaquinException.h
 * \brief Définition de la classe TaquinException.
 */

#ifndef TAQUINEXCEPTION_H
#define TAQUINEXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;

//! Classe TaquinException
/*!
 * \brief Exception du jeu de Taquin.
 * \see std::logic_error
 * \author Bruno Parmentier
 */
class TaquinException : public logic_error {
    //string msg {};
public:
    //! Constructeur de TaquinException
    /*!
     * Construit une TaquinException.
     * \param msg le message à envoyer
     */
    explicit TaquinException(const std::string &msg) : logic_error(msg) {}
    //TaquinException (string s) { msg = s; }
    //const char *what() const throw();
};

#endif // TAQUINEXCEPTION_H
