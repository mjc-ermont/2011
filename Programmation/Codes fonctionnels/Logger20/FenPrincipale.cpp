#include "FenPrincipale.h"

FenPrincipale::FenPrincipale(Serial* _com) :  historique(new Donnees()){


    qDebug() << "Test 1";
    connect(historique, SIGNAL(msg(QString)), this, SLOT(message(QString)));

    //------------------------------------------------------------------------------------------------------


    qDebug() << "Test 2";

    com = _com;


    qDebug() << "Test 3";
    setupUi(this);
    message("[INFO] Core initialized. GUI Loaded.");

    stack->setCurrentIndex(0);

    sel_capteur->addItems(curLine.getCapteursNames());
    for(int i=0;i<NB_VALEURS_MAX;i++) {
        QString val_name =curLine.getValueNames()[i];
        if(val_name != "-1")
            sel_valeur->addItem(val_name);
    }


    for(int i=0;i<NB_CAPTEURS ;i++) {
        QTableView *t = new QTableView;
        tableauxHist.append(t);

        tab_historique->addTab(t,curLine.getCapteursNames()[i]);
        t->setModel(historique->toTable(i));

    }

    carte = new MapsView(p_maps);


    if(QFile::exists(QApplication::applicationDirPath() + "/save.log")){
        historique->open();
    }

    message("[INFO] Loading boarding table...");

    tableauBord = new BoardingTable(container);
    message("[INFO] Loaded !");


    message("[INFO] Starting refreshing timers");

    timerAct = new QTimer();
    connect(timerAct,SIGNAL(timeout()),this,SLOT(requestAct()));

    timerAct->start(UPDATE_TIME);

    actTemps = new QTimer();
    connect(actTemps,SIGNAL(timeout()),this,SLOT(syncTime()));

    actTemps->start(1000);

    message("[INFO] All started !");



    connect(com,SIGNAL(dataRead(QStringList)),this,SLOT(informationsReceived(QStringList)));
    requestAct();

    #ifdef DEBUG
        message("[WARNING] !! DEBUG MODE ACTIVATED !! SERIAL COMMUNICATIONS ARE NOT ENABLED.");
    #endif

    h_depart = QTime::currentTime();
}

FenPrincipale::~FenPrincipale(){

}

void FenPrincipale::requestAct() {

    if(get_infos->isChecked())
        com->readData();

}

void FenPrincipale::syncTime() {
    int h,m,s;
    h = QTime::currentTime().hour();
    m = QTime::currentTime().minute();
    s = QTime::currentTime().second();

    if(s==42) {
        QPalette palette = lcd_sec->palette();
        palette.setColor(QPalette::Normal, QPalette::Foreground, Qt::red);
        lcd_sec->setPalette(palette);
    } else if((s>=42)&&(s<=45)) {
        s = 42;
    }else if(s == 46) {
        lcd_sec->setPalette(lcd_hour->palette());
    }


    if(m==42) {
        QPalette palette = lcd_sec->palette();
        palette.setColor(QPalette::Normal, QPalette::Foreground, Qt::red);
        lcd_sec->setPalette(palette);
    } else if(m == 43) {
        lcd_sec->setPalette(lcd_hour->palette());
    }

    lcd_hour->display(h);
    lcd_min->display(m);
    lcd_sec->display(s);
}

void FenPrincipale::informationsReceived(QStringList trames) {
    if(trames.size() > 0) {
        message("[INFO] Informations received.");

        for(int i=0;i<trames.size();i++) {
            message("*" + trames[i]);
            curLine.addData(trames[i]);
        }



        historique->appendLine(&curLine);
        tableauBord->update(&curLine);
        curLine.clear();

        for(int i=0;i<graphiques.size();i++) {
            graphiques[i]->majData(historique);
        }
    }

    #ifdef DEBUG
        message("[INFAKE] Informations received.");
        Line *l = new Line;
        l->randUpdate();
        historique->appendLine(l);
        tableauBord->update(l);

        double latAngle = l->getValue(0,0);
        double latMinute = l->getValue(0,1);
        double longAngle = l->getValue(0,2);
        double longMinute = l->getValue(0,3);

        /*
         *
         * CELA NE MARCHE PAAAAAAAAAAAAAAAAAAAAAAAAAAS !!!!!!!!!!!!!!!!!!!!!!
         *
         *
         */
        double valLat = latAngle + latMinute / 100;
        double valLong = longAngle + longMinute / 100;

        carte->addPoint(valLat,valLong);


        for(int i=0;i<graphiques.size();i++) {
            graphiques[i]->majData(historique);
        }
    #endif
}

void FenPrincipale::append(Line *a){
    historique->appendLine(a);
}

void FenPrincipale::message(QString message){

    message = QDateTime::currentDateTime().toString("[hh:mm:ss] ") + message;

    barreStatus->showMessage(message);
    console->appendPlainText(message);
}


void FenPrincipale::on_actionQuitter_triggered()
{
    qApp->quit();
}

void FenPrincipale::on_b_console_clicked()
{
    reinit_b();
    b_console->setDefault(true);

    stack->setCurrentIndex(1);
}

void FenPrincipale::on_b_tb_clicked()
{
    reinit_b();
    b_tb->setDefault(true);

    stack->setCurrentIndex(0);
}

void FenPrincipale::on_b_table_clicked()
{
    reinit_b();
    b_table->setDefault(true);

    stack->setCurrentIndex(2);
}

void FenPrincipale::on_b_param_clicked()
{
    reinit_b();
    b_param->setDefault(true);

    stack->setCurrentIndex(3);
}

void FenPrincipale::on_b_graph_clicked()
{
    reinit_b();
    b_graph->setDefault(true);

    stack->setCurrentIndex(4);
}

void FenPrincipale::on_b_carte_clicked()
{
    reinit_b();
    b_carte->setDefault(true);

    stack->setCurrentIndex(5);
}

void FenPrincipale::reinit_b(){
    b_tb->setDefault(false);
    b_table->setDefault(false);
    b_console->setDefault(false);
    b_param->setDefault(false);
    b_graph->setDefault(false);
    b_carte->setDefault(false);
}


void FenPrincipale::on_sel_capteur_currentIndexChanged(int index)
{
    sel_valeur->clear();

    for(int i=0;i<NB_VALEURS_MAX;i++) {
        QString val_name =curLine.getValueNames()[NB_VALEURS_MAX*index+i];
        if(val_name != "-1")
            sel_valeur->addItem(val_name);
    }
}

void FenPrincipale::on_add_graph_clicked()
{
    GraphicView* g = new GraphicView(historique, sel_capteur->currentIndex(), sel_valeur->currentIndex(),this);
    graphiques.append(g);

    QMdiSubWindow *w = zone_graph->addSubWindow(g);
    w->setGeometry(w->geometry().x(),w->geometry().y(),200,200);

    w->show();

    connect(g,SIGNAL(destroyed()),this,SLOT(graphClosed()));
}

void FenPrincipale::graphClosed() {
    GraphicView* g = (GraphicView *)sender();
    for(int i=0;i<graphiques.size();i++) {
        if(g == graphiques[i])
            graphiques.remove(i);
    }

}
