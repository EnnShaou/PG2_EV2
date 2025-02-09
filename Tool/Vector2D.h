#pragma once
#include "math.h"
/// <summary>
/// 2次元ベクトル
/// </summary>
struct Vector2 final {

	float x;
	float y;

	/// <summary>
	/// デフォルトコンストラクタ x, yを0.0で初期化します。
	/// </summary>
	Vector2() : x(0.0f), y(0.0f) {}
	/// <summary>
	/// パラメータ付きコンストラクタ
	/// </summary>
	/// <param name="inX">X 指定して初期化</param>
	/// <param name="inY">Y 指定して初期化</param>
	Vector2(float inX, float inY) : x(inX), y(inY) {}

	/// <summary>
	/// 加算代入演算子
	/// </summary>
	/// <param name="other">他のベクトルを加算</param>
	/// <returns>自身を更新します</returns>
	Vector2& operator+=(const Vector2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	/// <summary>
	/// 減算代入演算子
	/// </summary>
	/// <param name="other">他のベクトルを減算</param>
	/// <returns>自身を更新します</returns>
	Vector2& operator-=(const Vector2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
	/// <summary>
	/// スカラー乗算代入演算子
	/// </summary>
	/// <param name="scalar">スカラー値を掛ける</param>
	/// <returns>自身を更新します</returns>
	Vector2& operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}
	/// <summary>
	/// スカラー除算代入演算子
	/// </summary>
	/// <param name="scalar">スカラー値で割る</param>
	/// <returns>自身を更新します。</returns>
	Vector2& operator/=(float scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	}

	/// 加算演算子
	/// </summary>
	/// <param name="other">2つのベクトルを加算</param>
	/// <returns>新しいベクトルとして返します</returns>
	Vector2 operator+(const Vector2& other) const {
		Vector2 result = *this;
		result += other;
		return result;
	}

	/// <summary>
	/// 減算演算子
	/// </summary>
	/// <param name="other">2つのベクトルを減算</param>
	/// <returns>新しいベクトルとして返します</returns>
	Vector2 operator-(const Vector2& other) const {
		Vector2 result = *this;
		result -= other;
		return result;
	}

	/// <summary>
	/// スカラー乗算演算子
	/// </summary>
	/// <param name="scalar">ベクトルとスカラー値の積</param>
	/// <returns>新しいベクトルとして返します</returns>
	Vector2 operator*(float scalar) const {
		Vector2 result = *this;
		result *= scalar;
		return result;
	}

	/// <summary>
	/// スカラー除算演算子
	/// </summary>
	/// <param name="scalar">ベクトルとスカラー値の商</param>
	/// <returns>新しいベクトルとして返します</returns>
	Vector2 operator/(float scalar) const {
		Vector2 result = *this;
		result /= scalar;
		return result;
	}

	/// <summary>
	///  等価比較演算子
	/// </summary>
	/// <param name="other">2つのベクトル</param>
	/// <returns>等しいかを判定します</returns>
	bool operator==(const Vector2& other) const {
		constexpr float epsilon = 1e-6f; // 許容誤差
		return fabs(x - other.x) < epsilon && fabs(y - other.y) < epsilon;
	}

	/// <summary>
	///  非等価比較演算子
	/// </summary>
	/// <param name="other"> 2つのベクトル</param>
	/// <returns>等しくないかを判定します。</returns>
	bool operator!=(const Vector2& other) const { return !(*this == other); }

	/// <summary>
	/// Dot
	/// </summary>
	/// <param name="other"></param>
	/// <returns>Dot</returns>
	float dot(const Vector2& other) { return x * other.x + other.y * y; }
	/// <summary>
	/// ベクトルの長さを計算
	/// </summary>
	/// <returns>ベクトルの長さ</returns>
	float length() const { return sqrtf(x * x + y * y); }

	/// <summary>
	/// ベクトルを正規化
	/// </summary>
	/// <returns>長さが1のベクトルを返します（元のベクトルが0の場合、(0, 0)を返します）</returns>
	Vector2 normalize() const {
		float len = length();
		return len > 0 ? *this / len : Vector2(0.0f, 0.0f);
	}

	/// <summary>
	/// ベクトルのゼロ値を表す静的関数
	/// </summary>
	/// <returns>(0, 0) のベクトルを返します。</returns>
	static Vector2 zero() { return Vector2(0.0f, 0.0f); }
};
