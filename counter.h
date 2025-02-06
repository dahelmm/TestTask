#ifndef COUNTER_H
#define COUNTER_H

#include <QVector>
#include <thread>
#include <QObject>

class Counter : public QObject
{
        Q_OBJECT
    public:
        Counter(int id, int value = 0, QObject *parent = nullptr);

        int getValue() const { return p_value; };
        int getId() const { return p_id; };

        void increment();

    signals:
        void valueChanged();

    private:
        int p_id;
        int p_value;
};

class CounterDirector : public QObject
{
    public:
        CounterDirector(QObject *parent = nullptr);
        CounterDirector(QVector<Counter*> counters, QObject *parent = nullptr);
        ~CounterDirector();

        Counter *addCounter();
        void removeCounter(int const numberCounter);
        void incrementCounters();
        QVector<Counter*> & counters() & { return p_counters; };
        void loadCounters(QVector<Counter*> counters);
        void deleteCounters();

        void start();
        void stop();

    private:
        QVector<Counter*>       p_counters;
        std::thread             p_threadForIncrement;
        bool                    p_running;
        int                     p_idCurrentCounter;
};

#endif // COUNTER_H
