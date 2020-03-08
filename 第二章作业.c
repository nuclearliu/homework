//2.9
/*
(1)将链表第一个结点移至表尾
(2)BB:使结点q的前一个结点的next指向s  AA:将原链表拆成两个单向循环链表，使从pa开始到pb的前一个结点形成一个链表，其余结点形成另一个链表
*/

//2.10

Status DeleteK(SqList & a, int i, int k){
	//原程序循环了k次，每次进行一次整体移动。且移动次数、元素序号有误（count、j取值不对）
	if (i < 1 || k < 0 || i + k - 1> a.length)
		return INFEASIBLE;
	for (int cnt = i + k - 1; cnt <= a.length - 1; cnt++){
		a.elem[cnt - k] = a.elem[cnt];
	}
	return OK;

}

//2.12

bool cmp(const SqList & a, const SqList & b){
	int idx = 0;
	int l = min(a.length, b.length);
	while (idx <= length - 1 && a.elem[cnt] == b.elem[cnt]){
		//将idx定位至A'首元素的下标
		idx++;
	}
	bool ret;
	if (idx <= length - 1)
		ret = (a.elem[cnt] >= b.elem[cnt]);
	else {
		//A'或B‘为空
		ret = (a.length >= b.length);
	}
	return ret;
}

//2.20

Status deleteDuplicated(Linkedlist l){
	//时间复杂度O(n)
	LNode * p, *q，*temp;
	p = q = l->next; //	p、q均指向第一个结点
	while (p){
		q = q->next;
		while (q && q->data == p->data){ //将q移至与p不相同的第一个结点
			temp = q;
			q = q->next;
			free(temp);
		}
		p->next = q;
		p = q;
	}
	return OK;
}

//2.22

Status reverse(Linkedlist l){
	LNode * p = NULL;
	LNode * q = l->next;
	while (q){
		LNode * temp = q->next; //临时记录q的下一个结点
		q->next = p;
		p = q;
		q = temp;
	}
	l->next = p; //使头结点指向原链表的尾结点
	return OK;
}

//2.34

Status traversal(const XorLinkedList l){
	XorPointer key = NULL, p = l.left, temp;
	while (p){
		printf("%d\n", p.data);
		temp = p;
		p = XorP(key, p->LRPtr);
		key = temp;
	}
	return OK;
}

//2.35

Status insert(XorLinkedList l, int i, int data){
	XorPointer new = (XorPointer)malloc(sizeof(XorNode));
	new->data = data;
	XorPointer key = NULL, p = l.left, temp;
	int cnt = 1;
	while (p && cnt <= i - 1){
		cnt++;
		printf("%d\n", p.data);
		temp = p;
		p = XorP(key, p->LRPtr);
		key = temp;
	}
	if (!p){
		return ERROR; //无第i个结点
	}
	//此时p指向第i个结点，key指向第i - 1个结点
	new->LRPtr = XorP(key, p);
	key->LRPtr = XorP(XorP(key->LRPtr, p), new);
	p->LRPtr = XorP(XorP(p->LRPtr, key), new);
	return OK;
}

//2.38

Status locate(Linkedlist l, int x){
	LNode * p = l->next, * q = l->next;
	while (p && q->data != x){
		p = p->next;
	}
	if (!p)
		return ERROR;
	p->freq++;
	while (q && q->freq > p->freq){
		q = q->next;
	}
	if (q != p){
		//调整次序
		p->prior->next = p->next;
		p->prior = q->prior;
		q->prior->next = p;
		p->next = q;
		q->prior = p;
	}
	return OK;
}




























