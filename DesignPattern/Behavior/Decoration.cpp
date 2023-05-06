/* 动态获得某种行为 */
#include <iostream>
#include <string>

class Soldier {
public:
    Soldier() {};
    virtual ~Soldier() {};
    Soldier(const std::string& name) {
        name_ = name;
    }

    std::string getName() {
        return name_;
    }
    
    virtual void flight() = 0;
protected:
    std::string name_;
};

class Tean : public Soldier {
public:
    using Soldier::Soldier;
    void flight() override {
        std::cout << "拥有很高的战斗能力...\n";
    }
};

class DevilFruit : public Soldier {
public:
    virtual ~DevilFruit() {};
    void enchantment(Soldier* soldier) {
        soldier_ = soldier;
        name_ = soldier_->getName();
    }

protected:
    Soldier* soldier_ = nullptr;
};

class DarkFruit : public DevilFruit {
public:
    void flight() override {
        std::cout << soldier_->getName() << " 吃下了黑暗果实...." << std::endl;
    }
};

class QuakFruit : public DevilFruit {
public:
    void flight() override {
        std::cout << soldier_->getName() << " 吃下了震震果实..." << std::endl;
    }
};

int main (int argc, char *argv[])
{
    Tean* t = new Tean("david");
    DarkFruit* dark = new DarkFruit;
    QuakFruit* quak = new QuakFruit;
    dark->enchantment(t);
    quak->enchantment(t);
    dark->flight();
    quak->flight();

    delete t;
    delete dark;
    delete quak;
    return 0;
}
