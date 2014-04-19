/*!
 * \file dialogdimensions.h
 * \brief Définitions de la classe DialogDimensions
 */

#ifndef DIALOGDIMENSIONS_H
#define DIALOGDIMENSIONS_H

#include <QDialog>

namespace Ui {
class DialogDimensions;
}

//! Classe DialogDimensions
/*!
 * \brief Boîte de dialogue pour la sélection des dimensions de la grille
 * \author Bruno Parmentier
 */
class DialogDimensions : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDimensions(QWidget *parent = 0);
    ~DialogDimensions();
    unsigned getDimensions();

private:
    Ui::DialogDimensions *ui;
    unsigned dimensions;

    void setDimensions(unsigned dimensions);

private slots:
    void rbDim3Selected() { this->setDimensions(3); }
    void rbDim4Selected() { this->setDimensions(4); }
    void rbDim5Selected() { this->setDimensions(5); }
};

#endif // DIALOGDIMENSIONS_H
