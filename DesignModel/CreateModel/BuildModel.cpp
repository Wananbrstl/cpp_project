#include <iostream>
#include <string>

using namespace std;

typedef enum {
    ALLOCATION_MIN = 0,
    ALLOCATION_NORMAL,
    ALLOCATION_HIGH,
    ALLOCATION_MAX
} ENOTEBOOK_TYPE;


class CComputer {
public:
    void setName(string name) {
        name_ = name;
    }
    inline string getName() const {
        return name_;
    }

    void setWeight(string weight) {
        weight_ = weight;
    }
    inline string getWeight() const {
        return weight_;
    }

    void setHardDisk(string hard_disk) {
        hard_disk_ = hard_disk;
    }
    inline string getHardDisk() const {
        return hard_disk_;
    }

    void setMemory(string memory) {
        memory_ = memory;
    }
    inline string getMemory() const {
        return memory_;
    }

    void setCPU(string cpu) {
        cpu_ = cpu;
    }
    inline string getCPU() const {
        return cpu_;
    }

    void show() const {
        cout << "---------------- "<< name_ << " ---------------" << endl;
        cout << "Weight\t: " << weight_ << " kg" << endl;
        cout << "CPU\t: " << cpu_ << endl;
        cout << "memory\t: " << memory_ << endl;
        cout << "hard disk\t: " << hard_disk_ << endl;
    }

private:
    string name_;
    string weight_;
    string memory_;
    string cpu_;
    string hard_disk_;
};


/* interface */
class ComputerBuilder {
public:
    virtual ~ComputerBuilder(){};
    virtual void buildName() = 0;
    virtual void buildWeight() = 0;
    virtual void buildMemory() = 0;
    virtual void buildHardDisk() = 0;
    virtual void buildCPU() = 0;
    virtual CComputer* getCompter() = 0;
};

class CThinkPadX13Builder : public ComputerBuilder {
public:
    CThinkPadX13Builder() {
        computer_ = new CComputer;
    }

    void buildName() override {
        computer_->setName("ThinkPadX13");
    }

    void buildHardDisk() override{
        computer_->setHardDisk("512G");
    }

    void buildMemory() override {
        computer_->setMemory("32G");
    }

    void buildCPU() override {
        computer_->setCPU("12-I7");
    }

    void buildWeight() override {
        computer_->setWeight("1.32");
    }

    CComputer * getCompter() override{
        return computer_;
    }

private:
    CComputer* computer_;
};

class CMateBookProBuilder : public ComputerBuilder {
public:
    CMateBookProBuilder() {
        computer_ = new CComputer;
    }

    void buildName() override {
        computer_->setName("MateBookPro");
    }

    void buildHardDisk() override{
        computer_->setHardDisk("512G");
    }

    void buildMemory() override {
        computer_->setMemory("16G");
    }

    void buildCPU() override {
        computer_->setCPU("12-I5");
    }

    void buildWeight() override {
        computer_->setWeight("1.1");
    }

    CComputer * getCompter() override{
        return computer_;
    }

private:
    CComputer* computer_;
};

class CDirector {
public:
    CDirector(ComputerBuilder* cpbder) {
        computer_builder_ = cpbder;
    }

    void buildComputer() {
        computer_builder_->buildName();
        computer_builder_->buildWeight();
        computer_builder_->buildHardDisk();
        computer_builder_->buildMemory();
        computer_builder_->buildCPU();
    }
private:
    ComputerBuilder* computer_builder_;
};

int main (int argc, char *argv[])
{
    ComputerBuilder* computerBuilder1 = new CThinkPadX13Builder;
    CDirector* director1 = new CDirector(computerBuilder1);
    director1->buildComputer();
    ComputerBuilder* computerBuilder2 = new CMateBookProBuilder;
    CDirector* director2 = new CDirector(computerBuilder2);
    director2->buildComputer();

    CComputer* computer1 = computerBuilder1->getCompter();
    CComputer* computer2 = computerBuilder2->getCompter();
    computer1->show();
    computer2->show();

    delete computerBuilder1;
    delete director1;
    delete computerBuilder2;
    delete director2;
    delete computer1;
    delete computer2;
    return 0;
}
