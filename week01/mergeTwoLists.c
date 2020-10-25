typedef struct ListNode ListNode_t;
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2){
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;

    ListNode_t *p1;
    ListNode_t *p2;
    ListNode_t dummyhead;
    ListNode_t *p3;
    p3 = &dummyhead;
    p1 = l1;
    p2 = l2;
    while (p1 != NULL && p2 != NULL)
    {
        if (p1->val > p2->val)
        {
            p3->next = p2;
            p2 = p2->next;
        } else {
            p3->next = p1;
            p1 = p1->next;
        }
        p3 = p3->next;
    }
    if (p1 == NULL) p3->next = p2;
    if (p2 == NULL) p3->next = p1;
    return dummyhead.next;
}