#ifndef _STAGE_LOAD_H_
#define _STAGE_LOAD_H_

#include <atomic>
#include <thread>

class StageLoad : public Stage
{
public:
	void Init();
	void Release();
	void LoadWork();

private:

	void UpdateProgressValue(int val);

	std::atomic_int32_t m_nLoadPersent;
};

#endif // !_STAGE_LOAD_H_
