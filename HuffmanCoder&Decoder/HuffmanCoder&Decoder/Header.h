//
//  Header.h
//  HuffmanCoder&Decoder
//
//  Created by 刘可立 on 2020/4/18.
//  Copyright © 2020 刘可立. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <string.h>

typedef char ** HuffmanTreeCode;

class HuffmanTreeNode {
public:
    int weight;
    int parent, left, right;
    
    HuffmanTreeNode(){
        weight = parent = left = right = 0;
    }
};

class HuffmanTree {
public:
    int n;
    HuffmanTreeNode * nodes;
    char * chars;
    HuffmanTreeCode codes;
    
//    HuffmanTree(int num){
//        nodes = new HuffmanTreeNode[num];
//    }
    
    HuffmanTree(){
        n = 0;
    }
    
    ~HuffmanTree(){
        delete [] nodes;
        delete [] chars;
        for (int i = 1; i <= n; i++) {
            delete codes[i];
        }
    }
    
    void BuildTree(){
        printf("Input the number of nodes:\n");
        scanf("%d", &n);
        nodes = new HuffmanTreeNode[2 * n]; //0号单元未用
        chars = new char[n + 1];
        codes = new char * [n + 1];
        chars[0] = 'l';
        for (int i = 1; i <= n; i++) {
            fflush(stdin);
            printf("input char No.%d:\n", i);
            scanf("%c", chars + i);
            printf("input weight for char No.%d:\n", i);
            scanf("%d", &nodes[i].weight);
        }
        for (int i = n + 1; i <= 2 * n - 1; i++) {
            int min1 = 1 << 30, min2 = 1 << 30, idx1 = 0, idx2 = 0;
            for (int j = 1; j <= i - 1; j++) {
                if (nodes[j].parent){
                    continue;
                }
                if (nodes[j].weight < min2) {
                    min2 = nodes[j].weight;
                    idx2 = j;
                }
                if (min2 < min1) {
                    int temp = min2;
                    min2 = min1;
                    min1 = temp;
                    temp = idx1;
                    idx1 = idx2;
                    idx2 = temp;
                }
            }
            nodes[idx1].parent = i;
            nodes[idx2].parent = i;
            nodes[i].left = idx1;
            nodes[i].right = idx2;
            nodes[i].weight = nodes[idx1].weight + nodes[idx2].weight;
        }
        
        char * code = new char[n];
        code[n - 1] = '\0';
        for (int i = 1; i <= n; i++) {
            int start = n - 1;
            for (int cnt = i,p = nodes[cnt].parent; p; cnt = p, p = nodes[p].parent) {
                if (nodes[p].left == cnt) {
                    code[--start] = '0';
                } else {
                    code[--start] = '1';
                }
            }
            codes[i] = new char[n - start];
            strcpy(codes[i], &code[start]);
        }
    }
    
