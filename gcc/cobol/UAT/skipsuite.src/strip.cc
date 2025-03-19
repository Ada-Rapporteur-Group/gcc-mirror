#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <vector>

using namespace std;

int
main(int argc, char **argv)
  {
  vector<string>the_file;
  FILE *f = fopen(argv[1], "r");
  char ach[1024];
  while(fgets(ach, sizeof(ach), f))
    {
    the_file.push_back(ach);
    }
  fclose(f);

  int index = 0;
  int left;
  int right;
  while(index < (int)the_file.size() )
    {
    string center = the_file[index++];
    if( center.find("AT_SKIP_IF(false)") == 0 )
      {
      continue;
      }
    if( center.find("AT_SKIP_IF") == 0 )
      {
      left = index-2;
      while(left >= 0)
        {
        if( the_file[left].find("AT_SETUP") == 0 )
          {
          break;
          }
        left -= 1;
        }
      right = index;
      while( right < (int)the_file.size() )
        {
        if( the_file[right].find("AT_CLEANUP") == 0 )
          {
          break;
          }
        right += 1;
        }
      assert(left >= 0);
      assert(right < (int)the_file.size());
      for(int i=left; i<=right; i++)
        {
        printf("%s", the_file[i].c_str());
        }
      printf("\n\n");
      }
    }
  }