#include <stdio.h>
#include <sys/stat.h>
 
void printPermissions(const char *filename) {
    struct stat st;
    stat(filename, &st);
 
    printf("Permissions for %s: ", filename);
    printf((st.st_mode & S_IRUSR) ? "r" : "-");
    printf((st.st_mode & S_IWUSR) ? "w" : "-");
    printf((st.st_mode & S_IXUSR) ? "x" : "-");
    printf((st.st_mode & S_IRGRP) ? "r" : "-");
    printf((st.st_mode & S_IWGRP) ? "w" : "-");
    printf((st.st_mode & S_IXGRP) ? "x" : "-");
    printf((st.st_mode & S_IROTH) ? "r" : "-");
    printf((st.st_mode & S_IWOTH) ? "w" : "-");
    printf((st.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}
 
int main() {
    const char *filename = "sample.txt";
 
    FILE *fp = fopen(filename, "w");     // create a sample file
    fprintf(fp, "Testing chmod.\n");
    fclose(fp);
 
    printPermissions(filename);
 
    chmod(filename, S_IRUSR | S_IWUSR | S_IXUSR);   // set permission to rwx------ (700)
    printf("\nPermissions changed using chmod() to rwx for owner only.\n");
 
    printPermissions(filename);
    return 0;
}