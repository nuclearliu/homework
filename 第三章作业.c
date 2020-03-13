//3.3

/*
 the output is "stack"
 */

//3.7

/*
 step   OPTR栈       OPND栈       输入字符
 1      #                       A-B*C/D+E^F#
 2      #           A            -B*C/D+E^F#
 3      # -         A             B*C/D+E^F#
 4      # -         A B            *C/D+E^F#
 5      # - *       A B             C/D+E^F#
 6      # - *       A B C            /D+E^F#
 7      # - /       A B*C             D+E^F#
 8      # - /       A B*C D            +E^F#
 9      # +         A-B*C/D             E^F#
 10     # +         A-B*C/D E            ^F#
 11     # + ^       A-B*C/D E             F#
 12     # + ^       A-B*C/D E F            #
 13     #           A-B*C/D+E^F            #
 */

//3.10

void test(int & sum){
    sum = 0;
    int x;
    scanf("%d", &x);
    while (x){
        sum += x;
        scanf("%d", &x);
    }
    printf("%d", sum);
}

void test(int & sum){
    //使用堆栈
    Stack S;
    InitStack(S);
    int x;
    scanf("%d", &x);
    while (x){
        Push(S, x);
        scanf("%d", &x);
    }
    sum = 0;
    while (!StackEmpty(S)){
        int t;
        Pop(S, t);
        sum += t;
    }
    printf("%d", sum);
}

//3.12

/*
 the output is "char"
 */

//3.19

bool match(string str){
    Stack S;
    InitStack(S);
    bool ismatch = true;
    char * p = str, t;
    while (*p != '\0') {
        if (*p == '(' || *p == '[' || *p == '{'){
            Push(S, *p);
        }
        if (*p == ')' || *p == ']' || *p == '}'){
            if (StackEmpty(S)) {
                ismatch = false;
                break;
            }
            Pop(S, t);
            if (*p - t != 1 && *p - t != 2) { //ASCII码中 '('、')'、'['、']'、'{'、'}'分别为40,41,91,93,123,125
                ismatch = false;
                break;
            }
        }
        p++;
    }
    if (!StackEmpty(S)){
        ismatch = false;
    }
    return ismatch;
}

//3.21

void convert(string out, const string str){
    Stack S;
    InitStack(S);
    char * p = str, t;
    while (*p != '\0'){
        if (!isoperator(*p)){
            //处理运算数
            sprintf(out, "%c", *p);
        } else {
            //处理运算符
            if (StackEmpty(S)){
                Push(S, *p);
            } else {
                GetTop(S, t);
                while (!cmp(*p, t) && !StackEmpty(S)) { //若优先级小于等于栈顶运算符时，将栈顶运算符弹出并输出
                    Pop(S, t);
                    sprintf(out, "%c", t);
                    GetTop(S, t);
                }
                Push(S, *p);
            }
        }
        p++;
    }
    while (!StackEmpty(S)){ //把堆栈中存留的运算符一并输出
        Pop(S, t);
        sprintf(out, "%c", t);
    }
}

int isoperator(char c){
    int ret = 0;
    if (c == '+' || c == '-' || c == '*' || c == '/'){
        ret = 1;
    }
    return ret;
}

int cmp(char operator1, char operator1){ //输出1表示operator1比operator2优先级高
    int ret = 0;
    if ((operator1 == '*' || operator1 == '/') && (operator2 == '+' || operator2 == '-')){
        ret = 1;
    }
    return ret;
}

//3.28

typedef struct QNode{
    int data;
    struct QNode * next;
}QNode, * QueuePtr;

typedef struct {
    QueuePtr rear;
}LinkQueue;

void InitQueue(LinkQueue & Q){ //初始化
    Q.rear = (QueuePtr)malloc(sizeof(QNode));
    rear->next = NULL;
}

void EnQueue(LinkQueue & Q, int x){ //入队
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    p->data = x;
    p->next = Q.rear->next;
    Q.rear->next = p;
    Q.rear = p;
}

void DeQueue(LinkQueue & Q, int & x){ // 出队
    if (Q.rear->next != Q.rear){ //判断循环链表非空
        QueuePtr p = Q.rear->next->next;
        x = p->data;
        Q.rear->next->next = p->next;
        free(p);
    }
}

//3.32

void fibo(Queue Q){
    for (int i = 0; i <= k - 1; i++){
        EnQueue(Q, 0);
    }
    EnQueue(Q, 1);
    int out = 0, in = 1;
    while (in <= max){
        in = in * 2 - out; //f(n) = 2f(n-1) - f(n-k-1)
        if (in <= max){
            DeQueue(Q, out);
            EnQueue(in);
        }
    }
    //此时in为第n+1项
}
