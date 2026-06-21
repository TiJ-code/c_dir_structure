#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int32_t int32;

#define MAX 256
#define MAX_MODULES 100
#define END_KEYWORD "#END"

int32 main(void) {
  char root[MAX];

  char modules[MAX_MODULES][MAX];

  int32 count = 0;

  printf("Root dir:\n> ");
  scanf("%255s", root);

  printf("\nModules (exit: %s):\n", END_KEYWORD);

  while (count < MAX_MODULES) {
    printf("> ");

    scanf("%255s", modules[count]);

    if (!strcmp(modules[count], END_KEYWORD)) {
      break;
    }

    count++;
  }

  printf("\nCreating structure...\n");

  puts("Done.");

  return 0;
}
