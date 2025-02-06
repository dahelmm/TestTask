#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    workerForDB.connectToDatabase();
    //TODO: подключение/создание БД
    //TODO: старт потока для инкрементирования

    //TODO: подсчет частоты инкрементирования счетчиков и вывод значения в label
}

MainWindow::~MainWindow()
{
    //TODO: тормоз потока для инкрементирования
    delete ui;
}

void MainWindow::on_bttnAddCounter_clicked()
{
    //TODO: создание счетчика и добавление его значения в таблицу
}

void MainWindow::on_bttnDeleteCounter_clicked()
{
    //TODO: удаление выделенного счетчика (соответственно, проверка, выбран ли какой-то счетчик)
}

void MainWindow::on_bttnSave_clicked()
{
    //TODO: проверка подключения к БД, запись значений счетчиков
}
