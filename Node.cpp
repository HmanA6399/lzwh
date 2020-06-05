struct Node
{
    unsigned int entity, freq_val;

    Node *r, *l;

    Node(int entity, int freq_val) : entity(entity), freq_val(freq_val)
    {
        r = l = nullptr;
    }

    bool operator<(const Node &n)
    {
        return this->freq_val < n.freq_val;
    }

    bool operator>(const Node &n)
    {
        return this->freq_val > n.freq_val;
    }

    bool operator==(const Node &n)
    {
        return this->freq_val == n.freq_val;
    }

    bool operator==(int e)
    {
        return this->entity == e;
    }

    Node operator+(const Node &n) {
        Node nn(0, freq_val+n.freq_val);
        return nn;
    }
};
