#ifndef INFOS_H
#define INFOS_H
#include <QObject>
#include <vector>
#include <ui_mainwindow.h>

namespace Ui
{
    class MainWindow;
}

class CPUinfo: public QObject
{
    Q_OBJECT
    private:
        Ui::MainWindow *ui;
        int processors;
        std::string vendor_id;
        int cpu_family;
        int cpu_model;
        std::string model_name;
        int stepping;
        int microcode;
        double cpu_mhz;
        size_t cache_size;
        size_t physical_id;
        size_t core_id;
        size_t cpu_cores;
        double cpu_usage;
    public:
        CPUinfo(Ui::MainWindow *ui, QObject *parent);
        CPUinfo();
        ~CPUinfo();
        void fillStruct(std::vector <std::string> vec);
        void gatherInfo();
        void setUi(Ui::MainWindow *ptr);
        void setQObject(QObject *ptr);
        double getUsage();
        std::string getModelName();
        void updateGraph(Ui::MainWindow *ui,QVector <double> x, QVector <double> y);
};

int calc_total_usage(std::vector<int> num);
int calc_total_idle(std::vector<int> num);

#endif // INFOS_H
