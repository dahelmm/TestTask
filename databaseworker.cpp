#include "databaseworker.h"

#include <QFile>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseWorker::DatabaseWorker(QObject * parent) :
    QObject(parent),
    p_typeDataBase("QSQLITE"),
    p_nameDataBaseFile("database.db"),
    p_pathDataBaseFile(QString("./%1").arg(p_nameDataBaseFile)),
    p_hostNameDataBase("database")
{

}

DatabaseWorker::~DatabaseWorker()
{
    closeDatabase();
}

void DatabaseWorker::connectToDatabase()
{
    if(!QFile::exists(p_pathDataBaseFile)){
        //Создаем БД, если её нет
        createDataBase();
    }
    else {
        //Открываем, если есть
        openDataBase();
    }
}

void DatabaseWorker::closeDatabase()
{
    if(p_database.isOpen())
        p_database.close();
}

void DatabaseWorker::saveCounters(QVector<Counter *> & counters)
{
    if(!p_database.isOpen() || counters.isEmpty())
        return;
    QSqlQuery queryForDeletingData;
    if(!queryForDeletingData.exec("DELETE FROM Counters")){
        qWarning()<<QString("DB: error for deleting data")<<queryForDeletingData.lastError().text();
        return;
    }
    foreach(auto *counter, counters){
        QSqlQuery query;
        query.prepare("INSERT INTO Counters (idCounter, valueCounter) VALUES (:id, :value)");
        query.bindValue(":id", counter->getId());
        query.bindValue(":value", counter->getValue());
        if(!query.exec()){
            qWarning()<<QString("DB: error saving counter %1").arg(counter->getId())<<query.lastError().text();
            p_database.rollback();
        }
    }
}


QVector<Counter *> DatabaseWorker::loadCounters()
{
    QVector<Counter *> result;
    if(!p_database.isOpen())
        return result;
    QSqlQuery query("SELECT * FROM Counters");
    if(!query.exec()){
        qWarning()<<"DB: error with load data"<<query.lastError().text();
        return result;
    }
    while(query.next()){
        int idCounter = query.value(0).toInt();
        int valueCounter = query.value(1).toInt();
        Counter *counter = new Counter(idCounter, valueCounter);
        result.append(counter);
    }
    return result;
}

bool DatabaseWorker::createDataBase()
{
    if(openDataBase()){
        return createTable();
    }
    return false;
}

bool DatabaseWorker::openDataBase()
{
    p_database = QSqlDatabase::addDatabase(p_typeDataBase);
    if(p_database.isOpen())
        p_database.close();
    p_database.setHostName(p_hostNameDataBase);
    p_database.setDatabaseName(p_pathDataBaseFile);
    return p_database.open();
}

bool DatabaseWorker::createTable()
{
    QSqlQuery query;
    if (!query.exec(QString("CREATE TABLE %1 ("
                            "idCounter INTEGER, "
                            "valueCounter INTEGER);")
                    .arg("Counters"))) {
        qWarning() << QString("DB: error for create: %1")
                      .arg(query.lastError().text()) << __FILE__ << __LINE__;
        return false;
    }
    return true;
}

