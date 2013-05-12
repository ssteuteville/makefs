#include "make_generator.h"

bool correct_type(char* meta_path, char* file_path) 
{
    /*DEBUG*/printf("Entered correct_type: %s %s\n", file_path, meta_path);
    char* file_type = strrchr(file_path, '.');
    if(file_type == NULL)
        return false;
    /*DEBUG*/printf("correct_type: file_type = %s\n", file_type); 
    FILE* meta = fopen(meta_path, "r");
    /*DEBUG*/puts("correct_type: File opened");
    char file_in_meta[PATH_MAX] = {NULL};
    while(fgets(file_in_meta, PATH_MAX, meta) != NULL)//case one there is a .c or .cpp in .files.txt
    {
        /*DEBUG*/printf("correct_type: made it into loop, file_in_meta = %s\n", file_in_meta);
        char* temp = strrchr(file_in_meta, '.');
        /*DEBUG*/printf("correct_type: made it into loop, temp = %s\n", temp);
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
    /*DEBUG*/printf("correct_type: right after loop filetype: %s\n", file_type);
    if(strcmp(file_type, ".c") == 0 || strcmp(file_type, ".cpp") == 0)//case 2 no .c's or .cpp's in .files.txt
    {
        printf("correct_type: made it into case 2\n");
        fclose(meta);
        return true;
    }
    /*DEBUG*/printf("correct_type: about to close file\n");
    fclose(meta);
    return false;
}

void add_meta(char* meta_path, char* file_path) 
{
    /* 
    Function to append (use mode "a") filename to meta-data
    */
    /*DEBUG*/printf("Entered add_meta: meta_path: %s file_path %s\n", meta_path, file_path);
    FILE* meta = fopen(meta_path, "a");
    /*DEBUG*/printf("add_meta: opened file");
    char* file_name = strrchr(file_path, '/');
    file_name++;
    strncat(file_name, "\n", PATH_MAX);
    /*DEBUG*/printf("add_meta: filename: %s\n", file_name);
    if(file_name != NULL)
    {
        fprintf(meta, file_name);   
    }
    fclose(meta);


}

char* get_meta_path(char* new_file_path)
{
   /*DEBUG*/ printf("get_meta_path: new_file_path: %s\n", new_file_path);
    char* meta_path[PATH_MAX] = {NULL};
    char* temp = strrchr(new_file_path, '/');//get point to last occurence of '/'
    strncpy(meta_path, new_file_path, strlen(new_file_path) - strlen(temp));//copy only what is needed
    strncat(meta_path, "/.files.txt", PATH_MAX);//cancatenate metafile to the path
    return meta_path;
}

char* get_make_path(char* makefile_name)
{
    char* make_path[PATH_MAX] = {NULL};
    char* temp = strrchr(makefile_name, '/'); //Format /Makefile.flag1.flag2....flagn
    strncpy(make_path, makefile_name, (strlen(makefile_name) - (strlen(temp))+9));
    printf("About to return %s as make_path\n", make_path);
    return make_path;
}

char* get_cflags(char* init_flags)
{
    init_flags++;
    char* ret = malloc(sizeof(char)*PATH_MAX);
    if(strcmp(init_flags, "allf" ) == 0)//if all flags was chosen
        strcat(ret, "-g -Wall -pedantic -O2 -Wextra"); // append all flag options
    else//if the user chose specific flags
    {
        int i = 0;
        while(init_flags[i] != '\0')
        {   
            if(init_flags[i] != '.')
                strncat(ret, init_flags[i], PATH_MAX);
            else
                strncat(ret, " ", PATH_MAX);
            i++;
        }   
    }
    return ret;
}

bool make_gen(char* file_path, char* meta_path)
{
    puts("In make_gen");
    int i = 0;
    //First we will set up the cflags
    char* cflags_init = strrchr(file_path, '/');//format: /makefile.flag.flag1.flag2
    printf("cflags_init = %s\n", cflags_init);
    cflags_init = strchr(cflags_init, '.');//format: .flag.flag1.flag2
    printf("cflags_init now = %s\n", cflags_init);
    char* cflags = "CFLAGS = ";
    bool noflags = false;
    if(cflags_init != NULL)//if the user wants flags
    {
        strncat(cflags, get_make_path(cflags_init), PATH_MAX);
    }
    else 
    {
        noflags = true;
        printf("No flags declared\n");
    }

    //Now we will read the file names from the meta data file and determine a compiler
    FILE* meta = fopen(meta_path, "r");
    char compiler[PATH_MAX] = {NULL};
    strncat(compiler, "CC = ", PATH_MAX);
    char files[max_files][PATH_MAX] = {NULL};
    char file_name[PATH_MAX] = {NULL};
    bool determine_compiler = false;
    bool gcc = false;
    bool gplusplus = false;
    i = 0;
    char* deps[PATH_MAX] = {'\0'};
    strncat(deps, "DEPS = ", PATH_MAX);

    puts("About to loop through meta's files");
    while(fgets(file_name, PATH_MAX, meta) != NULL)
    {
        printf("Just got into loop file_name: %s\n", file_name);
        strcpy(files[i], file_name);
        files[i][strlen(files[i])-1] = '\0'; /* remove newline */
        if(files[i][strlen(files[i]) -1] == 'h')
        {
            strcat(deps, files[i]);
        }
        if(determine_compiler == false)
        {
            puts("Checking compiler type");
            if(files[i][strlen(files[i]) - 1] == 'c')
            {
                puts("setting compiler as gcc");
                strncat(compiler, "gcc", PATH_MAX);
                puts("compiler type set");
                determine_compiler = true;
                gcc = true;
            }
            else if(files[i][strlen(files[i]) - 1] == 'p')
            {
                puts("setting compiler as g++");
                strcat(compiler, "g++");
                determine_compiler = true;
                gplusplus = true;
                puts("compiler type set");
            }
        }
        i++;
    }
    printf("Made it out of loop\n");
    fclose(meta);
    printf("Closed file\n");
    char* runnable = files[0];
    runnable++;
    printf("Runnable name: %s", runnable);
    //All meta data has been loaded into memory and the compiler has been determined    
    
    printf("Initializing objects\n");
    char* objects[PATH_MAX] = {'\0'};
    strncat(objects, "OBJ = ", PATH_MAX);
    i = 1; //don't start at zero because this is the name of the directory not a file
    if(gcc == true)
    {
        while(i < strlen(files))
        {
            printf("Looping through files, current file name : %s\n", files[i]);
            if(strlen(files[i]) >2)
            {
                printf("made it into if\n");
                files[i][strlen(files[i])-1] = 'o';//change the c to an o
                strcat(objects, files[i]);//add to the object list  
                strncat(objects, " ", 1);          
            }
            i++;
        }
    }
    else if(gplusplus == true)
    {
        while(i < strlen(files))
        {
            if(strlen(files[i]) > 4)
            {
                files[i][strlen(files[i])-1] = '\0';//remove a p
                files[i][strlen(files[i])-1] = '\0';//remove a p
                files[i][strlen(files[i])-1] = 'o';//change the c to an o
                strcat(objects, files[i]);
                strncat(objects, " ", 1);
            }
            i++;
        }
    }
    printf("Made it out of file loading\n");
    char* make_path = malloc(sizeof(char)*PATH_MAX);
    make_path = get_make_path(file_path);
    FILE* makefile = fopen(make_path, "a");
    //start writing to make file
    fprintf(makefile, ".PHONY: clean");
    fprintf(makefile, "\n%s", compiler);
    if(noflags = false)
        fprintf(makefile, "\n%s", cflags);
    fprintf(makefile, "\n%s", objects);
    if(strcmp(deps, "DEPS = ") != 0)
        fprintf(makefile, "\n%s", deps);
    fprintf(makefile, "\n\n%%.o: %%.c $(DEPS)");//need to add if statement for dep
    fprintf(makefile, "\n\t$(CC) -c -o $@ $< $(CFLAGS)");//need to add if statement for cflags
    fprintf(makefile, "\n\n%s: $(OBJ)", runnable);
    fprintf(makefile, "\n\t$(CC) -o $@ $^ $(CFLAGS)");//need to add if statement for cflag
    fprintf(makefile, "\n\nclean:");
    fprintf(makefile, "\n\trm -f %s $(OBJ)\n", runnable);
    fclose(makefile);
    return true;
}
