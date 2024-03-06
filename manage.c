#include "studentsystem.h"

//将链表存入文件（管理员）
void mfileNode(mNode* head) {
	FILE* fp = fopen("./manNode.txt", "w");
	if (fp == NULL) {
		printf("未找到文件\n");
		return;
	}
	mNode* move = head->next;
	while (move != NULL) {
		if (fwrite(&move->man, sizeof(Man), 1, fp) != 1) {
			printf("写入失败\n");
			return;
		}
		move = move->next;
	}
	Sleep(1000);
	printf("写入成功\n");
	fclose(fp);
}

//从文件读取(管理员)
void mloadStudent(mNode* head) {
	//打开文件
	FILE* fp = fopen("./manNode.txt", "r");
	if (fp == NULL) {
		printf("未找到文件,跳过读取\n");
		return;
	}

	//创建一个结点
	mNode* new = (mNode*)malloc(sizeof(mNode));
	new->next = NULL;
	mNode* move = head;
	while (fread(&new->man, sizeof(Man), 1, fp) == 1) {
		move->next = new;
		move = new;

		new = (mNode*)malloc(sizeof(mNode));
		new->next = NULL;
	}
	free(new);
	//最后多定义一个new，要将它释放掉
	//关闭文件
	fclose(fp);

	//printf("读取成功\n");

}


void mMenu() {
	printf("---Student Information Management System---\n");
	printf("--\t         Manager model\t\t --\n");
	printf("--\t  0.退出 \t\t         --\n");
	printf("--\t  1.查看代办选项\t         --\n");
	printf("--\t  2.进入教师端\t\t\t --\n");
	printf("--\t  3.增加账号密码 \t\t --\n");
	printf("--\t  4.删除账号密码 \t\t --\n");
	printf("--\t  5.修改账号密码\t\t --\n");
	printf("--\t  6.查找账号密码\t\t --\n");
	printf("--\t  7.录入所有账号密码\t         --\n");
	printf("--\t  8.输出所有账号密码\t         --\n");
	printf("--\t  9.手动重新录入学生信息         --\n");
	printf("--\t  10.返回上一层 \t         --\n");
	printf("-------------------------------------------\n");
}

void Manager( Node* head, nNode* nhead,mNode* mhead,char*account ) {
	while (1) {

		system("cls");

		loadStudent(head);
		mloadStudent(mhead);
		nloadStudent(nhead);
		mMenu();
		int c;
		while (scanf("%d", &c) != 1)
		{
			scanf("%*[^\n]%*c");
			printf("输入非法，请重新输入\n");
			system("pause");
			system("cls");
			loadStudent(head);
			mloadStudent(mhead);
			nloadStudent(nhead);
			mMenu();
		}
		scanf("%*[^\n]%*c");

		switch (c) {
		case 1://查看代办选项/注册/修改/找回/申诉/更新成绩库
			printf("正在进入代办页面\n");
			Sleep(1000);
			Viewagency(head, mhead, nhead);
			break;
		case 2://进入教师端
			printf("正在进入教师端\n");
			Sleep(1000);
			Teachers(head, nhead, mhead, account, "man", "admanager");
			break;
		case 3://增加账号密码
			ainputAccount(mhead, head);
			break;
		case 4://删除账号密码
			adeleteAccount(mhead, head);
			break;
		case 5://修改账号密码
			areviseAccount(mhead, head);
			break;
		case 6://查找账号密码
			afindAccount(mhead, head);
			break;
		case 7://录入所有账号密码
			mloadStudent(mhead);
			loadStudent(head);
			system("pause");
			break;
		case 8://输出所有账号密码
			sprintfStdent(head);
			mprintfStdent(mhead);
			break;
		case 9://手动重新录入学生信息
			reviseStudent(head);
			break;
		case 10://返回上一层
			return;
			break;
		case 0://退出
			system("cls");
			printf("bye~~\n");
			system("pause");
			exit(0);
			break;
		default:
			printf("无此选项，重新选择吧\n");
			system("pause");
			break;
		}
	}
}

//查看代办选项/注册/修改/找回/申诉/更新成绩库
//进入教师端

