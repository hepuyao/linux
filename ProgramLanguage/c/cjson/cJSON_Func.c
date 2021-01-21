#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON_Func.h"

PkgNode* head;
MenuNode* mhead;

char *Allname;

void initJsonFile(char *JsonFilePath, char *PluginName) {
	char cv_content[MAX_LEN_STR];
	char *content = (char*)malloc(sizeof(char) * MAX_LEN_STR);
	FILE *fp;

	Allname = PluginName;

	if ((fp = fopen (JsonFilePath, "r")) == NULL) {
		printf("No FilePath Founded\n");
		return;
	}

	while (fgets (cv_content, MAX_LEN_STR, fp)) {
		content = strcat (content, cv_content);
	}
	fclose (fp);

	root = cJSON_Parse (content);
	free(content);

	if (!root) {
		printf ("Error Reading By : \" %s \"\n", cJSON_GetErrorPtr());
		return;
	} else {
		item = cJSON_GetObjectItem (root, PluginName);
	}
}

cJSON* getRoot() {
	return root;
}

char* getpureString(cJSON* cJson) {
	char* cJson_Data = cJSON_Print(cJson);
	int size = strlen(cJson_Data);
	for (int i = 0; i < size - 1; i++) {
		cJson_Data[i] = cJson_Data[i + 1];
		if (cJson_Data[i] == '\"')
			cJson_Data[i] = '\0';
	}
	return cJson_Data;
}

char* getMode() {
	cJSON *temp;
	temp = cJSON_GetObjectItem (item, "mode");
	return getpureString (temp);
}

MenuNode* getMenuListHead() {
	MenuNode *MenuList;
	MenuNode *track;
	cJSON *temp = item;
	int size = cJSON_GetArraySize(temp);
	for (int i = 0; i < size; i++) {
		cJSON *_temp = cJSON_GetArrayItem(temp, i);
		printf("\n%s\n", cJSON_Print(_temp));
		MenuNode *Node = (MenuNode*)malloc(sizeof(MenuNode));
		Node->name = getpureString(cJSON_GetObjectItem(_temp, "name"));
		Node->visible = getpureString(cJSON_GetObjectItem(_temp, "visible"));
		Node->childnode = NULL;
		Node->next = NULL;
		if (i) {
			track->next = Node;
			track = Node;
		} else {
			MenuList = Node;
			track = MenuList;
		}
	}
	return MenuList;
}

AppNode* getEntriesListHead(int index, cJSON *cJson) {
	AppNode *AppList;
	AppNode *track;
	cJSON *temp = cJSON_GetObjectItem (cJson, "entries");
	int size = cJSON_GetArraySize(temp);
	for (int i = 0; i < size; i++) {
		cJSON *_temp = cJSON_GetArrayItem(temp, i);
		AppNode *Node = (AppNode*)malloc(sizeof(AppNode));
		Node->name = getpureString(cJSON_GetObjectItem (_temp, "appname"));
		Node->path = getpureString(cJSON_GetObjectItem (_temp, "path"));
		Node->next = NULL;
		if (i) {
			track->next = Node;
			track = Node;
		}
		else {
			AppList = Node;
			track = AppList;
		}
	}
	return AppList;
}

PkgNode* getPkgListHead() {
	PkgNode *PkgList;
	PkgNode *track;
	char* mode = getMode();
	if (!strncmp(mode, "normal", (strlen(mode) > 6 ? strlen(mode) : 6)))
		return NULL;
	cJSON *temp = cJSON_GetObjectItem (item, mode);
	int size = cJSON_GetArraySize(temp);
	for (int i = 0; i < size; i++) {
		cJSON *_temp = cJSON_GetArrayItem(temp, i);
		PkgNode *Node = (PkgNode*)malloc(sizeof(PkgNode));
		Node->name = getpureString(cJSON_GetObjectItem (_temp, "pkgname"));
		Node->entries = getEntriesListHead(i, _temp);
		Node->next = NULL;
		if (i) {
			track->next = Node;
			track = Node;
		} else {
			PkgList = Node;
			track = PkgList;
		}
	}
	return PkgList;
}

void getJsonInfo() {
	if (strncmp(Allname, "ukcc", 4))
		head = getPkgListHead();
	else 
		mhead = getMenuListHead();
}

int containsPkg(char* PkgName) {
	PkgNode* temp = head;
        while(temp) {
                if (!strncmp(PkgName, temp->name, strlen(temp->name)))
			return 1;
		temp = temp->next;
        }
	return 0;
}

int containsApp(char* AppName) {
	PkgNode* temp = head;
	while(temp) {
		AppNode* _temp = temp->entries;
		while(_temp) {
			char* name = _temp->name;
			if (!strncmp(AppName, name, strlen(name)))
				return 1;
			_temp = _temp->next;
		}
		temp = temp->next;
	}
	return 0;
}

void printAllPkgNames() {
	PkgNode* temp = head;
	while(temp) {
		printf("%s\n", temp->name);
		temp = temp->next;
	}
}

void printAllAppNamesAndPaths() {
	PkgNode* temp = head;
        while(temp) {
                AppNode* _temp = temp->entries;
		printf("Pkg: %s\n", temp->name);
                while(_temp) {
                        printf("Path: %s\n", _temp->path);
			_temp = _temp->next;
                }
                temp = temp->next;
        }
}

void deleteAllData() {
        while(head->next) {
		PkgNode *temp = head;
		head = head->next;
                temp->entries;
                while(temp->entries->next) {
			AppNode* _temp = temp->entries;
			temp->entries = temp->entries->next;
			_temp->next = NULL;
			free(_temp->name);
			free(_temp->path);
                	free(_temp);
		}
		temp->next = NULL;
		free(temp->entries);
		free(temp->name);
          	free(temp);
        }
	free(head);
	cJSON_Delete(root);
}

int main() {
	cJSON *root = (cJSON*)malloc(sizeof(cJSON));
	initJsonFile("/home/kylin/.config/mate-panel-security-config.json", "mate-panel");
	//item = initJsonFile("./ukcc.json", "ukcc");
	printf("get Mode is : %s \n",getMode());
	getJsonInfo();
	if (head == NULL) return 0;
	//printf("\nif contains Pkg\"ddfdasd\" ?\n%d\nif contains App \"speony\" ?\n%d\n\n", containsPkg("ddfdasd"),containsApp("speony"));
	printAllAppNamesAndPaths();
	deleteAllData();
	return 0;
}
