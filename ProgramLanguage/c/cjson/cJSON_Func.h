#ifndef CJSON_FUNC__h
#define CJSON_FUNC__h

#include "cJSON.h"

#define MAX_LEN_STR 10005
typedef struct _App {
        char* name;
        char* path;
        struct _App *next;
} AppNode;

typedef struct _Pkg {
        char* name;
        struct _App *entries;
        struct _Pkg *next;
} PkgNode;

typedef struct _Menu {
        char *name;
        char *visible;
        struct _Menu *childnode;
        struct _Menu *next;
} MenuNode;

cJSON *root = NULL;
cJSON *item = NULL;

void initJsonFile (char *JsonFilePath, char *PluginName);
cJSON* getRoot();
PkgNode* getPkgListHead();
char* getMode();
void printAllPkgNames();
void deleteAllData();
void printAllAppNameAndPaths();
int containsPkg(char* PkgName);
int containsApp(char* AppName);
AppNode* getEntriesListHead(int index, cJSON* cJson);


#endif
