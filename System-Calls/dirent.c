#include <stdio.h>
#include <dirent.h>
 
int main() {
    struct dirent *entry;
    DIR *dp = opendir(".");   // open current directory
 
    if (dp == NULL) {
        printf("Could not open directory\n");
        return 1;
    }
 
    printf("Contents of current directory:\n");
    while ((entry = readdir(dp)) != NULL)
        printf("%s\n", entry->d_name);
 
    closedir(dp);
    return 0;
}