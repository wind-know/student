#pragma once
#include <stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<Windows.h>
#define _CRT_SECURE_NO_WARNINGS 

//学生
typedef struct grade {
	int match;
	int english;
	int chinese;
}GRA;
typedef struct Student {
	char account[11];
	char password[11];
	char mclass[64];
	int num;
	char name[20];
	char question[101];
	char answer[101];
	GRA score;
}Stu;
typedef struct _Node {
	Stu student;
	struct _Node* next;
}Node;
//老师＋管理
typedef struct Manage {
	char account[11];
	char password[11];
	char mclass[64];
	char name[20];
	char question[101];
	char answer[101];
}Man;
typedef struct mNode {
	Man man;
	struct mNode* next;
}mNode;

//查看代办
typedef struct Confidential {
	char account[11];
	int num;
	char mclass[64];
	char name[20];

	int chose;
	int over;

	char phonenum[101];

	int icomplaint[7];
	char ccomplaint[1000];

	char newPassword[11];
}Con;
typedef struct nNode {
	Con con;
	struct nNode* next;
}nNode;

//con
void nfileNode(nNode* nhead);

void nloadStudent(nNode* nhead);

void sreviseconfidential(Node* head, int Num);
void treviseconfidential(mNode* mhead, char* account);

void spassWordrevise(nNode* nhead, Node* head);
void dospassWordrevise(Node* head, char* account, char* newpassword);
void tpassWordrevise(nNode* nhead, mNode* mhead);
void dotpassWordrevise(mNode* mhead, char* account, char* newpassword);
void passWordrevise(Node* head, mNode* mhead, nNode* nhead);
void readpassWordrevise(nNode* nhead, Node* head, mNode* mhead);

void passWordretrieval(nNode* nhead, Node* head, mNode* mhead);
void spassWordretrieval(nNode* nhead, Node* head);
void readpassWordretrieval(nNode* nhead);
void tpassWordretrieval(nNode* nhead, mNode* mhead);

void Update(nNode* nhead, char* account, char* mclass, char* name);
void readUpdate(nNode* nhead);


void readGradeAppeals(nNode* nhead, Node* head);
void GradeAppeals(nNode* nhead, char* mclass, int num, char* account, char* name);
void doGradeAppeals(Node* head, int match, int english, int chinese, char* account);



//teacher
void Teachers(Node* head, nNode* nhead, mNode* mhead, char* account, char* mclass, char* name);

void Menu1();

void inputStudent(Node* head);

void printfStdent(Node* head);

void deleteStudent(Node* head);

void findStudent(Node* head);
void afindStudent(Node* head);
void nfindStudent(Node* head);
void mfindStudent(Node* head);

void fileNode(Node* head);
void tfileNode(Node* head);
void loadStudent(Node* head);

void reviseStudent(Node* head);
void asortStudent(Node* head);
void jsortStudent(Node* head);
void ssortStudent(Node* head);

void trevisemypassword(mNode* mhead, char* Account);
void Clean();
//student
void Menu2();

void Studentfind(Node* head, int Num);

void Stdentprintf(Node* head, char* mclass);

void Students(Node* head, nNode* nhead, char* mclass, int num, char* account, char* name);

void essayStudent(Node* head);
void srevisemypassword(Node* head, int Num);

//pass
void helpMenu();

void passing(Node* head, nNode* nhead, mNode* mhead);

void PASS(Node* head, nNode* nhead, mNode* mhead);

void passMenu();

void Initialization(mNode* mhead);

void helping(Node* head, nNode* nhead, mNode* mhead);

void ndeleteStudent(nNode* nhead, char* Account);

void ndelete(nNode* nhead, char* account);

//man
void mfileNode(mNode* head);

void mloadStudent(mNode* head);

void mMenu();

void Manager(Node* head, nNode* nhead, mNode* mhead,char*account);

void ainputAccount(mNode* mhead, Node* head);
void minputAccount(mNode* mhead);
void sinputAccount(Node* head);

void adeleteAccount(mNode* mhead, Node* head);
void mdeleteAccount(mNode* mhead);
void sdeleteAccount(Node* head);


void areviseAccount(mNode* mhead, Node* head);
void mreviseAccount(mNode* mhead);
void sreviseAccount(Node* head);


void afindAccount(mNode* mhead, Node* head);
void mfindAccount(mNode* mhead);
void sfindAccount(Node* head);

void sprintfStdent(Node* head);
void mprintfStdent(mNode* mhead);

void Viewagency(Node* head, mNode* mhead, nNode* nhead);
void agencyMenu();