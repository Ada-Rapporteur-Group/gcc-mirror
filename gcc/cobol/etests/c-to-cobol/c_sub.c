#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *
imitationcwd(char *p, size_t len)
    {
    strncpy(p, "/just/like/cwd", len);
    return p;
    }

long
string_to_long(char *p)
    {
    long retval;
    retval = atoll(p);
    printf("The C routine string_to_long got the string \"%s\" from the caller, \n", p );
    printf("and is returning the 64-bit value %ld\n", retval);
    return retval;
    }

char *
long_to_string(long l)
    {
    static char ach[64];
    sprintf(ach, "%ld", l);
    printf("The C code got the long integer %ld from the caller, \n", l );
    printf("and is returning the string \"%s\"\n", ach);
    return ach;
    }

void
Routine_B()
    {
    printf("   I am C routine_b(); I will call COBOL routine_c()\n");
    extern void routine_c();
    routine_c();
    }

void
routine_128(__int128 x)
  {
  while(x)
    {
    int digit = x % 10;
    x /= 10;
    printf("%c", digit + '0');
    }
  printf("\n");
  }