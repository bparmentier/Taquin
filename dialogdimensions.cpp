#include "dialogdimensions.h"
#include "ui_dialogdimensions.h"

DialogDimensions::DialogDimensions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDimensions)
{
    ui->setupUi(this);
    this->setWindowTitle("Dimensions de la grille");
    connect(ui->rbDim3, SIGNAL(clicked()),
            this,
            SLOT(rbDim3Selected()));
    connect(ui->rbDim4, SIGNAL(clicked()),
            this,
            SLOT(rbDim4Selected()));
    connect(ui->rbDim5, SIGNAL(clicked()),
            this,
            SLOT(rbDim5Selected()));
    this->dimensions = 3;
}

DialogDimensions::~DialogDimensions()
{
    delete ui;
}

unsigned DialogDimensions::getDimensions() {
    return this->dimensions;
}

void DialogDimensions::setDimensions(unsigned dimensions) {
    this->dimensions = dimensions;
}
