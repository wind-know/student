#include "studentsystem.h"

void Initialization(mNode* mhead) {
    mNode* pre = (mNode*)malloc(sizeof(mNode));
    pre->next = NULL;

    strcpy(pre->man.name, "admanager");
    strcpy(pre->man.mclass, "man");
    strcpy(pre->man.account, "G20040125");
    strcpy(pre->man.password, "12345678");
    if (mhead->next == NULL) {
        mhead->next = pre;
        printf("不存在管理员账号，已添加\n");
    }
    else {
        mNode* cur = mhead;
        int exist = 0; // 是否已经存在管理员账号的标志位
        while (cur != NULL) {
            if (strcmp(pre->man.account, cur->man.account) == 0) {
                // 如果已经存在管理员账号，则修改原有节点的账号信息
                strcpy(cur->man.name, "admanager");
                strcpy(cur->man.mclass, "man");
                strcpy(cur->man.password, "12345678");
                exist = 1;
            }
            cur = cur->next;
        }


        if (!exist) {
            // 如果不存在管理员账号，则将新节点添加到链表末尾
            pre->next=mhead->next;
            mhead->next = pre;

            printf("不存在至高管理员账号，已添加\n");

        }
    }

    mfileNode(mhead);
    // 清屏操作，可以根据需要自行添加
    free(pre); // 释放预先分配的内存空间
}

int main() {
    //system("chcp 65001");fubern
	Node* head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	mNode* mhead = (mNode*)malloc(sizeof(mNode));
	mhead->next = NULL;
    nNode* nhead = (nNode*)malloc(sizeof(nNode));
    nhead->next = NULL;

    mloadStudent(mhead);
	Initialization(mhead);	
    //Manager(head, nhead, mhead, '0');
	PASS(head, nhead, mhead);
    free(head);
    free(nhead);
    free(mhead);
	return 0;
}
