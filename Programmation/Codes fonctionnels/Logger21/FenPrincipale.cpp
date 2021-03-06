#include "FenPrincipale.h"
#include "InPut/fileimportdialog.h"

FenPrincipale::FenPrincipale(Serial* _com) {



    //------------------------------------------------------------------------------------------------------


    this->setWindowTitle("Récupérateur des informations reçues par le biais du Kiwi au melon.");

    com = _com;
    optimisation_graph = false;
    setupUi(this);

    stack->setCurrentIndex(0);


    sensormgr = new SensorManager(this);
    QVector<Sensor*> sensorList = sensormgr->getSensors();
    nbSensors = sensorList.size();
    foreach(Sensor* s, sensorList)
        sel_capteur->addItem(s->getName());

    for(int i=0;i<nbSensors ;i++) {
        QTableView *t = new QTableView;
        tableauxHist.append(t);

        tab_historique->addTab(t,sensormgr->getSensor(i)->getName());

        QStandardItemModel *modele = new QStandardItemModel;
       // int v=1;
       // modele->setHorizontalHeaderItem(0,new QStandardItem("Temps"));
        int v=0;
        foreach(SensorValue* s,  sensormgr->getSensor(i)->getValues()) {
            modele->setHorizontalHeaderItem(v,new QStandardItem(s->getName()));
            v++;
        }

        t->setModel(modele);
    }

    tableManager = new TableMgr(&tableauxHist);
    carte = new MapsView(c_maps);


    message("[INFO] Loading boarding table...");

    tableauBord = new BoardingTable(container,sensormgr);
    message("[INFO] Loaded !");


    qDebug() << "pizzdrfa";
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
    chronoWidget = new ChronoReaderWidget;
    chronolayout->addWidget(chronoWidget);


    QFile file("conf/url.ini");
    file.open(QIODevice::ReadOnly);
    QString url = QString(file.readAll());
    file.close();
    dataServerLineEdit->setText(url);

    QFile df("conf/datedepart.ini");
    df.open(QIODevice::ReadOnly);
    QString date = QString(df.readAll());
    df.close();

    int h=date.split(":").at(0).toInt();
    int m=date.split(":").at(1).toInt();
    int s=date.split(":").at(2).toInt() ;

    heureLancement->setTime(QTime(h,m,s));
    chronoWidget->laucherCounter(QTime(h,m,s));
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

    lcd_hour->display(QString("%1").arg(h, 10, 10, QChar('0').toUpper()));
    lcd_min->display(QString("%1").arg(m, 10, 10, QChar('0').toUpper()));
    lcd_sec->display(QString("%1").arg(s, 10, 10, QChar('0').toUpper()));
}

void FenPrincipale::informationsReceived(QStringList trames) {
    if(trames.size() > 0) {
        for(int i=0;i<trames.size();i++) {
            sensormgr->addData(trames[i]);
        }

        QPair<GraphicView*,QMdiSubWindow*> value;
        foreach(value,graphiques) {
            value.first->majData();
        }
    }
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

void FenPrincipale::on_actionOuvrir_triggered()
{
    FileImportDialog *fi_dialog = new FileImportDialog(this);
    fi_dialog->show();
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

    foreach(SensorValue *v, sensormgr->getSensor(index)->getValues())
        sel_valeur->addItem(v->getName());
}

void FenPrincipale::on_add_graph_clicked()
{
    GraphicView* g = new GraphicView(sel_capteur->currentIndex(), sel_valeur->currentIndex(),this);

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

void FenPrincipale::on_actualizeTableButton_clicked()
{
    if(check_all_values->isChecked()) {
        //TODO: Travailler
    } else {
        QTime start = time_start->time();
        QTime end   =   time_end->time();

        if(TimeCalcs::toMs(start) < TimeCalcs::toMs(end)) {
            start = TimeCalcs::fromMs(TimeCalcs::toMs(start) + TimeCalcs::toMs(h_depart));
            end   = TimeCalcs::fromMs(TimeCalcs::toMs(end) + TimeCalcs::toMs(h_depart));
            tableManager->actualisay(start,end,sensormgr);
        } else {
            start = TimeCalcs::fromMs(TimeCalcs::toMs(QTime::currentTime()) - TimeCalcs::toMs(time_start->time()));
            end   = TimeCalcs::fromMs(TimeCalcs::toMs(QTime::currentTime()) - TimeCalcs::toMs(time_end->time()));
            tableManager->actualisay(start,end,sensormgr);
        }
    }
}


void FenPrincipale::on_dataServerLineEdit_editingFinished()
{
    QFile file("conf/url.ini");
    file.open(QIODevice::ReadWrite);
    file.resize(0);
    file.write(dataServerLineEdit->text().toStdString().c_str());
    file.close();
}

void FenPrincipale::on_heureLancement_timeChanged(const QTime &time)
{
    QFile file("conf/datedepart.ini");
    file.open(QIODevice::ReadWrite);
    file.resize(0);
    file.write((QString::number(heureLancement->time().hour())+":"+QString::number(heureLancement->time().minute())+":"+QString::number(heureLancement->time().second())).toStdString().c_str());
    file.close();

}

void FenPrincipale::on_horizontalSlider_sliderMoved(int position)
{
    if(position<60) {
        if(position == 1)
            bowltext->setText(QString::number(position) + " minute");
        else
            bowltext->setText(QString::number(position) + " minutes");
    } else  {
        int heures = (position-position%60)/60;
        QString heureMsg = heures>1 ? " heures ":" heure ";

        int minutes = position%60;
        QString minutesMsg = minutes>1 ? " minutes ":" minute ";

        if(minutes == 0)
            bowltext->setText(QString::number(heures) + heureMsg);
        else
            bowltext->setText(QString::number(heures) + heureMsg + QString::number(minutes) + minutesMsg);
    }
}

void FenPrincipale::on_horizontalSlider_sliderReleased()
{
    int position = horizontalSlider->value();

    QPair<GraphicView*,QMdiSubWindow*> value;
    foreach(value,graphiques) {
     //  value.first->majData(QTime(0,position,0));
    }
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
