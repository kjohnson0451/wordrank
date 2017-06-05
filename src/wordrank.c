/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Keith Johnson
 * April 30, 2015
 *
 * For every string S, there are n other permutations of S. If all of those
 * permutations were put in alphabetical order, then S would fall under
 * a certain rank in that order. wordRank.c determines which rank that is.
 *
 * For example, AB would fall under rank 1, BA would fall under rank 2. 
 * 
 * usage: ./wordRank <string>
 *
 * example: ./workRank EXAMPLE
 *
 * To build: make
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <stdio.h>

unsigned short instances[26];
unsigned short numChars = 0;
unsigned long numPermus;

unsigned long factorial(unsigned short n)
{
  if (n == 0)
    return 1;
  else
    return(n * factorial(n-1));
}

unsigned long getRank(char str[], unsigned short pos)
{
  unsigned long foo = 0;
  unsigned short i = 0;

  if( numChars < 1 )
    return 0;
  
  numPermus = factorial(numChars);

  for(i=0;i<26;i++)
    numPermus /= factorial(instances[i]);
  
  i = 0;
          
  while( str[pos] - 'A' != i ) {    
    foo+= (numPermus / numChars) * instances[i];
    i++;
  }
  pos++;
  instances[i]--;
  numChars--;

  return foo + getRank(str, pos);
}

int main(int argc, char* argv[])
{
  unsigned short i;

  if(argc < 2) {
    fprintf(stderr, "ERROR: No string supplied\n");
    return 1;
  }

  for(i=0;i<26;i++)
    instances[i] = 0;
  
  i = 0;

  while(argv[1][i] != '\0') {
    if((argv[1][i] < 'A') || (argv[1][i] > 'Z')) {
      fprintf(stderr, "ERROR: String may only contain upper-case characters.\n");
      return 2;
    }
    instances[argv[1][i] - 'A']++;
    numChars++;
    i++;
  }

  printf("%lu\n", getRank(argv[1], 0) + 1);

  return 0;
}
