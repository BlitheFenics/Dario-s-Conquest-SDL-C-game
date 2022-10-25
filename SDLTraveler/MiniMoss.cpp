#include "MiniMoss.h"


MiniMoss::MiniMoss()
{
	rSrc = { 0, 15, 16, 18 };
	rDst = { 0,0, 32 ,32 };


	ObjInit();
}


MiniMoss::~MiniMoss()
{
}

void MiniMoss::Update(int offsetX, int offsetY)
{
	if (m_Alive)
	{
		framecount++;
		//baseX += direction;
		if (framecount % 2 == 0)
		{
			if (frame < 2)
			{
				frame++;
			}
			else
			{
				frame = 0;
			}
		}
		rSrc.x = frame * 16;

		baseY = m_onPlat->getY() - rDst.h;

		if (rDst.x >= m_onPlat->getDst().w + m_onPlat->getDst().x - rDst.w)
		{
			m_Flip = SDL_FLIP_NONE;
			m_moveSpeed = -1;
		}

		if (rDst.x <= m_onPlat->getDst().x)
		{
			m_Flip = SDL_FLIP_HORIZONTAL;
			m_moveSpeed = 1;
		}
		baseX += m_moveSpeed;
		Scroll(offsetX, offsetY);
	}
}

void MiniMoss::Render()
{
	// Render shit should go here
}

void MiniMoss::Clean()
{
	// Is this a joke?
}

void MiniMoss::DeSpawn()
{
	rDst.x = -100;
	rDst.y = -100;
	m_Alive = false;
}

void MiniMoss::Spawn(int x, int y, Platform* platform)
{
	m_Alive = true;
	rDst = { x, y, 32, 32 };
	m_onPlat = platform;
	ObjInit();
	/*rDst.x = m_onPlat->GetDst().x - rDst.w;
	*/
	baseY = m_onPlat->getY() - rDst.h;
	
}

void MiniMoss::OnPlat(Platform* platform)
{
	m_onPlat = platform;
}
