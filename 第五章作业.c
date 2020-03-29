//5.8

/*
 k = 2(i - 1) + (j + 1) % 2
 */

//5.11

/*
 (1)GetHead[ GetTail[GetTail[L1]] ]
 (2)GetHead[GetHead[GetTail[L2]]]
 (3)GetHead[GetHead[GetTail[GetTail[GetHead[L3]]]]]
 (4)GetHead[GetHead[GetHead[GetTail[GetTail[L4]]]]]
 (5)GetHead[GetHead[GetTail[GetTail[L5]]]]
 (6)GetHead[GetTail[GetHead[L6]]]
 (7)GetHead[GetHead[GetTail[GetHead[GetTail[L7]]]]]
 */

//5.21

Status MatrixAdd(TSMatrix & C, TSMatrix A, TSMatrix B){
    if (A.mu != B.mu || A.nu != B.nu) {
        return ERROR;
    }
    C.mu = A.mu;
    C.nu = A.nu
    int idx = 1, idx1 = 1, idx2 = 1;
    while (idx1 <= A.tu && idx2 <= B.tu) {
        if (A.data[idx1].i == B.data[idx2].i && A.data[idx1].j == B.data[idx2].j){
            if (A.data[idx1].e + B.data[idx2].e){
                C.data[idx].i = A.data[idx].i;
                C.data[idx].j = A.data[idx].j;
                C.data[idx].e = A.data[idx1].e + B.data[idx2].e;
                idx1++;
                idx2++;
            } else {
                idx1++;
                idx2++;
                continue;
            }
        } else if (A.data[idx1].i < B.data[idx2].i){
            C.data[idx] = A.data[idx1];
            idx1++;
        } else if (A.data[idx1].i > B.data[idx2].i){
            C.data[idx] = B.data[idx2];
            idx2++;
        } else if (A.data[idx1].j < B.data[idx2].j){
            C.data[idx] = A.data[idx1];
            idx1++;
        } else if (A.data[idx1].i > B.data[idx2].i){
            C.data[idx] = B.data[idx2];
            idx2++;
        }
        idx++;
    }
    C.tu = idx - 1;
}

//5.26

Status PrintMatrix(CrossList M){
    OLink * p;
    for (int i = 0; i <= M.mu - 1; i++){
        p = M.rhead + i;
        while (p) {
            printf("(%d, %d, %d)\n", p->i, p->j, p->e);
            p = p->right;
        }
    }
    return OK;
}
