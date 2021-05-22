#include "stdafx.h"
#include "Application.h"

Application::Application()
	: Width(1280), Height(720)
{
}

Application::~Application()
{
	DestroyWindow(m_hWnd);
	UnregisterClass(Application::ApplicationName, m_hInstance);
}

HRESULT Application::OnCreate(HINSTANCE hInstance, int CmdShow)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof WNDCLASSEX;
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = Application::ApplicationName;
	wcex.lpszClassName = Application::ApplicationName;
	wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	RegisterClassExW(&wcex);

	m_hInstance = hInstance;
	m_hWnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		Application::ApplicationName,
		Application::ApplicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,	//	항상 윈도우 정 중앙에 띄워준다
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		nullptr,
		nullptr,
		hInstance,
		this);

	if (!m_hWnd) return FALSE;

	RECT rc = { 0, 0, (LONG)Width, (LONG)Height };
	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - Width) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - Height) / 2;

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	MoveWindow(m_hWnd, centerX, centerY,
		rc.right - rc.left,
		rc.bottom - rc.top, TRUE);

	ShowWindow(m_hWnd, CmdShow);
	UpdateWindow(m_hWnd);

	return S_OK;
}

LRESULT Application::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_SIZE:
		{

		}
		break;

		case WM_CLOSE: case WM_QUIT:
		{
			PostQuitMessage(0);
			break;
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
