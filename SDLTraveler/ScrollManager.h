#pragma once
#include <cmath>

class ScrollManager
{
private:
	static ScrollManager* Scroller;
	ScrollManager();

	int offSetX = 0;
	int offSetY = 0;

	int limitLeft = 400;
	int limitRight = 0;

	int limitTop = 200;
	int limitBottom = 0;

	int shakeTimer = 0; // Used for screen shake
	int shakeOffset = 20; // Pixels of screen offset
	bool shakeDirection;
	bool shaking = false;


public:
	static ScrollManager* GetScroll();

	void SetPrescroll(int x, int y)
	{
		offSetX = x;
		offSetY = y;
	}

	void CheckBoundary() // this is to check that the setprescroll doesn't go too far.
	{
		if (offSetY > limitBottom - 500)
		{
			offSetY = limitBottom - 500;
		}
	}

	void Reset()
	{
		offSetX = 0;
		offSetY = 0;
	}

	int OffX()
	{
		return offSetX;
	}


	void SetLimits(int l)
	{
		limitRight = l - 400;
	}

	void SetLimits(int l, int b)
	{
		limitRight = l - 400;
		limitBottom = b - 200;
	}


	int GetLimitB()
	{
		return limitBottom;
	}

	int GetLimitL()
	{
		return limitLeft;
	}

	int GetLimitR()
	{
		return limitRight;
	}

	int OffY()
	{
		return offSetY;
	}

	void Scroll(int x, int y)
	{
		offSetX += x;
		offSetY += y;
	}
	void SetShake(bool shake) { shaking = shake; }
	bool GetShake() { return shaking; }
	// This is the juicy screen shake
	void ScreenShake()
	{
		shakeTimer+=60;

		offSetX += 5 * sin(shakeTimer * 3.141592654 / 180);

		if(shakeTimer > 250)
		{
			shakeTimer = 0;
			shaking = false;
		}
		/**		for (int i = 0; i < 200; i++)
		{
			if (shakeDirection == true)
			{
				if (shaking == true)
				{
					offSetX += shakeOffset;
					shakeDirection = false;
				}
				else
				{
					offSetX -= shakeOffset;
					shakeDirection = true;
				}
			}
		}
		shaking = false;
		*/
	}

	~ScrollManager();
};

