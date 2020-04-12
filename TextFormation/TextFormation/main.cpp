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

int StrLength(SString s);
void Format(FILE * out, FILE * in);
void StrCat(SString s1, SString s2);
void nextline(FILE * out);
void Return(FILE * out, int n);
void Space(FILE * out, int n);
void nextpage(FILE * out);
char * StrCpy(char * dst, const char * src);
int StrCmp(const char * s1, const char * s2);
void SignValue();
void logo();
int length = 0, width = 0, pagenum = StartPageNum;

int main(int argc, const char * argv[]) {
    logo();
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
            Space(out, 8);
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

void logo(){
    printf(
    " _____         _    ______                         _   _             \n"
    "|_   _|       | |   |  ___|                       | | (_)            \n"
    "  | | _____  _| |_  | |_ ___  _ __ _ __ ___   __ _| |_ _  ___  _ __  \n"
    "  | |/ _ \\ \\/ / __| |  _/ _ \\| '__| '_ ` _ \\ / _` | __| |/ _ \\| '_ \\ \n"
    "  | |  __/>  <| |_  | || (_) | |  | | | | | | (_| | |_| | (_) | | | |\n"
    "  \\_/\\___/_/\\_\\\\__| \\_| \\___/|_|  |_| |_| |_|\\__,_|\\__|_|\\___/|_| |_|\n"
    "                                                                     \n"
    "                                                                     \n"
    "______         _      _   __ _                                       \n"
    "| ___ \\       | |    | | / /| |                                      \n"
    "| |_/ /_   _  | |    | |/ / | |                                      \n"
    "| ___ \\ | | | | |    |    \\ | |                                      \n"
    "| |_/ / |_| | | |____| |\\  \\| |____                                  \n"
    "\\____/ \\__, | \\_____/\\_| \\_/\\_____/                                  \n"
    "        __/ |                                                        \n"
    "       |___/                                                         \n");
}
