
#include <iostream>
#include <string>

using namespace std;

class Product {
private:
    string name_;
public:
    virtual ~Product();
    virtual string getName() = 0;
};

class Product1 : public Product {
public:
    string getName() {
        return "Product1";
    }
};

class Product2 : public Product {
public:
    string getName() {
        return "Product2";
    }
};

class Factory{
public:
    enum ProductType {
        PRODUCT1 = 0,
        PRODUCT2, 
    };

public: 
    Product* createProduct(ProductType type) {
        Product* res = nullptr;
        switch (type) {
            case PRODUCT1 :
                res = new Product1();
                break;
            case PRODUCT2 :
                res = new Product2();
                break;
            default       : 
                break;
        }
        return res;
    }
};

int main (int argc, char *argv[])
{
    Factory* factory = new Factory;
    Product* pro1    = factory->createProduct(Factory::PRODUCT1);
    Product* pro2    = factory->createProduct(Factory::PRODUCT2);

    std::cout << "the first product is "  << pro1->getName() << std::endl;
    std::cout << "the second product is "  << pro2->getName() << std::endl;

    delete factory;
    delete pro1;
    delete pro2;
    return 0;
}
