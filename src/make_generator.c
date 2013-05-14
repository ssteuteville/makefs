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

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//THIS FUNCTION NEEDS TO BE DELETED ONCE WE ADD FILE_SYSTEM.C/H
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//THIS FUNCTION NEEDS TO BE DELETED ONCE WE ADD FILE_SYSTEM.C/H
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
char* get_meta_path(char* new_file_path)
{
   /*DEBUG*/ printf("get_meta_path: new_file_path: %s\n", new_file_path);
    char* meta_path[PATH_MAX] = {NULL};
    char* temp = strrchr(new_file_path, '/');//get point to last occurence of '/'
    strncpy(meta_path, new_file_path, strlen(new_file_path) - strlen(temp));//copy only what is needed
    strncat(meta_path, "/.files.txt", PATH_MAX);//cancatenate metafile to the path
    return meta_path;
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//THIS FUNCTION NEEDS TO BE DELETED ONCE WE ADD FILE_SYSTEM.C/H
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
char* get_make_path(char* makefile_name)
{
    char* make_path[PATH_MAX] = {NULL};
    char* temp = strrchr(makefile_name, '/'); //Format /Makefile.flag1.flag2....flagn
    strncpy(make_path, makefile_name, (strlen(makefile_name) - (strlen(temp))+9));
    return make_path;
}

char* get_cflags(char* init_flags)
{
    printf("Made it into get cflags\n");
    init_flags++;
    char* ret = malloc(sizeof(char)*PATH_MAX);
    printf("allocated space\n");
    strcpy(ret,"");
    printf("copied blank string\n");
    if(strcmp(init_flags, "allf" ) == 0)//if all flags was chosen
    {
        printf("about to cat\n");
        strcat(ret, "-g -Wall -pedantic -O2 -Wextra"); // append all flag options
    }
    else//if the user chose specific flags
    {
        printf("about to loop\n");
        int i = 0;
        while(init_flags[i] != '\0')
        {   
            printf("looping current flag char : %c\n", init_flags[i]);
            if(init_flags[i] != '.')
                strcat(ret, init_flags[i]);
            else
                strcat(ret, " ");
            i++;
        }   
    }
    printf("get_cflags about to return %s\n", ret);
    return ret;
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//THIS FUNCTION NEEDS TO BE DELETED ONCE WE ADD FILE_SYSTEM.C/H
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
char* load_meta(char (*list)[max_files][PATH_MAX], char* meta_path, int mode)//0 for normal mode
{                                                               //1 for determine compiler mode 
    FILE* meta = fopen(meta_path, "r");
    printf("Meta is open\n");
    char file_name[PATH_MAX] = {NULL};
    int i = 0;
    char ret[max_run];
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
                strncpy(ret,"gcc", max_run);
                printf("ret value set %s\n", ret);
                mode++;
            }
            else if((*list)[i][strlen((*list)[i]) - 1] == 'p')
            {
                puts("setting compiler as g++");
                strcpy(ret,"g++");
                puts("compiler type set");
                mode++;
            }
        }
        else if(mode == 0)
            strcpy(ret, "");
        i++;
    }
    printf("Made it out of loop\n");
    fclose(meta);   

return ret;

}

char* build_objects(char list[max_files][PATH_MAX], char* comp)
{
    char ret[PATH_MAX] = {NULL};
    if(comp[strlen(comp) -1] == 'c')
    {
        int i = 1;
        while(i < strlen(list))
        {
            printf("Looping through files, current file name : %s\n", list[i]);
            if(strlen(list[i]) >2)
            {
                printf("made it into if\n");
                list[i][strlen(list[i])-1] = 'o';//change the c to an o
                strcat(ret, list[i]);//add to the object list  
                strncat(ret, " ", 1);          
            }
            i++;
        }
    }
    else if(comp[strlen(comp) -1] == '+')
    {
        int i = 1;
        while(i < strlen(list))
        {
            if(strlen(list[i]) > 4)
            {
                list[i][strlen(list[i])-1] = '\0';//remove a p
                list[i][strlen(list[i])-1] = '\0';//remove a p
                list[i][strlen(list[i])-1] = 'o';//change the c to an o
                strcat(ret, list[i]);
                strncat(ret, " ", 1);
            }
            i++;
        }
    } 
    return ret;  
}

