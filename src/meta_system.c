#include "meta_system.h"

void remove_meta(char* meta_path, char* file_removed)
{
    puts("********************************");
    puts("Initiating remove_meta");
    char* buf = strrchr(file_removed, '/');
    if(buf != NULL)
        buf++;
    FILE* meta          = fopen(meta_path, "r");
    FILE* new_meta      = fopen("new_meta_data.txt", "w");
    char file_name[PATH_MAX] = {'\0'};
    char* p             = file_name;
    int i               = 0;
    char ret[PATH_MAX]       = {'\0'};
    printf("File to be deleted: %s\n", buf);
    puts("Looping through meta-data...");
    while(fgets(file_name, sizeof(file_name), meta) != NULL)
    {
        p[strlen(p)-1] = '\0';
        if (strcmp(file_name, buf) != 0) 
        {
            printf("%s read and added\n", file_name);
            fprintf(new_meta, "%s", file_name);
            fprintf(new_meta, "\n");
        }
    }
    remove(meta_path); /* remove old meta file*/
    rename("new_meta_data.txt", meta_path); /* rename to original meta file */
    fclose(meta);
    fclose(new_meta);
    puts("Exiting remove_meta");
    puts("********************************");
}

void rename_meta(char* meta_path, char* file_removed, char* file_renamed)
{
    puts("********************************");
    puts("Initiating rename_meta");
    FILE* meta          = fopen(meta_path, "r");
    FILE* new_meta      = fopen("new_meta_data.txt", "w");
    char file_name[PATH_MAX] = {'\0'};
    char* p             = file_name;
    int i               = 0; 
    char* removed = strrchr(file_removed, '/');
    removed++;
    char* renamed = strrchr(file_renamed, '/');
    renamed++;
    char ret[PATH_MAX]       = {'\0'};
    printf("File to be renamed: %s\n", file_removed);
    printf("New name will be: %s\n", file_renamed);
    puts("Looping through meta-data...");
    while(fgets(file_name, sizeof(file_name), meta) != NULL)
    {
        p[strlen(p)-1] = '\0';
        if (strcmp(file_name, removed) != 0) 
        {
            printf("%s read and added\n", file_name);
            fprintf(new_meta, "%s", file_name);
            fprintf(new_meta, "\n");
        }
        else
        {
            printf("%s read and renamed to %s\n", removed, renamed);
            fprintf(new_meta, "%s", renamed);
            fprintf(new_meta, "\n");  
        }
    }
    remove(meta_path); /* remove old meta file*/
    rename("new_meta_data.txt", meta_path); /* rename to original meta file */
    fclose(meta);
    fclose(new_meta);   
    puts("Exiting rename_meta");
    puts("********************************");
}


void add_meta(char* meta_path, char* file_path)
{  
    puts("********************************");
    puts("Initiating add_meta");
    printf("Meta path was: %s\n", meta_path);
    char* file_name = strrchr(file_path, '/');
    file_name++;
    FILE* meta = fopen(meta_path, "a");
    printf("Added %s to meta file\n", file_name);
    if(file_name != NULL)
    {
        printf("File name wasn't NULL\n");
        fprintf(meta, "%s\n",file_name);
    }
    fclose(meta);
    puts("Exiting add_meta");
    puts("********************************");


}

char* change_filename(char* path, char* filename)
{
    puts("********************************");
    puts("Initiating change_filename");
    char* buf = strrchr(path, '/');
    //printf("buf = %s\n", buf);
    char* ret = malloc(sizeof(char)*PATH_MAX);
    if(buf == NULL)
    {
        puts("Failed to change file name.");
        return path;
    }
    int path_size = strlen(path) - strlen(buf) + 1;
    printf("About to copy the path from %s\n", path);

    strncpy(ret, path, path_size);
    printf("About to cancat %s\n", filename);
    strncat(ret, filename, MAX_FILE_NAME);
    printf("Changed %s to %s\n", path, ret);
    puts("Exiting change_filename");
    puts("********************************");
    return ret;
}

int load_meta(char (*list)[MAX_FILES][PATH_MAX], char* meta_path)//0 for normal mode
{     
    puts("********************************");
    puts("Initiating load_meta");                                                        //1 for determine compiler mode 
    FILE* meta = fopen(meta_path, "r");
    printf("Meta is open\n");
    char file_name[PATH_MAX] = {'\0'};
    int i = 0;
    char ret[MAX_FILES] = {'\0'};
    int file_count = 0;
    puts("About to loop through meta's files");
    while(fgets(file_name, PATH_MAX, meta) != NULL)
    {
        printf("Just got into loop file_name: %s\n", file_name);
        strcpy((*list)[i], file_name);
        printf("incremenintg file count from %d to %d\n", file_count, file_count + 1);
        file_count++;
        (*list)[i][strlen((*list)[i])-1] = '\0';
        printf("list[%d] is %s\n", i, (*list)[i]);
        i++;
    }
    printf("Made it out of loop\n");
    fclose(meta);  
    printf("Exiting load_meta with %d as ret value\n", file_count); 
    puts("********************************");

    return file_count;

}
