#include "mainwindow.h"
#include "worker.hpp"
#include <QFile>
#include <QApplication>
#include <unistd.h>
#include <QThread>
#include <sys/socket.h>


/*
 * @Brief: main function.
 * This is where the multithreading happens.
 * First a Worker and Thread instance are created.
 * The thread will be responsible for running the retrieveCPUusage function
 * which is esentially an almost never ending loop, that retrieve and calculate cpu usage.
 * After each iteration of the loop, the dataReady signal is emitted.
 * This will trigger the updateGraphSlot which is gonna draw the live graph on the main window.
 * When the finished signal is emitted, both worker and threads are deleted.
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Worker *worker = new Worker();
    QThread *thread = new QThread();

    worker->moveToThread(thread);

    QObject::connect(thread, &QThread::started, worker, &Worker::retrieveCPUusage);
    QObject::connect(worker, &Worker::dataReady, &w, &MainWindow::updateGraphSlot);
    QObject::connect(worker, &Worker::finished, thread, &QThread::quit);
    QObject::connect(worker, &Worker::finished, worker, &QObject::deleteLater);
    QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    thread->start();
    w.show();
    return a.exec();
}

