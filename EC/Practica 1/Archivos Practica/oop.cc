class object
{
public:
    object(int i = 0):value(i) {}

    int get_value()
    {
        return this->value;
    }

    void set_value(int i)
    {
        this->value = i;
    }

private:
    int value;
};

int main()
{
    object o0, o1(1), o2;
    o2.set_value(2);
    return o0.get_value() + o1.get_value() + o2.get_value();
}
