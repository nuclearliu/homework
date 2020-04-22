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
    初始化哈希表
    将实现储存的30个姓名插入到哈希表
    输出平均查找长度
    输出Hash表
    while (用户输入 != EOF) {
        获取用户输入并搜索
    }
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

//记录查找长度
int cnt = 0;
//姓名集
char * names[] = {"WangHaoPeng", "DuWei", "GaoPeiLi", "HuYaoZhou", "Xiangjunjie", "XuNuo", "YangTianCheng", "ZhaiYuQi", "ChenQiuHang", "ChenXuanChi", "DuanKangSheng", "GuoXiangMin", "HeChengTian", "HuangJinDiao", "KangTongJia", "LiuKeLi", "YangRuoHai", "LiChunJian", "LiMengHan", "LiZhuoFan", "WangLi", "XiaChen", "XiongQiLong", "YinShiQiu", "YuanXinHe", "YuXiaoYu", "ZhangChaoHui", "ZhangXinYu", "ZhuYiQing", "ZengYangZhu"};
//哈希表抽象数据结构
class HashTable {
public:
    char names[41][15];
    
    HashTable(){ //初始化函数
        将每个串置为空
    }
    
    void insert(char * str){
        i = hash(str2int(str));
        if (第i个串为空){
            将str拷贝到第i个串位置;
        } else {
            while (第i个串不为空) {
                i = collision(i); //冲突处理
            }
            将str拷贝到第i个串位置;
        }
    }
    
    int hash(int k){
        返回 k mod 41
    }
    
    int str2int(char * str){
        将名字奇数位置上的字符相加并返回
    }
    
    int search(char * str){
        i = hash(str2int(str));
        if (第i个位置上与str内容相同 && ++比较次数){
            return i
        } else {
            while (第i个位置上与str内容不相同 && ++比较次数) {
                if (第i个串为空) {
                    return -1;
                }
                collision(i);
            }
        }
        return i;
    }
    
    int collision(int i){
        r = 伪随机序列的下一个数
        i = (i + r + 1) % 41
    }
};
