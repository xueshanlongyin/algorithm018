//时间复杂度O(n/k),空间复杂度(n+k),https://leetcode-cn.com/problems/design-hashmap/submissions/
typedef struct _Node {
    struct _Node* next;
    int key;
    int val;
} Node; //拉链法+单链表

int ListAdd(Node* n, int key, int val) {
    for (; n->next != NULL; n = n->next) { //如果存在,则更新val
        if (n->next->key == key) {
            n->next->val = val;
            return 0;
        }
    }
    Node* m = malloc(sizeof(Node));
    m->next = NULL;
    m->key = key;
    m->val = val;
    n->next = m;
    return 1;
}

int ListRemove(Node* n, int key) {
    for (; n->next != NULL; n = n->next) {
        if (n->next->key == key) {
            Node* t = n->next->next;
            free(n->next);
            n->next = t;
            return 1;
        }
    }
    return 0;
}

int ListFind(Node* n, int key, int* val) {
    for (; n->next != NULL; n = n->next) {
        if (n->next->key == key) {
            *val = n->next->val;
            return 1;
        }
    }
    return 0;
}

typedef struct {
    int amount;
    int total;
    Node* buckets;
} Map; //每个数组元素是桶

void MapRehash(Map* s, int total) { //当桶已占满时,再哈希减少碰撞
    Node* tmp = malloc(total * sizeof(Node));
    memset(tmp, 0, total * sizeof(Node));
    for (int i = 0; i < s->total; i++) {
        Node* l = s->buckets + i;//桶头节点
        Node* ptr = l->next;//桶头链表第一个元素
        while (ptr != NULL) {//链表是否为空,非空则稀释到新桶数组
            Node* nxt = ptr->next;//保留桶头链表第二个元素
            Node* dst = tmp + ptr->key % total;//再哈希桶头第一个元素确定新桶位置
            Node* remain = dst->next;//保留新桶位置的链表
            dst->next = ptr;//将链表头插入新桶位置
            ptr->next = remain;//将链表头与新桶位置的链表想连
            ptr = nxt;//将桶头链表第二个元素作为下一个再哈希的元素
        }
    }
    free(s->buckets);//释放原有桶数组
    s->total = total;
    s->buckets = tmp;//新桶数组
}

void MapPut(Map* s, int key, int val) {
    if (s->amount >= s->total * 2) {//桶满2倍扩容
        MapRehash(s, s->total * 2); 
    }
    if (ListAdd(s->buckets + key % s->total, key, val)) {
        s->amount++;
    }
}

void MapRemove(Map* s, int key) {
    if (ListRemove(s->buckets + key % s->total, key)) {
        s->amount--;
    }
}

int MapGet(Map* s, int key, int* val) {
    return ListFind(s->buckets + key % s->total, key, val);
}

Map* MapInit() {
    Map* m = malloc(sizeof(Map));
    m->amount = 0;
    m->total = 2069;
    m->buckets = malloc(m->total * sizeof(Node));
    memset(m->buckets, 0, m->total * sizeof(Node));
    return m;
}

void MapDestroy(Map* s) {
    for (int i = 0; i < s->total; i++) {
        Node* l = s->buckets + i;
        Node* ptr = l->next;
        while (ptr != NULL) {
            Node* tmp = ptr->next;
            free(ptr);
            ptr = tmp;
        }
    }
    free(s->buckets);
    free(s);
}

typedef struct {
    Map m;
} MyHashMap;

MyHashMap* myHashMapCreate() {
    return (MyHashMap*)MapInit();
}

void myHashMapPut(MyHashMap* obj, int key, int value) {
    MapPut((Map*)obj, key, value);
}

int myHashMapGet(MyHashMap* obj, int key) {
    int val;
    int r = MapGet((Map*)obj, key, &val);
    return r == 0 ? -1 : val;
}

void myHashMapRemove(MyHashMap* obj, int key) {
    MapRemove((Map*)obj, key);
}

void myHashMapFree(MyHashMap* obj) {
    MapDestroy((Map*)obj);
}
