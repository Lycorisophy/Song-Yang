#include <stdio.h>
#include <stdlib.h>
typedef struct ArcNode {
 int adjvex; // �û���ָ��Ķ����λ��
 struct ArcNode *nextarc; // ָ����һ������ָ��
 char alpha; 
 int *info; // �û������Ϣ��ָ��
}ArcNode;
typedef struct VNode {
 int data; // ������Ϣ
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
 printf("������DFA�������:");
 scanf("%d",&g.vexnum);
 while(g.vexnum>50){
  
  printf("\n������DFA�������:");
  scanf("%d",&g.vexnum);
 }
 i=g.vexnum*(g.vexnum-1);
 printf("������DFA������:");
 scanf("%d",&g.arcnum); 
 while(g.arcnum>i){
 
  printf("\n������DFA��������");
  scanf("%d",&g.arcnum);
 }
 getchar();
 printf("�������������(��һ��Ϊ��̬�����һ��Ϊ��̬):");
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
 
  t1:printf("�������%d���������,�������յ�(�ö��ŷָ�,�������ΪСд��ĸ)��",k+1); 
       scanf("%d,%c,%d",&v1,&alpha,&v2);
		if(start==v2 or end==v1)
		{
		printf("�������,��̬���ܳ�������ߣ���̬���ܳ������ұ�\n");
		goto t1;
		}  
  i=locateALG(g,v1);
  j=locateALG(g,v2);
  if(i<0||j<0||i==j||(g.vexnum<0)){
   
   k--;
   continue;
  }
  p=(ArcNode*)malloc(sizeof(ArcNode));//�������
  if(!p) return -1;
 
  p->adjvex=j;
  p->nextarc=g.vertices[i].firstarc;//����i������
  p->alpha=alpha;
  g.vertices[i].firstarc=p;//��ӵ������ 
 
 }
 printf("����ͼ���ڽӱ����ɹ�\n");
 return 1;
}
void printGra(ALGraph G){
 ArcNode *p;
 int i=0;
  printf("ͼ����%d�����㣬%d������\n",G.vexnum,G.arcnum);
  printf("��̬Ϊ:%d,��̬Ϊ:%d\n",G.vertices[0].data,G.vertices[G.vexnum-1].data);
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
	printf("  1.����DFA\n");
	printf("  2.��ʾDFA\n");
	printf("  3.ɾ��DFA\n");
	printf("  4.����DFAΪ TXT�ļ�\n");
	printf("  5.�˳�\n");
	printf("*****************\n");	
	printf("��ѡ��");
	scanf("%i",&cho);
	return cho;
}
void fprintGra(ALGraph G,FILE *wc){
 ArcNode *p;
 int i=0;
  fprintf(wc,"ͼ����%d�����㣬%d������\n",G.vexnum,G.arcnum);
  fprintf(wc,"��̬Ϊ:%d,��̬Ϊ:%d\n",G.vertices[0].data,G.vertices[G.vexnum-1].data);
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
int cho=printmenu();//�˵����� 
switch(cho)
{
case 1:CreateADG(g);// ����DFA 
break;
case 2:printGra(g);	//��ʾDFA 
break;
case 3:g.vexnum=0;//��0 
g.arcnum=0; 
g.alpha=NULL;
printf("ɾ���ɹ�\n");
break;
case 4:	
	printf(" �ļ�����ΪDFA.txt\n");
	FILE *wc =fopen("DFA.txt","w");
	if(wc==NULL) {
        printf("��ʧ��\n");
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