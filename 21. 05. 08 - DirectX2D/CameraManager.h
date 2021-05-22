#pragma once

class CameraManager : public BaseSingleton<CameraManager>
{
public:
	CameraManager();
	~CameraManager();

	float X;
	float Y;
};

#define _Camera CameraManager::Get()
