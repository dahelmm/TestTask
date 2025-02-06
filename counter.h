#ifndef COUNTER_H
#define COUNTER_H

#include <QVector>
#include <thread>
#include <QObject>

class Counter : public QObject
{
    public:
        Counter(int id, QObject *parent = nullptr);

        int getValue() const { return p_value; };
        int getId() const { return p_id; };

        void increment() { p_value+=1; };

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

        void start();
        void stop();

    private:
        QVector<Counter*>       p_counters;
        std::thread             p_threadForIncrement;
        bool                    p_running;
        int                     p_idCurrentCounter;
};

#endif // COUNTER_H
