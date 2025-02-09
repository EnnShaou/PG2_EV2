#pragma once
#include "obj.h"
#include <vector>
#include<memory>

/// <summary>
/// 弾クラス
/// </summary>
class Bullet :public Obj
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="vel">スピード</param>
	/// <param name="color">色</param>
	Bullet(Vector2 pos, Vector2 vel, unsigned int color);
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="WindowWidth">画面横幅</param>
	/// <param name="WindowHeight">画面縦幅</param>
	void UpDate(const int WindowWidth, const int WindowHeight);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;
private:

};

class player :public Obj
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="color">色</param>
	player(Vector2 pos, unsigned int color);
	~player();
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="WindowWidth">画面横幅</param>
	/// <param name="WindowHeight">画面縦幅</param>
	/// <param name="k">キー</param>
	/// <param name="pk">プレキー</param>
	void UpDate(const int WindowWidth, const int WindowHeight, char* k, char* pk);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;
	/// <summary>
	/// 弾のデータ取る
	/// </summary>
	/// <returns>弾のデータ</returns>
	std::vector<std::unique_ptr<Bullet>>& getBullet() { return m_bullet; }
	/// <summary>
	/// HP取る
	/// </summary>
	/// <returns>HP</returns>
	int getHp() { return hp; }
	/// <summary>
	/// HP減少
	/// </summary>
	void isDamage() { hp--; }
private:
	int hp;
	int shootCoolTime;
	//弾
	std::vector<std::unique_ptr<Bullet>>m_bullet;
};

class Enemies :public Obj
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="timer">敵移動、攻撃のタイマー</param>
	/// <param name="color">色</param>
	Enemies(Vector2 pos, int timer, unsigned int color);
	~Enemies();
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="WindowWidth">画面横幅</param>
	/// <param name="WindowHeight">画面縦幅</param>
	void UpDate(const int WindowWidth, const int WindowHeight);
	void Draw()override;
	/// <summary>
	/// 弾のデータ取る
	/// </summary>
	/// <returns>弾のデータ</returns>
	std::vector<std::unique_ptr<Bullet>>& getBullet() { return m_bullet; }
private:
	//弾
	std::vector<std::unique_ptr<Bullet>>m_bullet;
	int m_moveTimer;
	int m_moveTimerMax;
};


