//
//  main.cpp
//  HuffmanCoder&Decoder
//
//  Created by 刘可立 on 2020/4/18.
//  Copyright © 2020 刘可立. All rights reserved.
//

#include <iostream>
#include "Header.h"

int main(int argc, const char * argv[]) {
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
            default:
                printf("Instruction : ");
                fflush(stdin);
                scanf("%c", &c);
                break;
        }
    }
    return 0;
}

ADT HuffmanTree {
    数据对象 D ：D是具有相同特性数据元素的集合
    数据关系：R
    基本操作：
    Init(&t)
        读入各结点信息
        构造一个哈夫曼树并对其初始化
    DestroyList(&t)
        哈夫曼树t已存在
        销毁哈夫曼树t，释放分配的空间
    Empty(t)
        若t为空树，则返回TRUE，否则返回FALSE
    LeftChild(t, e)
        e是t中某节点
        返回e的左孩子，若e无左孩子，则返回空
    RightChild(t, e)
        e是t中某节点
        返回e的右孩子，若e无右孩子，则返回空
    Showtree(t)
        输出huffman树的各个节点信息
    Save(t)
        将构造好的huffman树存入文件中
    Read(t)
        从文件中读入huffman树
}

void BuildTree(){
    读入节点个数
    分配存储空间
    读入n个字符及其权值
    for (int i = n + 1; i <= 2 * n - 1; i++) {
        在前i - 1个结点中选择两个权值最小的树作为左右子树构成新的二叉树
        新二叉树的权值等于左右子树权值之和
    }
    for (int i = 1; i <= n; i++) {
        从叶子到根逆向求每个字符编码
    }
}

void display(){
    输出n个字符以及对应编码
    输出树的n个结点以及各结点的权值、父结点、左右子节点序号
}

void save(){
    读入文件路径
    对文件输出n个字符以及对应编码
    对文件输出树的2n-1个结点以及各结点的权值、父结点、左右子节点序号
}

void read(){
    读入文件路径
    从文件读入n个字符以及对应编码
    从文件读入树的2n-1个结点以及各结点的权值、父结点、左右子节点序号
}

void encode(){
    检查是否已建成树
    读入输入文件路径
    if (空文件 || 打不开){
        return;
    }
    while (未读到文件尾) {
        读入一个字符
        查找是否有其对应huffman编码
            若无，对文件原样输出
            若有，对文件输出其编码
    }
    fclose(fp);
}

void decode(){
    检查是否已建成树
    读入输入文件路径
    if (空文件 || 打不开){
        return;
    }
    while (未读到文件尾) {
        读入一个字符
        if (该字符不是0或1) {
            对文件原样输出
            continue;
        }
        从树根开始根据字符的值找左/右子节点
        if (找到了叶子结点){
            对文件输出相应字符
        }
    }
    fclose(fp);
}

void showtree(){ //以凹入表形式打印Huffman树
    调用先序遍历
    输出子节点时多输出一个/t
}

void print(){ //印代码文件
    读入文件路径
    if (空文件 || 打不开){
        return;
    }
    while (未读到文件尾) {
        读入一个字符
        输出该字符到终端和输出文件
        记录本行字符数
        if (字符数 == 50) {
            换行
            字符数 = 1
        }
    }
    fclose(fp);
}
