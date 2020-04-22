//
//  main.cpp
//  HashTable
//
//  Created by 刘可立 on 2020/4/18.
//  Copyright © 2020 刘可立. All rights reserved.
//

#include <iostream>
#include <string.h>
#include "Header.h"

void logo();

int main(int argc, const char * argv[]) {
    logo();
    HashTable table;
    for (int i = 0; i <= 29; i++) {
        table.insert(names[i]);
    }
//    for (int i = 0; i <= 40; i++) {
//        printf("%d : %s\n", i, table.names[i]);
//    }
    for (int i = 0; i <= 29; i++) {
        table.search(names[i]);
    }
    printf("ASL is %lf\n", (double)cnt / 30);
    cnt = 0;
    char str[15];
    printf("Input a name to search (input q to quit) :\n");
    scanf("%s", str);
    while (strcmp(str, "q")) {
        int p = table.search(str);
        if (p != -1) {
            printf("Found at %d\n", p);
            printf("查找 : %d次\n", cnt);
        } else {
            printf("Not found!\n");
        }
        cnt = 0;
        printf("Input a name to search (input q to quit) :\n");
        scanf("%s", str);
    }
    return 0;
}

void logo(){
    printf(
    " _   _           _   _____     _     _      \n"
    "| | | |         | | |_   _|   | |   | |     \n"
    "| |_| | __ _ ___| |__ | | __ _| |__ | | ___ \n"
    "|  _  |/ _` / __| '_ \\| |/ _` | '_ \\| |/ _ \\\n"
    "| | | | (_| \\__ \\ | | | | (_| | |_) | |  __/\n"
    "\\_| |_/\\__,_|___/_| |_\\_/\\__,_|_.__/|_|\\___|\n"
    "                                            \n"
    "______         _      _   __ _              \n"
    "| ___ \\       | |    | | / /| |             \n"
    "| |_/ /_   _  | |    | |/ / | |             \n"
    "| ___ \\ | | | | |    |    \\ | |             \n"
    "| |_/ / |_| | | |____| |\\  \\| |____         \n"
    "\\____/ \\__, | \\_____/\\_| \\_/\\_____/         \n"
    "        __/ |                               \n"
    "       |___/                                \n");
}

