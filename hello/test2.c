#include <string.h>
#include <stdio.h>

int main() 
{
    /* 20 consecutive arrays of 20 characters each */    
    char file_array[20][20] = {'\0'};
    char file_name[20]      = {'\0'};
    int i                   = 0;
    int num_files           = 0;

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
        while (fgets(file_name, 20, input_text) != NULL)
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

        /* flags and options can be modifiable later */
        fprintf(makefile, "CC = gcc\n");
        fprintf(makefile, "CFLAGS = -I.");

        if (num_files > 1)
        {
            fprintf(makefile, "\nDEPS =");
        }

        /* print out all .h files */
        int j = 0;
        char h[] = "h";

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
                file_array[i][strlen(file_array[i])-2] = '.';
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
    return 0;
}

/* 
CC = gcc
CFLAGS = -I.
DEPS = hello.h hello1.h hello2.h hello3.h
OBJ = hello.o hello1.o hello2.o hello3.o main.o

%.o: %.c $(DEPS)
    $(CC) -c -o $@ $< $(CFLAGS)

runnable: $(OBJ)
    $(CC) -o $@ $^ $(CFLAGS)

clean:
    rm -f runnable $(OBJ)
*/