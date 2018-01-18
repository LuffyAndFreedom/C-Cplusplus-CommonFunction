#include <stdio.h>

char *Strcpy(char *pDest, const char* pSrc)
{
    if(pDest == NULL || pSrc == NULL) return NULL;
    char *pOriDest = pDest;
    while((*pDest++ = *pSrc++) != '\0') ;
    pDest = '\0';
    return pOriDest;
}

char *Strncpy(char *pDest, const char *pSrc, size_t len)
{
    if(pDest == NULL || pSrc == NULL) return NULL;
    int nNum = 0;
    char *pOriDest = pDest;
    while(nNum++ < len && (*pDest++ = *pSrc++) != '\0');
    return pOriDest;

}

//memcpy 没有内存重叠没有问题, 有内存重叠的话会出问题
void *Memcpy(void *pDest, void *pSrc, size_t count)
{
    if(pDest == NULL || pSrc == NULL) return NULL;
    void *ret = pDest;
    while(count--)
    {
        *(char *)pDest = *(char *)pSrc;
        pDest = (char *)pDest + 1;
        pSrc = (char *)pSrc + 1;
    }
    return ret;
}

//内存重叠的问题是指，目标内存空间的首地址，包含在源内存空间中,在这两段内存空间有了交集,因而在使用memcpy进行内存复制操作时,这段重叠的内存空间会被破坏.
void *Memmove(void *pDest, void *pSrc, size_t count)
{
    if(pDest == NULL || pSrc == NULL) return NULL;
    void *ret = pDest;
   
    // pDest <= pSrc 目标地址小于或者等于，从低地址拷贝没有问题
    // (char *)pDest >= (char *)pSrc + count, 目标地址大于源地址+拷贝的长度，从低地址拷贝没有问题
    if(pDest <= pSrc || (char *)pDest >= (char *)pSrc + count)
    {
        //没有内存重叠，从低地址开始复制
        while(count--){
            *(char *)pDest = *(char *)pSrc;
            pDest = (char *)pDest + 1;
            pSrc = (char *)pSrc + 1;
        }
    } else {
        //说明目标内存空间的首地址，包含在源内存空间中
        //有内存重叠，从高地址开始复制
        pSrc = (char *)pSrc + count -1;
        pDest = (char *)pDest + count -1;
        while(count--){
            *(char *)pDest = *(char *)pSrc;
            pDest = (char *)pDest - 1;
            pSrc = (char *)pSrc - 1;
        }
    }
    return ret;
}
char *Strstr(const char* str1, const char* str2)
{
    if(str1 == NULL || str2 == NULL) return NULL;
    char *s1 = (char*)str1;
    char *s2 = (char*)str2;

    while(*s1)
    {
        char *p = s1;
        char *q = s2;
        while(*p && *q && (*p++ == *q++));
        if(*q == '\0') return s1;
        s1++;
    }
    return NULL;
}

char *Strcat(char *pDest,const char *pSrc)
{
    if(pSrc == NULL) return pDest;
    char *retDest = pDest;
    while(*pDest) pDest++;
    while(*pSrc && (*pDest++ = *pSrc++));
    *pDest = '\0';
    return retDest;
}

char *Strncat(char *pDest, const char* pSrc, size_t count)
{
    if(pSrc == NULL) return pDest;
    char *retDest = pDest;
    while(*pDest) pDest++;
    int nNum = 0;
    while(*pSrc && (nNum < count) && (*pDest++ = *pSrc++)) nNum++;
    *pDest = '\0';
    return retDest;
}

//返回值为int型， <0 str1小于str2， =0 str1等于str2， >0 str1大于str2
int Strcmp(const char* str1, const char* str2)
{
    if(str1 == NULL && str2 == NULL) return 0;
    if(str1 == NULL && str2 != NULL) return -1;
    if(str2 != NULL && str2 == NULL) return 1;
    while(*str1 && *str2 && (*str1 == *str2)){
        str1++;
        str2++;
    }
    return (*str1 - *str2);
}

int Strncmp(const char* str1, const char* str2, size_t count)
{
    if(str1 == NULL && str2 == NULL) return 0;
    if(str1 == NULL && str2 != NULL) return -1;
    if(str2 != NULL && str2 == NULL) return 1;
    int nNum = 0;
    while(*str1 && *str2 && (nNum < count) && (*str1++ == *str2++)) nNum++;
    //相等了之后还会继续++一次，所以应该取前一次值相减
    return (*(--str1) - *(--str2));
    
}

int Strlen(const char* str)
{
    if(str == NULL) return 0;
    int retNum = 0;
    while(*str++) retNum++;
    return retNum;
}

int main()
{
    char strcpy1[] = "wqerew3434";
    char strcpy2[20] = {0};
    char strcpy3[20] = {0};
    char strcpy4[20] = {0};
    char strcpy5[20] = {0};
    printf("Strcpy = %s.\n", Strcpy(strcpy2, strcpy1));
    printf("Strncpy = %s.\n", Strncpy(strcpy3, strcpy1, 20));
    printf("Memcpy = %s.\n", Memcpy(strcpy4, strcpy1, 5));
    printf("Memmove = %s.\n", Memmove(strcpy5, strcpy1, 6));
    
    char strstr1[]="fdukabi223kjkabf23iuiewstra";
    char strstr2[]="kabf";
    char *p = Strstr(strstr1, strstr2);
    printf("Strstr = %c.\n", *p);
    printf("p = %x.\n", p);

    char strcat1[] = "fsafjekjf3232";
    char strcat2[] = "fsjkfs";
    printf("Strcat= %s.\n", Strcat(strcat1, strcat2));
    printf("Strncat = %s.\n", Strncat(strcat1, strcat2, 2));

    char strcmp1[] = "asdfg12345";
    char strcmp2[] = "asdfg23456";
    printf("Strcmp = %d.\n", Strcmp(strcmp1, strcmp2));
    printf("Strncmp = %d.\n", Strncmp(strcmp1, strcmp2, 5));
    printf("Strncmp = %d.\n", Strncmp(strcmp1, strcmp2, 6));

    char strlen1[] = "1234567";
    printf("Strlen = %d.\n", Strlen(strlen1));
    return 0;
}
