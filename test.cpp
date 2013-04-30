#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main() 
{
    /* Compile: g++ test.cpp */
        // $ ./a.out
        // hello.c hello.h main.c
        // (a Makefile is then generated)

    string file_c   = ""; /* hello.c */
    string file_h   = ""; /* hello.h */
    string driver_c = ""; /* main.c */
    ofstream ofile("Makefile");

    cin >> file_c;
    cin >> file_h;
    cin >> driver_c;

    /* strip off .c and .h */
    string file_no_c    = file_c.substr(0, file_c.size()-2);
    string file_no_h    = file_h.substr(0, file_h.size()-2);
    string driver_no_c  = driver_c.substr(0, driver_c.size()-2);

    /* write to Makefile */
    ofile << "runnable: " << file_no_h + ".o " << driver_no_c + ".o " << "\n";
    ofile << "\t" << "g++ -Wall -pedantic -g -o runnable " << file_no_h + ".o " << driver_no_c + ".o " << "\n\n";
    
    ofile << file_no_h + ".o: " << file_h << " " << file_c << "\n";
    ofile << "\t" << "g++ -Wall -pedantic -g -c " << file_c << "\n\n";

    ofile << driver_no_c + ".o: " << file_no_h + ".o " << "\n";
    ofile << "\t" << "g++ -Wall -pedantic -g -c " << driver_c << "\n\n";

    ofile << "clean:" << "\n";
    ofile << "\t" << "rm -f runnable " << "*.o" << "\n";

    return 0;
}

/* 
Output should be:

runnable: hello.o main.o 
    g++ -Wall -pedantic -g -o runnable hello.o main.o 

hello.o: hello.h hello.c
    g++ -Wall -pedantic -g -c hello.c

main.o: hello.o 
    g++ -Wall -pedantic -g -c main.c

clean:
    rm -f runnable *.o
*/