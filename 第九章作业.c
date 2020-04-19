//9.31

int x = - 1 << 30; //先让x取一个很小的负数
int order = true;

int isOrdered(Bintree t){ //根据：二叉排序树的中序序列递增
    DFS(t);
    return order;
}

void DFS(Bintree t){
    if (!t || !order) {
        return;
    }
    DFS(t->left);
    if (t->data >= x) { //x应为遍历中上一次被访问的值
        x = t->data;
    } else {
        order = false;
        return;
    }
    DFS(t->right);
}

//9.33

void NoLessThanX(Bintree t, int x){
    if (!t){
        return;
    }
    NoLessThanX(t->right, x);
    if (t->data >= x){ //当根的关键字不小于x时输出根并对左子树调用递归
        printf("%d\t", t->data);
        NoLessThanX(t->left, x);
    }
}
