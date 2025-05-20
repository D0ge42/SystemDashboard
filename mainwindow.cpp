#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "infos.hpp"

/*
 * @Brief: function that gets triggered when the signal dataReady is emitted.
 * It sets up both the data and design of the graph.
 * @Params:
 * Time and Usage vectors, provided by the dataReady signals.
 * perc, which is the percentage we're gonna set in the percentage_label.
*/

void MainWindow::updateGraphSlot(QVector<double> time, QVector<double> usage, double perc)
{
    QCPGraph *graph = ui->plot->addGraph();
    QCPGraph *graph2 = ui->plot->addGraph();
    QCPBars *bars1 = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);
    QCPBars *bars2 = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);
    CPUinfo cpu;

    cpu.gatherInfo();
    setGraphAndBarsStyle(graph,graph2,bars1,bars2,time,usage);
    handleLayers(graph);
    setAxisStyle();
    ui->perc_label->setNum(perc);
    ui->model_label->setText(cpu.getModelName().c_str());
    ui->plot->replot();
}

/*
 * @Brief : function responsible for handling graphical layers.
 * There's a main layer used as reference and layers are placed
 * either above or below it.
 * @Params:
 * Main graph, used to setup layers.
*/

void MainWindow::handleLayers(QCPGraph *graph)
{
    if (ui->plot->layer("abovemain") == NULL)
        ui->plot->addLayer("abovemain", ui->plot->layer("main"), QCustomPlot::limAbove);
    if (ui->plot->layer("belowmain") == NULL)
        ui->plot->addLayer("belowmain", ui->plot->layer("main"), QCustomPlot::limBelow);
    graph->setLayer("abovemain");
    ui->plot->xAxis->grid()->setLayer("belowmain");
    ui->plot->yAxis->grid()->setLayer("belowmain");
}

/*
 * @Brief Function responsible for setting up previously initialized Graphs and Bars
 * It sets their data and their style.
 * At the start, we iterate over the usage vector and make a new vector out of it.
 * The new vector will contain halved values of the usage vector.
 * This is purely a stylish choice.
 * @Params:
 * Graphs and bars, along with usage and time vectors.
*/

void MainWindow::setGraphAndBarsStyle(QCPGraph *graph, QCPGraph *graph2,QCPBars *bars1,
                                      QCPBars *bars2, QVector<double> time, QVector<double>usage)
{

    QVector<double>y1;
    std::copy(usage.begin(),usage.end(),std::back_inserter(y1));
    for (int i = 0; i < y1.length(); i++)
        y1[i]/=2;

    // Graph style
    ui->plot->rescaleAxes();
    ui->plot->yAxis->setRange(0, 2);
    ui->plot->yAxis->setRange(0, 100);
    ui->plot->xAxis->setRange(0, 100);
    graph->setData(time, usage);
    graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 5));
    graph->setPen(QPen(QColor(120, 120, 120), 2));

    // Graph2 Style
    graph2->setData(time, usage);
    graph2->setPen(Qt::NoPen);
    graph2->setBrush(QColor(200, 200, 200, 20));
    graph2->setChannelFillGraph(graph);

    // Bars1 style
    bars1->setWidth(1);
    bars1->setData(time, y1);
    bars1->setPen(Qt::NoPen);
    bars1->setBrush(QColor(10, 140, 70, 160));

    //Bars2 style
    bars2->setWidth(1);
    bars2->setData(time, y1);
    bars2->setPen(Qt::NoPen);
    bars2->setBrush(QColor(10, 100, 50, 70));
    bars2->moveAbove(bars1);
}


/*
 * @Brief function that will setup axys stylesheet.
*/

void MainWindow::setAxisStyle()
{

    ui->plot->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->plot->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->plot->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->plot->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->plot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->plot->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->plot->xAxis->setTickLabelColor(Qt::white);
    ui->plot->yAxis->setTickLabelColor(Qt::white);
    ui->plot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->plot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->plot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->plot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->plot->xAxis->grid()->setSubGridVisible(true);
    ui->plot->yAxis->grid()->setSubGridVisible(true);
    ui->plot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->plot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->plot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->plot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    ui->plot->setBackground(plotGradient);

    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    ui->plot->axisRect()->setBackground(axisRectGradient);
}

/* Constructors and Destructors. MainWindow is also responsible for setting up ui.*/

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow *MainWindow::getUi()
{
    return this->ui;
}

