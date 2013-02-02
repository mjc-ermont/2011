#include "dialog.h"

AskDialog::AskDialog()
{
    setupUi(this);

    connect(pushButton,SIGNAL(clicked()),this,SLOT(continueClicked()));
    fen=NULL;


    QFile file("conf/serialPorts.ini");
    file.open(QIODevice::ReadOnly);
    QStringList paths = QString(file.readAll()).split(';');

    for(int i=0;i<paths.size();i++)
        selectEntry->addItem(paths[i]);

    selectEntry->addItem("Autre");
    textEntry->setVisible(false);
    addToList->setVisible(false);
}

AskDialog::~AskDialog()
{
    if(fen!=NULL)
        delete fen;
}

void AskDialog::continueClicked()
{
    QString port = "";
    if(selectEntry->currentText() == "Autre")
        port = textEntry->text();
    else
        port = selectEntry->currentText();

    Serial* com = new Serial(port);

    com->start();


    fen = new FenPrincipale(com);

    fen->show();

    this->close();
}

void AskDialog::on_selectEntry_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "Autre") {
        textEntry->setVisible(true);
        addToList->setVisible(true);
    } else {
        textEntry->setVisible(false);
        addToList->setVisible(false);
    }
}

void AskDialog::on_addToList_clicked() {
    if(textEntry->text() == "")
        return;


    qDebug()<<selectEntry->size();

    selectEntry->removeItem(selectEntry->size().rheight()-1);
    selectEntry->addItem(textEntry->text());
    selectEntry->addItem("Autre");
}

void AskDialog::saveToFile() {
  /*  QStringList entries;
    for(int i=0;i<selectEntry->size().rheight()-1;i++)
        entries<<selectEntry->itemText(i);*/

   /* QFile file("conf/serialPorts.ini");
    file.remove();*/
    QFile::resize("conf/serialPorts.ini",1);
}
