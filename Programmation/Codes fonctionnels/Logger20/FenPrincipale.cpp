#include "FenPrincipale.h"
#include "ui_FenPrincipale.h"

FenPrincipale::FenPrincipale(Serial* _com) : ui(new Ui::FenPrincipale), historique(new Donnees()){


    qDebug() << "Test 1";
    connect(historique, SIGNAL(msg(QString)), this, SLOT(message(QString)));

    //------------------------------------------------------------------------------------------------------


    qDebug() << "Test 2";

    com = _com;


    qDebug() << "Test 3";
    ui->setupUi(this);
    message("[INFO] Core initialized. GUI Loaded.");

    ui->stack->setCurrentIndex(0);

    ui->sel_capteur->addItems(curLine.getCapteursNames());
    for(int i=0;i<NB_VALEURS_MAX;i++) {
        QString val_name =curLine.getValueNames()[i];
        if(val_name != "-1")
            ui->sel_valeur->addItem(val_name);
    }


    for(int i=0;i<NB_CAPTEURS ;i++) {
        QTableView *t = new QTableView;
        tableauxHist.append(t);

        ui->tab_historique->addTab(t,curLine.getCapteursNames()[i]);
        t->setModel(historique->toTable(i));

    }


    if(QFile::exists(QApplication::applicationDirPath() + "/save.log")){
        historique->open();
    }

    message("[INFO] Loading boarding table...");

    tableauBord = new BoardingTable(ui->container);
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
}

FenPrincipale::~FenPrincipale(){
    delete ui;
}

void FenPrincipale::requestAct() {

    if(ui->get_infos->isChecked())
        com->readData();

}

void FenPrincipale::syncTime() {
    int h,m,s;
    h = QTime::currentTime().hour();
    m = QTime::currentTime().minute();
    s = QTime::currentTime().second();

    if(s==42) {
        QPalette palette = ui->lcd_sec->palette();
        palette.setColor(QPalette::Normal, QPalette::Foreground, Qt::red);
        ui->lcd_sec->setPalette(palette);
    } else if((s>=42)&&(s<=45)) {
        s = 42;
    }else if(s == 46) {
        ui->lcd_sec->setPalette(ui->lcd_hour->palette());
    }


    if(m==42) {
        QPalette palette = ui->lcd_sec->palette();
        palette.setColor(QPalette::Normal, QPalette::Foreground, Qt::red);
        ui->lcd_sec->setPalette(palette);
    } else if(m == 43) {
        ui->lcd_sec->setPalette(ui->lcd_hour->palette());
    }

    ui->lcd_hour->display(h);
    ui->lcd_min->display(m);
    ui->lcd_sec->display(s);
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
    }

    #ifdef DEBUG
        message("[INFAKE] Informations received.");
        Line *l = new Line;
        l->randUpdate();
        historique->appendLine(l);
        tableauBord->update(l);
    #endif
}

void FenPrincipale::append(Line *a){
    historique->appendLine(a);
}

void FenPrincipale::message(QString message){

    message = QDateTime::currentDateTime().toString("[hh:mm:ss] ") + message;

    ui->statusBar->showMessage(message);
    ui->console->appendPlainText(message);
}


void FenPrincipale::on_actionQuitter_triggered()
{
    qApp->quit();
}

void FenPrincipale::on_b_console_clicked()
{
    reinit_b();
    ui->b_console->setDefault(true);

    ui->stack->setCurrentIndex(1);
}

void FenPrincipale::on_b_tb_clicked()
{
    reinit_b();
    ui->b_tb->setDefault(true);

    ui->stack->setCurrentIndex(0);
}

void FenPrincipale::on_b_table_clicked()
{
    reinit_b();
    ui->b_table->setDefault(true);

    ui->stack->setCurrentIndex(2);
}

void FenPrincipale::on_b_param_clicked()
{
    reinit_b();
    ui->b_param->setDefault(true);

    ui->stack->setCurrentIndex(3);
}

void FenPrincipale::on_b_graph_clicked()
{
    reinit_b();
    ui->b_graph->setDefault(true);

    ui->stack->setCurrentIndex(4);
}

void FenPrincipale::reinit_b(){
    ui->b_tb->setDefault(false);
    ui->b_table->setDefault(false);
    ui->b_console->setDefault(false);
    ui->b_param->setDefault(false);
    ui->b_graph->setDefault(false);
}


void FenPrincipale::on_sel_capteur_currentIndexChanged(int index)
{
    ui->sel_valeur->clear();

    for(int i=0;i<NB_VALEURS_MAX;i++) {
        QString val_name =curLine.getValueNames()[NB_VALEURS_MAX*index+i];
        if(val_name != "-1")
            ui->sel_valeur->addItem(val_name);
    }
}

void FenPrincipale::on_add_graph_clicked()
{
    GraphicView* g = new GraphicView();
    graphiques.append(g);
    ui->zone_graph->addSubWindow(g)->show();
}
