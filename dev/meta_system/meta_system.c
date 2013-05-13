/*FILE PRACTICE removing a line from a file.*/
#include <stdio.h>
#include <limits.h>
#include <string.h>
#define MAX_FILE_NAME 35
#define MAX_FILES 20


void remove_meta(char* old_meta_file, char* file_removed)
{
    puts("********************************");
    puts("Initiating remove_meta");
    FILE* meta          = fopen(old_meta_file, "r");
    FILE* new_meta      = fopen("new_meta_data.txt", "w");
    char file_name[256] = {'\0'};
    char* p             = file_name;
    int i               = 0;
    char ret[256]       = {'\0'};
    printf("File to be deleted: %s\n", file_removed);
    puts("Looping through meta-data...");
    while(fgets(file_name, sizeof(file_name), meta) != NULL)
    {
        p[strlen(p)-1] = '\0';
        if (strcmp(file_name, file_removed) != 0) 
        {
            printf("%s read and added\n", file_name);
            fprintf(new_meta, "%s", file_name);
            fprintf(new_meta, "\n");
        }
    }
    remove(old_meta_file); /* remove old meta file*/
    rename("new_meta_data.txt", old_meta_file); /* rename to original meta file */
    fclose(meta);
    fclose(new_meta);
    puts("Exiting remove_meta");
    puts("********************************");
}

void rename_meta(char* old_meta_file, char* file_removed, char* file_renamed)
{
    puts("********************************");
    puts("Initiating rename_meta");
    FILE* meta          = fopen(old_meta_file, "r");
    FILE* new_meta      = fopen("new_meta_data.txt", "w");
    char file_name[256] = {'\0'};
    char* p             = file_name;
    int i               = 0;
    char ret[256]       = {'\0'};
    printf("File to be renamed: %s\n", file_removed);
    printf("New name will be: %s\n", file_renamed);
    puts("Looping through meta-data...");
    while(fgets(file_name, sizeof(file_name), meta) != NULL)
    {
        p[strlen(p)-1] = '\0';
        if (strcmp(file_name, file_removed) != 0) 
        {
            printf("%s read and added\n", file_name);
            fprintf(new_meta, "%s", file_name);
            fprintf(new_meta, "\n");
        }
    }
    printf("%s read and renamed to %s\n", file_removed, file_renamed);
    fprintf(new_meta, "%s", file_renamed);
    fprintf(new_meta, "\n");
    remove(old_meta_file); /* remove old meta file*/
    rename("new_meta_data.txt", old_meta_file); /* rename to original meta file */
    fclose(meta);
    fclose(new_meta);   
    puts("Exiting rename_meta");
    puts("********************************");
}

void add_meta(char* meta_file, char* filename)
{  
    puts("********************************");
    puts("Initiating add_meta");
    FILE* meta = fopen(meta_file, "a");
    printf("Added %s to meta file\n", filename);
    fprintf(meta, "%s\n",filename);
    fclose(meta);
    puts("Exiting add_meta");
    puts("********************************");


}

char* change_filename(char* path, char* filename)
{
    puts("********************************");
    puts("Initiating change_filename");
    char* buf = strrchr(path, '/');
    char ret[PATH_MAX] = {'\0'};
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
void main(int argc, char** argv)
{
	char files[MAX_FILES][PATH_MAX]   = {'\0'};
	char* test                        = NULL;
    char* file_to_remove              = "a.c";
    char* file_to_rename              = "b.c";
    char* file_to_add                 = "d.c";
    char* new_name_for_file           = "wubwub.c";
    char* file_name_to_change         = "/dir/dir/dir/go.c";
    char* name_to_change_file         = "gooch.c";
    remove_meta(argv[1], file_to_remove);
    rename_meta(argv[1], file_to_rename, new_name_for_file);
    add_meta(argv[1], file_to_add);
    printf("Return value actually was %s\n",change_filename(file_name_to_change, name_to_change_file));

}