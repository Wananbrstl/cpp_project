#include <bits/stdc++.h>
#include <functional>

using namespace std;


void show(){
    cout << "hello" << endl;
}

int main (int argc, char *argv[])
{
    
    function<void()> s = show;
    s();

    return 0;
}
