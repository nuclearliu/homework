//4.5

/*
 the output is :
    t=THESE ARE BOOKSv=YXYu=XWXWXW
 */

//4.8

/*
    i       1   2   3   4   5   6   7   8   9   10
 next[i]    0   1   1   2   1   1   2   3   4   1
 
 KMP:
    s = 'ADBADABBAABADABBADADA'
  pat = 'ADABBADADA'
 
 i = 3  j = 3    ADBADABBAABADABBADADA 失配 j = next[j] = 1
                 ADABBADADA
 
 i = 3  j = 1    ADBADABBAABADABBADADA
                   ADABBADADA
 ...
 
 i = 10 j = 7    ADBADABBAABADABBADADA 失配 j = next[j] = 2
                    ADABBADADA
 
 i = 10 j = 2    ADBADABBAABADABBADADA
                         ADABBADADA
 
 i = 22 j = 11   ADBADABBAABADABBADADA 匹配，退出循环
                            ADABBADADA
 
 */

//4.10

 typedef char * StringType;

void reverse(StringType & str){ //修改原串
    for (int i = str[0]; i > str[0] / 2; i--) {
        swap(str[i], str[str[0] - i + 1])；
    }
}

void reverse(StringType & out, const StringType str){ //输出到out
    out[0] = str[0];
    for (int i = str[0]; i >= 1; i--) {
        out[str[0] - i + 1] = str[i]；
    }
}


//4.20

Status delete(SString & s, const SString t){
    int * next = malloc(sizeof(int) * t[0]);
    getNext(t, next);
    while (i <= s[0]){ //循环至i遍历了整个串
        while (i <= s[0] || j <= t[0]){ //KMP搜索
            if (j == 0 || s[i] == t[j]){
                i++;
                j++;
            } else {
                j = next[j];
            }
        }
        if (j > t[0]){ //每当搜索到t，进行删除
            s[0] -= t[0];
            for (int idx = i; idx <= s[0]; idx++) {
                s[idx - t[0]] = s[idx];
            }
            i -= t[0];
            j = 1;
        }
    }
}

void getNext(const char * str, int * next){
    int i = 1, j = 0;
    while (i < str[0]) {
        if (j == 0 || str[i] == str[j]){
            i++;
            j++;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}
