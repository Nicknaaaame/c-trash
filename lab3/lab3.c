#include <stdio.h>
#include <stdlib.h>
#include <grp.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>

void printFileProperties(struct stat stats, char* path);

int main(int argc, char **argv){
	struct stat stats;
	char* path;

    printf("Enter source file path: ");
    scanf("%s", path);
    if (stat(path, &stats) == 0){
		printFileProperties(stats, path);
	}
    else {
        printf("Unable to get file properties.\n");
        printf("Please check whether '%s' file exists.\n", path);
    }
	return 0;
}


void printFileProperties(struct stat stats, char* path) {
	struct passwd *pwd;
	struct group *gr;

	if(S_ISDIR(stats.st_mode)) 
		printf("d");
	else
		if(S_ISREG(stats.st_mode)) 
			printf("-");
		else
			printf("?");
	printf("\n");
	
	if(stats.st_mode & S_IRUSR) printf("r"); else printf("-");
	if(stats.st_mode & S_IWUSR) printf("w"); else printf("-");
	if(stats.st_mode & S_IWUSR) printf("x"); else printf("-");
	printf("\n");
	if(stats.st_mode & S_IRGRP) printf("r"); else printf("-");
	if(stats.st_mode & S_IWGRP) printf("w"); else printf("-");
	if(stats.st_mode & S_IWGRP) printf("x"); else printf("-");
	printf("\n");
	if(stats.st_mode & S_IROTH) printf("r"); else printf("-");
	if(stats.st_mode & S_IWOTH) printf("w"); else printf("-");
	if(stats.st_mode & S_IWOTH) printf("x"); else printf("-");
	printf("\n");

	if(pwd = getpwuid(stats.st_uid)){
		printf("%s\n", pwd->pw_name);
	}

	if(gr = getgrgid(stats.st_gid)){
		printf("%s\n", gr->gr_name);
	} 

	printf("%d\n", stats.st_size);

	// File modification time
    struct tm dt = *(gmtime(&stats.st_mtime));
    printf("%d-%d-%d %d:%d:%d\n", dt.tm_mday, dt.tm_mon, 
								dt.tm_year + 1900, dt.tm_hour, 
								dt.tm_min, dt.tm_sec);


	printf("%s\n", basename(path));
}
