#include "MossBoss.h"


MossBoss* MossBoss::mossy;

MossBoss* MossBoss::GetMossy()
{
	if (mossy == nullptr)
	{
		mossy = new MossBoss;
	}
	return mossy;
}