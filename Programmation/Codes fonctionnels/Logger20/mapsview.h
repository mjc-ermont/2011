#ifndef MAPSVIEW_H
#define MAPSVIEW_H


#include <QWebView>
#include <QWebFrame>
#include <QFile>

#include <FenPrincipale.h>
#include <defines.h>

class MapsView : public QWebView
{
    Q_OBJECT
public:
    explicit MapsView(QWidget *parent = 0);

    void addPoint(int x, int y);

private:
    int index;

};

#endif // MAPSVIEW_H
