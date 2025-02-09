#pragma once
#include<Tool/Vector2D.h>
#include "math.h"
#include <Novice.h>
#include <assert.h>
struct Matrix3x3 final {
	float m[3][3];
};
////////////////////////////////////////////////////////////////////////////陣列変換

inline Matrix3x3 MakeTranslateMatrix(const Vector2 translate) { return { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, translate.x, translate.y, 1.0f }; }

inline Vector2 MakeTranslateVector2(const Matrix3x3 translate) { return { translate.m[2][0], translate.m[2][1] }; }

////////////////////////////////////////////////////////////////////////////陣列計算

inline Vector2 TranslateVector2(const Matrix3x3 changeMatrix, const Vector2 vector) {
	Vector2 result;
	result.x = vector.x * changeMatrix.m[0][0] + vector.y * changeMatrix.m[1][0] + 1.0f * changeMatrix.m[2][0];
	result.y = vector.x * changeMatrix.m[0][1] + vector.y * changeMatrix.m[1][1] + 1.0f * changeMatrix.m[2][1];
	float w = vector.x * changeMatrix.m[0][2] + vector.y * changeMatrix.m[1][2] + 1.0f * changeMatrix.m[2][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	return result;
}

inline Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {
	Matrix3x3 result = {};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				result.m[i][j] += matrix1.m[i][k] * matrix2.m[k][j];
			}
		}
	}
	return result;
}

////////////////////////////////////////////////////////////////////////////陣列生成

inline Matrix3x3 MakeScaleMatrix(const Vector2 scale) { return { scale.x, 0.0f, 0.0f, 0.0f, scale.y, 0.0f, 0.0f, 0.0f, 1.0f }; }

inline Matrix3x3 MakeRotateMatrix(const float theta) { return { cosf(theta), sinf(theta), 0, -sinf(theta), cosf(theta), 0, 0.0f, 0.0f, 1.0f }; }

inline Matrix3x3 Inverse(Matrix3x3 matrix) {
	float determinant = (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] + matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] + matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1]) -
		(matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] + matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] + matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]);

	return Matrix3x3{ (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) / determinant,  -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]) / determinant,
					 (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]) / determinant,

					 -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]) / determinant, (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]) / determinant,
					 -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]) / determinant,

					 (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]) / determinant,  -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]) / determinant,
					 (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]) / determinant };
}

inline Matrix3x3 Transpose(Matrix3x3 matrix) {

	return Matrix3x3{ matrix.m[0][0], matrix.m[1][0], matrix.m[2][0], matrix.m[0][1], matrix.m[1][1], matrix.m[2][1], matrix.m[0][2], matrix.m[1][2], matrix.m[2][2] };
}

////////////////////////////////////////////////////////////////////////////陣列表示

inline void MatrixScreenPrintf(int x, int y, Matrix3x3 matrix) {
	int kColumnWidth = 80;
	int kRowHeight = 40;
	for (int row = 0; row < 3; ++row) {
		for (int column = 0; column < 3; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%.02f", matrix.m[row][column]);
		}
	}
}

////////////////////////////////////////////////////////////////////////////陣列結合

inline Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate) {
	return { scale.x * cosf(rotate), scale.x * sinf(rotate), 0, -scale.y * sinf(rotate), scale.y * cosf(rotate), 0, translate.x, translate.y, 1 };
}

inline Matrix3x3 MatrixMix(Matrix3x3 matrix1, Matrix3x3 matrix2) {
	Matrix3x3 result = Multiply(matrix1, matrix2);
	return result;
}

inline Matrix3x3 MatrixMix(Matrix3x3 matrix1, Matrix3x3 matrix2, Matrix3x3 matrix3) {
	Matrix3x3 result = Multiply(matrix1, matrix2);
	result = Multiply(result, matrix3);
	return result;
}

inline Matrix3x3 MatrixMix(Matrix3x3 matrix1, Matrix3x3 matrix2, Matrix3x3 matrix3, Matrix3x3 matrix4) {
	Matrix3x3 result = Multiply(matrix1, matrix2);
	result = Multiply(result, matrix3);
	result = Multiply(result, matrix4);
	return result;
}

////////////////////////////////////////////////////////////////////////////world改変陣列

inline Matrix3x3 MakeWorldMatrix(Matrix3x3 origin) { return origin; }

inline Matrix3x3 MakeViewMatrix(Matrix3x3 origin, float posX, float posY) {
	Vector2 move = { posX, posY };
	Matrix3x3 move2 = MakeTranslateMatrix(move);
	Matrix3x3 result = MatrixMix(origin, move2);
	return Inverse(result);
}

inline Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom) {
	return { 2.0f / (right - left), 0.0f, 0.0f, 0.0f, 2.0f / (top - bottom), 0.0f, (left + right) / (left - right), (top + bottom) / (bottom - top), 1.0f };
}

inline Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height) {
	return { width / 2.0f, 0.0f, 0.0f, 0.0f, -(height / 2.0f), 0.0f, left + (width / 2.0f), top + (height / 2.0f), 1.0f };
}

inline Matrix3x3 WorldMatrix(Vector2 pos, Vector2 scale, float theta) {

	Matrix3x3 worldMatrix = {};
	worldMatrix = Multiply(MakeScaleMatrix(scale), MakeRotateMatrix(theta));
	worldMatrix = Multiply(worldMatrix, MakeTranslateMatrix(pos));
	return worldMatrix;
}
inline Matrix3x3 InverseMatrix(const Matrix3x3& mat) {
	float a = mat.m[0][0], b = mat.m[0][1], c = mat.m[1][0], d = mat.m[1][1];
	float tx = mat.m[2][0], ty = mat.m[2][1];
	float det = a * d - b * c;
	float invDet = 1.0f / det;
	Matrix3x3 inverse = { d * invDet, -b * invDet, 0.0f, -c * invDet, a * invDet, 0.0f, (c * ty - d * tx) * invDet, (b * tx - a * ty) * invDet, 1.0f };
	return inverse;
}
inline Vector2 Transform(const Vector2& v, const Matrix3x3& mat) {
	Vector2 result;
	result.x = mat.m[0][0] * v.x + mat.m[1][0] * v.y + mat.m[2][0];
	result.y = mat.m[0][1] * v.x + mat.m[1][1] * v.y + mat.m[2][1];
	return result;
}
