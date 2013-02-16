#include "dialog.h"

AskDialog::AskDialog()
{
    setupUi(this);

    connect(pushButton,SIGNAL(clicked()),this,SLOT(continueClicked()));
    fen=NULL;


    QFile file("conf/serialPorts.ini");
    file.open(QIODevice::ReadOnly);
    QStringList paths = QString(file.readAll()).split(';');
    nItems=0;

    for(int i=0;i<paths.size();i++) {
        nItems++;
        selectEntry->addItem(paths[i]);
    }

    nItems++;
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

    selectEntry->removeItem(nItems-1);
    nItems++;
    selectEntry->addItem(textEntry->text());
    selectEntry->addItem("Autre");

    saveToFile();
}

void AskDialog::on_removeButton_clicked()
{
    if(selectEntry->currentText() != "Autre") {
        nItems--;
        selectEntry->removeItem(selectEntry->currentIndex());
        saveToFile();
    }
}


void AskDialog::saveToFile() {
    QStringList entries;
    for(int i=0;i<nItems-1;i++)
        entries<<selectEntry->itemText(i);

    QFile file("conf/serialPorts.ini");
    file.open(QFile::ReadWrite);
    file.resize(0);
    QString s = entries.join(";");
    s.replace("\n","");
    file.write(s.toStdString().c_str());
}

