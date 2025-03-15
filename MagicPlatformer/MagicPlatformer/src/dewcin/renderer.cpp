#include "renderer.h"

namespace dewcin
{
	void Renderer::SetTransformedPixel(int x, int y, const Matrix3x3& transform, const RGBColor& color)
	{
		auto point = transform.transformPoint(static_cast<float>(x), static_cast<float>(y));
		SetPixel(static_cast<int>(point.first), static_cast<int>(point.second), color);
	}
	
	void Renderer::SetPixel(int x, int y, const RGBColor& color)
	{
		BitmapBuffer& buffer = getInstance().buffer;

		// clipping
		if (x < 0 || x >= buffer.width || y < 0 || y >= buffer.height)
			return;

		// convert (u8, u8, u8) rgb color to u32 representation
		uint32_t raw_color = (color.red << 16) | (color.green << 8) | (color.blue << 0);

		uint8_t* row = (uint8_t*)buffer.memory + x * bytes_per_pixel + y * buffer.pitch;
		auto pixel = (uint32_t*)row;
		*pixel = raw_color;
	}

	void Renderer::FillRectangle(const Rect& rect, const RGBColor& color)
	{
		BitmapBuffer& buffer = getInstance().buffer;

		int minX = rect.x;
		int minY = rect.y;
		int maxX = rect.x + rect.width;
		int maxY = rect.y + rect.height;

		// clipping
		if (minX < 0)			  minX = 0;
		if (minY < 0)			  minY = 0;
		if (maxX > buffer.width)  maxX = buffer.width;
		if (maxY > buffer.height) maxY = buffer.height;

		// convert (u8, u8, u8) rgb color to u32 representation
		uint32_t raw_color = (color.red << 16) | (color.green << 8) | (color.blue << 0);

		uint8_t* row = (uint8_t*)buffer.memory + minX * bytes_per_pixel + minY * buffer.pitch;
		for (int y = minY; y < maxY; y++)
		{
			auto pixel = (uint32_t*)row;
			for (int x = minX; x < maxX; x++)
			{
				*pixel++ = raw_color;
			}
			row += buffer.pitch;
		}
	}

	void Renderer::FillTransformedRectangle(const Rect& rect, const Matrix3x3& transform, const RGBColor& color)
	{
		// Compute center of the rectangle
		int cx = rect.x + rect.width / 2;
		int cy = rect.y + rect.height / 2;
		
		// Transform each corner around the center
		auto topLeft = transform.transformPoint(static_cast<float>(rect.x - cx), static_cast<float>(rect.y - cy));
		auto topRight = transform.transformPoint(static_cast<float>(rect.x + rect.width - cx), static_cast<float>(rect.y - cy));
		auto bottomLeft = transform.transformPoint(static_cast<float>(rect.x - cx), static_cast<float>(rect.y + rect.height - cy));
		auto bottomRight = transform.transformPoint(static_cast<float>(rect.x + rect.width - cx), static_cast<float>(rect.y + rect.height - cy));
		
		// Translate back to original center
		topLeft.first += static_cast<float>(cx); topLeft.second += static_cast<float>(cy);
		topRight.first += static_cast<float>(cx); topRight.second += static_cast<float>(cy);
		bottomLeft.first += static_cast<float>(cx); bottomLeft.second += static_cast<float>(cy);
		bottomRight.first += static_cast<float>(cx); bottomRight.second += static_cast<float>(cy);

		// Fill the transformed rectangle 
		FillPolygon({ topLeft, topRight, bottomRight, bottomLeft }, color);
	}

