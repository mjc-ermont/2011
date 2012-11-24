#include "FenPrincipale.h"

FenPrincipale::FenPrincipale(Serial* _com) :  historique(new Donnees()){


    qDebug() << "Test 1";
    connect(historique, SIGNAL(msg(QString)), this, SLOT(message(QString)));


    //------------------------------------------------------------------------------------------------------


    qDebug() << "Test 2";

    com = _com;
    optimisation_graph = false;

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

    carte = new MapsView(c_maps);
    befLine = 0;


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

void FenPrincipale::resizeEvent(QResizeEvent *) {
    if(optimisation_graph)
        optimise_graph();

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
        QPalette palette = lcd_min->palette();
        palette.setColor(QPalette::Normal, QPalette::Foreground, Qt::red);
        lcd_min->setPalette(palette);
    } else if(m == 43) {
        lcd_min->setPalette(lcd_hour->palette());
    }

    lcd_hour->display(h);
    lcd_min->display(m);
    lcd_sec->display(s);
}

void FenPrincipale::informationsReceived(QStringList trames) {
    if(trames.size() > 0) {
     //   message("[INFO] Informations received.");

      /*  for(int i=0;i<trames.size();i++) {
            message("*" + trames[i]);
            qDebug() << ;
        }*/
        for(int i=0;i<trames.size();i++)
            curLine.addData(trames[i]);


        historique->appendLine(&curLine);
        tableauBord->update(&curLine);
        curLine.clear();

        for(int i=0;i<graphiques.size();i++) {
            graphiques[i].first->majData(historique);
        }
    }

    #ifdef DEBUG
    /*    message("[INFAKE] Informations received.");

        Line *l = new Line;
        l->randUpdate(befLine);
        befLine = l;
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

        double valLat = latAngle + latMinute / 100;
        double valLong = longAngle + longMinute / 100;

        carte->addPoint(valLat,valLong);


        for(int i=0;i<graphiques.size();i++) {
            graphiques[i].first->majData(historique);
        }*/
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

    QPair<GraphicView*,QMdiSubWindow*> group;
    QMdiSubWindow *w = zone_graph->addSubWindow(g);
    group.first = g;
    group.second = w;

    graphiques.append(group);

    w->setGeometry(w->geometry().x(),w->geometry().y(),200,200);

    w->show();

    connect(g,SIGNAL(destroyed()),this,SLOT(graphClosed()));

    if(optimisation_graph) {
        optimise_graph();
    }
    g->setWindowTitle(g->windowTitle() + " (" + QString::number(graphiques.size() - 1) + ")");
}

void FenPrincipale::graphClosed() {
    GraphicView* g = (GraphicView *)sender();
    for(int i=0;i<graphiques.size();i++) {
        if(g == graphiques[i].first)
            graphiques.remove(i);
    }

    if(optimisation_graph) {
        optimise_graph();
    }
}

void FenPrincipale::on_btn_optimiser_clicked()
{
    if(btn_optimiser->isChecked())
        optimise_graph();

    optimisation_graph = btn_optimiser->isChecked();
}

void FenPrincipale::optimise_graph() {
    int nbItems = graphiques.size();
    qDebug() << "Nb graphs: " << nbItems;
    qDebug() << "Taille w: " << zone_graph->geometry().width() << "| h: " << zone_graph->geometry().height();


    int rowNb;
    int rowSize = zone_graph->geometry().height();
    int colNb;
    int colSize = zone_graph->geometry().width();

    for(int i=0;i<graphiques.size();i++) {
        int row, rowStretch, col, colStretch;
        bool error = false;
        switch(nbItems) {
            case 1:
                row = 0;
                rowStretch = 1;
                col = 0;
                colStretch = 1;
                rowNb = 1;
                colNb = 1;
                break;
            case 2:
                row = 0;
                rowStretch = 1;
                col = i;
                colStretch = 1;
                rowNb = 1;
                colNb = 2;
                break;
            case 3:
                row = !(i == 0);
                rowStretch = 1;
                col = (i == 2);
                colStretch = (i == 0) ? 2 : 1;
                rowNb = 2;
                colNb = 2;
                break;
            case 4:
                row = !(i<=1);
                rowStretch = 1;
                col = !((i==0) || (i==2));
                colStretch = 1;
                rowNb = 2;
                colNb = 2;
                break;
            case 5:
                row = !(i<3);
                rowStretch = (i==1) +1;
                col = (i<=2) ? i : ((i == 3) ? 0 : 2 );
                colStretch = 1;
                rowNb = 2;
                colNb = 3;
                break;
            case 6:
                row = !(i<3);
                rowStretch = 1;
                col = (i<=2) ? i : i-3;
                colStretch = 1;
                rowNb = 2;
                colNb = 3;
                break;
            case 7:
                row = !(i<3);
                rowStretch = 1;
                col = (i<=2) ? ((i==2) ? 3 : i): i-3;
                colStretch = (i == 1) ? 2 : 1;
                rowNb = 2;
                colNb = 4;
                break;
            case 8:
                row = !(i<=3);
                rowStretch = 1;
                col = (i<=3) ? i : i-4;
                colStretch = 1;
                rowNb = 2;
                colNb = 4;
                break;
            case 9:
                if(i<=4)
                    row = 0;
                else if(i<=7)
                    row = 1;
                else
                    row = 2;

                rowStretch = ((i == 5) || (i ==7)) + 1;

                if(i<=4) {
                    col = i;
                    colStretch = 1;
                } else if(i == 5) {
                    col = 0;
                    colStretch = 1;
                } else if(i == 6) {
                    col = 1;
                    colStretch = 3;
                } else if(i == 7) {
                    col = 4;
                    colStretch = 1;
                } else if(i == 8) {
                    col = 1;
                    colStretch = 3;
                }


                rowNb = 3;
                colNb = 5;
                break;
            case 10:
                if(i<=3)
                    row = 0;
                else if(i<=5)
                    row = 1;
                else
                    row = 2;

                rowStretch = 1;
                colStretch = ((i == 4) || (i == 5)) + 1;

                if(i<=3) {
                    col = i;
                } else if(i >= 6) {
                    col = i-6;
                } else if(i == 4) {
                    col = 0;
                } else if(i == 5) {
                    col = 2;
                }


                rowNb = 3;
                colNb = 4;
                break;
            default:
                error = true;
        }
        if(!error)
            graphiques[i].second->setGeometry(col * (colSize / colNb),row * (rowSize / rowNb), (colSize / colNb) * colStretch, (rowSize / rowNb) * rowStretch);
    }
}
