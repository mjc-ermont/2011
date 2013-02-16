#ifndef DIALOG_H
#define DIALOG_H

#include <QtGui>
#include "ui_dialog.h"
#include "InPut/serial.h"
#include "FenPrincipale.h"

class AskDialog : public QDialog, public Ui::Dialog
{
    Q_OBJECT

public:
    AskDialog();
    ~AskDialog();

protected:
    void saveToFile();
private slots:
    void continueClicked();
    void on_selectEntry_currentIndexChanged(const QString &arg1);

    void on_addToList_clicked();

    void on_removeButton_clicked();

private:
    FenPrincipale* fen;
    int nItems;
};

#endif // DIALOG_H