	void Renderer::DrawRectangle(const Rect& rect, const RGBColor& color)
	{
		BitmapBuffer& buffer = getInstance().buffer;

		int minX = rect.x;
		int minY = rect.y;
		int maxX = rect.x + rect.width;
		int maxY = rect.y + rect.height;

		// clipping
		if (minX < 0)			  minX = 0;
		if (minY < 0)			  minY = 0;
		if (maxX > buffer.width)  maxX = buffer.width;
		if (maxY > buffer.height) maxY = buffer.height;

		for (int x = minX; x <= maxX; x++)
		{
			SetPixel(x, minY, color);
			SetPixel(x, maxY, color);
		}

		for (int y = minY; y <= maxY; y++)
		{
			SetPixel(minX, y, color);
			SetPixel(maxX, y, color);
		}
	}

	void Renderer::PlotLineLow(int x0, int y0, int x1, int y1, const RGBColor& color)
	{
		int dx = x1 - x0;
		int dy = y1 - y0;
		int yi = 1;
		if (dy < 0)
		{
			yi = -1;
			dy = -dy;
		}
		int D = (2 * dy) - dx;
		int y = y0;

		for (int x = x0; x <= x1; x++)
		{
			SetPixel(x, y, color);
			if (D > 0)
			{
				y = y + yi;
				D = D + (2 * (dy - dx));
			}
			else
			{
				D = D + 2 * dy;
			}
		}
	}

	void Renderer::PlotLineHigh(int x0, int y0, int x1, int y1, const RGBColor& color)
	{
		int dx = x1 - x0;
		int dy = y1 - y0;
		int xi = 1;
		if (dx < 0)
		{
			xi = -1;
			dx = -dx;
		}
		int D = (2 * dx) - dy;
		int x = x0;

		for (int y = y0; y <= y1; y++)
		{
			SetPixel(x, y, color);
			if (D > 0)
			{
				x = x + xi;
				D = D + (2 * (dx - dy));
			}
			else
			{
				D = D + 2 * dx;
			}
		}
	}

	void Renderer::DrawLine(int x0, int y0, int x1, int y1, const RGBColor& color)
	{
		if (abs(y1 - y0) < abs(x1 - x0))
		{
			int startX = x0 > x1 ? x1 : x0;
			int startY = x0 > x1 ? y1 : y0;
			int endX = x0 > x1 ? x0 : x1;
			int endY = x0 > x1 ? y0 : y1;

			PlotLineLow(startX, startY, endX, endY, color);
		}
		else
		{
			int startX = y0 > y1 ? x1 : x0;
			int startY = y0 > y1 ? y1 : y0;
			int endX = y0 > y1 ? x0 : x1;
			int endY = y0 > y1 ? y0 : y1;
			
			PlotLineHigh(startX, startY, endX, endY, color);
		}
	}

	void Renderer::DrawCircle(int radius, int originX, int originY, const RGBColor& color)
	{
		for (int y = -radius; y <= radius; y++)
			for (int x = -radius; x <= radius; x++)
				if (x * x + y * y > radius * radius - radius && x * x + y * y < radius * radius + radius)
					SetPixel(originX + x, originY + y, color);
	}

	void Renderer::FillCircle(int radius, int originX, int originY, const RGBColor& color)
	{
		for (int y = -radius; y <= radius; y++)
			for (int x = -radius; x <= radius; x++)
				if (x * x + y * y < radius * radius + radius)
					SetPixel(originX + x, originY + y, color);
	}

	void Renderer::getWindowDimensions(int* outWidth, int* outHeight)
	{
		RECT clientRect;
		GetClientRect(getInstance().windowHandle, &clientRect);

		*outWidth = clientRect.right - clientRect.left;
		*outHeight = clientRect.bottom - clientRect.top;
	}