    void display(){
        printf("%d characters in total:\n", n);
        for (int i = 1; i <= n; i++){
            printf("%c : %s\n", chars[i], codes[i]);
        }
        printf("HuffmanTree nodes:\n");
        printf("\tweight\t\tparent\t\tleft\t\tright\n");
        for (int i = 1; i <= 2 * n - 1; i++) {
            printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i, nodes[i].weight, nodes[i].parent, nodes[i].left, nodes[i].right);
        }
    }
    
    void save(){
        printf("Where do you want to save to?\n");
        char direction[50];
        scanf("%s", direction);
        FILE * fp = fopen(direction, "w");
        while (!fp) {
            printf("Input the right direction and file name!\n");
            scanf("%s", direction);
            fp = fopen(direction, "w");
        }
        fprintf(fp, "%d,", n);
        for (int i = 1; i <= n; i++){
            fprintf(fp, "%c,%s,", chars[i], codes[i]);
        }
        for (int i = 1; i <= 2 * n - 1; i++) {
            fprintf(fp, "%d,%d,%d,%d,", nodes[i].weight, nodes[i].parent, nodes[i].left, nodes[i].right);
        }
        fclose(fp);
    }
    
    void read(){
        printf("From where do you want to read?\n");
        char direction[50];
        scanf("%s", direction);
        FILE * fp = fopen(direction, "r");
        if (!fp || feof(fp)){
            return;
        }
        char str[10];
        fscanf(fp, "%[^,],", str);
        n = atoi(str);
        nodes = new HuffmanTreeNode[2 * n]; //0号单元未用
        chars = new char[n + 1];
        codes = new char * [n + 1];
        for (int i = 1; i <= n; i++){
            fscanf(fp, "%[^,],", str);
            chars[i] = str[0];
            fscanf(fp, "%[^,],", str);
            codes[i] = new char[sizeof(str) + 1];
            strcpy(codes[i], str);
        }
        for (int i = 1; i <= 2 * n - 1; i++) {
            fscanf(fp, "%[^,],", str);
            nodes[i].weight = atoi(str);
            fscanf(fp, "%[^,],", str);
            nodes[i].parent = atoi(str);
            fscanf(fp, "%[^,],", str);
            nodes[i].left = atoi(str);
            fscanf(fp, "%[^,],", str);
            nodes[i].right = atoi(str);
        }
        fclose(fp);
    }
    
    void encode(){
        if (n == 0) {
            printf("Tree is not built!\n");
            return;
        }
        printf("Which file do you want to encode?\n");
        char direction[50];
        scanf("%s", direction);
        FILE * fp = fopen(direction, "r");
        char c;
        fscanf(fp, "%c", &c);
        if (!fp || feof(fp)){
            printf("Can't open or empty file!\n");
            return;
        }
        FILE * fp1 = fopen("EncodedFile.txt", "w");
        while (!feof(fp)) {
            chars[0] = c; //设置哨兵
            int i;
            for (i = n; i >= 0; i--) {
                if (chars[i] == c) {
                    break;
                }
            }
            if (i) {
                fprintf(fp1, "%s", codes[i]);
            } else {
                char ch = tolower(c);
                chars[0] = ch;
                for (i = n; i >= 0; i--) {
                    if (chars[i] == ch) {
                        break;
                    }
                }
                if (i) {
                    fprintf(fp1, "%s", codes[i]);
                } else {
                    fprintf(fp1, "%c", ch);
                }
            }
            fscanf(fp, "%c", &c);
        }
        fclose(fp);
        fclose(fp1);
    }
    
    void decode(){
        if (n == 0) {
            printf("Tree is not built!\n");
            return;
        }
        printf("Which file do you want to decode?\n");
        char direction[50];
        scanf("%s", direction);
        FILE * fp = fopen(direction, "r");
        char c;
        fscanf(fp, "%c", &c);
        if (!fp || feof(fp)){
            printf("Can't open or empty file!\n");
            return;
        }
        FILE * fp1 = fopen("DecodedFile.txt", "w");
        int p = 2 * n - 1;
        while (!feof(fp)) {
            if (c != '0' && c != '1') {
                fprintf(fp1, "%c", c);
                fscanf(fp, "%c", &c);
                continue;
            }
            if (p > n) {
                if (c == '0') {
                    p = nodes[p].left;
                } else if (c == '1'){
                    p = nodes[p].right;
                }
            }
            if (p <= n){
                fprintf(fp1, "%c", chars[p]);
                p = 2 * n - 1;
            }
            fscanf(fp, "%c", &c);
        }
        fclose(fp);
        fclose(fp1);
    }
    
    void showtree(){
        if (!n) {
            return;
        }
        printf("The tree is:\n");
        FILE * fp = fopen("TreePrint.txt", "w");
        treeform(2 * n - 1, 1, fp);
        fclose(fp);
    }
    
    void treeform(int i, int layer, FILE * fp){
        if (i > n) {
            tab(layer - 1, fp);
            printf("%d\n", i);
            fprintf(fp, "%d\n", i);
            treeform(nodes[i].left, layer + 1, fp);
            treeform(nodes[i].right, layer + 1 ,fp);
        } else {
            tab(layer - 1, fp);
            printf("%c\n", chars[i]);
            fprintf(fp, "%c\n", chars[i]);
        }
    }
    
    void tab(int n, FILE * fp){
        for (int i = 1; i <= n; i++) {
            printf("\t");
            fprintf(fp, "\t");
        }
    }
    
    void print(){
        printf("Input the encoded file:\n");
        char direction[50];
        scanf("%s", direction);
        FILE * fp = fopen(direction, "r");
        FILE * fp1 = fopen("CodePrin.txt", "w");
        int i = 0;
        char c;
        fscanf(fp, "%c", &c);
        if (feof(fp)){
            printf("Empty file %s!", direction);
            return;
        }
        while (!feof(fp)) {
            if (c == '\n' || c == '\r') {
                fscanf(fp, "%c", &c);
                continue;
            }
            printf("%c", c);
            fprintf(fp1, "%c", c);
            i++;
            if (i == 50) {
                printf("\n");
                fprintf(fp1, "\n");
                i = 0;
            }
            fscanf(fp, "%c", &c);
        }
        printf("\nAlso see CodePrin.txt\n");
        fclose(fp);
        fclose(fp1);
    }
};

#endif /* Header_h */
