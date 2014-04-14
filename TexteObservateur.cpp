#include "TexteObservateur.h"

TexteObservateur::TexteObservateur(SujetDObservation *sdo) : QLabel() {
    jeu = static_cast<Taquin *> (sdo);
    jeu->attacher(this);

    QFont font("Monospace");
    font.setStyleHint(QFont::TypeWriter);
    font.setBold(true);
    font.setPointSize(12);
    this->setFont(font);
    this->rafraichir(sdo);
}

TexteObservateur::~TexteObservateur() noexcept {
    jeu->detacher(this);
}

void TexteObservateur::rafraichir(SujetDObservation *sdo) {
    if (sdo != jeu) {
        return;
    }
    oss.str("");
    oss.flush();
    oss << *jeu;

    this->setText(oss.str().c_str());
}

