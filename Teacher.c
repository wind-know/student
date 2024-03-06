#include "studentsystem.h"

void Teachers(Node* head, nNode* nhead,mNode* mhead,char*account, char* mclass,char*name) {
	while (1) {

		system("cls");
		loadStudent(head);
		mloadStudent(mhead);
		Menu1();

		int c;
		while (scanf("%d", &c)!= 1)
		{
			scanf("%*[^\n]%*c");
			printf("输入非法，请重新输入\n");
			system("pause");
			system("cls");
			loadStudent(head);
			mloadStudent(mhead);
			Menu1();
		}
		scanf("%*[^\n]%*c");


		switch (c) {
		case 1://增加
			inputStudent(head);
			break;
		case 2://删除
			deleteStudent(head);
			break;
		case 3://修改
			reviseStudent(head);
			break;
		case 4://查询
			findStudent(head);
			break;
		case 5://输出
			printfStdent(head);
			break;
		case 6://下载
			tfileNode(head);
			printf("已经下载到\"D:/Tstudent.txt\"文件夹下\n");
			system("pause");
			break;
		case 7://分析
			essayStudent(head);
			break;
		case 8://提醒
			Update(nhead, account, mclass, name);
			break;
		case 9://排序
			asortStudent(head);
			break;
			treviseconfidential(mhead,account);
		case 10://修改密码
			trevisemypassword(mhead, account);
			break;
		case 11://返回上一层
			return;
			break;
		case 0 ://退出
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

//清屏
void Clean() {
	system("pause");
	system("cls");
}

//将链表固定存入文件
void tfileNode(Node* head) {
	FILE* fp = fopen("D:/Tstudent.txt", "w");
	if (fp == NULL) {
		printf("未找到学生文件\n");
		return;
	}
	Node* move = head->next;
	while (move != NULL) {
		if (fwrite(&move->student, sizeof(Stu), 1, fp) != 1) {
			printf("写入失败\n");
			return;
		}
		move = move->next;
	}
	printf("写入成功\n");
	system("pause");
	fclose(fp);

}


//将链表存入文件
void fileNode(Node* head) {
	FILE* fp = fopen("./studentNode.txt", "w");
	if (fp == NULL) {
		printf("未找到学生文件\n");
		return;
	}
	Node* move = head->next;
	while (move != NULL) {
		if (fwrite(&move->student, sizeof(Stu), 1, fp) != 1) {
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
void loadStudent(Node* head) {
	//打开文件
	FILE* fp = fopen("./studentNode.txt", "r");
	if (fp == NULL) {
		printf("--\t 未找到学生文件,跳过读取\t --\n");
		return;
	}

	//创建一个结点
	Node* new = (Node*)malloc(sizeof(Node));
	new->next = NULL;
	Node* move = head;
	while (fread(&new->student, sizeof(Stu), 1, fp) == 1) {
		move->next = new;
	move = new;

		new = (Node*)malloc(sizeof(Node));
		new->next = NULL;
	}
	free(new);
	//最后多定义一个new，要将它释放掉
	//关闭文件
	fclose(fp);

	//printf("读取成功\n");

}


void Menu1() {

	printf("---Student Information Management System---\n");
	printf("--\t         teacher model\t\t --\n");
	printf("--\t  0.退出 \t\t         --\n");
	printf("--\t  1.增加新的学生信息\t         --\n");
	printf("--\t  2.删除学生信息\t\t --\n");
	printf("--\t  3.修改学生信息 \t\t --\n");
	printf("--\t  4.查询学生信息 \t\t --\n");
	printf("--\t  5.输出本班成绩\t\t --\n");
	printf("--\t  6.下载到文件中\t\t --\n");
	printf("--\t  7.成绩分析\t\t         --\n");
	printf("--\t  8.提醒管理员更新成绩\t         --\n");
	printf("--\t  9.学生排序 \t\t         --\n");
	printf("--\t  10.修改原密码 \t         --\n");
	printf("--\t  11.返回上一层 \t         --\n");
	printf("-------------------------------------------\n");
}


//增加
void inputStudent(Node* head) {
	Node* pre = (Node*)malloc(sizeof(Node));
	pre->next = NULL;
	//暂存
	printf("请输入班级\n");
	scanf("%63s", pre->student.mclass);
	scanf("%*[^\n]%*c");

	printf("请输入学号,姓名\n");
	scanf("%d %19s", &pre->student.num, pre->student.name);
	scanf("%*[^\n]%*c");

	Node* cur = head;
	while (cur->next != NULL) {
		if (pre->student.num == cur->student.num) {
			printf("学号重复啦，请重新输入吧\n");
			free(pre);
			system("pause");
			return;
		}
		cur = cur->next;
	}//找到最后节点

	printf("请输入成绩数学,英语,语文:\n");
	scanf("%d%d%d",&pre->student.score.match, &pre->student.score.english, &pre->student.score.chinese);
	scanf("%*[^\n]%*c");
	while (pre->student.score.match > 100) {
		printf("---------------------------\n");
		printf("数学最高100分，当前已经超出哦\n");
		printf("请输入成绩数学:\n");
		scanf("%d", &pre->student.score.match);
	}
	while (pre->student.score.english > 100) {
		printf("英语最高100分，当前已经超出哦\n");
		printf("请输入成绩英语:\n");
		scanf("%d", &pre->student.score.english);
	}
	while (pre->student.score.chinese > 100) {
		printf("语文最高100分，当前已经超出哦\n");
		printf("请输入成绩语文:\n");
		scanf("%d", &pre->student.score.chinese);
	}
	sprintf(pre->student.account, "S%d", pre->student.num);
	strcpy(pre->student.password, "00000000");

	strcpy(pre->student.question, "你玩原神嘛");
	strcpy(pre->student.answer, "万元神万的");

	printf("正在添加......\n");
	//录入

	
	//Node* moveLast(Node*head){
	// 	Node* cur = head;
	//  while (cur->next != NULL) {
	//	cur = cur->next;
	//  }
	// return cur;
	//}

	cur->next= pre;

	fileNode(head);
	system("pause");
}
//修改密保
void treviseconfidential(mNode* mhead, char*account) {
	if (!strcmp('0', account)) {
		printf("管理员身份，无密保\n");
		return;
	}

	mNode* move = mhead->next;
	while (move != NULL) {
		if (!strcmp(move->man.account, account)) {
			printf("请输入密保问题：\n");
			scanf("%100s", move->man.question);
			scanf("%*[^\n]%*c");

			printf("请输入密保答案:\n");
			scanf("%100s", move->man.answer);
			scanf("%*[^\n]%*c");

			mfileNode(mhead);
			printf("修改成功\n");

			system("pause");
			return;
		}
		move = move->next;
	}
	printf("未找到学生\n");
	system("pause");
}


//删除
void deleteStudent(Node*head) {
	if (head->next == NULL) {
		printf("暂无学生\n");
		system("pause");
		return;
	}

	printf("请输入学生学号:");
	int Num = 0;
	scanf("%d", &Num);
	scanf("%*[^\n]%*c");

	Node* move = head;
	while (move->next != NULL) {
		if (move->next->student.num == Num) {
			Node* ret = move->next;
			move->next = ret->next;
			free(ret);
			ret = NULL;
			fileNode(head);
			printf("学号为%d的学生已删除\n",Num);
			Clean();
			return;
		}
		move = move->next;
	}
	printf("未找到\n");
	system("pause");
}

//修改
void reviseStudent(Node* head) {
	printf("请输入要修改的学生的学号:\n");
	int Num;
	scanf("%d", &Num);
	scanf("%*[^\n]%*c");
	Node* move = head->next;
	while (move != NULL) {
		if (move->student.num == Num) {
			printf("请输入班级\n");
			scanf("%63s", move->student.mclass);
			scanf("%*[^\n]%*c");

			printf("请输入姓名:\n");
			scanf("%19s", move->student.name);
			scanf("%*[^\n]%*c");

			printf("请输入成绩数学,英语,语文:\n");
			scanf("%d%d%d", &move->student.score.match, &move->student.score.english, &move->student.score.chinese);
			scanf("%*[^\n]%*c");

			while (move->student.score.match > 100) {
				printf("数学最高100分，当前已经超出哦\n");
				printf("请输入成绩数学:\n");
				scanf("%d", &move->student.score.match);
			}			
			while (move->student.score.english > 100) {
				printf("英语最高100分，当前已经超出哦\n");
				printf("请输入成绩英语:\n");
				scanf("%d", &move->student.score.english);
			}
			while (move->student.score.chinese > 100) {
				printf("语文最高100分，当前已经超出哦\n");
				printf("请输入成绩语文:\n");
				scanf("%d", &move->student.score.chinese);
			}

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

//查找（学号）
void nfindStudent(Node* head) {

	printf("请输入要查找的学生学号：");
	int Num;
	scanf("%d", &Num);
	scanf("%*[^\n]%*c");
	Node* move = head;
	while (move!= NULL) {
		if (move->student.num == Num) {
			printf("学号：%-10d\t 班级：%-10s\t 姓名：%-10s\t \n", move->student.num, move->student.mclass, move->student.name);
			Sleep(100);
			printf("数学: %-10d\t 英语: %-10d\t 语文： %-10d\t\n", move->student.score.match, move->student.score.english, move->student.score.chinese);
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

//查找（姓名）
void mfindStudent(Node* head) {

	printf("请输入要查找的学生姓名：");
	char name[20] = { '\0' };
	scanf("%19s", name);
	scanf("%*[^\n]%*c");
	Node* move = head;
	while (move != NULL) {
		if (!strcmp(move->student.name, name)) {
			printf("学号：%-10d\t 班级：%-10s\t 姓名：%-10s\t \n", move->student.num, move->student.mclass, move->student.name);
			Sleep(100);
			printf("数学: %-10d\t 英语: %-10d\t 语文： %-10d\t\n", move->student.score.match, move->student.score.english, move->student.score.chinese);
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

//查询（综合）
void afindStudent(Node* head) {

	printf("请输入要查找的学生 学号和姓名：");
	char name[20] = { '\0' };
	int Num;
	scanf("%d%19s", &Num, name);
	scanf("%*[^\n]%*c");
	Node* move = head;
	while (move != NULL) {
		if (move->student.num == Num) {
			if (!strcmp(move->student.name, name)) {
				printf("学号：%-10d\t 班级：%-10s\t 姓名：%-10s\t \n", move->student.num, move->student.mclass, move->student.name);
				Sleep(100);
				printf("数学: %-10d\t 英语: %-10d\t 语文： %-10d\t\n", move->student.score.match, move->student.score.english, move->student.score.chinese);
				Sleep(100);
				printf("------------------------------------------------------------\n");
				Sleep(100);
				system("pause");
				return;
			}

		}
		move = move->next;
	}

	printf("未找到\n");
	system("pause");
}

//总查找
void findStudent(Node* head){
	printf("1：按学号查询\n");
	printf("2：按姓名查询\n");
	printf("3：综合查询\n");
	printf("请选择要查找的方式:\n");

	int c;
	while (scanf("%d", &c) != 1)
	{
		scanf("%*[^\n]%*c");
		printf("输入非法，请重新选择\n");

	}
	scanf("%*[^\n]%*c");
	switch (c) {
	case 1:
		nfindStudent(head);
		break;
	case 2:
		mfindStudent(head);
		break;
	case 3:
		afindStudent(head);
		break;
	default:
		printf("无此服务，将返回菜单\n");
		system("pause");
		break;
	}

}

//打印
void printfStdent(Node* head) {
	if (head->next == NULL) {
		printf("暂无学生\n");
		system("pause");
		return;
	}
	int a = 0;
	Node* move = head->next;

	while (move != NULL) {

		a++;
		printf("学生%d:\n\n", a);

		printf("学号：%-10d\t 班级：%-10s\t 姓名：%-10s\t \n", move->student.num, move->student.mclass, move->student.name);
		Sleep(100);
		printf("数学: %-10d\t 英语: %-10d\t 语文： %-10d\t\n", move->student.score.match, move->student.score.english, move->student.score.chinese);
		Sleep(100);
		printf("------------------------------------------------------------\n");
		Sleep(100);
		move = move->next;
	}
	system("pause");
}



//分析函数
void essayStudent(Node* head) {
	Node* move = head;

	char mclass[20];
	printf("请输入要分析的班级：\n");
	scanf("%s", mclass);
	scanf("%*[^\n]%*c");

	int mgood = 0,egood = 0, cgood = 0;
	int mok = 0, eok = 0, cok = 0;
	double all = 0;
	while (move->next != NULL) {
		if (!strcmp(mclass, move->next->student.mclass))
		{
			all++;
			if (move->next->student.score.match >= 85) {
				mgood++;
			}
			else if (move->next->student.score.match >= 60 && move->next->student.score.match < 85) {
				mok++;
			}

			if (move->next->student.score.english >= 85) {
				egood++;
			}
			else if (move->next->student.score.english >= 60 && move->next->student.score.english < 85) {
				eok++;
			}

			if (move->next->student.score.chinese >= 85) {
				cgood++;
			}
			else if (move->next->student.score.chinese >= 60 && move->next->student.score.chinese < 85) {
				cok++;
			}
		}
		move = move->next;
	}
	if(all!=0){
		printf("学生有:%d位\n", (int)all);
		printf("--------------------------------------------\n");
		Sleep(100);
		printf("--数学成绩达到优秀的学生有:%d位\n", mgood);
		printf("--占全班的比例为:%lf%%\n\n", mgood / all * 100);
		Sleep(100);
		printf("--数学成绩达到及格但未达到优秀的学生有:%d位\n", mok);
		printf("--占全班的比例为:%lf%%\n", mok / all * 100);
		printf("--------------------------------------------\n");
		Sleep(100);

		printf("--英语成绩达到优秀的学生有:%d位\n", egood);
		printf("--占全班的比例为:%lf%%\n\n", egood / all * 100);
		Sleep(100);
		printf("--英语成绩达到及格但未达到优秀的学生有:%d位\n", eok);
		printf("--占全班的比例为:%lf%%\n", eok / all * 100);
		printf("--------------------------------------------\n");
		Sleep(100);

		printf("--语文成绩达到优秀的学生有:%d位\n", cgood);
		printf("--占全班的比例为:%lf%%\n\n", cgood / all * 100);
		Sleep(100);
		printf("--语文成绩达到及格但未达到优秀的学生有:%d位\n", cok);
		printf("--占全班的比例为:%lf%%\n", cok / all * 100);
		printf("--------------------------------------------\n");
		system("pause");
	}
	else {
		printf("没有收录这个班级学生信息哦\n");
		system("pause");
	}
}

void asortStudent(Node* head) {
	printf("1：从小到大排序\n");
	printf("2：从大到小排序\n");
	printf("请选择要排序的方向:\n");

	int c;
	while (scanf("%d", &c) != 1)
	{
		scanf("%*[^\n]%*c");
		printf("输入非法，请重新选择\n");

	}
	scanf("%*[^\n]%*c");
	switch (c) {
	case 1:
		ssortStudent(head);
		break;
	case 2:
		jsortStudent(head);
		break;
	default:
		printf("无此服务，将返回菜单\n");
		system("pause");
		break;
	}

}
//学生排序（从小到大）
void ssortStudent(Node* head) {
	system("cls");
	Node* save = NULL;
	Node* move = NULL;
	if (head != NULL ) {
		printf("注意！当前没有学生\n");
		system("pause");
		return;
	}
	if(head->next == NULL){
		printf("注意！当前学生不需要排序\n");
		system("pause");
		return;
	}
	printf("请问依据什么排序\n");
	printf("1：按学号\n");
	printf("2：按数学成绩\n");
	printf("3：按英语成绩\n");
	printf("4：按语文成绩\n");
	printf("5：按姓名排序\n");
	printf("6：按班级排序\n");
	printf("请选择要排序的方式:\n");
	int c;
	while (scanf("%d", &c) != 1)
	{
		scanf("%*[^\n]%*c");
		printf("输入非法，请重新选择\n");

	}
	scanf("%*[^\n]%*c");
	switch (c) {
	case 1:
		for (Node* turn = head->next; turn->next != NULL; turn = turn->next) {
			for (move = head->next; move->next != save; move = move->next) {
				if (move->student.num > move->next->student.num) {
					Stu temp = move->student;
					move->student = move->next->student;
					move->next->student = temp;
				}
			}
			save = move;
		}
		fileNode(head);
		printfStdent(head);
		return;
		break;
	case 2:
		for (Node* turn = head->next; turn->next != NULL; turn = turn->next) {
			for (move = head->next; move->next != save; move = move->next) {
				if (move->student.score.match > move->next->student.score.match) {
					Stu temp = move->student;
					move->student = move->next->student;
					move->next->student = temp;
				}
			}
			save = move;
		}
		break;
	case 3:
		for (Node* turn = head->next; turn->next != NULL; turn = turn->next) {
			for (move = head->next; move->next != save; move = move->next) {
				if (move->student.score.english > move->next->student.score.english) {
					Stu temp = move->student;
					move->student = move->next->student;
					move->next->student = temp;
				}
			}
			save = move;
		}
		break;
	case 4:
		for (Node* turn = head->next; turn->next != NULL; turn = turn->next) {
			for (move = head->next; move->next != save; move = move->next) {
				if (move->student.score.chinese > move->next->student.score.chinese) {
					Stu temp = move->student;
					move->student = move->next->student;
					move->next->student = temp;
				}
			}
			save = move;
		}
		break;
	case 5:
		for (Node* turn = head->next; turn->next != NULL; turn = turn->next) {
			for (move = head->next; move->next != save; move = move->next) {
				if (strcmp(move->student.name, move->next->student.name) > 0) {
					Stu temp = move->student;
					move->student = move->next->student;
					move->next->student = temp;
				}
			}
			save = move;
		}
		break;
	case 6:
		for (Node* turn = head->next; turn->next != NULL; turn = turn->next) {
			for (move = head->next; move->next != save; move = move->next) {
				if (strcmp(move->student.mclass, move->next->student.mclass) > 0) {
					Stu temp = move->student;
					move->student = move->next->student;
					move->next->student = temp;
				}
			}
			save = move;
		}
		break;
	default:
		printf("无此服务，将返回菜单\n");
		system("pause");
		break;
	}
	fileNode(head);
	printfStdent(head);
	return;
}

//学生排序（从大到小）
void jsortStudent(Node* head) {
	Node* save = NULL;
	Node* move = NULL;
	if (head != NULL) {
		printf("注意！当前没有学生\n");
		system("pause");
		return;
	}
	if (head->next == NULL) {
		printf("注意！当前学生不需要排序\n");
		system("pause");
		return;
	}
	printf("请问依据什么排序\n");
	printf("1：按学号\n");
	printf("2：按数学成绩\n");
	printf("3：按英语成绩\n");
	printf("4：按语文成绩\n");
	printf("5：按姓名排序\n");
	printf("6：按班级排序\n");
	printf("请选择要排序的方式:\n");
	int c;
	while (scanf("%d", &c) != 1)
	{
		scanf("%*[^\n]%*c");
		printf("输入非法，请重新选择\n");

	}
	scanf("%*[^\n]%*c");

		switch (c) {
		case 1:
			for (Node* turn = head->next; turn->next != NULL; turn = turn->next) {
				for (move = head->next; move->next != save; move = move->next) {
					if (move->student.num < move->next->student.num) {
						Stu temp = move->student;
						move->student = move->next->student;
						move->next->student = temp;
					}
				}
				save = move;
			}
			break;
		case 2:
			for (Node* turn = head->next; turn->next != NULL; turn = turn->next) {
				for (move = head->next; move->next != save; move = move->next) {
					if (move->student.score.match < move->next->student.score.match) {
						Stu temp = move->student;
						move->student = move->next->student;
						move->next->student = temp;
					}
				}
				save = move;
			}
			break;
		case 3:
			for (Node* turn = head->next; turn->next != NULL; turn = turn->next) {
				for (move = head->next; move->next != save; move = move->next) {
					if (move->student.score.english < move->next->student.score.english) {
						Stu temp = move->student;
						move->student = move->next->student;
						move->next->student = temp;
					}
				}
				save = move;
			}
			break;
		case 4:
			for (Node* turn = head->next; turn->next != NULL; turn = turn->next) {
				for (move = head->next; move->next != save; move = move->next) {
					if (move->student.score.chinese < move->next->student.score.chinese) {
						Stu temp = move->student;
						move->student = move->next->student;
						move->next->student = temp;
					}
				}
				save = move;
			}
			break;
		case 5:
			for (Node* turn = head->next; turn->next != NULL; turn = turn->next) {
				for (move = head->next; move->next != save; move = move->next) {
					if (strcmp(move->student.name, move->next->student.name) < 0) {
						Stu temp = move->student;
						move->student = move->next->student;
						move->next->student = temp;
					}
				}
				save = move;
			}
			break;
		case 6:
			for (Node* turn = head->next; turn->next != NULL; turn = turn->next) {
				for (move = head->next; move->next != save; move = move->next) {
					if (strcmp(move->student.mclass, move->next->student.mclass) < 0) {
						Stu temp = move->student;
						move->student = move->next->student;
						move->next->student = temp;
					}
				}
				save = move;
			}
			break;
		default:
			printf("无此服务，将返回菜单\n");
			system("pause");
			break;
		}
		fileNode(head);
		printfStdent(head);
		return;
}

//老师修改密码
void trevisemypassword(mNode* mhead, char*Account) {

	mNode* move = mhead->next;
	while (move != NULL) {
		if (!strcmp(move->man.account,Account)) {

			printf("请输入新密码:\n");
			scanf("%10s", move->man.password);
			scanf("%*[^\n]%*c");

			mfileNode(mhead);
			printf("修改成功\n");

			system("pause");
			return;
		}
		move = move->next;
	}
	printf("未找到老师\n");
	system("pause");
}

//void sortStudent(Node* head){}
//void Menu()
//{
//}
// 
//指定插入
void insertStudent(Node* head, int position) {
	Node* pre = (Node*)malloc(sizeof(Node));
	pre->next = NULL;

	// 暂存
	printf("请输入班级：\n");
	scanf("%63s", pre->student.mclass);
	scanf("%*[^\n]%*c");

	printf("请输入学号和姓名：\n");
	scanf("%d %19s", &pre->student.num, pre->student.name);
	scanf("%*[^\n]%*c");

	Node* cur = head;
	int count = 0;

	while (cur->next != NULL && count < position - 1) {
		cur = cur->next;
		count++;
	}

	if (count < position - 1) {
		printf("指定位置超出链表长度，无法插入。\n");
		free(pre);
		return;
	}

	pre->next = cur->next;
	cur->next = pre;

	printf("数据成功插入到位置 %d。\n", position);

	fileNode(head);
	system("pause");
}

