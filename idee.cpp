#include "idee.h"

using namespace std;

Idee::Idee(){
    m_nom="default";
}

Idee::Idee(QString nom){
    m_nom = nom;
}

Idee::Idee(QString nom, QString description){
    m_nom = nom;
    m_description = description;
}

QString Idee::getNom(){
    return m_nom;
}
QPoint Idee::getPosition(){
    return m_position;
}
void Idee::setPosition(QPoint pos){
    m_position=pos;
}

