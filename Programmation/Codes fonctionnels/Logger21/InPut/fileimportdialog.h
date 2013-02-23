#ifndef FILEIMPORTDIALOG_H
#define FILEIMPORTDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include "../FenPrincipale.h"
#include "ui_fileimportdialog.h"


class FileImportDialog : public QDialog, public Ui::FileImportDialog
{
    Q_OBJECT
    
public:
    explicit FileImportDialog(FenPrincipale *parent = 0);
    ~FileImportDialog();
    
private slots:
    void on_choirlefichier_clicked();

    void on_buttonBox_accepted();

private:
    FenPrincipale* m_parent;
};

#endif // FILEIMPORTDIALOG_H