//增加账号密码
//删除账号密码
//修改账号密码
//增加
void ainputAccount(mNode* mhead, Node* head) {
	printf("增加学生账号请输入1，增加老师或者管理员账号请输入2\n");
	int c;
	while (scanf("%d", &c) != 1)
	{
		scanf("%*[^\n]%*c");
		printf("输入非法，请重新输入\n");
	}
	scanf("%*[^\n]%*c");

	switch (c) {
	case 1:
		sinputAccount(head);
		break;
	case 2:
		minputAccount(mhead);
		break;
	default:
		printf("无此服务，将返回菜单\n");
		break;
	}
}
void minputAccount(mNode* mhead) {
	mNode* pre = (mNode*)malloc(sizeof(mNode));
	pre->next = NULL;
	//暂存
	char a = getchar();
	char c = '\0';
	while (c != 'T' && c != 'G'){
		printf("选择该账号是老师还是管理员（T为老师，G为管理员）\n");

		scanf("%c", &c);
		scanf("%*[^\n]%*c");

		if (c == 'T') {
			printf("请输入账号所在班级\n");
			scanf("%63s", pre->man.mclass);
			scanf("%*[^\n]%*c");
		}
		else if (c == 'G') {
			char* m = "man";
			strcpy(pre->man.mclass , m);
		}
	} 
	strcpy(pre->man.question, "你玩原神嘛");
	strcpy(pre->man.answer, "万元神万的");

	
	pre->man.account[0] = c;

	printf("请输入姓名：\n");
	scanf("%19s", pre->man.name);
	scanf("%*[^\n]%*c");

	printf("请输入账号(不包含首字母)：\n");
	scanf("%9s", &(pre->man.account[1]));
	scanf("%*[^\n]%*c");

	printf("请输入密码：\n");
	scanf("%10s", pre->man.password);
	scanf("%*[^\n]%*c");


	mNode* cur = mhead;
	while (cur->next != NULL) {
		if (!strcmp(pre->man.account, cur->man.account)) {
			printf("账号重复啦，请重新输入吧\n");
			free(pre);
			system("pause");
			return;
		}
		cur = cur->next;
	}//找到最后节点

	
	printf("正在添加......\n");
	cur->next = pre;

	mfileNode(mhead);
	free(pre);
	system("pause");
}
void sinputAccount(Node*head) {

	//暂存
	int Num=0;
	printf("请输入要创建账号的学生学号\n");
	while (scanf("%d", Num) != 1) {
		scanf("%*[^\n]%*c");
		printf("输入错误，请输入正确的学号\n");
	}
	scanf("%*[^\n]%*c");
	getchar();
	Node* move = head;
	int flag = 0;
	while (move != NULL) {
		if (move->student.num == Num) {
			flag = 1;
			move->student.account[0] = 'S';
			printf("请输入账号(不包含首字母)\n");
			scanf("%9s", &(move->student.account[1]));
			scanf("%*[^\n]%*c");

			printf("请输入密码\n");
			scanf("%10s", move->student.password);
			scanf("%*[^\n]%*c");
			break;
		}
		move = move->next;
	}
	if (!flag) {
		printf("该学生不存在\n");
		system("pause");
		return;
	}

	Node* cur = head;
	while (cur->next != NULL) {
		if (!strcmp(move->student.account, cur->student.account)) {
			printf("账号重复啦，请重新输入吧\n");

			system("pause");
			return;
		}
		cur = cur->next;
	}//找到最后节点
	printf("正在添加......\n");
	fileNode(head);

	system("pause");
}

