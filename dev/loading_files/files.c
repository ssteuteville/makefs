/*FILE PRACTICE removing a line from a file.*/
#include <stdio.h>
#include <limits.h>
#include <string.h>

char* load_meta(char (*list)[20][PATH_MAX], char* meta_path, int mode)//0 for normal mode
{																//1 for determine compiler mode	
	FILE* meta = fopen(meta_path, "r");
    printf("Meta is open\n");
    char file_name[PATH_MAX] = {'\0'};
    int i = 0;
    char ret[20] = {'\0'};
    puts("About to loop through meta's files");
    while(fgets(file_name, PATH_MAX, meta) != NULL)
    {
        printf("Just got into loop file_name: %s\n", file_name);
        strcpy((*list)[i], file_name);
        (*list)[i][strlen((*list)[i])-1] = '\0';
        puts("about to determine compiler");
        if(mode == 1)
        {
            puts("Checking compiler type");
            if((*list)[i][strlen((*list)[i]) - 1] == 'c')
            {
                puts("setting compiler as gcc");
                strncpy(ret,"gcc", 20);
                printf("ret value set %s\n", ret);
                mode++;
            }
            else if((*list)[i][strlen((*list)[i]) - 1] == 'p')
            {
                puts("setting compiler as g++");
                strcpy(ret,"g++");
                printf("ret value set %s\n", ret);
                mode++;
            }
            puts("compiler type set");
        }
        else if(mode == 0)
        	strcpy(ret, "");
        i++;
    }
    printf("Made it out of loop\n");
    fclose(meta);	

return ret;

}

void main(int argc, char** argv)
{
	char files[20][PATH_MAX] = {'\0'};
	char* test;
	test = load_meta(&files, argv[1], 1);
	printf("Compiler : %s\n",test);
	int i = 0;
	for(i; i < strlen(files); i++)
	{
		printf("File at index %d: %s\n",i,files[i]);
	}


}
