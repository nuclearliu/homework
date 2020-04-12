//
//  main.cpp
//  TextFormation
//
//  Created by 刘可立 on 2020/4/7.
//  Copyright © 2020 刘可立. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include "Header.h"


void Format(FILE * out, FILE * in);
int StrLength(SString s){
    遍历串，直到读到串尾的'\0'，记录循环次数
}
void StrCat(SString s1, SString s2){
    确保s1有足够的剩余空间
    将s2的第一个字符拷贝到s1的第StrLength(s1)个字符
    不断拷贝，直到s2的最后一个字符
}
char * StrCpy(char * dst, const char * src){
    从src的第一个字符开始，只要非0就拷贝到dst的相应位置
}
int StrCmp(const char * s1, const char * s2){
    从第一个字符开始，逐个比较s1和s2对应位置上的字符
    若相等则比较下一个
    若不相等则输出两字符的差
    若s1和s2完全相等，则返回0
}

void nextline(FILE * out);
void Return(FILE * out, int n);
void Space(FILE * out, int n);
void nextpage(FILE * out);

void SignValue();
int length = 0, width = 0, pagenum = StartPageNum;

int main(int argc, const char * argv[]) {
    printf("Input the file:\n");
    scanf("%s", dir);
    while (!(fp1 = fopen((char *)dir, "r"))) {
        printf("No such file:%s\nTry again:\n", dir);
        scanf("%s", dir);
    }
    fflush(stdin);
    SignValue();
    fp2 = fopen("output.txt", "w");
    Format(fp2, fp1);
    return 0;
}

int StrLength(SString s){
    int i;
    for (i = 0; *s != '\0'; s++, i++);
    return i;
}

void StrCat(SString s1, SString s2){
    int m = StrLength(s1);
    int i;
    for (i = 0; s2[i] != '\0'; i++){
        s1[i + m] = s2[i];
    }
    s1[i + m] = '\0';
}

char * StrCpy(char * dst, const char * src){
    char * ret = (char *)dst;
    while(*src){
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
    return ret;
}

int StrCmp(const char * s1, const char * s2){
    while (*s1 == *s2 && *s1 != '\0'){
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

void nextpage(FILE * out){
    if (FootingLen >= 3) {
        fprintf(out, "\n");
        Space(out, PageWed / 2);
        fprintf(out, "%2d\n", pagenum);
        Return(out, HeadingLen + FootingLen - 2);
    } else {
        Return(out, HeadingLen + FootingLen);
    }
    length = 0;
    width = 0;
    pagenum++;
    Space(out, LeftMargin);
}

void nextpage(FILE * out){
    如果页底空白不少于三行，则输出页码
    输出若干个'\n'
    将新页的总行数和新行的总字符记为0
    页码+1
}

void nextline(FILE * out){
    if (length + FootingLen == PageLen){
        fprintf(out, "\n");
        nextpage(out);
    } else {
        length++;
        width = 0;
        fprintf(out, "\n");
        Space(out, LeftMargin);
    }
}

void nextline(FILE * out){
    如果换行后需要翻页：
        换行
        调用翻页函数
    否则：
        输出一个'\n'
        输出左空白
        将新行的总字符记为0
}

void Format(FILE * out, FILE * in){
    SString str;
    Return(out, HeadingLen);
    Space(out, LeftMargin);
    int scan = 1;
    while (!feof(in)) {
        if (scan){
            fscanf(in, "%s", str);
        }
        scan = 1;
        if (StrCmp((char *)str,"@") == 0) {
            nextline(out);
            continue;
        }
        if (width + StrLength(str) <= PageWed){
            width += StrLength(str) + 1;
            fprintf(out, "%s ", str);
        } else {
            nextline(out);
            scan = 0;
            continue;
        }
        
    }
    nextpage(out);
    printf("Done!\nOutput file at output.txt\n");
}

void Format(FILE * out, FILE * in){
    输出第一页的空行
    while (文档未读完) {
        fscanf(一个字);
        如果字是"@"，则换行并且空8个字符
        如果输出后会超过页宽限制，则换行
        输出到本行，记录本行总字符数
    }
}

void Return(FILE * out, int n){
    for (int i = 1; i <= n; i++) {
        fprintf(out, "\n");
    }
}


void Space(FILE * out, int n){
    for (int i = 1; i <= n; i++) {
        fprintf(out, " ");
    }
}

void SignValue(){
    int finish = 0;
    char c;
    while(!finish){
        printf("当前排版参数：\n"
               "页长：%d\t页宽：%d\t左空白%d\t头长%d\t脚长%d\t起始页号%d\n", PageLen, PageWed, LeftMargin, HeadingLen, FootingLen, StartPageNum);
        printf("是否修改排版参数(y/n)?:");
        scanf("%c", &c);
        if (c == 'y'){
            printf("Adjust the Page Length to :");
            scanf("%d", &PageLen);
            printf("Adjust the Page Wedth to :");
            scanf("%d", &PageWed);
            printf("Adjust the Left Margin to :");
            scanf("%d", &LeftMargin);
            printf("Adjust the Heading Length to :");
            scanf("%d", &HeadingLen);
            printf("Adjust the Footing Length to :");
            scanf("%d", &FootingLen);
            printf("Adjust the Starting Page Number to :");
            scanf("%d", &StartPageNum);
        } else if (c == 'n'){
            finish = 1;
        } else {
            printf("Error!\n");
            scanf("%c", &c);
        }
        fflush(stdin);
    }
}




ADT String {
    数据对象：D = {ai | ai ∈ CharacterSet, i = 1, 2, ..., n, n>=0}
    数据关系：R = {< ai-1 , ai > | ai-1 , ai ∈ D, i = 2, ..., n}
    基本操作：
    StrAssign(&T, chars)
        构造一个其值等于chars的字符串
    Strcpy(&L, s)
        复制字符串L到s
    StrCmp(L)
        按字典序比较两个字符串
    StrLen(s, t)
        返回s的字符串⻓度
    StrCat(&s1, s2)
        把s2拷贝到s1的后面，接成一个⻓的字符串
    DestroyString(&S)
        销毁字符串S
}

