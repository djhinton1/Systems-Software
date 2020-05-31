/*
Part A - Mystery Caches
*/

#include <stdlib.h>
#include <stdio.h>

#include "support/mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real" memory
 * addresses. You can use any convenient integer value as a memory address,
 * you should not be able to cause a segmentation fault by providing a memory
 * address out of your programs address space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  int count = 0;
  flush_cache();
  access_cache(count);
  while(access_cache(count)){
    count++;
  }
  return count;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int block_size) {
  /* YOUR CODE GOES HERE */
  int count = 0;
  int i;
  flush_cache();
  access_cache(0);
  while(access_cache(0)){
    for(i = 0; i <= count; i++){
      access_cache(i);
    }
    count += block_size;
  }
  return count - block_size;
}
/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int cache_size) {
  /* YOUR CODE GOES HERE */
  int memAddress = 1;
  int count = 0;
  int i;
  flush_cache();
  access_cache(0);
  while(access_cache(0)){
    for(i = 0; i <= count; i++){
      memAddress += cache_size;
      access_cache(memAddress);

    }
  //  if(!access_cache(0))
    //  return count;
    count++;
  }
  return count;
}

int main(void) {
  int size;
  int assoc;
  int block_size;

  cache_init(0, 0);

  block_size = get_block_size();
  size = get_cache_size(block_size);
  assoc = get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
