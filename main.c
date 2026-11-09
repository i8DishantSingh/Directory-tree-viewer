#include<stdio.h>
#include<dirent.h>
#include<string.h>

void print_file(const char *name, int is_dir, int indent) {
    printf("%*c", indent * 2, ' '); // Indent the output based on the depth of the directory
    if(is_dir) {
        printf("\033[0;34m%s\033[0m\n", name); // Print directory names in blue]");
    }else{
        printf("%s\n", name);
    }
}


int walk(const char *path, int indent){
    DIR *dir = opendir(path); //open the directory specified by the path
    if(dir == NULL) {
        perror("opendir");
        return -1;
    }

    struct dirent *dp;
    while((dp = readdir(dir)) != NULL) {
        const char *name = dp->d_name;

        if( strcmp(name, ".") == 0 || strcmp(name, "..") == 0 ) {
            continue; // Skip the current and parent directory entries
        }

        if( dp->d_type == DT_DIR ) { //If the entry is a directory
            print_file(name,1 , indent);
            // Recursively call walk on the subdirectory
            size_t len = strlen(path) + strlen(name) + 2;
            char subpath[len];
            snprintf(subpath, len, "%s/%s", path, name);
            walk(subpath, indent + 1);
        } else { //If the entry is a file
            print_file(name, 0, indent);
        }
    }

    closedir(dir);
    return 0;
}

int main(int argc, char **argv)
{

    const char *path = "."; //Default path is current directory
    if(argc > 1) {
        path = argv[1]; //If a path is provided as an argument, use that instead
    }
    int err = walk(path, 0);


    return err;
}