#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H

#include <Qwt/qwt_plot.h>
#include <Qwt/qwt_plot_curve.h>

class GraphicView : public QwtPlot
{
    public:
        explicit GraphicView(QWidget *parent = 0);

    signals:

    public slots:
    
};

#endif // GRAPHICVIEW_H
