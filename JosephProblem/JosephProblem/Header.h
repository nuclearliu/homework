//
//  Header.h
//  JosephProblem
//
//  Created by 刘可立 on 2020/3/22.
//  Copyright © 2020 刘可立. All rights reserved.
//

#ifndef Header_h
#define Header_h

int m = 1000000;
int n = 100000;

class LinearList {
public:
    int * member;
    int * data;
    int last;
    LinearList(int n): last(n - 1){
        data = (int*)malloc(sizeof(int) * n);
        member = (int*)malloc(sizeof(int) * n);
        for (int i = 0; i <= n - 1; i++){
            data[i] = rand() % m + 1;
        }
        for (int i = 0; i <= n - 1; i++){
            member[i] =  i;
        }
    }
    ~LinearList(){
        free(member);
        free(data);
    }
    int & operator[](int n){
        return data[n];
    }
    void Delete(int n){
        if (n < 0 || n > last){
            return;
        }
        for(int i = n + 1; i <= last; i++){
            member[i - 1] = member[i];
            data[i - 1] = data[i];
        }
        last--;
        return;
    }
};

class LNode{
public:
    int idx;
    int data;
    LNode * prior;
    LNode * next;
    LNode(int n){
        idx = n;
        data = rand() % m + 1;
    }
};
class LinkedList {
public:
    LNode * head;
    LinkedList(int n){
        head = new LNode(0);
        LNode * p = head;
        for (int i = 1; i <= n - 1; i++){
            p->next = new LNode(i);
            p->next->prior = p;
            p = p->next;
        }
        p->next = head;
        head->prior = p;
    }
    void Delete(LNode * p, bool big = false){
        if (p->next == p){
            head = NULL;
            if (!big){
                printf("%8d", p->idx + 1);
//            std::cout << p->idx + 1 << " ";
            }
            delete p;
        } else {
            p->prior->next = p->next;
            p->next->prior = p->prior;
            if (!big){
                printf("%8d", p->idx + 1);
    //            std::cout << p->idx + 1 << " ";
            }
            delete p;
        }
    }
};

#endif /* Header_h */
