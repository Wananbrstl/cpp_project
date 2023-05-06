#include <iostream>
#include <string>

using namespace std;

class Product {
public : 
    virtual ~Product() {};
    virtual void show() = 0;
};

class Product1 : public Product {
public:
    void show() override {
        std::cout << "This is Product1\n";
    }
};

class Product2 : public Product {
public:
    void show() override {
        std::cout << "This is Product2\n";
    }
};

class Factory{
public:
    enum ProductType {
        PRODUCT1 = 0,
        PRODUCT2,
    };

    virtual ~Factory() {};
    virtual Product* createProduct() = 0;
};

class Product1Factory : public Factory {
public:
    Product * createProduct() override {
        return new Product1;
    }
};

class Product2Factory : public Factory{
public:
    Product * createProduct() override {
        return new Product2;
    }
};



int main (int argc, char *argv[])
{
    Factory* factory1 = new Product1Factory;
    Factory* factory2 = new Product2Factory;
    
    Product* pro1 = factory1->createProduct();
    Product* pro2 = factory2->createProduct();

    pro1->show();
    pro2->show();

    delete factory1;
    delete factory2;
    delete pro1;
    delete pro2;
    return 0;
}
