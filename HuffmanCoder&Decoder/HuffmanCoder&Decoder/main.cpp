//
//  main.cpp
//  HuffmanCoder&Decoder
//
//  Created by 刘可立 on 2020/4/18.
//  Copyright © 2020 刘可立. All rights reserved.
//

#include <iostream>
#include "Header.h"

void logo();
void help();

int main(int argc, const char * argv[]) {
    logo();
    HuffmanTree tree;
//    tree.BuildTree();
//    for (int i = 1; i <= 5; i++) {
//        printf("%c : %s\n", tree.chars[i], tree.codes[i]);
//    }
//    tree.save();
//    HuffmanTree anothertree;
//    anothertree.read();
//    anothertree.display();
//    anothertree.encode();
//    anothertree.decode();
//    anothertree.showtree();
//    anothertree.print();
    char c;
    
    printf("Instruction : ");
    scanf("%c", &c);
    fflush(stdin);
    while (c != 'q') {
        switch (c) {
            case 'I':
            case 'i':
                tree.BuildTree();
                printf("Instruction : ");
                fflush(stdin);
                scanf("%c", &c);
                break;
            case 'E':
            case 'e':
                tree.encode();
                printf("Instruction : ");
                fflush(stdin);
                scanf("%c", &c);
                break;
            case 'D':
            case 'd':
                tree.decode();
                printf("Instruction : ");
                fflush(stdin);
                scanf("%c", &c);
                break;
            case 'P':
            case 'p':
                tree.print();
                printf("Instruction : ");
                fflush(stdin);
                scanf("%c", &c);
                break;
            case 'T':
            case 't':
                tree.showtree();
                printf("Instruction : ");
                fflush(stdin);
                scanf("%c", &c);
                break;
            case 'A':
            case 'a':
                tree.display();
                printf("Instruction : ");
                fflush(stdin);
                scanf("%c", &c);
                break;
            case 'S':
            case 's':
                tree.save();
                printf("Instruction : ");
                fflush(stdin);
                scanf("%c", &c);
                break;
            case 'R':
            case 'r':
                tree.read();
                printf("Instruction : ");
                fflush(stdin);
                scanf("%c", &c);
                break;
            case 'H':
            case 'h':
                help();
                printf("Instruction : ");
                fflush(stdin);
                scanf("%c", &c);
                break;
            default:
                printf("Invalid instruction! Input h to view help.\n");
                printf("Instruction : ");
                fflush(stdin);
                scanf("%c", &c);
                break;
        }
    }
    return 0;
}

void logo(){
    printf(
    " _   _        __  __                     _____             \n"
    "| | | |      / _|/ _|                   |_   _|            \n"
    "| |_| |_   _| |_| |_ _ __ ___   __ _ _ __ | |_ __ ___  ___ \n"
    "|  _  | | | |  _|  _| '_ ` _ \\ / _` | '_ \\| | '__/ _ \\/ _ \\\n"
    "| | | | |_| | | | | | | | | | | (_| | | | | | | |  __/  __/\n"
    "\\_| |_/\\__,_|_| |_| |_| |_| |_|\\__,_|_| |_\\_/_|  \\___|\\___|\n"
    "                                                           \n"
    "______         _      _   __ _                             \n"
    "| ___ \\       | |    | | / /| |                            \n"
    "| |_/ /_   _  | |    | |/ / | |                            \n"
    "| ___ \\ | | | | |    |    \\ | |                            \n"
    "| |_/ / |_| | | |____| |\\  \\| |____                        \n"
    "\\____/ \\__, | \\_____/\\_| \\_/\\_____/                        \n"
    "        __/ |                                              \n"
    "       |___/                                               \n");
}

void help(){
    printf("***************************************************\n"
           "*  i : initialization a tree                      *\n"
           "*  s : save a huffman tree                        *\n"
           "*  r : read a huffman tree                        *\n"
           "*  e : encode a file                              *\n"
           "*  d : decode a file                              *\n"
           "*  p : print huffman code                         *\n"
           "*  a : show huffman tree                          *\n"
           "*  t : show huffman tree in tree form             *\n"
           "*  q : terminate the process                      *\n"
           "***************************************************\n");
}
