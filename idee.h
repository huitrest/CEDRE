#ifndef IDEE_H
#define IDEE_H

#include <Qpoint>
#include <Qstring>
#include <vector>

class Idee
{
public:
    Idee();
    Idee(QString nom);
    Idee(QString nom,QString description);
    QString getNom();
    QPoint getPosition();
    void setPosition(QPoint pos);
private:
    QString m_nom;
    QString m_description;
    QPoint m_position;
};

#endif // IDEE_H
