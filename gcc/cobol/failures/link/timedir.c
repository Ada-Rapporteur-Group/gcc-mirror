#include <dirent.h>
#include <stdio.h>
#include <time.h>

void showdir( struct tm *local, struct dirent *ent );

int
main(int argc, char *argv[])
{
  time_t now = time(NULL);

  struct tm *local = localtime(&now);

  DIR *dir = opendir(".");
  struct dirent *ent;
  int i=0;
  while( (ent = readdir(dir)) != NULL ) {
    // printf("%4d\t", i++);
    printf( "%s:%d: tm @ %p, ent @ %p\n", __FILE__, __LINE__, local, ent );
    fflush(stdout);
    showdir( local, ent );
  }
 
  return 0;
}
