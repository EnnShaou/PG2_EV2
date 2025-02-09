#pragma once
#include"random"
#include "Tool/Camera.h"

inline bool IsCircleColliding(Vector2 Pos, Vector2 Size, Vector2 fromPos, Vector2 fromSize) {
	Vector2 d = Pos - fromPos;
	float distanceSquared = d.length();
	float radiusSum = fromSize.x + Size.x;
	return distanceSquared < radiusSum;
}

/// <summary>
/// ランダム用クラス
/// </summary>
class Random
{
public:
	/// <summary>
	/// コンストラクタ　
	/// </summary>
	/// <param name="min">乱数の最小値</param>
	/// <param name="max">乱数の最大値</param>
	Random(float min, float max)
		: seed_generator_(), random_engine_(seed_generator_()),
		distribution_(min, max), fixed(distribution_(random_engine_)) {}

	~Random() = default;

	/// <summary>
	/// 乱数の値
	/// </summary>
	/// <returns>float型の値を返す</returns>
	float Rand() {
		fixed = distribution_(random_engine_);
		return fixed;
	}
	/// <summary>
	/// ランダム範囲を再設定
	/// </summary>
	/// <param name="min">乱数の最小値</param>
	/// <param name="max">乱数の最大値</param>
	void SetRange(float min, float max) {
		distribution_ = std::uniform_real_distribution<float>(min, max);
	}

private:
	//戻り値を扱う変数
	float fixed;
	// ランダムシードを生成する
	std::random_device seed_generator_;
	// 乱数エンジン（メルセンヌ・ツイスター）をシードで初期化する
	std::mt19937 random_engine_;
	//範囲で一様分布の乱数を生成する
	std::uniform_real_distribution<float> distribution_;
};

/// <summary>
/// 状態
/// </summary>
enum class State {
	ALIVE,
	DEADENTER,
	DEAD

};

/// <summary>
/// オブジェクトクラス
/// </summary>
class Obj
{
public:
	Obj();
	~Obj() {}
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() {}
	/// <summary>
	/// 座標値取る
	/// </summary>
	/// <returns>座標</returns>
	Vector2 getPos() { return m_pos; }
	/// <summary>
	/// 座標を設定
	/// </summary>
	/// <param name="pos">制定する座標</param>
	void setPos(Vector2 pos) { m_pos = pos; }
	/// <summary>
	/// サイズを取る
	/// </summary>
	/// <returns>サイズ値</returns>
	Vector2 getSize() { return m_size; }
	/// <summary>
	/// サイズを設定
	/// </summary>
	/// <param name="size">設定するサイズ</param>
	void setSize(Vector2 size) { m_size = size; }
	/// <summary>
	/// スピード取る
	/// </summary>
	/// <returns>スピード値</returns>
	Vector2 getVel() { return m_vel; }
	/// <summary>
	/// スピード設定
	/// </summary>
	/// <param name="vel">設定するスピード値</param>
	void setVel(Vector2 vel) { m_vel = vel; }
	/// <summary>
	/// 状態を取る
	/// </summary>
	/// <returns>状態</returns>
	State getState() { return m_state; }
	/// <summary>
	/// 状態を設定
	/// </summary>
	/// <param name="state">設定する状態</param>
	void setState(State state) { m_state = state; }
protected:
	Vector2 m_pos;
	Vector2 m_size;
	Vector2 m_vel;
	State m_state;
	int deadTimer;
	unsigned int m_color;
};



