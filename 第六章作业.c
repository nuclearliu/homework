//6.8

/*
 设树的高度为n，则有：
 n0 = k^(n - 1)
 n0 + n1 = (k^n - 1)/(k - 1)
 消去n，得：
 n0 = (k - 1)n1 + 1
 */

//6.26

/*
 概率:      0.07    0.19    0.02    0.06    0.32    0.03    0.21    0.10
 等长编码:   000     001     010     011     100     101     110     111        WPL = 3
 哈夫曼编码: 0010     10    00000    0001     01     00001    11     0011       WPL = 2.61
 使用哈夫曼编码的信息传输效率更高。
 */

//6.49

int isComplete(BinTree t){
    //层序遍历来判断是否为完全二叉树
    int complete = 1;
    int k = 0; //k = 1表示之后的遍历过程再不能出现子结点存在的情况
    BinTree p;
    InitQueue(Q);
    if (t){
        EnQueue(Q, t);
    }
    while (!QueueEmpty(Q)) {
        DeQueue(Q, p);
        if (!p->left && p->right){
            complete = 0;
            break;
        }
        if (k && (p->left || p->right)){
            complete = 0;
            break;
        }
        if (!p->right) {
            k = 1;
        }
        if (p->left){
            EnQueue(Q, p->left);
        }
        if (p->right){
            EnQueue(Q, p->right);
        }
    }
    return complete;
}

//6.65

BinTree BuildTree(int * a1, int * a2, int length){ //a1为前序序列，a2为中序序列
    if (length == 0){
        return NULL;
    }
    BinTree p = new(Node); //生成根结点
    p->data = a1[0];
    int i;
    for (i = 0; i <= length - 1; i++) { //确定根在中序序列中的位置
        if (a2[i] == a1[0]){
            break;
        }
    }
    //递归调用，生成左右子树
    p->left = BuildTree(a1 + 1, a2, i);
    p->right = BuildTree(a1 + i + 1, a2 + i + 1, length - i - 1);
}

//6.43

void swap(BinTree t){
    if (!t){
        return;
    }
    BinTree p = t->left;
    t->left = t->right;
    t->right = p;
    swap(t->left);
    swap(t->right);
}

//6.45

BinTree Delete(BinTree t, int x){
    if (!t){
        return t;
    }
    if (t->data == x){
        remove(t);
        return NULL;
    } else {
        t->left = Delete(t->left);
        t->right = Delete(t->right);
        return t;
    }
}

void remove(BinTree t){ //删除以t为根的子树并释放空间
    if (!t){
        return;
    }
    remove(t->left);
    remove(t->right);
    free(t);
}

//6.16

/*
 Info   A   B   C   D   E   F   G   H   I   J   K   L   M   N
 Ltag   0   0   0   1   0   1   0   1   0   0   1   1   1   1
 Lchild 2   4   6   2   7   3   10  14  12  13  13  9   10  11
 Rtag   0   0   1   1   0   0   0   1   1   1   0   0   1   1
 Rchild 3   5   6   5   8   9   11  3   12  13  14  0   11  8
 */

//6.44

int DepthOfX(BinTree t, int x){
    BinTree p;
    InitQueue(Q);
    if (!t){
        return 0;
    }
    EnQueue(Q, t);
    //层序遍历二叉树以找到元素值为x的结点
    while (!QueueEmpty(Q)) {
        DeQueue(Q, p);
        if (p->data == x){
            clear(Q);
            break;
        }
        if (p->left){
            EnQueue(Q, p->left);
        }
        if (p->right){
            EnQueue(Q, p->right);
        }
    }
    return Depth(p);
}

int Depth(BinTree t){
    if (!t){
        return 0;
    }
    if (!t->left && !t->right){
        return 1;
    }
    return Depth(t->left) > Depth(t.right) ? Depth(t->left) + 1 : Depth(t->right) + 1;
}

//6.47

void LevelOrderTraversal(BinTree t){ //层序遍历二叉树
    BinTree p;
    InitQueue(Q);
    if (t){
        EnQueue(Q, t);
    }
    while (!QueueEmpty(Q)) {
        DeQueue(Q, p);
        visit(p);
        if (p->left){
            EnQueue(Q, p->left);
        }
        if (p->right){
            EnQueue(Q, p->right);
        }
    }
}
