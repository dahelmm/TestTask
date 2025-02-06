#include "counter.h"

Counter::Counter(int id, QObject * parent) :
    QObject(parent),
    p_id(id),
    p_value(0)
{

}

CounterDirector::CounterDirector(QObject *parent) :
    QObject(parent),
    p_running(false),
    p_idCurrentCounter(0)
{

}

CounterDirector::CounterDirector(QVector<Counter *> counters, QObject * parent) :
    QObject(parent),
    p_counters(counters)
{

}

CounterDirector::~CounterDirector()
{
    stop();
    qDeleteAll(p_counters);
    p_counters.clear();
}

Counter *CounterDirector::addCounter()
{
    Counter *counter = new Counter(p_idCurrentCounter++, this);
    p_counters.append(counter);
    return counter;
}

void CounterDirector::removeCounter(const int numberCounter)
{
    if(numberCounter >= p_counters.count() || numberCounter < 0)
        return;
    Counter *removingCounter = p_counters.takeAt(numberCounter);
    removingCounter->deleteLater();
}

void CounterDirector::incrementCounters()
{
    while(p_running){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        foreach (auto *counter, p_counters) {
            counter->increment();
        }
    }
}

void CounterDirector::start()
{
    p_running = true;
    p_threadForIncrement = std::thread(&CounterDirector::incrementCounters, this);
}

void CounterDirector::stop()
{
    p_running = false;
    if (p_threadForIncrement.joinable()) {
        p_threadForIncrement.join();
    }
}
