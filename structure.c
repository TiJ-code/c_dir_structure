#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>

typedef int32_t int32;

#define MAX 256
#define MAX_MODULES 100
#define END_KEYWORD "#END"

#define TAG_DIRS "dirs"

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

  xmlDoc *doc = xmlReadFile("template.xml", NULL, 0);

  if (!doc) {
    puts("Could not load XML");
    return 1;
  }

  xmlNode *rootNode = xmlDocGetRootElement(doc);

  for (xmlNode *n = rootNode->children; n; n = n->next) {
    if (n->type != XML_ELEMENT_NODE)
      continue;

    if (!strcmp((char *)n->name, TAG_DIRS)) {
      // create dirs here
    }
  }

  xmlFreeDoc(doc);

  puts("Done.");

  return 0;
}
