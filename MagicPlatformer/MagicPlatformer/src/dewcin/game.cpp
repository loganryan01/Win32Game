#include "game.h"

#include "renderer.h"

#include "input.h"

namespace dewcin
{
	Game::Game()
	{
		// Init window properties to default values
		windowTitle = L"Magic Platformer";
		windowWidth = 1280;
		windowHeight = 720;
	}

	// Handles window events
	LRESULT CALLBACK WindowCallback(
		HWND windowHandle,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	)
	{
		LRESULT result = 0;

		switch (message)
		{
			case WM_CLOSE:
			{
				Game::getInstance().running = false;
				OutputDebugString(L"window close\n");
			}
			break;

			case WM_DESTROY:
			{
				Game::getInstance().running = false;
				OutputDebugString(L"window destroy\n");
			}
			break;

			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
			case WM_KEYDOWN:
			case WM_KEYUP:
			{
				auto VKCode = static_cast<uint32_t>(wParam);

				bool wasDown = (lParam & (1 << 30)) != 0;
				bool isDown = (lParam & (1 << 31)) == 0;

				Input::ProcessKeyboardInput(VKCode, wasDown, isDown);
			}
			break;

			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_MBUTTONDOWN:
			case WM_MBUTTONUP:
			case WM_XBUTTONDOWN:
			case WM_XBUTTONUP:
			{
				Input::ProcessMouseInput(wParam, lParam);
			}
			break;

			case WM_MOUSEMOVE:
			{
				Input::UpdateMousePosition(lParam);
			}
			break;

			case WM_PAINT:
			{
				OutputDebugString(L"window paint\n");

				PAINTSTRUCT paint;
				HDC device_context = BeginPaint(windowHandle, &paint);

				int width, height;
				Renderer::getWindowDimensions(&width, &height);

				Renderer::CopyBufferToWindow(device_context, width, height);

				EndPaint(windowHandle, &paint);
			}
			break;

			default:
				result = DefWindowProc(windowHandle, message, wParam, lParam);
		}

		return result;
	}

	void Game::StopWindow()
	{
		running = false;
	}

	void Game::StartWindow()
	{
		Renderer::ResizeFrameBuffer(windowWidth, windowHeight);
		
		const wchar_t* className = L"dewcin_window";

		WNDCLASS windowClass = {};

		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = WindowCallback;
		windowClass.hInstance = hInstance;
		windowClass.lpszClassName = className;

		if (!RegisterClass(&windowClass))
		{
			OutputDebugString(L"Failed to register window class\n");
			return;
		}

		DWORD windowStyle = WS_MAXIMIZEBOX | WS_SYSMENU | WS_CAPTION;

		RECT windowRect = {};
		windowRect.left = 0;
		windowRect.top = 0;
		windowRect.right = windowWidth;
		windowRect.bottom = windowHeight;

		AdjustWindowRect(&windowRect, windowStyle, false);

		windowHandle = CreateWindowEx(
			0,
			className,
			windowTitle.c_str(),
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top,
			nullptr,
			nullptr,
			hInstance,
			nullptr
		);

		if (!windowHandle)
		{
			OutputDebugString(L"Failed to create a window\n");
			return;
		}

		OutputDebugString(L"GAME INIT\n");
		running = true;

		Renderer::setWindowHandle(windowHandle);

		// Init the clock
		LARGE_INTEGER cpu_frequency;
		QueryPerformanceFrequency(&cpu_frequency);

		LARGE_INTEGER last_counter;
		QueryPerformanceCounter(&last_counter);

		while (running)
		{
			LARGE_INTEGER current_counter;
			QueryPerformanceCounter(&current_counter);

			int64_t counter_elapsed = current_counter.QuadPart - last_counter.QuadPart;

			float delta = (float)counter_elapsed / (float)cpu_frequency.QuadPart; // in seconds

			last_counter = current_counter;

			// Process windows messages
			MSG message;
			while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
			{
				if (message.message == WM_QUIT)
					running = false;

				TranslateMessage(&message);
				DispatchMessage(&message); // Send message to the WindowProc (WindowCallback)
			}

			// Update & render

			Renderer::Clear();

			getInstance().update(delta);

			HDC deviceContext = GetDC(windowHandle);

			int width, height;
			Renderer::getWindowDimensions(&width, &height);

			Renderer::CopyBufferToWindow(deviceContext, width, height);

			ReleaseDC(windowHandle, deviceContext);
		}
	}
}