//
//  main.c
//  Fibonacci
//
//  Created by 刘可立 on 2020/2/25.
//  Copyright © 2020 刘可立. All rights reserved.
//

#include <stdio.h>

int fibonacci(int k, int m);
int func(int *a, int n);
const int arrsize = 10;

int main(int argc, const char * argv[]) {
    int m, k, a[arrsize];
    //1.17调试
    printf("input k and m:\n");
    scanf("%d%d", &k, &m);
    int result = fibonacci(k, m);
    if (result != -1 && k > 0) {
        printf("%d\n", result);
    } else {
        printf("error\n");
    }
    //1.19调试
    func(a, 10);
    
    return 0;
}

int fibonacci(int k, int m){ //1.17
    int ret;
    if (m >= 0 && m <= k - 2) {
        ret = 0;
    } else if (m == k - 1 || m == k){
        ret = 1;
    } else if (m > k){
        /*
        ret = 0;
        for (int i = m - k; i <= m - 1; i++){
            ret += fibonacci(k, i);
        }
         */
        ret = 2 * fibonacci(k, m - 1) - fibonacci(k, m - k - 1);
    } else {
        ret = -1;
    }
    return ret;
}
int func(int *a, int n){ //1.19
    int ret = 1; //与scanf返回值类似，为向数组a中写入数据个数
    a[0] = 1;
    for (int i = 1; i <= n - 1; i++){
        if (i > arrsize - 1){
            printf("n > arrsize!\nOnly %d values signed!\n", arrsize);
            break;
        }
        if (a[i - 1] >= (1 << 30) / i){ //int最大为2的31次方-1
            break;
        }
        a[i] = 2 * i * a[i - 1];
        ret++;
    }
    return ret;
}
