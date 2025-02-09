#pragma once
#include "Matrix3x3.h"

class Camera
{
public:
	static void SetPosition(Vector2 pos) { m_pos = pos; }
	static void SetScale(Vector2 scale) { m_scale = scale; }
	static void SetRotation(float theta) { m_theta = theta; }
	static void SetWindowSize(UINT windowW, UINT windowH) {
		m_windowH = windowH;
		m_windowW = windowW;
	}
	static Vector2 CameraTransform(Vector2 pos, Vector2 localSpace) {
		const float W = static_cast<float>(m_windowW);
		const float H = static_cast<float>(m_windowH);
		const float left = -(W / 2.0f);
		const float top = H / 2.0f;
		const float right = W / 2.0f;
		const float bottom = -(H / 2.0f);

		Matrix3x3 cameraWorldMatrix = WorldMatrix(m_pos, m_scale, m_theta);
		Matrix3x3 worldMatrix = WorldMatrix(pos, Vector2(1.0f, 1.0f), 0.0f);
		Matrix3x3 viewMatrix = InverseMatrix(cameraWorldMatrix);
		Matrix3x3 orthoMatrix = MakeOrthographicMatrix(left, top, right, bottom);
		Matrix3x3 viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, W, H);
		Matrix3x3 wvpMatrix = Multiply(Multiply(worldMatrix, viewMatrix), orthoMatrix);
		wvpMatrix = Multiply(wvpMatrix, viewportMatrix);

		return Transform(localSpace, wvpMatrix);
	}
	static void DrawAxes() {

		Vector2 xStart = Vector2(-20000.0f, 0.0f);
		Vector2 xEnd = Vector2(20000.0f, 0.0f);
		Vector2 yStart = Vector2(0.0f, -2000.0f);
		Vector2 yEnd = Vector2(0.0f, .0f);

		xStart = CameraTransform(Vector2(0.0f, 0.0f), xStart);
		xEnd = CameraTransform(Vector2(0.0f, 0.0f), xEnd);
		yStart = CameraTransform(Vector2(0.0f, 0.0f), yStart);
		yEnd = CameraTransform(Vector2(0.0f, 0.0f), yEnd);


		Novice::DrawLine(static_cast<int>(xStart.x), static_cast<int>(xStart.y), static_cast<int>(xEnd.x), static_cast<int>(xEnd.y), GREEN);
		Novice::DrawLine(static_cast<int>(yStart.x), static_cast<int>(yStart.y), static_cast<int>(yEnd.x), static_cast<int>(yEnd.y), RED);
	}
	static void move() {

		int wheel = Novice::GetWheel();
		if (wheel < 0 && m_scale.x < 1.6f - 0.02f)
		{
			m_scale += Vector2(0.02f, 0.02f);
		}
		if (wheel > 0 && m_scale.x > 0.6f + 0.02f)
		{
			m_scale -= Vector2(0.02f, 0.02f);
		}
	}
private:
	static UINT m_windowH;
	static UINT m_windowW;
	static Vector2 m_pos;
	static Vector2 m_scale;
	static float m_theta;
};
inline UINT Camera::m_windowW = 1280;
inline UINT Camera::m_windowH = 720;
inline Vector2 Camera::m_pos = Vector2(0, 0);
inline Vector2 Camera::m_scale = Vector2(1.0f, 1.0f);
inline float Camera::m_theta = 0.0f;