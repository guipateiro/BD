#ifndef DATA_HPP
#define DATA_HPP

class Data{
public:
    int time;
    int origem;
    char operacao;
    char dado;

    Data();
    Data(int time, int origem, char operacao, char dado);
    virtual ~Data() = default;

};

#endif