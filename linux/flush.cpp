#include <iostream>
#include <fstream>
#include <dirent.h>

using namespace std;

int main (int argc, char *argv[])
{
    fstream fs("test.txt", ios_base::app);
    if(!fs.is_open()){ 
        return -1;
    }
    cout << "yes" << endl;
    fs << "Hello";
    fs.close();
    
    DIR* dir;
    return 0;
}