//删除
void adeleteAccount(mNode* mhead, Node* head) {
	printf("删除学生账号请输入1，删除老师或者管理员账号请输入2\n");
	int c;
	while (scanf("%d", &c) != 1)
	{
		scanf("%*[^\n]%*c");
		printf("输入非法，请重新输入\n");
	}
	scanf("%*[^\n]%*c");

	switch (c) {
	case 1:
		sdeleteAccount(head);
		break;
	case 2:
		mdeleteAccount(mhead);
		break;
	default:
		printf("无此服务，将返回菜单\n");
		system("pause");
		break;
	}
}
void mdeleteAccount(mNode* mhead) {
	if (mhead->next == NULL) {
		printf("暂无账号\n");
		system("pause");
		return;
	}

	printf("请输入要删除的账号(包含首字母):");
	char Account[11];
	scanf("%10s", Account);
	scanf("%*[^\n]%*c");

	mNode* move = mhead;
	while (move->next != NULL) {
		if (!strcmp(move->next->man.account,Account )) {
			mNode* ret = move->next;
			move->next = ret->next;
			free(ret);
			ret = NULL;
			mfileNode(mhead);
			printf("该账号已删除\n");
			system("pause");
			return;
		}
		move = move->next;
	}
	printf("未找到\n");
	system("pause");
}
void sdeleteAccount(Node* head) {
	if (head->next == NULL) {
		printf("暂无账号\n");
		system("pause");
		return;
	}

	printf("请输入要删除的账号(包含首字母):");
	char Account[11];
	scanf("%10s", Account);
	scanf("%*[^\n]%*c");

	Node* move = head;
	while (move->next != NULL) {
		if (!strcmp(move->next->student.account, Account)) {
			Node* ret = move->next;
			move->next = ret->next;
			free(ret);
			ret = NULL;
			fileNode(head);
			printf("该账号已删除\n");
			system("pause");
			return;
		}
		move = move->next;
	}
	printf("未找到\n");
	system("pause");
}
////修改
void areviseAccount(mNode* mhead, Node* head) {
	printf("修改学生账号请输入1，修改老师或者管理员账号请输入2\n");
	int c;
	while (scanf("%d", &c) != 1)
	{
		scanf("%*[^\n]%*c");
		printf("输入非法，请重新输入\n");
	}
	scanf("%*[^\n]%*c");

	switch (c) {
	case 1:
		sreviseAccount(head);
		break;
	case 2:
		mreviseAccount(mhead);
		break;
	default:
		printf("无此服务，将返回菜单\n");
		break;
	}
}
void mreviseAccount(mNode* mhead) {
	printf("请输入要修改的账号(包含首字母):\n");
	char Account[11];
	scanf("%10s", Account);
	scanf("%*[^\n]%*c");
	printf("进入修改中\n");
	mNode* move = mhead->next;
	while (move != NULL) {
		if (!strcmp(move->man.account, Account)) {
			char c = '\0';
			while (c != 'T' && c != 'G') {
				printf("选择该账号是老师还是管理员（T为老师，G为管理员）\n");
				scanf(" %c", &c);
				scanf("%*[^\n]%*c");
				strcpy(move->man.mclass , "man");
				if (c == 'T') {
					printf("请输入账号所在班级\n");
					scanf("%63s", move->man.mclass);
					scanf("%*[^\n]%*c");
				}
			}
			move->man.account[0] = c;
			printf("请输入姓名\n");
			scanf("%10s", move->man.name);
			scanf("%*[^\n]%*c");

			char newAccount[11];
			memset(newAccount, '\0', sizeof(newAccount));
			newAccount[0] = c;
			printf("请输入账号(不包括首字母)\n");
			scanf("%9s", &newAccount[1]);
			scanf("%*[^\n]%*c");
			mNode* check = mhead->next;
			while (check != NULL) {
				if (strcmp(check->man.account, move->man.account) && !strcmp(check->man.account, newAccount)) {
					printf("新的账号已经存在，请重新输入\n");
					memset(newAccount, '\0', sizeof(newAccount));
					newAccount[0] = c;
					scanf("%9s", &newAccount[1]);
					scanf("%*[^\n]%*c");
					check = mhead;
				}
				else {
					check = check->next;
				}
			}
			strcpy(move->man.account, newAccount);
			printf("请输入密码:\n");
			scanf("%9s", move->man.password);
			scanf("%*[^\n]%*c");

			mfileNode(mhead);
			printf("修改成功\n");

			system("pause");
			return;
		}
		move = move->next;
	}
	printf("未找到\n");
	system("pause");
}

void sreviseAccount(Node* head) {
	printf("请输入要修改的账号(包含首字母):\n");
	char Account[11];
	scanf("%10s", &Account);
	scanf("%*[^\n]%*c");
	printf("进入修改中\n");
	Node* move = head->next;
	while (move != NULL) {
		if (!strcmp(move->student.account, Account)) {

			printf("请输入账号所在班级\n");
			scanf("%63s", move->student.mclass);
			scanf("%*[^\n]%*c");
			printf("请输入姓名\n");
			scanf("%19s", move->student.name);
			scanf("%*[^\n]%*c");

			char newAccount[11];
			memset(newAccount, '\0', sizeof(newAccount));
			newAccount[0] = 'S';
			printf("请输入账号(不包括首字母)\n");
			scanf("%9s", &newAccount[1]);
			scanf("%*[^\n]%*c");
			Node* check = head->next;
			while (check != NULL) {
				if (strcmp(check->student.account, move->student.account) && !strcmp(check->student.account, newAccount)) {
					printf("新的账号已经存在，请重新输入\n");
					memset(newAccount, '\0', sizeof(newAccount));
					newAccount[0] = 'S';
					scanf("%9s", &newAccount[1]);
					scanf("%*[^\n]%*c");
					check = head;
				}
				else {
					check = check->next;
				}
			}
			strcpy(move->student.account, newAccount);
			printf("请输入密码:\n");
			scanf("%10s", move->student.password);
			scanf("%*[^\n]%*c");

			fileNode(head);
			printf("修改成功\n");

			system("pause");
			return;
		}
		move = move->next;
	}
	printf("未找到\n");
	system("pause");
}
//查找账号密码
void afindAccount(mNode* mhead, Node* head) {
	printf("查找学生账号请输入1，查找老师或者管理员账号请输入2\n");
	int c;
	while (scanf("%d", &c) != 1)
	{
		scanf("%*[^\n]%*c");
		printf("输入非法，请重新输入\n");
	}
	scanf("%*[^\n]%*c");

	switch (c) {
	case 1:
		sfindAccount(head);
		break;
	case 2:
		mfindAccount(mhead);
		break;
	default:
		printf("无此服务，将返回菜单\n");
		break;
	}
}

