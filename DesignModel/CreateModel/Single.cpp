#include <iostream>
#include <string>

#define HUGRY 0

using namespace std;

class Single;

#if HUGRY

/* hugry single */
class Single{
public:
    Single(const Single& other) = delete;
    Single operator=(const Single& other) = delete;

    static Single* getInstance() {
        return single;
    }

private:
    Single() = default;
    static Single* single;;
};

Single* Single::single = new Single;

#else 

/* lazy single */
class Single {
public:
    Single(const Single& other) = delete;
    Single operator=(const Single& other) = delete;
    
    static Single* getInstance() {
        if(single_ == nullptr) {
            single_ = new Single;
        }
        return single_;
    }

private:
    Single() = default;
    static Single* single_;
};

Single* Single::single_ = nullptr;

#endif

int main (int argc, char *argv[])
{
#if HUGRY
    cout << "hugry single" << endl;
#else
    cout << "lazy single" << endl;
#endif
    Single* single1 = Single::getInstance(); 
    Single* single2 = Single::getInstance();
    cout << "the first class address is "  << single1 << endl;
    cout << "the second class address is "  << single2 << endl;

    return 0;
}
