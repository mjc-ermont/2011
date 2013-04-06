#include "fileimportdialog.h"

FileImportDialog::FileImportDialog(FenPrincipale *parent) : QDialog(parent)
{
    m_parent = parent;
    setupUi(this);
}

FileImportDialog::~FileImportDialog()
{
}

void FileImportDialog::on_choirlefichier_clicked() {
    QString path = QFileDialog::getOpenFileName(this,"Jus de carotte");
    if(path != "")
        fileLineEdit->setText(path);
}

void FileImportDialog::on_buttonBox_accepted() {
    QFile f(fileLineEdit->text());
    f.open(QFile::ReadOnly);
    QString content = f.readAll();
    QStringList trames = content.split("@");
    int i=0;
    QTime base = QTime::currentTime();
    foreach(QString trame, trames) {
        Data* d = m_parent->getSensorMgr()->addData(trame);
        if(d != NULL)
            d->time = QTime(base.hour(),base.minute(),base.second()+i);

        i++;
    }
}
