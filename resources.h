﻿#include "common.h"
class CEdge{
private:
	int tail, head;
	int weight, capacity;
public:
	CEdge(int a, int b, int c, int d);
	CEdge(int a, int b, int c);
	CEdge(CEdge &x);
	int getHead(){return head;}
	int getTail(){return tail;}
	int getWeight(){return weight;}
	int getCap(){return capacity;}
	bool operator<(CEdge& x){
		if(weight<x.weight)
			return 1;
		else 
			return 0;
	}
};

class CGraph{
private:
	int numVertex;
	int numEdge;
	list<CEdge*> IncidentList;//图的所有边组成的链表
public:
	set<int> S;
	set<int> V;
	int d[N+10];
	int p[N+10];
	//p1  一个map，其中元素是度数和顶点编号构成的pair。按照度数的降序排列。
	map<int,int> degree_vertex;
	multimap<int,int> degree_vertex2;
	//p2  邻接链表
	map<int,list<int>> adjlist;
	//p3  邻接矩阵
	vector<vector<CEdge*>> adjmatrix;
	//p4  给定一个顶点，求一个list，该list中存储了与该顶点关联的所有边
	map<int,list<CEdge*>> nelist;
	
	CGraph(char* inputFile);
	CGraph(list<CEdge*> listEdge);
	CGraph(CGraph &);
	int getNumVertex(){
		return numVertex;
	}
	int getNumEdge(){
		return numEdge;
	}
	int cmp(const pair<int,int> &x, const pair<int, int> &y){
		return x.second > y.second;
	}
	void p1(){
		list<CEdge*>::iterator it,iend;
		multimap<int,int>::iterator it2;
		iend=IncidentList.end();
		vector<pair<int,int>> dv_vec;
		for(int i=1;i<=N;i++)
			degree_vertex[i]=0;
		for(it=IncidentList.begin();it!=iend;it++)
			degree_vertex[(*it)->getTail()]++;
		for(int i=1;i<=N;i++)
			degree_vertex2.insert(pair<int,int>(degree_vertex[i],i));
		it2=--degree_vertex2.end();
		printf("project 1:\n");
		for(;it2!=degree_vertex2.begin();it2--)
			printf("%d,%d\n",it2->second,it2->first);
	}

	void p2(){
		list<CEdge*>::iterator it,iend;
		list<int>::iterator it2,iend2;
		iend=IncidentList.end();
		//printf("incidentList:\n");
		for(it=IncidentList.begin();it!=iend;it++){
			adjlist[(*it)->getTail()].push_back((*it)->getHead());
			//printf("%d,%d\n",(*it)->getTail(),(*it)->getHead());
		}
		it2=adjlist[3].begin();
		iend2=adjlist[3].end();
		printf("\n");
		printf("project 2:\n");
		printf("3:");
		for(;it2!=iend2;it2++)
			printf("%d ",*it2);
	}

	void p3(){
		list<CEdge*>::iterator it,iend;
		iend=IncidentList.end();
		CEdge* emptyedge=new CEdge(-1,-1,-1,-1);
		for(int i=0;i<=numVertex;i++)
		{
			vector<CEdge*> vec;
			for(int j=0;j<=numVertex;j++)
			{
				vec.push_back(emptyedge);
			}
			adjmatrix.push_back(vec);
		}
		for(it=IncidentList.begin();it!=iend;it++){
			//CEdge* e = new CEdge((*it)->getTail(),(*it)->getHead(),(*it)->getWeight(),(*it)->getCap());
			adjmatrix[(*it)->getTail()][(*it)->getHead()] = *it ;
		}
		printf("\n");
		printf("project 3:\n");
		printf("%d,%d",adjmatrix[2][3]->getTail(),adjmatrix[2][3]->getHead());
	}

	void p4(){
		list<CEdge*>::iterator it,iend;
		
		iend=IncidentList.end();
		for(it=IncidentList.begin();it!=iend;it++){
			nelist[(*it)->getTail()].push_back(*it);
		}
		printf("\n");
		printf("project 4:\n");
		list<CEdge*>::iterator it2,iend2;
		iend2=nelist[3].end();
		for(it2=nelist[3].begin();it2!=iend2;it2++)
			printf("%d %d\n",(*it2)->getTail(),(*it2)->getHead());
	}
	
	void Update(int i){
		list<CEdge*>::iterator it,iend;
		it=nelist[i].begin();
		iend=nelist[i].end();
		for(;it!=iend;it++)
			if((*it)->getWeight()+d[i]<d[(*it)->getHead()]){
				d[(*it)->getHead()]=(*it)->getWeight()+d[i];
				p[(*it)->getHead()]=i;
			}
	}

	int FindMin(){
		set<int>::iterator vi,vend;
		vend=V.end();
		int mini=10000000;
		int loc=0;
		for(vi=V.begin();vi!=vend;vi++)
			if(mini>=d[*vi])
				{mini=d[*vi];loc=*vi;}
		return loc;
	}

	void DijkstraAlg(CGraph &g,int s){
		int i,j;
		for(i=1;i<=N;i++)
			V.insert(i);
		for(i=1;i<=N;i++)
			{d[i]=INF;p[i]=-2;}
		S.insert(s);
		V.erase(s);
		d[s]=0;
		p[s]=-1;
		Update(s);
		while (V.size()!=0){
			j=FindMin();
			S.insert(j);
			V.erase(j);
			Update(j);
					}
		printf("\n 1->8:%d\n",d[153]);
	}
};