void mfindAccount(mNode* mhead) {

	printf("请输入要查找的账号(包含首字母):\n");
	char Account[11];
	scanf("%10s", Account);
	scanf("%*[^\n]%*c");
	mNode* move = mhead;
	while (move->next != NULL) {
		if (!strcmp(move->man.account, Account)) {
			printf("姓名为：%s\n", move->man.name);
			Sleep(100);
			printf("账号为：%s\n", move->man.account);
			Sleep(100);
			printf("密码为：%s\n", move->man.password);
			Sleep(100);
			printf("------------------------------------------------------------\n");
			Sleep(100);
			system("pause");
			return;
		}
		move = move->next;
	}

	printf("未找到\n");
	system("pause");
}

void sfindAccount(Node* head) {

	printf("请输入要查找的账号(包含首字母):\n");
	char Account[10];
	scanf("%10s", Account);
	scanf("%*[^\n]%*c");
	Node* move = head;
	while (move->next != NULL) {
		if (!strcmp(move->student.account, Account)) {
			printf("姓名为：%s\n", move->student.name);
			Sleep(100);
			printf("账号为：%s\n", move->student.account);
			Sleep(100);
			printf("密码为：%s\n", move->student.password);
			Sleep(100);
			printf("------------------------------------------------------------\n");
			Sleep(100);
			system("pause");
			return;
		}
		move = move->next;
	}

	printf("未找到\n");
	system("pause");
}

//录入所有账号密码

//输出所有账号密码
void mprintfStdent(mNode* mhead) {
	if (mhead->next == NULL) {
		printf("暂无\n");
		system("pause");
		return;
	}
	int a = 0;
	mNode* move = mhead->next;

	while (move != NULL) {

		a++;
		printf("账号%d:\n\n", a);
		printf("姓名为：%s\n", move->man.name);
		Sleep(100);
		printf("班级为：%s\n", move->man.mclass);
		Sleep(100);
		printf("账号为：%s\n", move->man.account);
		Sleep(100);
		printf("密码为：%s\n", move->man.password);
		Sleep(100);
		printf("------------------------------------------------------------\n");
		Sleep(100);
		move = move->next;
	}
	system("pause");

}

void sprintfStdent(Node* head) {
	if (head->next == NULL) {
		printf("暂无学生\n");
		system("pause");
		return;
	}
	int a = 0;
	Node* move = head->next;

	while (move != NULL) {

		a++;
		printf("学生账号%d:\n\n", a);		
		printf("学号为：%d\n", move->student.num);
		Sleep(100);
		printf("姓名为：%s\n", move->student.name);
		Sleep(100);
		printf("班级为：%s\n", move->student.mclass);
		Sleep(100);
		printf("账号为：%s\n", move->student.account);
		Sleep(100);
		printf("密码为：%s\n", move->student.password);
		Sleep(100);
		printf("------------------------------------------------------------\n");
		Sleep(100);
		move = move->next;
	}
	system("pause");

}
//手动重新录入学生信息




void agencyMenu() {
	printf("---Student Information Management System---\n");
	printf("--           agency  model\t\t--\n");
	printf("--      0.远深，退出！ \t\t         --\n");
	printf("--      1.密码注册！！ \t\t         --\n");
	printf("--      2.密码修改！！ \t\t         --\n");
	printf("--      3.密码找回！！ \t\t         --\n");
	printf("--      4.成绩申诉！！ \t\t         --\n");
	printf("--      5.更新成绩库！ \t\t         --\n");
	printf("-------------------------------------------\n");
}
//查看代办
void Viewagency(Node* head, mNode* mhead, nNode* nhead) {
	while (1) {
		system("cls");
		loadStudent(head);
		mloadStudent(mhead);
		nloadStudent(nhead);
		agencyMenu();
		int c;
		while (scanf("%d", &c) != 1)
		{
			scanf("%*[^\n]%*c");
			printf("输入非法，请重新输入\n");
			system("pause");
			system("cls");
			loadStudent(head);
			mloadStudent(mhead);
			nloadStudent(nhead);
			agencyMenu();
		}
		scanf("%*[^\n]%*c");
		switch (c) {
		case 1://密码注册
			readpassWordrevise(nhead, head, mhead);
			break;
		case 2://密码修改
			readpassWordrevise(nhead, head, mhead);
			break;
		case 3://密码找回
			readpassWordretrieval(nhead);
			break;
		case 4://成绩申诉
			readGradeAppeals(nhead, head);
			break;
		case 5://提醒更新
			readUpdate(nhead);
			break;
		case 0://退出
			return;
			break;
		default:
			printf("无此选项，重新选择吧\n");
			system("pause");
			break;
		}

	}
}