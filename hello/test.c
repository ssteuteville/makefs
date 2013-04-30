#include <string.h>
#include <stdio.h>

int main() 
{
    /* Compile: gcc test.c */
        // $ ./a.out
        // hello.c hello.h main.c
        // (a Makefile is then generated)

    char file_c[20]     = {'\0'}; /* hello.c */
    char file_h[20]     = {'\0'}; /* hello.h */
    char driver_c[20]   = {'\0'}; /* main.c */
    FILE* makefile = fopen("Makefile", "w");

    scanf("%s", file_c);
    scanf("%s", file_h);
    scanf("%s", driver_c);

    /* redundant if .h is the same name as .c */
    char file_no_c[19]   = {'\0'};
    char file_no_h[19]   = {'\0'};
    char driver_no_c[19] = {'\0'};

    strcpy(file_no_c, file_c);
    strcpy(file_no_h, file_h);
    strcpy(driver_no_c, driver_c);

    char* p_file_no_c   = file_no_c;
    char* p_file_no_h   = file_no_h;
    char* p_driver_no_c = driver_no_c;

    /* strip off .c and .h */
    p_file_no_c[strlen(p_file_no_c)-2]      = '\0';
    p_file_no_h[strlen(p_file_no_h)-2]      = '\0';
    p_driver_no_c[strlen(p_driver_no_c)-2]  = '\0';

    char dot_o[] = ".o";

    char file_with_o[20]   = {'\0'};
    char driver_with_o[20] = {'\0'};

    strcpy(file_with_o, file_no_h);
    strcpy(driver_with_o, driver_no_c);

    /* now have hello.o, main.o */
    strncat (file_with_o, dot_o, 2);
    strncat (driver_with_o, dot_o, 2);

    /* write to Makefile */
    fprintf(makefile, "runnable: %s %s", file_with_o, driver_with_o);
    fputs("\n", makefile);
    fputs("\t", makefile);
    fprintf(makefile, "g++ -Wall -pedantic -g -o runnable %s %s", file_with_o, driver_with_o);
    fputs("\n", makefile);
    fputs("\n", makefile);
    fprintf(makefile, "%s: %s %s", file_with_o, file_h, file_c);
    fputs("\n", makefile);
    fputs("\t", makefile);
    fprintf(makefile, "g++ -Wall -pedantic -g -c %s", file_c);
    fputs("\n", makefile);
    fputs("\n", makefile);
    fprintf(makefile, "%s: %s", driver_with_o, file_with_o);
    fputs("\n", makefile);
    fputs("\t", makefile);   
    fprintf(makefile, "g++ -Wall -pedantic -g -c %s", driver_c);
    fputs("\n", makefile);
    fputs("\n", makefile);
    fputs("clean:", makefile);
    fputs("\n", makefile);
    fputs("\t", makefile);  
    fputs("rm -f runnable *.o", makefile);
    fputs("\n", makefile);

    return 0;
}

/* 
Output should be:

all: hello.o main.o 
    g++ -Wall -pedantic -g -o all hello.o main.o 

hello.o: hello.h hello.c
    g++ -Wall -pedantic -g -c hello.c

main.o: hello.o 
    g++ -Wall -pedantic -g -c main.c

clean:
    rm -f all *.o
*/