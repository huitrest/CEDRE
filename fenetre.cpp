#include "fenetre.h"


Fenetre::Fenetre():QWidget()
{
    setFixedSize(800, 800);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
    this, SLOT(ShowContextMenu(const QPoint&)));
    m_scene = new QGraphicsScene(this);
    m_scene->setSceneRect(0,0,800,800);
    m_view = new QGraphicsView(m_scene,this);
    //m_view->setGeometry(0,0,500,500);
    m_view->show();
    v_idees=new std::vector <Idee*>;
    v_texte=new std::vector <QGraphicsTextItem*>;
    v_liens=new std::vector <Lien*>;
    v_ligne=new std::vector <QGraphicsLineItem*>;
    //zoom
}

void Fenetre::afficherIdee(Idee* idee,const QPoint& position)
{
    QGraphicsTextItem *text = m_scene->addText(idee->getNom());
    v_texte->push_back(text);
    text->setPos(position);
    idee->setPosition(position);
    //QGraphicsProxyWidget* slider = m_scene->addWidget(new QSlider(Qt::Horizontal,0));
}

void Fenetre::afficherLien(Lien* lien)
{
    v_liens->push_back(lien);
    QPen pen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin);
    QLine line(lien->getIdee1()->getPosition(),lien->getIdee2()->getPosition());
    QGraphicsLineItem *ligne= m_scene->addLine(line, pen);
    v_ligne->push_back(ligne);
}

void Fenetre::supprimerIdee(int pos){//supprime une idee et le texte affiché
    m_scene->removeItem(v_texte->at(pos));//fait disparaitre le texte
    Idee* idee = v_idees->at(pos);
    QGraphicsTextItem* text = v_texte->at(pos);
    delete(text);
    v_texte->erase(v_texte->begin()+pos);
    int trouve=0;
    int *tab = (int*) malloc(sizeof(int)*v_liens->size());
    v_idees->erase(v_idees->begin()+pos);
    for(unsigned int i=0;i<v_liens->size();i++){//regarde tous les liens concernés et les stocke dans tab
        if(idee->getNom()==v_liens->at(i)->getIdee1()->getNom() ||  idee->getNom()==v_liens->at(i)->getIdee2()->getNom()){
            tab[trouve]=i;
            trouve++;
        }
    }
    delete(idee);
    if(trouve>0){
            for(int i=0;i<trouve;i++){
                supprimerLien(tab[i]-i);//décalage dans le vecteur à chaque suppression
            }
    }
}

void Fenetre::supprimerLien(int pos){//supprime le lien et la ligne tracée
    m_scene->removeItem(v_ligne->at(pos));
    Lien* lien = v_liens->at(pos);
    delete(lien);
    QGraphicsLineItem* ligne = v_ligne->at(pos);
    delete(ligne);
    v_ligne->erase(v_ligne->begin()+pos);
    v_liens->erase(v_liens->begin()+pos);
}
void Fenetre::ShowContextMenu(const QPoint& pos) // Affiche le menu de contexte (pour creer l'idee)
{

    QPoint globalPos = this->mapToGlobal(pos);
    QMenu menu;
    const QString* strIdee=new QString("Créer Idée");
    QAction* actIdee=new QAction(*strIdee,&menu);
    menu.addAction(actIdee);

    const QString* strLien=new QString("Créer Lien");
    QAction* actLien=new QAction(*strLien,&menu);
    menu.addAction(actLien);

    const QString* strIdeeSuppr=new QString("Supprimer Idée");
    QAction* actIdeeSuppr=new QAction(*strIdeeSuppr,&menu);
    menu.addAction(actIdeeSuppr);

    const QString* strLienSuppr=new QString("Supprimer Lien");
    QAction* actLienSuppr=new QAction(*strLienSuppr,&menu);
    menu.addAction(actLienSuppr);
    QAction* selectedItem = menu.exec(globalPos);
    if (selectedItem==actIdee)
    {
        QString nomIdee = QInputDialog::getText(this, tr(""),
                                                 tr("Nom de l'idée:"));
        Idee* idee = new Idee(nomIdee);
        afficherIdee(idee,pos);
        v_idees->push_back(idee);
    }
    else if(selectedItem==actLien){
        QString nomIdee1 = QInputDialog::getText(this, tr(""),
                                                 tr("Nom de l'idée 1:"));
        QString nomIdee2 = QInputDialog::getText(this, tr(""),
                                                 tr("Nom de l'idée 2:"));
        Idee* Idee1=NULL;
        Idee* Idee2=NULL;
        for(unsigned int i=0;i<v_idees->size();i++){
            if(nomIdee1==v_idees->at(i)->getNom()){
                Idee1=v_idees->at(i);
            }
            if(nomIdee2==v_idees->at(i)->getNom()){
                Idee2=v_idees->at(i);
            }

        }
        if(Idee1!=NULL && Idee2!=NULL && Idee1!=Idee2){
                Lien* lien = new Lien(*Idee1,*Idee2);
                afficherLien(lien);
        }
    }
    else if(selectedItem==actIdeeSuppr){
        QString nomIdee = QInputDialog::getText(this, tr(""),
                                                 tr("Nom de l'idée:"));
        int pos=-1;
        for(unsigned int i=0;i<v_idees->size();i++){
            if(nomIdee==v_idees->at(i)->getNom()){
               pos=i;
            }
        }
        if(pos!=-1){
                supprimerIdee(pos);
        }

    }
    else if(selectedItem==actLienSuppr){
        QString nomIdee1 = QInputDialog::getText(this, tr(""),
                                                 tr("Nom de l'idée 1:"));
        QString nomIdee2 = QInputDialog::getText(this, tr(""),
                                                 tr("Nom de l'idée 2:"));

        int pos1=0;
        int pos2=1;
        for(unsigned int i=0;i<v_liens->size();i++){
            if(nomIdee1==v_liens->at(i)->getIdee1()->getNom() || nomIdee1==v_liens->at(i)->getIdee2()->getNom()){
                pos1=i;
            }
            if(nomIdee2==v_liens->at(i)->getIdee1()->getNom() || nomIdee2==v_liens->at(i)->getIdee2()->getNom()){
                pos2=i;
            }

        }
        if(pos1==pos2){
                supprimerLien(pos2);
        }
    }
    else
    {
    }
}
void Fenetre::mousePressEvent(QMouseEvent *event)//redefinition de mousePressEvent() (gere les clics de souris)
{
    if(event->button() == Qt::RightButton)//si clic droit affiche le menu de contexte à la position du clic
    {
        this->ShowContextMenu(event->pos());
    }
}
void Fenetre::keyPressEvent( QKeyEvent * event )//redefinition de keyPressEvent() (gere les touches pressees)
{
    if(event->key() == 43)//si + est pressee zoom *2
    {
        m_view->scale(2,2);
    }
    if(event->key() == 45){//si - est pressee zoom /2
       m_view->scale(0.5,0.5);
    }
}


