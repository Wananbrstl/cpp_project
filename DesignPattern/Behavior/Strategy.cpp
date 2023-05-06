#include <bits/stdc++.h>

using namespace std;

class AbstractAlgorithm {
public:
    virtual void work() = 0;
    virtual ~AbstractAlgorithm(){}
};

class Algorithm1 : public AbstractAlgorithm {
public: 
    void work() override {
        cout << "algorithm1 work!\n";
    }
};

class Algorithm2 : public AbstractAlgorithm {
    void work() override {
        cout << "algorithm2 work!\n";
    }
};

/* classical useage */
void work(AbstractAlgorithm* algorithm){
    //...
    algorithm->work();
    //..
}

int main (int argc, char *argv[])
{
    AbstractAlgorithm* algorithm1 = new Algorithm1;
    algorithm1->work();
    AbstractAlgorithm* algorithm2 = new Algorithm2; 
    algorithm2->work();

    delete algorithm1;
    delete algorithm2;
    return 0;
}