bool make_gen(char* file_path)
{
    puts("In make_gen");
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //THE LINE BELOW NEEDS TO BE CHANGED ONCE WE USE META_SYSTEM
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    char* meta_path = get_meta_path(file_path);//path to .files.txt
    char* cflags_init = strrchr(file_path, '/');//format: /makefile.flag.flag1.flag2
    cflags_init = strchr(cflags_init, '.');//format: .flag.flag1.flag2
    char cflags[PATH_MAX];
    strcat(cflags,"CFLAGS = ");
    bool noflags = false;
    char runnable[max_run] = {NULL}; // name of the runnable
    
    char compiler[PATH_MAX] = {NULL};//compiler type
    strncat(compiler, "CC = ", PATH_MAX);
    
    char files[max_files][PATH_MAX] = {NULL};//list of files in meta file
    
    char* objects[PATH_MAX] = {'\0'};
    strncat(objects, "OBJ = ", PATH_MAX);
    //Perhaps we should add some of the following logic to get_cflags()?
    if(cflags_init != NULL)//if the user wants flags
    {
        printf("about to cat\n");
        char* temp = get_cflags(cflags_init);
        printf("%s\n", temp);
        strncat(cflags, temp, PATH_MAX);
        printf("completed cat\n");
    }
    else 
    {
        noflags = true;
        printf("No flags declared\n");
    }

    //Now we will read the file names from the meta data file and determine a compiler
    printf("meta: %s\n", meta_path);
    //load meta files into files and cancatenate correct compiler type to compiler
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //THE LINE BELOW NEEDS TO BE CHANGED ONCE WE USE META_SYSTEM
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    strncat(compiler, load_meta(&files, meta_path, 1), PATH_MAX);
    //DEBUGGING
    printf("Made it out of loop\n");
    printf("Closed file\n files[0] = %s\n", files[0]);
    //copy the runnable name from the list of files
    strncpy(runnable, files[0]+1, max_run);
    printf("Runnable name: %s", runnable);
    //All meta data has been loaded into memory and the compiler has been determined    
    printf("Initializing objects\n");
    strncat(objects, build_objects(files, compiler),PATH_MAX);
    printf("Made it out of file loading\n");
    char* make_path = get_make_path(file_path);
    FILE* makefile = fopen(make_path, "a");
    //start writing to make file
    fprintf(makefile, ".PHONY: clean");
    fprintf(makefile, "\n%s", compiler);
    if(noflags == false)
        fprintf(makefile, "\n%s", cflags);
    fprintf(makefile, "\n%s", objects);
    fprintf(makefile, "\n\n%%.o: %%.c");//need to add if statement for dep
    fprintf(makefile, "\n\t$(CC) -c -o $@ $< $(CFLAGS)");//need to add if statement for cflags
    fprintf(makefile, "\n\n%s: $(OBJ)", runnable);
    fprintf(makefile, "\n\t$(CC) -o $@ $^ $(CFLAGS)");//need to add if statement for cflag
    fprintf(makefile, "\n\nclean:");
    fprintf(makefile, "\n\trm -f %s $(OBJ)\n", runnable);
    fclose(makefile);
    return true;
}

char* determine_compiler(char* meta_path)
{
    printf("Made it into determine_compiler\n");
    FILE* meta = fopen(meta_path, "r");
    char* file_name = malloc(sizeof(char)*PATH_MAX);
    while(fgets(file_name, PATH_MAX, meta) != NULL)
    {
        printf("Just got into loop file_name: %s\n", file_name);    
        puts("Checking compiler type");
        printf("Comparing %c to %s\n",file_name[strlen(file_name) - 2], file_name);
        if(file_name[strlen(file_name)- 2] == 'c')
        {
            puts("setting compiler as gcc");
            fclose(meta);
            return "gcc";
        }
        else if(file_name[strlen(file_name) - 2] == 'p')
        {
            puts("setting compiler as g++");
            fclose(meta);
            return "g++";
        }
    }
    return "Nothing To Compare";   
}