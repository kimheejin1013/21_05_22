#include "stdafx.h"
#include "TimerManager.h"

#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>

TimerManager::TimerManager()
	: m_CurrentTime(0), m_FPSFrameCount(0), m_FPSTimeElapsed(0), m_FrameRate(0),
	  m_TimeElapsed(0), m_WorldTime(0)
{
	//	고오오오오오급 타이머
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&m_PreroidTime)) {
		m_IsHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&m_LastTime);
		m_TimeScale = 1.0f / m_PreroidTime;
	}
	else {
		m_IsHardware = false;
		m_LastTime = timeGetTime();
		m_TimeScale = 0.001f;
	}
}

void TimerManager::UpdateTime(float frameLock)
{
	if (m_IsHardware) QueryPerformanceCounter((LARGE_INTEGER*)&m_CurrentTime);
	else m_CurrentTime = timeGetTime();

	m_TimeElapsed = (m_CurrentTime - m_LastTime) * m_TimeScale;

	//	VSync
	if (frameLock > 0.0f) {
		while (m_TimeElapsed < (1.0f / frameLock)) {
			if (m_IsHardware) QueryPerformanceCounter((LARGE_INTEGER*)&m_CurrentTime);
			else m_CurrentTime = timeGetTime();

			m_TimeElapsed = (m_CurrentTime - m_LastTime) * m_TimeScale;
		}
	}

	m_LastTime = m_CurrentTime;
	m_FPSFrameCount++;
	m_FPSTimeElapsed += m_TimeElapsed;
	m_WorldTime += m_TimeElapsed;

	if (m_FPSTimeElapsed > 1.0f)
	{
		m_FrameRate = m_FPSFrameCount;
		m_FPSFrameCount = 0;
		m_FPSTimeElapsed = 0.0f;
	}
}

void TimerManager::DrawFPSTime()
{
	WCHAR str[256] = { 0, };
	static TCHAR TimeTextdStrings[] = L"WorldTime : %.2f\nFrameCount : %f\nFPS : %d";

	//	유니코드를 기반으로 한다면 wsprintf 를 사용해야하나, 이건 float 형식을 지원 안함
	//	그래서 float 형식을 사용하려면 _stprintf_s() 를 사용한다 (_s 가 붙으면  safety)
	_stprintf_s(str, TimeTextdStrings, m_WorldTime, m_TimeElapsed, m_FrameRate);
	_Renderer->DrawFontText(D2D1::RectF(0.0f, 0.0f, 200.0f, 100.0f), str);
}
