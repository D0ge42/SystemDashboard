#ifndef WORKER_H
#define WORKER_H
#include <QObject>
#include <vector>
#include <ui_mainwindow.h>
#include "infos.hpp"

namespace Ui
{
    class MainWindow;
}

class Worker : public QObject
{
    Q_OBJECT
    public:
        Worker();
        ~Worker();
    public slots:
        void retrieveCPUusage();
        void process();
    signals:
        void finished();
        void error(QString error);
        void dataReady(QVector<double> x, QVector<double> y,double perc);

    private:

};

int calc_total_usage(std::vector<int> num);
int calc_total_idle(std::vector<int> num);

#endif // WORKER_H
