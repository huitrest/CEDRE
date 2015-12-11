#ifndef LIEN_H
#define LIEN_H

#include <Qline>
#include "idee.h"

class Lien
{
public:
    Lien(Idee idee1,Idee idee2);
    Idee* getIdee1();
    Idee* getIdee2();
private:
    Idee m_idee1;
    Idee m_idee2;
    QLine* m_ligne;
};


#endif // LIEN_H
