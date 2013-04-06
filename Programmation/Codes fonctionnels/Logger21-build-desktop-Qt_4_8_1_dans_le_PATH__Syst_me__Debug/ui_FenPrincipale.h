/********************************************************************************
** Form generated from reading UI file 'FenPrincipale.ui'
**
** Created: Sat Mar 23 17:10:38 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENPRINCIPALE_H
#define UI_FENPRINCIPALE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QCommandLinkButton>
#include <QtGui/QDial>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMdiArea>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStackedWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QTimeEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FenPrincipale
{
public:
    QAction *actionQuitter;
    QAction *actionOuvrir;
    QWidget *widgetCentral;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout_2;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QLCDNumber *lcd_hour;
    QLabel *label;
    QLCDNumber *lcd_min;
    QLabel *label_2;
    QLCDNumber *lcd_sec;
    QDial *dial_2;
    QVBoxLayout *chronolayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QDial *dial;
    QPushButton *b_tb;
    QPushButton *b_graph;
    QPushButton *b_carte;
    QPushButton *b_console;
    QPushButton *b_table;
    QPushButton *b_param;
    QTextBrowser *textBrowser_4;
    QStackedWidget *stack;
    QWidget *p_tabl_bord;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *container;
    QWidget *p_debug_console;
    QHBoxLayout *horizontalLayout;
    QPlainTextEdit *console;
    QWidget *p_historique;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *check_all_values;
    QTimeEdit *time_start;
    QTimeEdit *time_end;
    QCommandLinkButton *actualizeTableButton;
    QTabWidget *tab_historique;
    QWidget *p_params;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QCheckBox *get_infos;
    QCheckBox *interpol_curve;
    QWidget *p_graphics;
    QGridLayout *gridLayout_3;
    QMdiArea *zone_graph;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *sel_capteur;
    QComboBox *sel_valeur;
    QPushButton *add_graph;
    QPushButton *btn_optimiser;
    QHBoxLayout *horizontalLayout_5;
    QSlider *horizontalSlider;
    QLabel *bowltext;
    QWidget *p_maps;
    QGridLayout *gridLayout_5;
    QVBoxLayout *c_maps;
    QStatusBar *barreStatus;
    QMenuBar *menuBar;
    QMenu *menuFichier;

    void setupUi(QMainWindow *FenPrincipale)
    {
        if (FenPrincipale->objectName().isEmpty())
            FenPrincipale->setObjectName(QString::fromUtf8("FenPrincipale"));
        FenPrincipale->resize(792, 695);
        FenPrincipale->setUnifiedTitleAndToolBarOnMac(false);
        actionQuitter = new QAction(FenPrincipale);
        actionQuitter->setObjectName(QString::fromUtf8("actionQuitter"));
        actionOuvrir = new QAction(FenPrincipale);
        actionOuvrir->setObjectName(QString::fromUtf8("actionOuvrir"));
        widgetCentral = new QWidget(FenPrincipale);
        widgetCentral->setObjectName(QString::fromUtf8("widgetCentral"));
        verticalLayout_5 = new QVBoxLayout(widgetCentral);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        frame_2 = new QFrame(widgetCentral);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMinimumSize(QSize(0, 142));
        frame_2->setMaximumSize(QSize(200, 16777215));
        frame_2->setAutoFillBackground(false);
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(232, 232, 232);\n"
""));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lcd_hour = new QLCDNumber(frame_2);
        lcd_hour->setObjectName(QString::fromUtf8("lcd_hour"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lcd_hour->sizePolicy().hasHeightForWidth());
        lcd_hour->setSizePolicy(sizePolicy);
        lcd_hour->setFrameShape(QFrame::NoFrame);
        lcd_hour->setFrameShadow(QFrame::Raised);
        lcd_hour->setSmallDecimalPoint(false);
        lcd_hour->setNumDigits(2);
        lcd_hour->setDigitCount(2);
        lcd_hour->setSegmentStyle(QLCDNumber::Filled);
        lcd_hour->setProperty("intValue", QVariant(42));

        horizontalLayout_2->addWidget(lcd_hour);

        label = new QLabel(frame_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lcd_min = new QLCDNumber(frame_2);
        lcd_min->setObjectName(QString::fromUtf8("lcd_min"));
        lcd_min->setStyleSheet(QString::fromUtf8(""));
        lcd_min->setFrameShape(QFrame::NoFrame);
        lcd_min->setLineWidth(1);
        lcd_min->setNumDigits(2);
        lcd_min->setProperty("intValue", QVariant(42));

        horizontalLayout_2->addWidget(lcd_min);

        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lcd_sec = new QLCDNumber(frame_2);
        lcd_sec->setObjectName(QString::fromUtf8("lcd_sec"));
        lcd_sec->setFrameShape(QFrame::NoFrame);
        lcd_sec->setNumDigits(2);
        lcd_sec->setProperty("intValue", QVariant(42));

        horizontalLayout_2->addWidget(lcd_sec);

        dial_2 = new QDial(frame_2);
        dial_2->setObjectName(QString::fromUtf8("dial_2"));

        horizontalLayout_2->addWidget(dial_2);


        gridLayout_2->addWidget(frame_2, 0, 0, 1, 1);

        chronolayout = new QVBoxLayout();
        chronolayout->setSpacing(6);
        chronolayout->setObjectName(QString::fromUtf8("chronolayout"));

        gridLayout_2->addLayout(chronolayout, 0, 1, 1, 2);

        frame = new QFrame(widgetCentral);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setMinimumSize(QSize(0, 0));
        frame->setMaximumSize(QSize(200, 16777215));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(1);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        dial = new QDial(frame);
        dial->setObjectName(QString::fromUtf8("dial"));

        verticalLayout->addWidget(dial);

        b_tb = new QPushButton(frame);
        b_tb->setObjectName(QString::fromUtf8("b_tb"));
        sizePolicy1.setHeightForWidth(b_tb->sizePolicy().hasHeightForWidth());
        b_tb->setSizePolicy(sizePolicy1);
        b_tb->setMinimumSize(QSize(85, 65));
        b_tb->setAutoFillBackground(false);
        b_tb->setAutoDefault(false);
        b_tb->setDefault(true);
        b_tb->setFlat(false);

        verticalLayout->addWidget(b_tb);

        b_graph = new QPushButton(frame);
        b_graph->setObjectName(QString::fromUtf8("b_graph"));
        b_graph->setMinimumSize(QSize(85, 60));

        verticalLayout->addWidget(b_graph);

        b_carte = new QPushButton(frame);
        b_carte->setObjectName(QString::fromUtf8("b_carte"));
        b_carte->setMinimumSize(QSize(0, 50));

        verticalLayout->addWidget(b_carte);

        b_console = new QPushButton(frame);
        b_console->setObjectName(QString::fromUtf8("b_console"));
        sizePolicy1.setHeightForWidth(b_console->sizePolicy().hasHeightForWidth());
        b_console->setSizePolicy(sizePolicy1);
        b_console->setMinimumSize(QSize(85, 50));

        verticalLayout->addWidget(b_console);

        b_table = new QPushButton(frame);
        b_table->setObjectName(QString::fromUtf8("b_table"));
        sizePolicy1.setHeightForWidth(b_table->sizePolicy().hasHeightForWidth());
        b_table->setSizePolicy(sizePolicy1);
        b_table->setMinimumSize(QSize(85, 50));

        verticalLayout->addWidget(b_table);

        b_param = new QPushButton(frame);
        b_param->setObjectName(QString::fromUtf8("b_param"));
        b_param->setMinimumSize(QSize(85, 50));

        verticalLayout->addWidget(b_param);

        textBrowser_4 = new QTextBrowser(frame);
        textBrowser_4->setObjectName(QString::fromUtf8("textBrowser_4"));
        textBrowser_4->setEnabled(false);

        verticalLayout->addWidget(textBrowser_4);

        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(4, 1);
        verticalLayout->setStretch(5, 1);
        verticalLayout->setStretch(7, 15);

        gridLayout_2->addWidget(frame, 1, 0, 1, 1);

        stack = new QStackedWidget(widgetCentral);
        stack->setObjectName(QString::fromUtf8("stack"));
        p_tabl_bord = new QWidget();
        p_tabl_bord->setObjectName(QString::fromUtf8("p_tabl_bord"));
        verticalLayout_2 = new QVBoxLayout(p_tabl_bord);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        container = new QGridLayout();
        container->setSpacing(6);
        container->setObjectName(QString::fromUtf8("container"));

        verticalLayout_2->addLayout(container);

        stack->addWidget(p_tabl_bord);
        p_debug_console = new QWidget();
        p_debug_console->setObjectName(QString::fromUtf8("p_debug_console"));
        horizontalLayout = new QHBoxLayout(p_debug_console);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        console = new QPlainTextEdit(p_debug_console);
        console->setObjectName(QString::fromUtf8("console"));
        console->setReadOnly(true);

        horizontalLayout->addWidget(console);

        stack->addWidget(p_debug_console);
        p_historique = new QWidget();
        p_historique->setObjectName(QString::fromUtf8("p_historique"));
        verticalLayout_3 = new QVBoxLayout(p_historique);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        check_all_values = new QCheckBox(p_historique);
        check_all_values->setObjectName(QString::fromUtf8("check_all_values"));

        horizontalLayout_4->addWidget(check_all_values);

        time_start = new QTimeEdit(p_historique);
        time_start->setObjectName(QString::fromUtf8("time_start"));

        horizontalLayout_4->addWidget(time_start);

        time_end = new QTimeEdit(p_historique);
        time_end->setObjectName(QString::fromUtf8("time_end"));
        time_end->setDateTime(QDateTime(QDate(2000, 1, 1), QTime(0, 10, 0)));
        time_end->setTime(QTime(0, 10, 0));
        time_end->setCurrentSection(QDateTimeEdit::HourSection);

        horizontalLayout_4->addWidget(time_end);

        actualizeTableButton = new QCommandLinkButton(p_historique);
        actualizeTableButton->setObjectName(QString::fromUtf8("actualizeTableButton"));

        horizontalLayout_4->addWidget(actualizeTableButton);


        verticalLayout_4->addLayout(horizontalLayout_4);

        tab_historique = new QTabWidget(p_historique);
        tab_historique->setObjectName(QString::fromUtf8("tab_historique"));

        verticalLayout_4->addWidget(tab_historique);


        verticalLayout_3->addLayout(verticalLayout_4);

        stack->addWidget(p_historique);
        p_params = new QWidget();
        p_params->setObjectName(QString::fromUtf8("p_params"));
        gridLayout = new QGridLayout(p_params);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(p_params);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton, 2, 0, 1, 1);

        get_infos = new QCheckBox(p_params);
        get_infos->setObjectName(QString::fromUtf8("get_infos"));
        get_infos->setChecked(true);

        gridLayout->addWidget(get_infos, 0, 0, 1, 1);

        interpol_curve = new QCheckBox(p_params);
        interpol_curve->setObjectName(QString::fromUtf8("interpol_curve"));

        gridLayout->addWidget(interpol_curve, 1, 0, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 2);
        stack->addWidget(p_params);
        p_graphics = new QWidget();
        p_graphics->setObjectName(QString::fromUtf8("p_graphics"));
        gridLayout_3 = new QGridLayout(p_graphics);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        zone_graph = new QMdiArea(p_graphics);
        zone_graph->setObjectName(QString::fromUtf8("zone_graph"));

        gridLayout_3->addWidget(zone_graph, 2, 0, 1, 1);

        frame_3 = new QFrame(p_graphics);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        sel_capteur = new QComboBox(frame_3);
        sel_capteur->setObjectName(QString::fromUtf8("sel_capteur"));

        horizontalLayout_3->addWidget(sel_capteur);

        sel_valeur = new QComboBox(frame_3);
        sel_valeur->setObjectName(QString::fromUtf8("sel_valeur"));

        horizontalLayout_3->addWidget(sel_valeur);

        add_graph = new QPushButton(frame_3);
        add_graph->setObjectName(QString::fromUtf8("add_graph"));

        horizontalLayout_3->addWidget(add_graph);

        btn_optimiser = new QPushButton(frame_3);
        btn_optimiser->setObjectName(QString::fromUtf8("btn_optimiser"));
        btn_optimiser->setCheckable(true);

        horizontalLayout_3->addWidget(btn_optimiser);


        gridLayout_3->addWidget(frame_3, 3, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSlider = new QSlider(p_graphics);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(180);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(horizontalSlider);

        bowltext = new QLabel(p_graphics);
        bowltext->setObjectName(QString::fromUtf8("bowltext"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(bowltext->sizePolicy().hasHeightForWidth());
        bowltext->setSizePolicy(sizePolicy2);
        bowltext->setMinimumSize(QSize(150, 0));
        bowltext->setMaximumSize(QSize(150, 16777215));
        bowltext->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(bowltext);


        gridLayout_3->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        gridLayout_3->setRowStretch(0, 7);
        stack->addWidget(p_graphics);
        p_maps = new QWidget();
        p_maps->setObjectName(QString::fromUtf8("p_maps"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(p_maps->sizePolicy().hasHeightForWidth());
        p_maps->setSizePolicy(sizePolicy3);
        gridLayout_5 = new QGridLayout(p_maps);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        c_maps = new QVBoxLayout();
        c_maps->setSpacing(6);
        c_maps->setObjectName(QString::fromUtf8("c_maps"));

        gridLayout_5->addLayout(c_maps, 0, 0, 1, 1);

        stack->addWidget(p_maps);

        gridLayout_2->addWidget(stack, 1, 1, 1, 2);

        gridLayout_2->setRowStretch(0, 1);
        gridLayout_2->setColumnStretch(0, 1);

        verticalLayout_5->addLayout(gridLayout_2);

        FenPrincipale->setCentralWidget(widgetCentral);
        barreStatus = new QStatusBar(FenPrincipale);
        barreStatus->setObjectName(QString::fromUtf8("barreStatus"));
        FenPrincipale->setStatusBar(barreStatus);
        menuBar = new QMenuBar(FenPrincipale);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 792, 25));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QString::fromUtf8("menuFichier"));
        FenPrincipale->setMenuBar(menuBar);

        menuBar->addAction(menuFichier->menuAction());
        menuFichier->addAction(actionOuvrir);
        menuFichier->addSeparator();
        menuFichier->addAction(actionQuitter);

        retranslateUi(FenPrincipale);

        stack->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(FenPrincipale);
    } // setupUi

    void retranslateUi(QMainWindow *FenPrincipale)
    {
        FenPrincipale->setWindowTitle(QApplication::translate("FenPrincipale", "FenPrincipale", 0, QApplication::UnicodeUTF8));
        actionQuitter->setText(QApplication::translate("FenPrincipale", "Quitter", 0, QApplication::UnicodeUTF8));
        actionQuitter->setShortcut(QApplication::translate("FenPrincipale", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionOuvrir->setText(QApplication::translate("FenPrincipale", "Ouvrir", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FenPrincipale", ":", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FenPrincipale", ":", 0, QApplication::UnicodeUTF8));
        b_tb->setText(QApplication::translate("FenPrincipale", "Tableau de bord", 0, QApplication::UnicodeUTF8));
        b_graph->setText(QApplication::translate("FenPrincipale", "Graphiques", 0, QApplication::UnicodeUTF8));
        b_carte->setText(QApplication::translate("FenPrincipale", "Carte", 0, QApplication::UnicodeUTF8));
        b_console->setText(QApplication::translate("FenPrincipale", "Console", 0, QApplication::UnicodeUTF8));
        b_table->setText(QApplication::translate("FenPrincipale", "Historique", 0, QApplication::UnicodeUTF8));
        b_param->setText(QApplication::translate("FenPrincipale", "Param\303\250tres", 0, QApplication::UnicodeUTF8));
        check_all_values->setText(QApplication::translate("FenPrincipale", "(ne marche pas)", 0, QApplication::UnicodeUTF8));
        actualizeTableButton->setText(QApplication::translate("FenPrincipale", "Actualiser", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("FenPrincipale", "Trololol bob", 0, QApplication::UnicodeUTF8));
        get_infos->setText(QApplication::translate("FenPrincipale", "Activer mise \303\240 jour des infos", 0, QApplication::UnicodeUTF8));
        interpol_curve->setText(QApplication::translate("FenPrincipale", "Interpoler les valeurs de courbe", 0, QApplication::UnicodeUTF8));
        add_graph->setText(QApplication::translate("FenPrincipale", "Ajouter le graphique", 0, QApplication::UnicodeUTF8));
        btn_optimiser->setText(QApplication::translate("FenPrincipale", "OPTIMISATION", 0, QApplication::UnicodeUTF8));
        bowltext->setText(QApplication::translate("FenPrincipale", "1 minute", 0, QApplication::UnicodeUTF8));
        menuFichier->setTitle(QApplication::translate("FenPrincipale", "Fichier", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FenPrincipale: public Ui_FenPrincipale {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENPRINCIPALE_H
