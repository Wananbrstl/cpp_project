#include <iostream>
#include <string>


class Resum {
public:
    Resum() = default;
    Resum(const std::string& name, const std::string& age, const std::string& education ) {
        name_ = name;
        age_ = age;
        education_ = education;
    }

    Resum(const Resum& other) {
        name_ = other.name_;
        age_  = other.age_;
        education_ = other.education_;
    }

public:
    void setName(const std::string& name) {name_ = name;}
    std::string getName() const {return name_;}
    void setAge(const std::string& age) {age_ = age;}
    std::string getAge() const {return age_;}
    void setEducation(const std::string& education) {education_ = education;}
    std::string getEducation() const {return education_;}

    virtual Resum* clone() {
        return new Resum(*this);
    }

    void show() const {
        std::cout << "My name is " << name_  << ", "
                  << "I'm " << age_ << " years old."
                  << "My education is " << education_ << std::endl;
    }

private:
    std::string name_;
    std::string age_;
    std::string education_;
};

int main (int argc, char *argv[])
{
    Resum* resum1 = new Resum("Jack", "21", "high school");
    resum1->show();

    Resum* resum2 = resum1->clone();
    resum2->setName("Mike");
    resum2->setAge("25");
    resum2->show();

    delete resum1;
    delete resum2;
    return 0;
}
