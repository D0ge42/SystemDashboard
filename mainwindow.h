#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        Ui::MainWindow* getUi();
        void setAxisStyle();
        void setGraphAndBarsStyle(QCPGraph *graph, QCPGraph *graph2,QCPBars *bars1,
                                  QCPBars *bars2, QVector<double> x, QVector<double>y);
        void handleLayers(QCPGraph *graph);
    public slots:
        void updateGraphSlot(QVector<double> x, QVector<double> y,double perc);
    private:
        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
