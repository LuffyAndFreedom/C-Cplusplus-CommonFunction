#include <stdio.h>

/*
 * 大小写均敏感
 * __FILE__ 本行语句在源文件的文件名
 * __LINE__ 本条语句在源文件的第几行
 * __func__ 本条语句在源文件的哪个函数中
 */

int main()
{
    FILE *fp = NULL;
    char temp[] = "adfd";

    fp = fopen("./log.txt", "w+");
    fprintf(fp, "This is testing for fprintf...\n");
    fputs("This is testing for fputs...\n", fp);
    
    fprintf(fp, "HTTP" " " "%s, %d.\n", temp, 6);
    printf("HTTP" " " "%s, %d, Line = %d, File = %s, Function = %s.\n", temp, 6, __LINE__, __FILE__, __FUNCTION__);
    fclose(fp);

}
