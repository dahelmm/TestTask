#include "mainwindow.h"
#include "ui_mainwindow.h"

enum ColumnsForTable {
    idCounter = 0,
    valueCounter
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList columnsHeader;
    columnsHeader<<"ID счётчика"<<"Значение счётчика";
    ui->tableWidgetDisplay->setColumnCount(2);
    ui->tableWidgetDisplay->setHorizontalHeaderLabels(columnsHeader);
    ui->tableWidgetDisplay->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //подключение/создание БД
    p_workerForDB.connectToDatabase();
    //TODO: инициализация данных из БД
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
    //создание счетчика и добавление его значения в таблицу
    Counter *addedCounter = p_counterDirector.addCounter();
    int rowCountInDisplay = ui->tableWidgetDisplay->rowCount();
    ui->tableWidgetDisplay->insertRow(rowCountInDisplay);
    ui->tableWidgetDisplay->setItem(rowCountInDisplay, idCounter, new QTableWidgetItem(QString::number(addedCounter->getId())));
    ui->tableWidgetDisplay->setItem(rowCountInDisplay, valueCounter, new QTableWidgetItem(QString::number(addedCounter->getValue())));
}

void MainWindow::on_bttnDeleteCounter_clicked()
{
    //удаление выделенного счетчика (соответственно, проверка, выбран ли какой-то счетчик)
    int currentCounter = ui->tableWidgetDisplay->currentRow();
    p_counterDirector.removeCounter(currentCounter);
    ui->tableWidgetDisplay->removeRow(currentCounter);
}

void MainWindow::on_bttnSave_clicked()
{
    //TODO: проверка подключения к БД, запись значений счетчиков
}
