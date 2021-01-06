//存储路径为 /tmp/demo/main.c
//其生成的可执行文件为 main.exe，位于同一路径下
#include<stdio.h>
int main(int argc,char* argv[])
{
    FILE * fp;
    if((fp = fopen(argv[1],"r")) == NULL){
        printf("file open fail");
    }
    else{
        printf("file open true");
    }
    return 0;
}
