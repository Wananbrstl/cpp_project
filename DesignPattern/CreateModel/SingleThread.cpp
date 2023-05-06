/* single with thread */

#include <iostream>
#include <string>
#include <mutex>

#define HUGRY 0

using namespace std;

class Single;

#if HUGRY

/* hugry single */
/* thread is safe */
class Single{
public:
    Single(const Single& other) = delete;
    Single operator=(const Single& other) = delete;

    static Single* getInstance() {
        return single;
    } 

    static void clear() {
        if(nullptr != single) {
            delete single;
            single = nullptr;
        }
    }

private:
    Single() = default;
    static Single* single;;
};

Single* Single::single = new Single;

#else 

/* lazy single */
/* thread is not safe */
class Single {
public:
    Single(const Single& other) = delete;
    Single operator=(const Single& other) = delete;
    
    static Single* getInstance() {
        // method 1
        // mtx.lock();
        // if(single_ == nullptr) {
        //     single_ = new Single;
        // }

        // method 2(better)
        if(nullptr == single_) { // filter
            mtx.lock();
            if(nullptr == single_) {
                single_ = new Single;
            }
            mtx.unlock();
        }
        // mtx.unlock();
        return single_;
    }

    static void clear() {
        if(single_ != nullptr) {
            delete single_;
            single_ = nullptr;
        }
    }

private:
    Single() = default;
    static Single* single_;

    /* thread safe */
    static mutex mtx;
};

Single* Single::single_ = nullptr;
mutex Single::mtx;

#endif

/* a better lazy single*/
class StaticSingle {
public:
    static StaticSingle* getInstance() {
        static StaticSingle res;
        return &res;
    }
    
    StaticSingle(const StaticSingle& other) = delete;
    StaticSingle operator=(const StaticSingle& other) = delete;
private:
    StaticSingle() = default;
};

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
    // single1->clear();
    // single2->clear();
    Single::clear();
    return 0;
}

