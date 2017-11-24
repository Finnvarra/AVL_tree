#include "AVL.h"

int main(int argc, char* argv[])
{
    string file1, file2;
    file1=argv[1];
    file2= argv[2];
    AVL<string> A(file2);
    string name;
    string funct;
    ifstream in;
    in.open(file1);
    while (in>>funct)
    {
        if (funct == "clear")
        {
            A.clear();
        }
        else if(funct=="add")
        {
            in>>name;
            A.add(name);
        }
        else if (funct== "print")
        {
            A.print();
        }
        else if (funct== "find")
        {
            in>>name;
            A.find(name);
        }
        else if(funct=="remove")
        {
            in>>name;
            A.remove(name);
        }
    }
    in.close();
    return 0;
}
