/* Makefile generator */

#include <string.h>
#include <stdio.h>

int main(int num_args, char* arg_strings[]) 
{
    char allf[]         = "allf";
    char total_cflags[] = "CFLAGS = ";

    /* if user enters CFLAGS options */
    int j = 1;

    if (num_args > 1)
    {
        /* user entered make allf (enable all flags) */
        if (strcmp(allf, arg_strings[1]) == 0)
        {
            strcat(total_cflags, "-g -Wall -pedantic -O2 -Wextra");
            printf("Args read: %s\n", total_cflags);
        }
        else
        {   
            /* read in CFLAGS individually */
            while (j < num_args)
            {
                strcat(total_cflags, arg_strings[j]);
                strcat(total_cflags, " ");  
                j++;              
            }
            printf("Args read: %s\n", total_cflags);
        }
    }

    /* 40 consecutive arrays of 40 characters each */    
    char file_array[40][40] = {'\0'};
    char file_name[25]      = {'\0'};
    int i                   = 0;
    int num_files           = 0;

    /* execute Linux command: change this path to the directory storing the files
        to be compiled. test2.c can be compiled and ran from anywhere. The generated
        Makefile will be put in the folder with the rest of the files. 

        ls -R > files.text will grab all the files in the current directory and 
        output them each on a newline into files.txt. Then read from that file! */
    char* cmd = "cd /home/andreas/Documents/makefs/test_prog_multiple_new; ls -R > files.txt";
    system(cmd);

    /* open file for reading */
    FILE* input_text = fopen ("/home/andreas/Documents/makefs/test_prog_multiple_new/files.txt", "r");
    /* open file for writing */
    FILE* makefile = fopen("/home/andreas/Documents/makefs/test_prog_multiple_new/Makefile", "w");

    if (input_text == NULL)
    {
        perror("Error opening file");
    }
    else 
    {
        while (fgets(file_name, 25, input_text) != NULL)
        {
            printf("[%d] read a file: %s", i, file_name);

            /* copy file name (static string) into array */
            strcpy(file_array[i], file_name);
            i++;
        }

        /* save total number of files read */
        num_files = i;

        /* close the file */
        fclose(input_text);

        /* print out array */
        for (i = 0; i < num_files; ++i)
        {
            printf("Array[%d]: %s", i, file_array[i]);
        }

        /* flags and options can be modifiable later -- I think these flags
            are the most we would need to accept from input */
        fprintf(makefile, ".PHONY: clean\n");
        fprintf(makefile, "CC = gcc");

        /* if there were CFLAGS defined */
        if (num_args > 1)
        {
            fprintf(makefile, "\n%s", total_cflags);
        }

        if (num_files > 1)
        {
            fprintf(makefile, "\nDEPS =");
        }

        /* print out the .h files */
        for (i = 0; i < num_files; ++i)
        {
            /* remove '\n' at the end of each string */
            file_array[i][strlen(file_array[i])-1] = '\0';
            if (file_array[i][strlen(file_array[i])-1] == 'h')
            {
                fprintf(makefile, " %s", file_array[i]);
            }
        }
        fprintf(makefile, "\nOBJ =");

        /* print out .c files (replace .c with .o) */
        for (i = 0; i < num_files; ++i)
        {
            if (file_array[i][strlen(file_array[i])-1] == 'c')
            {
                file_array[i][strlen(file_array[i])-1] = 'o';
                fprintf(makefile, " %s", file_array[i]);
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
    cmd = "cd /home/andreas/Documents/makefs/test_prog_multiple_new; make";
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