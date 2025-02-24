#pragma once

#include <Windows.h>

#include <stdint.h>

namespace dewcin
{
	struct RGBColor
	{
		uint8_t red, green, blue;
	};

	struct Rect
	{
		int x, y, width, height;
	};

	class Renderer
	{
		friend LRESULT CALLBACK WindowCallback(
			HWND windowHandle,
			UINT message,
			WPARAM wParam,
			LPARAM lParam
		);

		friend class Game;

		struct BitmapBuffer
		{
			int width, height;
			BITMAPINFO info;
			void* memory;
			int pitch; // in bytes
		};

	private:
		static const int bytes_per_pixel = 4;

		HWND windowHandle = nullptr;
		BitmapBuffer buffer = {};
		RGBColor clearColor = { 255, 255, 255 };

	public:
		inline static void SetClearColor(const RGBColor& color) { getInstance().clearColor = color; }

		static void SetPixel(int x, int y, const RGBColor& color);

		static void FillRectangle(const Rect& rect, const RGBColor& color);

		static void DrawRectangle(const Rect& rect, const RGBColor& color);

		static void DrawLine(int x0, int y0, int x1, int y1, const RGBColor& color);

		static void DrawCircle(int radius, int originX, int originY, const RGBColor& color);

		static void FillCircle(int radius, int originX, int originY, const RGBColor& color);

	private:
		Renderer() = default;

		Renderer(const Renderer&) = delete;
		Renderer& operator= (const Renderer&) = delete;

		~Renderer() = default;

		inline static Renderer& getInstance()
		{
			static Renderer renderer;
			return renderer;
		}

	private:
		inline static void setWindowHandle(HWND _windowHandle) { getInstance().windowHandle = _windowHandle; }

		static void getWindowDimensions(int* outWidth, int* outHeight);

		static void ResizeFrameBuffer(int width, int height);

		static void CopyBufferToWindow(HDC deviceContext, int windowWidth, int windowHeight);

		static void Clear();

		static void PlotLineLow(int x0, int y0, int x1, int y1, const RGBColor& color);
		static void PlotLineHigh(int x0, int y0, int x1, int y1, const RGBColor& color);
	};
}