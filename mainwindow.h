#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "counter.h"
#include "databaseworker.h"

#include <QMainWindow>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void on_bttnAddCounter_clicked();
        void on_bttnDeleteCounter_clicked();
        void on_bttnSave_clicked();

        void calculateIncrementTime();

    private:
        void initializationUI();
        void addCounterToUI(Counter *counter);

    private:
        Ui::MainWindow *ui;

        DatabaseWorker p_workerForDB;
        CounterDirector p_counterDirector;
        QElapsedTimer p_elapsedTimer;
};
#endif // MAINWINDOW_H
