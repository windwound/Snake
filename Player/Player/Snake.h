#pragma once
#include "resource.h"
#define  WIDTH 22
#define  HIGTH 22
enum box{
	empty,
	fruit,
	full
};
enum direct{
	left,
	right,
	up,
	down
};
typedef struct Point{
	int X;
	int Y;
	const Point& operator =(const Point& rs){
		X=rs.X;
		Y=rs.Y;
		return *this;
	}
}Point;
typedef struct MPOSITION{
} *POSITION;
class Node{
public:
	//friend class CSnake;
	//friend class desk;
	Node(){
		data.X=0;
		data.Y=0;
		next=NULL;
	}
	Node(int x,int y){
		data.X=x;
		data.Y=y;
		next=NULL;
	};
	~Node(){
		delete next;
	}
public:
	Point data;
	Node* next;
public:
	void show(HWND hwnd){
		CClientDC dc(hwnd);
		CBrush br;
		br.CreateSolidBrush(RGB(0,255,0));
		dc.SelectBrush(br);
		RECT rect={20*(data.X-1),20*(data.Y-1),20*(data.X),20*(data.Y)};
		dc.Rectangle(&rect);
		dc.DrawEdge(&rect,EDGE_RAISED,BF_RECT);
	}
	void hide(HWND hwnd){
	CClientDC dc(hwnd);
	CBrush br;
	br.CreateSolidBrush(RGB(255,255,255));
	RECT rect={20*(data.X-1),20*(data.Y-1),20*(data.X),20*(data.Y)};
	dc.FillRect(&rect,br);
	}
};
class CSnake
{
public:
	friend class desk;
	CSnake(desk* dk);
	~CSnake(void);
private:
	Node* m_head;
	Node* m_tail;
	int m_dirct;
	desk *m_desk;
	int status;
public:
	void go();
	void show(HWND hwnd);
	int eat(int x,int y);
	POSITION getfristpos(){return (POSITION)(m_head->next);}
	Node* getnext(POSITION& pos){
		Node* pNode=(Node*)pos;
		pos=(POSITION)((Node*)pos)->next;
		return pNode;
	}
	void destory(){
		delete m_head;
	}
	

};

class desk{
public:
	desk(HWND hwnd):m_hwnd(hwnd){
		m_snake=NULL;
		init();
	}
	~desk(){
		KillTimer(m_hwnd,1);
	delete m_snake;
	}
private:
	CSnake* m_snake;
	Node  m_fruit;
public:
	HWND m_hwnd;
public:
	box m_block[WIDTH][HIGTH];
	void run(){
		m_snake->show(m_hwnd);
		showfruit();
	}
	void ontimer(){
		m_snake->go();
		
	}
	void onkeydown(int dt){
		m_snake->m_dirct=dt;
		if(m_snake->status)
		     m_snake->go();
	}
	int getdirect(){
		return m_snake->m_dirct;
	}
	void setrowcol(int x,int flag){
		if(flag==0)
			for(int i=0;i<WIDTH;i++)
				m_block[x][i]=full;
		else 
			for(int i=0;i<HIGTH;i++)
				m_block[i][x]=full;
	}
	void genfruit(){
		int x,y;
		do
		{
			x=rand()%20+1;
			y=rand()%20+1;
		}while(m_block[x][y]==full);
		m_block[x][y]=fruit;
		m_fruit.data.X=x;
		m_fruit.data.Y=y;
	}
	void showfruit()
	{
		m_fruit.show(m_hwnd);
	}
	void init()
	{
		memset(m_block,empty,sizeof(m_block));
		setrowcol(0,0);
		setrowcol(21,0);
		setrowcol(0,1);
		setrowcol(21,1);
		if(m_snake)
			m_snake->destory();
		if(m_fruit.data.X!=0)
			m_fruit.hide(m_hwnd);
		 m_snake=new CSnake(this);
		 genfruit();
	}
};