#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUDDY_ALLOC_IMPLEMENTATION
#include "buddy_alloc.h"
#undef BUDDY_ALLOC_IMPLEMENTATION

int main (int argc, char * argv[])
{
  size_t arena_size = atoi (argv[1]);
  size_t alloc_size = atoi (argv[2]);

  int i, n;

  /* You need space for the metadata and for the arena */
  void * buddy_metadata = malloc (buddy_sizeof (arena_size));
  char * buddy_arena = (char *)malloc (arena_size);
  struct buddy * buddy = buddy_init (buddy_metadata, buddy_arena, arena_size);

  while (1)
    {
      /* Allocate using the buddy allocator */
      char * data = (char *)buddy_malloc (buddy, alloc_size);
      printf (" data = 0x%llx\n", (long long unsigned int)data);
      if (data == NULL)
        break;
    }

  for (i = 0, n = 0; i < arena_size; i++)
    if (buddy_arena[i])
      n++;
  printf (" n = %d\n", n);


  /* Free using the buddy allocator */
//buddy_free (buddy, data);

  free (buddy_metadata);
  free (buddy_arena);

  return 0;
}
