#include <stdio.h>
#include <stdlib.h>
typedef struct ArcNode {
 int adjvex; // 该弧所指向的顶点的位置
 struct ArcNode *nextarc; // 指向下一条弧的指针
 char alpha; 
 int *info; // 该弧相关信息的指针
}ArcNode;
typedef struct VNode {
 int data; // 顶点信息
 ArcNode *firstarc; 
}VNode, AdjList[50];
typedef struct {
 AdjList vertices;
 int vexnum, arcnum; 
 char alpha;
}ALGraph;
int locateALG(ALGraph g,int v){
 for(int i=0;i<g.vexnum;i++){
  if(g.vertices[i].data==v)
   return i;
 }
 return -1;
}
int CreateADG(ALGraph &g){
 int i,j,k,l,start,end;
 ArcNode *p;
 int v1,v2;
 int c;
 char alpha;
 printf("请输入DFA的有穷集数:");
 scanf("%d",&g.vexnum);
 while(g.vexnum>50){
  
  printf("\n请输入DFA的有穷集数:");
  scanf("%d",&g.vexnum);
 }
 i=g.vexnum*(g.vexnum-1);
 printf("请输入DFA规则数:");
 scanf("%d",&g.arcnum); 
 while(g.arcnum>i){
 
  printf("\n请输入DFA规则数：");
  scanf("%d",&g.arcnum);
 }
 getchar();
 printf("请依次输入有穷集(第一个为初态，最后一个为终态):");
 for(i=0;i<g.vexnum;i++){
 
  scanf("%d",&c);
  l=locateALG(g,c);
  if(l>=0){
   
   i--;
   continue;
  }
  g.vertices[i].data=c;
  g.vertices[i].firstarc=NULL;
 }
 start=g.vertices[0].data;
 end=g.vertices[g.vexnum-1].data;
 for(k=0;k<g.arcnum;k++){
 
  t1:printf("请输入第%d条弧的起点,符号与终点(用逗号分隔,符号最好为小写字母)：",k+1); 
       scanf("%d,%c,%d",&v1,&alpha,&v2);
		if(start==v2 or end==v1)
		{
		printf("输入错误,终态不能出现在左边，初态不能出现在右边\n");
		goto t1;
		}  
  i=locateALG(g,v1);
  j=locateALG(g,v2);
  if(i<0||j<0||i==j||(g.vexnum<0)){
   
   k--;
   continue;
  }
  p=(ArcNode*)malloc(sizeof(ArcNode));//建立结点
  if(!p) return -1;
 
  p->adjvex=j;
  p->nextarc=g.vertices[i].firstarc;//顶点i的链表
  p->alpha=alpha;
  g.vertices[i].firstarc=p;//添加到最左边 
 
 }
 printf("有向图的邻接表创建成功\n");
 return 1;
}
void printGra(ALGraph G){
 ArcNode *p;
 int i=0;
  printf("图中有%d个顶点，%d条弧：\n",G.vexnum,G.arcnum);
  printf("初态为:%d,终态为:%d\n",G.vertices[0].data,G.vertices[G.vexnum-1].data);
  for(i=0;i<G.vexnum;i++){
   p=G.vertices[i].firstarc;
   printf("%d\t",G.vertices[i].data);
   while(p){
   	G.alpha=p->alpha;
    printf("<%d,%c,%d>",G.vertices[i].data,G.alpha,G.vertices[p->adjvex].data);
    p=p->nextarc; 
   }
   printf("\n");
  }
}
int printmenu(){
	int cho;
	printf("*****************\n");	
	printf("  1.建立DFA\n");
	printf("  2.显示DFA\n");
	printf("  3.删除DFA\n");
	printf("  4.保存DFA为 TXT文件\n");
	printf("  5.退出\n");
	printf("*****************\n");	
	printf("请选择：");
	scanf("%i",&cho);
	return cho;
}
void fprintGra(ALGraph G,FILE *wc){
 ArcNode *p;
 int i=0;
  fprintf(wc,"图中有%d个顶点，%d条弧：\n",G.vexnum,G.arcnum);
  fprintf(wc,"初态为:%d,终态为:%d\n",G.vertices[0].data,G.vertices[G.vexnum-1].data);
  for(i=0;i<G.vexnum;i++){
   p=G.vertices[i].firstarc;
   fprintf(wc,"%d\t",G.vertices[i].data);
   while(p){
   	G.alpha=p->alpha;
    fprintf(wc,"<%d,%c,%d>",G.vertices[i].data,G.alpha,G.vertices[p->adjvex].data);
    p=p->nextarc; 
   }
   fprintf(wc,"\n");
  }
}
int main(void)
{
ALGraph g;
int a;
char str;
g.vexnum=1;
g.arcnum=0; 
g.alpha=NULL;
g.vertices[0].data=0;
while(1){
int cho=printmenu();//菜单函数 
switch(cho)
{
case 1:CreateADG(g);// 建立DFA 
break;
case 2:printGra(g);	//显示DFA 
break;
case 3:g.vexnum=0;//归0 
g.arcnum=0; 
g.alpha=NULL;
printf("删除成功\n");
break;
case 4:	
	printf(" 文件名称为DFA.txt\n");
	FILE *wc =fopen("DFA.txt","w");
	if(wc==NULL) {
        printf("打开失败\n");
        a=1;}
	while(a != 1)
	{
	fprintGra(g,wc);
	 fclose(wc);
	}	
break;
case 5:
return 0;
 default:
   break;
}	
}
return 1;
}