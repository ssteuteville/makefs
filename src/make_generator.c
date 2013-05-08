#include "make_generator.h"

bool correct_type(char* meta_path, char* file_path) 
{
    printf("Entered correct_type: %s %s\n", file_path, meta_path);
    char* file_type = strrchr(file_path, '.');
    printf("correct_type: file_type = %s\n", file_type); 
    FILE* meta = fopen(meta_path, "r");
    puts("correct_type: File opened");
    char file_in_meta[PATH_MAX];
    puts("correct_type: file_in_meta allocated");
    while(fgets(file_in_meta, PATH_MAX, meta) != NULL)//case one there is a .c or .cpp in .files.txt
    {
        printf("correct_type: made it into loop, file_in_meta = %s\n", file_in_meta);
        char* temp = strrchr(file_in_meta, '.');
        printf("correct_type: made it into loop, temp = %s\n", temp);
        if(temp != NULL)
        {
            if((strcmp(temp, file_type) == 0 && strcmp(temp, ".cpp")==0)||
                (strcmp(temp, file_type) == 0 && strcmp(temp, ".c")==0))
            {
                fclose(meta);
                return true;
            } 
        }
    }
    printf("correct_type: right after loop\n");
    if(strcmp(file_type, ".c") == 0 || strcmp(file_type, ".cpp"))//case 2 no .c's or .cpp's in .files.txt
    {
        printf("correct_type: made it into case 2\n");
        fclose(meta);
        return true;
    }
    printf("correct_type: made it out of loop\n");
    fclose(meta);
    return false;
}

void add_meta(char* meta_path, char* file_path) 
{
    /* 
    Function to append (use mode "a") filename to meta-data
    */
    printf("Entered add_meta: meta_path: %s file_path %s\n", meta_path, file_path);
    FILE* meta = fopen(meta_path, "a");
    printf("add_meta: opened file");
    char* file_name = strrchr(file_path, '/');
    file_name++;
    strncat(file_name, "\n", PATH_MAX);
    printf("add_meta: filename: %s\n", file_name);
    if(file_name != NULL)
    {
        fprintf(meta, file_name);   
    }
    fclose(meta);


}

char* get_meta_path(char* new_file_path)
{
    printf("get_meta_path: new_file_path: %s\n", new_file_path);
    char* meta_path[PATH_MAX];
    char* temp = strrchr(new_file_path, '/');
    printf("temp after strrchr = %s\n", temp);
    strncpy(meta_path, new_file_path, strlen(new_file_path) - strlen(temp));
    printf("meta_path after copy = %s\n", meta_path);
    puts("About to concat [./files.txt]");
    strncat(meta_path, "/.files.txt", PATH_MAX);
    printf("New meta_path after concat = %s\n", meta_path);
    return meta_path;

}