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
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            "idCounter INTEGER, "
                            "valueCounter INTEGER);")
                    .arg("Counters"))) {
        qWarning() << QString("DB: error for create: %1")
                      .arg(query.lastError().text()) << __FILE__ << __LINE__;
        return false;
    }
    return true;
}

