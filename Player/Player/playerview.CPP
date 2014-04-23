#include "StdAfx.h"
#include "PlayerView.h"



LRESULT CPlayerView::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	delete image;
	KillTimer(1);
	delete m_desk;
	
	return 0;
}

LRESULT CPlayerView::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int dt=m_desk->getdirect();
  if(wParam==VK_UP&&dt!=down)
  {  
	  m_desk->onkeydown(up);
  }
 else if(wParam==VK_DOWN&&dt!=up)
  {  
	  m_desk->onkeydown(down);
  }
 else if(wParam==VK_LEFT&&dt!=right)
  {  
	  m_desk->onkeydown(left);
  }
  else if(wParam==VK_RIGHT&&dt!=left)
  {  
	  m_desk->onkeydown(right);
  }
  else if(wParam==VK_SPACE)
  {  
	  if(flag==1)
	  { 
		  KillTimer(1);
			flag=0;
	  }
	  else
	  {
		  SetTimer(1,200,NULL);
		  flag=1;
	  }
	 
  }
	return 0;
}

LRESULT CPlayerView::OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_desk->ontimer();
	return 0;
}

