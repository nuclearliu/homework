//
//  main.cpp
//  JosephProblem
//
//  Created by 刘可立 on 2020/3/22.
//  Copyright © 2020 刘可立. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Header.h"
using namespace std;

void logo();
void userguide();
void help();

int main(int argc, const char * argv[]) {
    logo();
    srand((unsigned)time(NULL));
    double duration;
    clock_t start = 0, end;
    int code, type = 1;
    if (argc == 4){
        userguide();
        m = atoi(argv[1]);
        n = atoi(argv[2]);
        type = atoi(argv[3]);
        if (m == 0 || n == 0){
            printf("Wrong input. Run with -h to see help.\n");
            exit(1);
        }
    } else if (argc == 1 || argc == 0){
        userguide();
        printf("Input m:");
        scanf("%d", &m);
        printf("Input n:");
        scanf("%d", &n);
        printf("Input type:");
        scanf("%d", &type);
    } else if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'h' && argv[1][2] == '\0'){
        help();
        return 0;
    } else {
        printf("Wrong input. Run with -h to see help.\n");
        exit(1);
    }
    bool big = false;
    if (n > 100) {
        big = true;
    }
    FILE *fp = fopen("sequence.data", "w");
    if (type == 0){
        LinearList ring(n);
        fprintf(fp, "The codes are:");
        for (int i = 0; i <= n - 1; i++) {
            fprintf(fp, "%8d", ring[i]);
        }
        fprintf(fp, "\nThe sequence is:");
        if (!big){
            printf("The codes are:");
            for (int i = 0; i <= n - 1; i++) {
                printf("%8d", ring[i]);
            }
            printf("\nThe sequence is:");
        }
    //  ring[0]=3;ring[1]=1;ring[2]=7;ring[3]=2;ring[4]=4;ring[5]=8;ring[6]=4;
        int i = 0;
        code = m % n;
        start = clock();
        do {
            i = (i + code + ring.last) % (ring.last + 1);
            fprintf(fp, "%8d", ring.member[i] + 1);
            if (!big){
                printf("%8d", ring.member[i] + 1);
//                cout << ring.member[i] + 1 << " ";
            }
            if (ring.last)
                code = ring[i] % ring.last;
            ring.Delete(i);
        } while (ring.last > -1);
    } else if (type == 1){
        LinkedList ring(n);
        LNode * p = ring.head, * temp;
        fprintf(fp, "The codes are:");
        fprintf(fp, "%8d", p->data);
        p = p->next;
        for ( ; p != ring.head; p = p->next){
            fprintf(fp, "%8d", p->data);
        }
        fprintf(fp, "\nThe sequence is:");
        if (!big){
            printf("The codes are:");
            printf("%8d", p->data);
            p = p->next;
            for ( ; p != ring.head; p = p->next){
                printf("%8d", p->data);
            }
            printf("\nThe sequence is:");
        }
        start = clock();
        code = m % n;
        while (ring.head) {
            for (int j = 1; j <= code - 1; j++){
                p = p->next;
            }
            if (n > 1)
                code = p->data % (n - 1);
            temp = p;
            p = p->next;
            fprintf(fp, "%8d", temp->idx + 1);
            ring.Delete(temp, big);
            n--;
        }
    } else {
        printf("Wrong input!\n");
        exit(1);
    }
    end = clock();
    if (big){
        printf("Done! The sequence is in sequence.data");
    }
    duration = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nduration: %.2fs", duration);
    puts("");
    return 0;
}

void logo(){
    printf(
    " _____       _               ___                      _                ______          _     _                \n"
    "/  ___|     | |             |_  |                    | |               | ___ \\        | |   | |               \n"
    "\\ `--.  ___ | |_   _____      | | ___  ___  ___ _ __ | |__  _   _ ___  | |_/ / __ ___ | |__ | | ___ _ __ ___  \n"
    " `--. \\/ _ \\| \\ \\ / / _ \\     | |/ _ \\/ __|/ _ \\ '_ \\| '_ \\| | | / __| |  __/ '__/ _ \\| '_ \\| |/ _ \\ '_ ` _ \\ \n"
    "/\\__/ / (_) | |\\ V /  __/ /\\__/ / (_) \\__ \\  __/ |_) | | | | |_| \\__ \\ | |  | | | (_) | |_) | |  __/ | | | | |\n"
    "\\____/ \\___/|_| \\_/ \\___| \\____/ \\___/|___/\\___| .__/|_| |_|\\__,_|___/ \\_|  |_|  \\___/|_.__/|_|\\___|_| |_| |_|\n"
    "                                               | |                                                  \n"
    "                                               |_|                                                  \n"
    "______         _      _   __ _                                                                      \n"
    "| ___ \\       | |    | | / /| |                                                                     \n"
    "| |_/ /_   _  | |    | |/ / | |                                                                     \n"
    "| ___ \\ | | | | |    |    \\ | |                                                                     \n"
    "| |_/ / |_| | | |____| |\\  \\| |____                                                                 \n"
    "\\____/ \\__, | \\_____/\\_| \\_/\\_____/                                                                 \n"
    "        __/ |                                                                                       \n"
    "       |___/                                                                                        \n");
}

void userguide(){
    printf("****************************************************************************************************\n"
           "*                 m 作为报数上限, n 为人数, type 为0或1分别对应顺序存储和链式存储                  *\n"
           "****************************************************************************************************\n");
}

void help(){
    printf("****************************************************************************************************\n"
           "*                 通过 ./a.out m n type 来运行, 或直接运行./a.out 之后手动输入m, n, type           *\n"
           "*                 m 作为报数上限, n 为人数, type 为0或1分别对应顺序存储和链式存储                  *\n"
           "****************************************************************************************************\n");
}
