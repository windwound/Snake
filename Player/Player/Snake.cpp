#include "StdAfx.h"
#include "Snake.h"
//HBITMAP ht;
CSnake::CSnake(desk* dk)
{
	m_desk=dk;
	m_dirct=right;
	status=1;
	Node *pt,*ptmp;
	for(int i=0;i<5;i++)
	{
		pt=new Node;
		pt->data.X=8+i;
		pt->data.Y=10;
		m_desk->m_block[pt->data.X][pt->data.Y]=full;
		if(i==0)
		{
			//pt->next=NULL;
			m_head=pt;
		}
		else
		{
			//pt->next=ptmp;
			ptmp->next=pt;
		}
		ptmp=pt;
	}
	//m_head=pt;
	pt->next=NULL;
	m_tail=pt;
}

CSnake::~CSnake(void)
{
	destory();
}
void CSnake::go(){
	Node *tmp,hd;
	hd.data=m_head->data;
	int ax,ay;
    ax=m_tail->data.X;
	ay=m_tail->data.Y;
	if(m_dirct==right)
		ax++;
	else if(m_dirct==left)
		ax--;
	else if(m_dirct==up)
		ay--;
	else if(m_dirct==down)
		ay++;
	if(fruit==eat(ax,ay)) return;
	if(m_desk->m_block[ax][ay]==full)
	{ 
		KillTimer(m_desk->m_hwnd,1);
		status=0;
		MessageBeep(MB_OK);
		if(IDYES==MessageBox(m_desk->m_hwnd,_T("Game Over!Try Again?"),_T("Snake"),MB_YESNO))
		{
			m_desk->init();
			::InvalidateRect(m_desk->m_hwnd,NULL,TRUE);
			SetTimer(m_desk->m_hwnd,1,200,NULL);
		}
		return;
	}
	for(tmp=m_head;tmp->next!=NULL;tmp=tmp->next)
	{
		tmp->data=tmp->next->data;
	}
	m_tail->data.X=ax;
	m_tail->data.Y=ay;
	hd.hide(m_desk->m_hwnd);
	m_tail->show(m_desk->m_hwnd);
	m_desk->m_block[hd.data.X][hd.data.Y]=empty;
	m_desk->m_block[m_tail->data.X][m_tail->data.Y]=full;
}
int CSnake::eat(int x,int y){
	box rt;
	if((rt=m_desk->m_block[x][y])==fruit)
	{
		Node* pNode=new Node(x,y);
		m_tail->next=pNode;
		m_tail=pNode;
		pNode->show(m_desk->m_hwnd);
		m_desk->m_block[m_tail->data.X][m_tail->data.Y]=full;
		m_desk->genfruit();
		m_desk->showfruit();
	}
	return rt;
}
void CSnake::show(HWND hwnd){
	for(Node* tmp=m_head;tmp!=NULL;tmp=tmp->next)
	{
		tmp->show(hwnd);
	}
}