#include "studentsystem.h"

void Students(Node* head, nNode* nhead,char *mclass,int num,char*account, char* name) {
	while (1) {

		system("cls");
		loadStudent(head);

		Menu2();

		int c;
		while (scanf("%d", &c) != 1)
		{
			scanf("%*[^\n]%*c");
			printf("输入非法，请重新输入\n");
			system("pause");
			system("cls");
			loadStudent(head);
			Menu1();
		}
		scanf("%*[^\n]%*c");


		switch (c) {
		case 1://查询
			Studentfind(head, num);
			break;
		case 2://查全班
			Stdentprintf(head,mclass);
			break;
		case 3://分析
			essayStudent(head);
			break;
		case 4://申诉
			GradeAppeals(nhead, mclass, num, account, name);
			break;
		case 5://返回上一层
			return;
			break;
		case 6://修改密保问题
			sreviseconfidential(head,num);
			break;
		case 7://密码改
			srevisemypassword(head,num);
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


void Menu2() {
	printf("---Student Information Management System---\n");
	printf("--           student model\t\t --\n");
	printf("--\t      0.退出 \t\t         --\n");
	printf("--\t      1.成绩查询\t         --\n");
	printf("--\t      2.查询本班成绩\t\t --\n");
	printf("--\t      3.成绩分析 \t\t --\n");
	printf("--\t      4.成绩申诉 \t\t --\n");
	printf("--\t      5.返回上一层 \t         --\n");
	printf("--\t      6.修改密保问题\t\t --\n");
	printf("--\t      7.修改我的密码\t\t --\n");
	printf("-------------------------------------------\n");
}

void Studentfind(Node* head,int Num) {//查询信息
	Node* move = head;
	while (move != NULL) {
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

void Stdentprintf(Node* head,char*mclass) {
	if (head->next == NULL) {
		printf("暂无学生\n");
		system("pause");
		return;
	}
	int a = 0;
	Node* move = head->next;

	while (move != NULL) {

		if(!strcmp(move->student.mclass,mclass)){
			a++;
			printf("学生%d:\n\n", a);

			printf("学号：%-10d\t 班级：%-10s\t 姓名：%-10s\t \n", move->student.num, move->student.mclass, move->student.name);
			Sleep(100);
			printf("数学: %-10d\t 英语: %-10d\t 语文：%-10d\t\n", move->student.score.match, move->student.score.english, move->student.score.chinese);
			Sleep(100);
			printf("------------------------------------------------------------\n");
			Sleep(100);
		}
		move = move->next;
	}
	system("pause");
}

//修改密保
void sreviseconfidential(Node* head, int Num) {

	Node* move = head->next;
	while (move != NULL) {
		if (move->student.num == Num) {
			printf("------------------------------------------------------------\n");
			printf("原密保问题：%s\n",move->student.question);
			printf("原密保答案：%s\n", move->student.answer);
			printf("------------------------------------------------------------\n");
			printf("请输入密保问题：\n");
			scanf("%100s", move->student.question);
			scanf("%*[^\n]%*c");

			printf("请输入密保答案:\n");
			scanf("%100s", move->student.answer);
			scanf("%*[^\n]%*c");

			fileNode(head);
			printf("修改成功\n");

			system("pause");
			return;
		}
		move = move->next;
	}
	printf("未找到学生\n");
	system("pause");
}

//修改密码
void srevisemypassword(Node* head, int Num) {

	Node* move = head->next;
	while (move != NULL) {
		if (move->student.num == Num) {

			printf("请输入新密码:\n");
			scanf("%10s", move->student.password);
			scanf("%*[^\n]%*c");

			fileNode(head);
			printf("修改成功\n");

			system("pause");
			return;
		}
		move = move->next;
	}
	printf("未找到学生\n");
	system("pause");
}