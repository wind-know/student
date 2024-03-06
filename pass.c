#include "studentsystem.h"




void passMenu() {
	printf("---Student Information Management System---\n");
	printf("--           logon  model\t\t --\n");
	printf("--      0.远深，退出！ \t\t         --\n");
	printf("--      1.还有五秒钟到达战场\t         --\n");
	printf("--      2.帮帮我，管理员先生\t\t --\n");
	printf("-------------------------------------------\n");
}
void helpMenu() {
	printf("---Student Information Management System---\n");
	printf("--           help  model \t\t --\n");
	printf("--      \t0.远深，退出！ \t         --\n");
	printf("--      \t1.密码注册！！ \t         --\n");
	printf("--      \t2.密码修改！！ \t         --\n");
	printf("--      \t3.密码找回！！ \t         --\n");
	printf("-------------------------------------------\n");
}
void helping(Node* head, nNode* nhead, mNode* mhead) {
	while (1) {
		system("cls");
		loadStudent(head);
		mloadStudent(mhead);
		nloadStudent(nhead);
		helpMenu();
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
			helpMenu();
		}
		scanf("%*[^\n]%*c");
		switch (c) {
		case 1://密码注册
			passWordrevise(head,mhead,nhead);
			break;
		case 2://密码修改
			passWordrevise(head, mhead, nhead);
			break;
		case 3://密码找回
			passWordretrieval(nhead, head, mhead);
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

void passing(Node* head, nNode* nhead, mNode* mhead) {
	char account[11] = { '\0' };
	char password[11] = { '\0' };
	printf("请输入账号:\n");
	scanf("%10s", account);
	scanf("%*[^\n]%*c");
	printf("请输入密码:\n");
	scanf("%10s", password);
	scanf("%*[^\n]%*c");
	printf("正在登录中......\n");
	Sleep(1000);
	system("cls");

	if (account[0] == 'G' || account[0] == 'T') {
		mNode* move = mhead;
		while (move != NULL) {
			if (!strcmp(move->man.account, account)) {
				if (!strcmp(move->man.password, password)) {

					if (account[0] == 'T') {
						printf("老师你好，欢迎使用本系统\n");
						if (strcmp(move->man.question, "你玩原神嘛") == 0 && strcmp(move->man.answer, "万元神万的") == 0) {
							printf("老师你好，初次登录请更改密保\n");
							system("pause");
							treviseconfidential(mhead, move->man.account);
						}
						system("pause");
						Teachers(head,  nhead, mhead, move->man.account, move->man.mclass, move->man.name);
						return;
					}
					else if (account[0] == 'G') {
						printf("管理员你好，欢迎使用本系统\n");
						system("pause");
						Manager(head,nhead, mhead, move->man.account);
						return;
					}
				}
				else {
					printf("密码错误哦，请重新输入\n");
					system("pause");
					return;
				}
			}
			move = move->next;
		
		}
		printf("该账号不存在,请重新选择\n");
		system("pause");
	}
	else if (account[0] == 'S') {
		Node* move = head;
		while (move != NULL) {

			if (!strcmp(move->student.account, account)) {
				if (!strcmp(move->student.password, password)) {
					printf("同学你好，欢迎使用本系统\n");
					system("pause");
					if (strcmp(move->student.question, "你玩原神嘛") == 0 && strcmp(move->student.answer, "万元神万的") == 0) {
						printf("同学你好，初次登录请更改密保\n");
						system("pause");
						sreviseconfidential(head, move->student.num);
					}
					Students(head, nhead, move->student.mclass, move->student.num, move->student.account, move->student.name);
					return;
				}
				else {
					printf("密码错误哦，请重新输入\n");
					system("pause");
					return;
				}
			}
			move = move->next;
		}
		printf("该账号不存在,请重新选择\n");
		system("pause");
	}
	else {
		printf("账号格式错误，请输入以\"G\", \"T\"或\"S\"开头的账号\n");
		system("pause");
		return;
	}
}

void PASS(Node* head, nNode* nhead, mNode* mhead) {

	while (1) {
		system("cls");
		loadStudent(head);
		mloadStudent(mhead);
		nloadStudent(nhead);
		passMenu();
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
			passMenu();
		}
		scanf("%*[^\n]%*c");
		switch (c) {
		case 1://登录
			passing(head,nhead,mhead);
			break;
		case 2://申诉
			helping(head,nhead,mhead);
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


//将链表存入文件
void nfileNode(nNode* nhead) {
	FILE* fp = fopen("./helpNode.txt", "w");
	if (fp == NULL) {
		printf("未找到学生文件\n");
		return;
	}
	nNode* move = nhead->next;
	while (move != NULL) {
		if (fwrite(&move->con, sizeof(Con), 1, fp) != 1) {
			printf("写入失败\n");
			return;
		}
		move = move->next;
	}
	Sleep(1000);
	printf("写入成功\n");
	fclose(fp);

}

//从文件读取
void nloadStudent(nNode* nhead) {
	//打开文件
	FILE* fp = fopen("./helpNode.txt", "r");
	if (fp == NULL) {
		printf("--\t 未找到代办文件,跳过读取\t --\n");
		return;
	}

	//创建一个结点
	nNode* new = (nNode*)malloc(sizeof(nNode));
	new->next = NULL;
	nNode* move = nhead;
	while (fread(&new->con, sizeof(Con), 1, fp) == 1) {
		move->next = new;
		move = new;

		new = (nNode*)malloc(sizeof(nNode));
		new->next = NULL;
	}
	free(new);
	//最后多定义一个new，要将它释放掉
	//关闭文件
	fclose(fp);

	//printf("读取成功\n");

}




//密码注册

//密码修改
void passWordrevise(Node* head, mNode* mhead, nNode* nhead) {

	printf("1：学生账号密码修改\n");
	printf("2：老师账号密码修改\n");
	printf("请选择:\n");

	int c;
	while (scanf("%d", &c) != 1)
	{
		scanf("%*[^\n]%*c");
		printf("输入非法，请重新选择\n");

	}
	scanf("%*[^\n]%*c");
	switch (c) {
	case 1:
		spassWordretrieval(nhead,head);
		break;
	case 2:
		tpassWordretrieval(nhead, mhead);
		break;
	default:
		printf("无此服务，将返回菜单\n");
		system("pause");
		break;
	}

}
//密码修改学生
void spassWordrevise(nNode* nhead,Node*head) {

	char question[100] = { '\0' };
	char answer[100] = { '\0' };
	char Account[11] = { '\0' };
	char Password[11] = { '\0' };
	int flag = 0;
	nNode* pre = (nNode*)malloc(sizeof(nNode));
	pre->con.chose = 2;
	pre->con.over = 0;
	pre->next = NULL;
	//暂存
	printf("请输入要更改密码的账号：\n");
	scanf("%10s", Account);
	scanf("%*[^\n]%*c");
	if (Account[0] != 'S') {
		free(pre);
		printf("非学生账户\n");
		system("pause");
		return;
	}
	printf("请输入要更改密码的账号的密码：\n");
	scanf("%10s", Password);
	scanf("%*[^\n]%*c");

	Node* move = head;
	while (move != NULL) {
		if (!strcmp(move->student.account,Account)) {
			if (!strcmp(move->student.password, Password)) {
				pre->con.num = move->student.num;
				strcpy(pre->con.name, move->student.name);
				strcpy(pre->con.account,Account);
				strcpy(pre->con.mclass, move->student.mclass);
				flag = 1;
			}
		}
		move = move->next;
	}

	if (flag) {

		nNode* cur = nhead;
		while (cur->next != NULL) {

			cur = cur->next;
		}//找到最后节点

		printf("请输入更改之后的密码：\n");
		scanf("%10s", pre->con.newPassword);
		scanf("%*[^\n]%*c");
		printf("正在加载\n");
		cur->next = pre;
		nfileNode(nhead);
		system("pause");
	}
	else {
		free(pre);
		printf("账号或密码错误，无法修改\n");
		system("pause");
	}
}
//密码修改学生操作
void dospassWordrevise(Node* head,char*account,char*newpassword) {
	Node* move = head;
	printf("修改中\n");
	Sleep(100);
	while (move != NULL) {
		if (!strcmp(move->student.account, account)) {
			strcpy(move->student.password, newpassword);
			fileNode(head);
			printf("修改完成\n");
			system("pause");
		}
		move = move->next;
	}
}
//密码修改老师
void tpassWordrevise(nNode* nhead, mNode* mhead) {

	char question[100] = { '\0' };
	char answer[100] = { '\0' };
	char Account[11] = { '\0' };
	char Password[11] = { '\0' };
	int flag = 0;
	nNode* pre = (nNode*)malloc(sizeof(nNode));
	pre->con.chose = 2;
	pre->con.over = 0;
	pre->next = NULL;
	//暂存
	printf("请输入要更改密码的账号：\n");
	scanf("%10s", Account);
	scanf("%*[^\n]%*c");
	if (Account[0] != 'T') {
		free(pre);
		printf("非老师账户\n");
		system("pause");
		return;
	}
	printf("请输入要更改密码的账号的密码：\n");
	scanf("%10s", Password);
	scanf("%*[^\n]%*c");

	mNode* move = mhead;
	while (move != NULL) {
		if (!strcmp(move->man.account, Account)) {
			if (!strcmp(move->man.password, Password)) {
				pre->con.num = 0;
				strcpy(pre->con.name, move->man.name);
				strcpy(pre->con.account, Account);
				strcpy(pre->con.mclass, move->man.mclass);
				pre->con.num = 0;
				flag = 1;
			}
		}
		move = move->next;
	}

	if (flag) {

		nNode* cur = nhead;
		while (cur->next != NULL) {

			cur = cur->next;
		}//找到最后节点

		printf("请输入更改之后的密码：\n");
		scanf("%10s", pre->con.newPassword);
		scanf("%*[^\n]%*c");
		printf("正在加载\n");
		cur->next = pre;
		nfileNode(nhead);
		system("pause");
	}
	else {
		free(pre);
		printf("账号或密码错误，无法修改\n");
		system("pause");
	}
}
//密码修改老师操作
void dotpassWordrevise(mNode* mhead, char* account, char* newpassword) {
	mNode* move = mhead;
	printf("修改中\n");
	Sleep(100);
	while (move != NULL) {
		if (!strcmp(move->man.account, account)) {
			strcpy(move->man.password, newpassword);
			mfileNode(mhead);
			printf("修改完成\n");
			system("pause");
		}
		move = move->next;
	}
}
//密码修改读取
void readpassWordrevise(nNode* nhead, Node* head, mNode* mhead) {

	if (nhead->next == NULL) {
		printf("暂无密码修改申请\n");
		system("pause");
		return;
	}
	int a = 0;
	nNode* move = nhead->next;

	while (move != NULL) {
		if (move->con.chose == 2) {
			a++;
			printf("密码修改申请 %d:\n\n", a);

			printf("学号为：%d\n", move->con.num);
			printf("学号为0,代表老师账号\n");
			Sleep(100);
			printf("账号为：%s\n", move->con.account);
			Sleep(100);
			printf("姓名为：%s\n", move->con.name);
			Sleep(100);
			printf("班级为：%s\n", move->con.mclass);
			Sleep(100);
			printf("更改之后的密码:%s\n", move->con.newPassword);
			Sleep(100);
			printf("------------------------------------------------------------\n");
			Sleep(100);
			if (move->con.over == 1) {
				printf("(已完成该代办)\n");
			}
			else{
				printf("是否同意该申请 \n");
				printf("1同意，2拒绝\n");
				int c;
				while (scanf("%d", &c) != 1)
				{
					scanf("%*[^\n]%*c");
					printf("输入非法，请重新选择\n");

				}
				scanf("%*[^\n]%*c");
				switch (c) {
				case 1:
					if (move->con.num != 0)
					{
						move->con.over = 1;
						nfileNode(nhead);
						dospassWordrevise(head, move->con.account, move->con.newPassword);
					}
					else
					{
						move->con.over = 1;
						nfileNode(nhead);
						dotpassWordrevise(head, move->con.account, move->con.newPassword);
					}
					break;
				case 2:
					break;
				default:
					printf("无此服务，默认拒绝\n");
					system("pause");
					break;
				}
			}
			ndelete(nhead, move->con.account);
		}
		move = move->next;
	}
	printf("------------------------------------------------------------\n");
	printf("没有密码修改申请啦，看看别的吧\n");
	system("pause");
}

//密码找回
void passWordretrieval(nNode* nhead, Node* head, mNode* mhead) {
	printf("1：学生账号密码找回\n");
	printf("2：老师账号密码找回\n");
	printf("请选择:\n");

	int c;
	while (scanf("%d", &c) != 1)
	{
		scanf("%*[^\n]%*c");
		printf("输入非法，请重新选择\n");

	}
	scanf("%*[^\n]%*c");
	switch (c) {
	case 1:
		spassWordretrieval(nhead, head);
		break;
	case 2:
		tpassWordretrieval(nhead, mhead);
		break;
	default:
		printf("无此服务，将返回菜单\n");
		system("pause");
		break;
	}
}
//密码找回学生
void spassWordretrieval(nNode* nhead, Node* head) {

	char question[100] = { '\0' };
	char answer[100] = { '\0' };
	char Account[11] = { '\0' };
	int flag = 0;
	nNode* pre = (nNode*)malloc(sizeof(nNode));
	pre->con.chose = 3;
	pre->con.over = 0;
	pre->next = NULL;
	//暂存
	printf("请输入要找回密码的账号：\n");
	scanf("%10s", Account);
	scanf("%*[^\n]%*c");
	if (Account[0] != 'S') {
		free(pre);
		printf("非学生账户\n");
		system("pause");
		return;
	}
	printf("请输入密保问题：\n");
	scanf("%100s", question);
	scanf("%*[^\n]%*c");

	printf("请输入密保答案:\n");
	scanf("%100s", answer);
	scanf("%*[^\n]%*c");
	char phonenum[101] = { '\0' };
	printf("请输入电话号码:\n");
	scanf("%100s", phonenum);
	scanf("%*[^\n]%*c");

	Node* move = head;
	while (move != NULL) {
		if (!strcmp(move->student.account, Account)) {
			if (!strcmp(move->student.question, question) && !strcmp(move->student.answer, answer))
			{
				strcpy(pre->con.phonenum, phonenum);
				pre->con.num = move->student.num;
				strcpy(pre->con.name, move->student.name);
				strcpy(pre->con.account, Account);
				strcpy(pre->con.mclass, move->student.mclass);
				flag = 1;

			}
		}
		move = move->next;
	}

	if (flag) {

		nNode* cur = nhead;
		while (cur->next != NULL) {

			cur = cur->next;
		}//找到最后节点

		printf("正在加载\n");
		cur->next = pre;
		nfileNode(nhead);
		printf("申请已提交\n");
		system("pause");
	}
	else {
		free(pre);
		printf("密保错误，无法修改\n");
		system("pause");
	}
}
//密码找回老师
void tpassWordretrieval(nNode* nhead, mNode* mhead) {

	char question[100] = { '\0' };
	char answer[100] = { '\0' };
	char Account[11] = { '\0' };
	int flag = 0;
	nNode* pre = (nNode*)malloc(sizeof(nNode));
	pre->con.chose = 3;
	pre->con.over = 0;
	pre->next = NULL;
	//暂存
	printf("请输入要找回密码的账号：\n");
	scanf("%10s", Account);
	scanf("%*[^\n]%*c");
	if (Account[0] != 'T') {
		free(pre);
		printf("非老师账户\n");
		system("pause");
		return;
	}	


	printf("请输入密保问题：\n");
	scanf("%100s", question);
	scanf("%*[^\n]%*c");

	printf("请输入密保答案:\n");
	scanf("%100s", answer);
	scanf("%*[^\n]%*c");
	char phonenum[101] = { '\0' };
	printf("请输入电话号码:\n");
	scanf("%100s", phonenum);
	scanf("%*[^\n]%*c");


	mNode* move = mhead;
	while (move != NULL) {
		if (!strcmp(move->man.account, Account)) {
			if (!strcmp(move->man.question, question) && !strcmp(move->man.answer, answer))
			{
				strcpy(pre->con.phonenum, phonenum);
				pre->con.num = 0;
				strcpy(pre->con.name, move->man.name);
				strcpy(pre->con.account, Account);
				strcpy(pre->con.mclass, move->man.mclass);
				flag = 1;

			}
		}
		move = move->next;
	}
	if (flag) {

		nNode* cur = nhead;
		while (cur->next != NULL) {

			cur = cur->next;
		}//找到最后节点
		printf("正在加载\n");
		cur->next = pre;
		nfileNode(nhead);
		printf("申请已提交\n");
		system("pause");
	}
	else {
		free(pre);
		printf("密保错误，无法修改\n");
		system("pause");
		return;
	}
}
//密码找回读取
void readpassWordretrieval(nNode* nhead) {

	if (nhead->next == NULL) {
		printf("暂无密码找回申请\n");
		system("pause");
		return;
	}
	int a = 0;
	nNode* move = nhead->next;

	while (move != NULL) {
		if (move->con.chose == 3) {
			a++;
			printf("密码找回申请 %d:\n\n", a);

			printf("学号为：%d\n", move->con.num);
			printf("学号为0,代表老师账号\n");
			Sleep(100);
			printf("账号为：%s\n", move->con.account);
			Sleep(100);
			printf("姓名为：%s\n", move->con.name);
			Sleep(100);
			printf("班级为：%s\n", move->con.mclass);
			Sleep(100);
			printf("------------------------------------------------------------\n");
			Sleep(100);
			if (move->con.over == 1) {
				printf("（已完成该代办）\n");
			}
			else
			{
				printf("是否同意该申请 \n");
				printf("1同意，2拒绝\n");
				int c;
				while (scanf("%d", &c) != 1)
				{
					scanf("%*[^\n]%*c");
					printf("输入非法，请重新选择\n");

				}
				scanf("%*[^\n]%*c");
				switch (c) {
				case 1:
					move->con.over = 1;
					nfileNode(nhead);
					printf("请致电:%s,告知对方密码\n", move->con.phonenum);
					break;
				case 2:
					break;
				default:
					printf("无此服务，默认拒绝\n");
					system("pause");
					break;
				}
			}
			ndelete(nhead, move->con.account);

		}
		move = move->next;
	}
	printf("------------------------------------------------------------\n");
	printf("没有密码找回申请啦，看看别的吧\n");
	system("pause");

}


//成绩申诉
void GradeAppeals(nNode* nhead, char* mclass, int num, char* account,char*name) {

	nNode* pre = (nNode*)malloc(sizeof(nNode));
	pre->con.chose = 4;
	pre->con.over = 0;
	pre->next = NULL;
	//暂存
	strcpy(pre->con.name, name);
	strcpy(pre->con.account, account);
	strcpy(pre->con.mclass, mclass);
	pre->con.num = num;

	printf("请输入要更改前的成绩（数学，英语，语文）\n");
	scanf("%d%d%d", &pre->con.icomplaint[1], &pre->con.icomplaint[2], &pre->con.icomplaint[3]);
	scanf("%*[^\n]%*c");

	printf("请输入要更改后的成绩（数学，英语，语文）\n");
	scanf("%d%d%d", &pre->con.icomplaint[4], &pre->con.icomplaint[5], &pre->con.icomplaint[6]);
	scanf("%*[^\n]%*c");

	printf("请输入申诉理由\n");
	scanf("%999s",pre->con.ccomplaint);
	scanf("%*[^\n]%*c");

	nNode* cur = nhead;
	while (cur->next != NULL) {

		cur = cur->next;
	}//找到最后节点

	printf("正在加载\n");

	cur->next = pre;

	nfileNode(nhead);
	printf("申请已提交\n");
	system("pause");

}
//成绩申诉读取
void readGradeAppeals(nNode* nhead,Node* head) {

		if (nhead->next == NULL) {
			printf("暂无申诉\n");
			system("pause");
			return;
		}
		int a = 0;
		nNode* move = nhead->next;

		while (move != NULL) {
			if(move->con.chose==4){
				a++;
				printf("申诉 %d:\n\n", a);

				printf("学号为：%d\n", move->con.num);
				Sleep(100);
				printf("账号为：%s\n", move->con.account);
				Sleep(100);
				printf("姓名为：%s\n", move->con.name);
				Sleep(100);
				printf("班级为：%s\n", move->con.mclass);
				Sleep(100);
				printf("更改前的成绩（数学，英语，语文）\n");
				printf("数学：%-10d\t 英语：%-10d\t 语文：%-10d\t \n", move->con.icomplaint[1], move->con.icomplaint[2], move->con.icomplaint[3]);
				Sleep(100);
				printf("更改后的成绩（数学，英语，语文）\n");
				printf("数学：%-10d\t 英语：%-10d\t 语文：%-10d\t \n", move->con.icomplaint[4], move->con.icomplaint[5], move->con.icomplaint[6]);
				Sleep(100);
				printf("申诉理由：%s\n", move->con.ccomplaint);
				Sleep(100);
				printf("------------------------------------------------------------\n");
				Sleep(100);
				if (move->con.over == 1) {
					printf("（已完成该代办）\n");
					
				}
				else{
					printf("是否同意该申请 \n");
					printf("1同意，2拒绝\n");
					int c;
					while (scanf("%d", &c) != 1)
					{
						scanf("%*[^\n]%*c");
						printf("输入非法，请重新选择\n");

					}
					scanf("%*[^\n]%*c");
					switch (c) {
					case 1:
						move->con.over = 1;
						nfileNode(nhead);
						doGradeAppeals(head, move->con.icomplaint[4], move->con.icomplaint[5], move->con.icomplaint[6], move->con.account);

						break;
					case 2:
						break;
					default:
						printf("无此服务，默认拒绝\n");
						system("pause");
						break;
					}
				}
				ndelete(nhead, move->con.account);
			}
			move = move->next;
		}
		printf("------------------------------------------------------------\n");
		printf("没有申诉啦，看看别的吧\n");
		system("pause");
}
//成绩申诉操作
void doGradeAppeals(Node* head, int match, int english,int chinese,char*account) {
	Node* move = head;
	printf("修改中\n");
	Sleep(100);
	while (move != NULL) {
		if (!strcmp(move->student.account, account)) {
			move->student.score.match=match;
			move->student.score.english=english;
			move->student.score.chinese=chinese;

			fileNode(head);
			printf("修改完成\n");

			system("pause");

		}
		move = move->next;
	}

}

//更新成绩库
void Update(nNode* nhead, char* account,char*mclass, char* name) {

	nNode* pre = (nNode*)malloc(sizeof(nNode));
	pre->con.chose = 5;
	pre->con.over =0;
	pre->next = NULL;
	//暂存
	pre->con.num = 0;


	strcpy(pre->con.name, name);
	strcpy(pre->con.account, account);
	strcpy(pre->con.mclass, mclass);

	printf("请输入想要告诉管理员的话\n");
	scanf("%*[^\n]%*c");
	scanf("%999s", pre->con.ccomplaint);
	scanf("%*[^\n]%*c");

	nNode* cur = nhead;
	while (cur->next != NULL) {

		cur = cur->next;
	}//找到最后节点

	printf("正在加载\n");

	cur->next = pre;

	nfileNode(nhead);
	printf("申请已提交\n");
	system("pause");
}
//更新成绩库读取
void readUpdate(nNode* nhead) {
	if (nhead->next == NULL) {
		printf("暂无更新成绩库申请\n");
		system("pause");
		return;
	}
	int a = 0;
	nNode* move = nhead->next;

	while (move != NULL) {
		if (move->con.chose == 5) {
			a++;
			printf("更新成绩库请求 %d:\n\n", a);

			printf("账号为：%s\n", move->con.account);
			Sleep(100);
			printf("姓名为：%s\n", move->con.name);
			Sleep(100);
			printf("班级为：%s\n", move->con.mclass);
			Sleep(100);
			printf("想要说的话：%s\n", move->con.ccomplaint);
			Sleep(100);
			printf("------------------------------------------------------------\n");
			if (move->con.over == 1) {
				printf("（已完成该代办）\n");
			}
			else
			{
				move->con.over = 1;
				nfileNode(nhead);
			}
			ndelete(nhead, move->con.account);
		}
		move = move->next;
	}
	printf("------------------------------------------------------------\n");
	printf("没有更新请求啦，看看别的吧\n");
	system("pause");

}

//删除代办链表
void ndeleteStudent(nNode * nhead, char* Account) {
	nNode* move = nhead;
	while (move->next != NULL) {
		if (!strcmp(move->next->con.account, Account)) {
			nNode* ret = move->next;
			move->next = ret->next;
			free(ret);
			ret = NULL;
			nfileNode(nhead);
			printf("该代办已删除\n");
			system("pause");

			return;
		}
		move = move->next;
	}
	printf("未找到\n");
	system("pause");
}
//
void ndelete(nNode* nhead, char*account) {
	printf("------------------------------------------------------------\n");
	printf("是否删除该申请：\n");
	printf("1删除，2保留\n");
	int d;
	while (scanf("%d", &d) != 1)
	{
		scanf("%*[^\n]%*c");
		printf("输入非法，请重新选择\n");

	}
	scanf("%*[^\n]%*c");
	switch (d) {
	case 1:
		ndeleteStudent(nhead,account);
		break;
	case 2:
		break;
	default:
		printf("无此服务，默认保留\n");
		system("pause");
		break;
	}
}