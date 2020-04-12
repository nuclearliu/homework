//7.22

int visited[MAX_VERTEX_NUM] = {0};
int connected = 0; //若第i个顶点有到第j个顶点的路径，置为1

int isConnected(ALGraph G, int i, int j){
    DFS(ALGraph, i, j);
    return connected;
}

void DFS(ALGraph G, i, j){
    if (connected) { //若已判断为连通则直接return
        return;
    }
    ArcNode * p;
    visited[i] = 1;
    for (p = G.vertices[i].firstarc; p; p = p->nextarc) {
        if (p->adjvex == j){ //如果遍历序列中出现第j个顶点，则判断为找到
            connected = 1;
            return;
        }
        if (!visited[p->adjvex]) {
            DFS(ALGraph, p->adjvex, j); //递归调用
        }
    }
}
