#ifndef FENETRE_H
#define FENETRE_H
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <QListView>
#include <QMenu>
#include <QInputDialog>
#include <QSlider>
#include <stdio.h>
#include "idee.h"
#include "lien.h"

class Fenetre: public QWidget
{
public:
    Fenetre();
    void afficherIdee(Idee* idee,const QPoint& position);
    void afficherLien(Lien* lien);
    void supprimerIdee(int pos);
    void supprimerLien(int pos);
    void ShowContextMenu(const QPoint& pos);
protected:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent( QKeyEvent * event );
private:
    QGraphicsScene *m_scene;
    QGraphicsView *m_view;
    std::vector <Idee*>* v_idees;
    std::vector <QGraphicsTextItem*>* v_texte;
    std::vector <Lien*>* v_liens;
    std::vector <QGraphicsLineItem*>* v_ligne;
};

#endif // FENETRE_H
