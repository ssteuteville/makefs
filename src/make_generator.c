#include "make_generator.h"
#include "meta_system.h"
/*added comment to test SublimeGit :P*/
bool correct_type(char* meta_path, char* file_path) 
{
    /*DEBUG*/printf("Entered correct_type: %s %s\n", file_path, meta_path);
    char* file_type = strrchr(file_path, '.');
    if(file_type == NULL)
        return false;
    /*DEBUG*/printf("correct_type: file_type = %s\n", file_type); 
    FILE* meta = fopen(meta_path, "r");
    /*DEBUG*/puts("correct_type: File opened");
    char file_in_meta[PATH_MAX] = {'\0'};
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



char* get_cflags(char* init_flags)
{
    printf("Made it into get cflags\n");
    init_flags++;
    char* ret = malloc(sizeof(char)*PATH_MAX);
    printf("allocated space\n");
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
            {
                //strcat(ret, init_flags[i]);
                ret += init_flags[i];//this won't work but it also wont segfault =(
                printf("ret = %s\n", ret);
            }
            else
                strcat(ret, " ");
            i++;
        }   
    }
    printf("get_cflags about to return %s\n", ret);
    return ret;
}


char* build_objects(char list[max_files][PATH_MAX], char* comp, int num_files)
{
    char ret[PATH_MAX] = {'\0'};
    if(comp[strlen(comp) -1] == 'c')
    {
        int i = 1;
        while(i < num_files)
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
        while(i < num_files)
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
    char* meta_path = change_filename(file_path, ".files.txt");
    char* cflags_init = strrchr(file_path, '/');//format: /makefile.flag.flag1.flag2
    cflags_init = strchr(cflags_init, '.');//format: .flag.flag1.flag2
    char cflags[PATH_MAX];
    strcat(cflags,"CFLAGS = ");
    bool noflags = false;
    char runnable[max_run] = {'\0'}; // name of the runnable
    int file_count = 0;
    
    char compiler[PATH_MAX] = {'\0'};//compiler type
    strncat(compiler, "CC = ", PATH_MAX);
    
    char files[max_files][PATH_MAX] = {'\0'};//list of files in meta file
    
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
    strncat(compiler, determine_compiler(meta_path), PATH_MAX);
    file_count = load_meta(&files, meta_path);
    //DEBUGGING
    printf("Made it out of loop\n");
    printf("Closed file\n files[0] = %s\n", files[0]);
    //copy the runnable name from the list of files
    strncpy(runnable, files[0]+1, max_run);
    printf("Runnable name: %s", runnable);
    //All meta data has been loaded into memory and the compiler has been determined    
    printf("Initializing objects\n");
    strncat(objects, build_objects(files, compiler, file_count),PATH_MAX);
    printf("Made it out of file loading\n");
    char* make_path = change_filename(file_path, "Makefile");
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