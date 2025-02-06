#ifndef COUNTER_H
#define COUNTER_H

class Counter
{
    public:
        Counter(int id);

        int getValue() const { return p_value; };
        int getId() const { return p_id; };

    private:
        int p_id;
        int p_value;
};

#endif // COUNTER_H
