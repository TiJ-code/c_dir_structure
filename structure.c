#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>

typedef int32_t int32;

#define MAX 256
#define MAX_MODULES 100
#define END_KEYWORD "#END"

#define TAG_DIRS "dirs"
#define TAG_DIR "dir"

static inline void mkdir_if_missing(const char *path) { mkdir(path, 0755); }

void replace(char *dst, const char *src, const char *find, const char *repl) {
  const char *pos = strstr(src, find);

  if (!pos) {
    strcpy(dst, src);
    return;
  }

  size_t left = pos - src;

  strncpy(dst, src, left);

  dst[left] = 0;

  strcat(dst, repl);

  strcat(dst, pos + strlen(find));
}

void resolve_path(char *out, const char *pattern, const char *root,
                  const char *module) {
  char temp[1024];

  replace(temp, pattern, "!ROOT", root);

  replace(out, temp, "!MODULES", module);
}

void create_dirs(xmlNode *dirs, const char *root, char modules[][MAX],
                 int moduleCount) {
  xmlChar *pathAttr = xmlGetProp(dirs, (xmlChar *)"name");

  if (!pathAttr)
    return;

  const char *pattern = (char *)pathAttr;

  for (int32 i = 0; i < moduleCount; i++) {
    char base[1024];

    resolve_path(base, pattern, root, modules[i]);

    mkdir_if_missing(root);
    mkdir_if_missing(base);

    for (xmlNode *child = dirs->children; child; child = child->next) {
      if (child->type != XML_ELEMENT_NODE)
        continue;

      if (strcmp((char *)child->name, TAG_DIR))
        continue;

      xmlChar *name = xmlGetProp(child, (xmlChar *)"name");

      if (!name)
        continue;

      char final[2048];

      snprintf(final, sizeof(final), "%s/%s", base, (char *)name);

      mkdir_if_missing(final);

      xmlFree(name);
    }
  }

  xmlFree(pathAttr);
}

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
      create_dirs(n, root, modules, count);
    }
  }

  xmlFreeDoc(doc);

  puts("Done.");

  return 0;
}
