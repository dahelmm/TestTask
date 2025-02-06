#ifndef DATABASEWORKER_H
#define DATABASEWORKER_H

#include "counter.h"

#include <QObject>
#include <QSql>
#include <QSqlDatabase>
#include <QHash>

class DatabaseWorker : public QObject
{
        Q_OBJECT

    public:
        explicit DatabaseWorker(QObject *parent = nullptr);
        ~DatabaseWorker();

        void connectToDatabase();
        void closeDatabase();

        void saveCounters(QVector<Counter*> &counters);
        QVector<Counter *> loadCounters();

    private:
        bool createDataBase();
        bool openDataBase();
        bool createTable();

    private:
        QSqlDatabase p_database;

        const QString p_typeDataBase;
        const QString p_nameDataBaseFile;
        const QString p_pathDataBaseFile;
        const QString p_hostNameDataBase;
};

#endif // DATABASEWORKER_H
