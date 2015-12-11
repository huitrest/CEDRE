#include "lien.h"

Lien::Lien(Idee idee1,Idee idee2)
{
    m_idee1=idee1;
    m_idee2=idee2;
    m_ligne=new QLine(idee1.getPosition(),idee2.getPosition());
}

Idee* Lien::getIdee1(){
    return &m_idee1;
}

Idee* Lien::getIdee2(){
    return &m_idee2;
}
