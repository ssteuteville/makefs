/* Makefile generator */

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

int main(int num_args, char* arg_strings[]) 
{
    /*char* cmd = "pwd > path.txt";
    system(cmd);

    FILE* path = fopen("path.txt", "r");

    char path_name[100] = {'\0'};
    fgets(path_name, 100, path);*/

    char* cmd = "ls -R > files.txt";
    system(cmd);

    /* open file for reading */
    FILE* input_text = fopen ("files.txt", "r");
    
    /* open file for writing */
    FILE* makefile = fopen("Makefile", "w");

    if (input_text == NULL)
    {
        perror("Error opening file");
    }
    else 
    {
        /* 40 consecutive arrays of 40 characters each */    
        char file_array[40][40] = {'\0'};
        char file_name[25]      = {'\0'};
        int i                   = 1;
        int num_files           = 0;
        char compiler_choice[9] = "CC = ";
        char allf[5]            = "allf";
        char total_cflags[45]   = "CFLAGS = ";
        bool determine_compiler = false;
        bool gcc                = false;
        bool gplusplus          = false;

        /* if user enters CFLAGS options */
        if (num_args > 1)
        {
            /* user entered 'make allf' (enable all flags) */
            if (strcmp(allf, arg_strings[1]) == 0)
            {
                strcat(total_cflags, "-g -Wall -pedantic -O2 -Wextra");
                /*printf("Args read: %s\n", total_cflags);*/
            }
            else
            {   
                /* read in CFLAGS individually */
                while (i < num_args)
                {
                    strcat(total_cflags, arg_strings[i]);
                    strcat(total_cflags, " ");  
                    i++;              
                }
                /*printf("Args read: %s\n", total_cflags);*/
            }
        }

        i = 0;
        while (fgets(file_name, 25, input_text) != NULL)
        {
            /* copy file name (static string) into array */
            strcpy(file_array[i], file_name);
            
            /* remove '\n' at the end of each string */
            file_array[i][strlen(file_array[i])-1] = '\0';

            if (determine_compiler == false)
            {
                /* if a .c file is read */
                if (file_array[i][strlen(file_array[i])-1] == 'c')
                {
                    /* compile with gcc */
                    strcat(compiler_choice, "gcc");
                    /*printf("%s\n", compiler_choice);*/
                    determine_compiler = true;
                    gcc = true;

                }
                /* if a .cpp file is read: specifically if there is a p at the end */
                if (file_array[i][strlen(file_array[i])-1] == 'p')
                {
                    /* compile with g++ */
                    strcat(compiler_choice, "g++");
                    /*printf("%s\n", compiler_choice);*/
                    determine_compiler = true;
                    gplusplus = true;
                }
            }
            i++;
        }

        /* save total number of files read */
        num_files = i;

        /* close the file */
        fclose(input_text);

        /* Begin generating Makefile */
        fprintf(makefile, ".PHONY: clean");
        fprintf(makefile, "\n%s", compiler_choice);

        /* if there were CFLAGS defined */
        if (num_args > 1)
        {
            fprintf(makefile, "\n%s", total_cflags);
        }

        /* files.txt contains .:, files.txt, and filename.c/cpp */
        if (num_files > 3)
        {
            fprintf(makefile, "\nDEPS =");
        }

        /* print out the .h files */
        for (i = 0; i < num_files; ++i)
        {
            if (file_array[i][strlen(file_array[i])-1] == 'h')
            {
                fprintf(makefile, " %s", file_array[i]);
            }
        }
        fprintf(makefile, "\nOBJ =");

        if (gcc == true)
        {
            /* print out .c files (replace c with o) */
            for (i = 0; i < num_files; ++i)
            {
                if (file_array[i][strlen(file_array[i])-1] == 'c')
                {
                    file_array[i][strlen(file_array[i])-1] = 'o';
                    fprintf(makefile, " %s", file_array[i]);
                }
            }
        }
        else if (gplusplus == true) { 
            /* print out .cpp files (replace cpp with o) */
            for (i = 0; i < num_files; ++i)
            {
                if (file_array[i][strlen(file_array[i])-1] == 'p')
                {
                    file_array[i][strlen(file_array[i])-1] = '\0';
                    file_array[i][strlen(file_array[i])-1] = '\0';
                    file_array[i][strlen(file_array[i])-1] = 'o';
                    fprintf(makefile, " %s", file_array[i]);
                }
            }            
        }

        if (num_files > 1)
        {
            /* to print % add a % before it to escape */
            fprintf(makefile, "\n\n%%.o: %%.c $(DEPS)");
            fprintf(makefile, "\n\t$(CC) -c -o $@ $< $(CFLAGS)");
        }
        fprintf(makefile, "\n\nrunnable: $(OBJ)");
        fprintf(makefile, "\n\t$(CC) -o $@ $^ $(CFLAGS)");
        fprintf(makefile, "\n\nclean:");
        fprintf(makefile, "\n\trm -f runnable $(OBJ)\n");
    }
    
    /* close the file */
    fclose(makefile);

    /* execute make and get "runnable" executable in directory */
    cmd = "make";
    system(cmd);

    /* clean up */
    cmd = "rm a.out files.txt";
    system(cmd);

    return 0;
}

/* 
CC = gcc
DEPS = hello.h hello1.h hello2.h hello3.h
OBJ = hello.o hello1.o hello2.o hello3.o main.o

%.o: %.c $(DEPS)
    $(CC) -c -o $@ $< $(CFLAGS)

runnable: $(OBJ)
    $(CC) -o $@ $^ $(CFLAGS)

clean:
    rm -f runnable $(OBJ)
*/