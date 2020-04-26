//10.25

#define SIZE 100
#define MAXINT (1 << 30)
typedef struct{
    int rc;
    int next;
} SLNode;

typedef struct{
    SLNode r[SIZE];
    int length;
} SLinkListType;

void InsertSort(SLinkListType & l){
    l.r[0].next = 1;
    l.r[1].next = 0;
    for (int i = 2; i <= l.length; i++) { //将第i个元素和前i - 1个元素进行比较
        int p = l.r[0].next, q = 0;
        while (l.r[i].rc >= l.r[p].rc) {
            q = p;
            p = l.r[p].next;
        }
        l.r[q].next = i;
        l.r[i].next = p;
    }
}

//10.42

int middle(int * x, int length){
    return func(x, length, x % 2 ? x / 2 + 1 : x / 2) //第三个参数即 ceil(x/2)
}

int func(int * array, int length, int n){
    //功能:返回数组排序后的第n个记录
    //参数:(数组(0号单元不使用), sizeof(x), n)
    int * x;
    memcpy(x, array, length * sizeof(int));//将数组拷贝到x，避免更改原数组
    int pivot = x[1], i = 1, j = n; //借鉴快速排序的思路
    while (i < j) {
        while (x[j] >= pivot && i < j) {
            j--;
        }
        x[i] <-> x[j];
        while (x[i] <= pivot && i < j) {
            i++;
        }
        x[j] <-> x[i];
    }
    //此时pivot在第i位，它的左侧应均小于pivot，右侧均大于pivot。也就是说pivot在正确的序号上。
    if (i == n){ //所求的元素正好是pivot
        return x[i];
    } else if (i > n){ //所求元素小于pivot，在左半侧递归地搜索
        return func(x, i - 1, n);
    } else if (i < n){ //所求元素大于pivot，在右半侧递归地搜索
        return func(x + i + 1, length - i, n - i);
    }
}