	void Renderer::ResizeFrameBuffer(int width, int height)
	{
		BitmapBuffer& buffer = getInstance().buffer;

		if (buffer.memory)
		{
			VirtualFree(buffer.memory, 0, MEM_RELEASE);
		}

		buffer.width = width;
		buffer.height = height;

		buffer.info.bmiHeader.biSize = sizeof(buffer.info.bmiHeader);
		buffer.info.bmiHeader.biWidth = buffer.width;
		buffer.info.bmiHeader.biHeight = -(buffer.height);
		buffer.info.bmiHeader.biPlanes = 1;
		buffer.info.bmiHeader.biBitCount = 32;
		buffer.info.bmiHeader.biCompression = BI_RGB;

		int bufferMemorySize = buffer.width * buffer.height * bytes_per_pixel;
		buffer.memory = VirtualAlloc(nullptr, bufferMemorySize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		buffer.pitch = buffer.width * bytes_per_pixel;
	}

	void Renderer::CopyBufferToWindow(HDC deviceContext, int windowWidth, int windowHeight)
	{
		BitmapBuffer& buffer = getInstance().buffer;

		StretchDIBits(
			deviceContext,
			0, 0, windowWidth, windowHeight,
			0, 0, buffer.width, buffer.height,
			buffer.memory,
			&(buffer.info),
			DIB_RGB_COLORS,
			SRCCOPY
		);
	}

	void Renderer::Clear()
	{
		BitmapBuffer& buffer = getInstance().buffer;

		FillRectangle({ 0, 0, buffer.width, buffer.height }, getInstance().clearColor);
	}

	void Renderer::FillPolygon(const std::vector<std::pair<float, float>>& vertices, const RGBColor& color)
	{
		if (vertices.size() < 3) return; // Not a valid polygon

		// Find the min and max Y values
		float minY = vertices[0].second, maxY = vertices[0].second;
		for (const auto& v : vertices)
		{
			if (v.second < minY) minY = v.second;
			if (v.second > maxY) maxY = v.second;
		}

		// Iterate through scanlines
		for (auto y = static_cast<int>(ceil(minY)); y <= static_cast<int>(floor(maxY)); y++)
		{
			std::vector<float> intersections;

			// Find intersections with each edge
			for (size_t i = 0; i < vertices.size(); i++)
			{
				auto v1 = vertices[i];
				auto v2 = vertices[(i + 1) % vertices.size()]; // Wrap around to first vertex

				// Check if the edge crosses the current scanline
				if ((v1.second <= static_cast<float>(y) && v2.second > static_cast<float>(y)) || 
					(v2.second <= static_cast<float>(y) && v1.second > static_cast<float>(y)))
				{
					// Compute intersection using line equation
					float x = v1.first + (static_cast<float>(y) - v1.second) * (v2.first - v1.first) / (v2.second - v1.second);
					intersections.push_back(x);
				}

			}

			// Sort intersections (they should be in pairs)
			std::sort(intersections.begin(), intersections.end());

			// Fill between pairs of intersections
			for (size_t i = 0; i < intersections.size(); i += 2)
			{
				if (i + 1 >= intersections.size())
				{
					continue;
				}

				auto xStart = static_cast<int>(ceil(intersections[i]));
				auto xEnd = static_cast<int>(floor(intersections[i + 1]));

				for (int x = xStart; x <= xEnd; x++)
				{
					SetPixel(x, y, color);
				}
			}
		}
	}

	void Renderer::DrawTextWithScale(int x, int y, int scale, char c, const RGBColor& color)
	{
		if (c != '0')
			return;
		
		for (int row = 0; row < scale; row++)
		{
			for (int col = 0; col < scale; col++)
			{
				SetPixel(x * scale + col, y * scale + row, color);
			}
		}
	}

	void Renderer::DrawTextOnBitmap(int x, int y, int scale, const char* text, const RGBColor& color)
	{
		int offsetX = 0;
		while (*text)
		{
			auto letter = printableChars[*text - 32];

			// If the scale is 2, it must do the first row twice
			for (int row = 0; row < 7; row++)
			{
				for (int col = 0; col < 5; col++)
				{
					DrawTextWithScale(x + col + offsetX, y + row, scale, static_cast<char>(letter[row][col]), color);
				}
			}

			offsetX += 6;
			text++;
		}
	}
}