//
//  Header.h
//  HashTable
//
//  Created by 刘可立 on 2020/4/18.
//  Copyright © 2020 刘可立. All rights reserved.
//

#ifndef Header_h
#define Header_h

int cnt = 0;

char * names[] = {"WangHaoPeng", "DuWei", "GaoPeiLi", "HuYaoZhou", "Xiangjunjie", "XuNuo", "YangTianCheng", "ZhaiYuQi", "ChenQiuHang", "ChenXuanChi", "DuanKangSheng", "GuoXiangMin", "HeChengTian", "HuangJinDiao", "KangTongJia", "LiuKeLi", "YangRuoHai", "LiChunJian", "LiMengHan", "LiZhuoFan", "WangLi", "XiaChen", "XiongQiLong", "YinShiQiu", "YuanXinHe", "YuXiaoYu", "ZhangChaoHui", "ZhangXinYu", "ZhuYiQing", "ZengYangZhu"};

class HashTable {
public:
    char names[41][15];
    HashTable(){
        for (int i = 0; i <= 40; i++) {
            names[i][0] = '\0';
        }
    }
    
    void insert(char * str){
        int i = hash(str2int(str));
        if (names[i][0] == '\0'){
            strcpy(names[i], str);
        } else {
            while (names[i][0] != '\0') {
                srand(i);
                i = (i + rand() % 6 + 1) % 41;
            }
            strcpy(names[i], str);
        }
    }
    
    int hash(int k){
        return k % 41;
    }
    
    int str2int(char * str){
        int n = 0;
    //    n = str[0] * str[strlen(str) - 1] + str[3];
        for (int i = 0; i <= strlen(str) - 1; i += 2) {
            n += str[i];
        }
        return n;
    }
    
    int search(char * str){
        int i = hash(str2int(str));
        if (strcmp(str, names[i]) == 0 && ++cnt){
            ;
        } else {
            while (++cnt && strcmp(str, names[i]) != 0) {
                if (names[i][0] == '\0') {
                    return -1;
                }
                srand(i);
                i = (i + rand() % 6 + 1) % 41;
            }
        }
        return i;
    }
};

#endif /* Header_h */
