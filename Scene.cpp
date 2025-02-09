#include "Scene.h"
#include<Novice.h>

TITLE::TITLE()
{
}

TITLE::~TITLE()
{
}

void TITLE::UpDate(const int WindowWidth, const int WindowHeight, char* k, char* pk)
{
	WindowHeight;
	WindowWidth;
	if (!k || !pk)
	{
		return;
	}
	if (k[DIK_SPACE] && !pk[DIK_SPACE])
	{
		sceneManager->ChangeScene(new InGame(WindowWidth, WindowHeight));//ゲームシーンへ
	}
}

void TITLE::Draw()
{
	Novice::ScreenPrintf(0, 0, "isTitle");
	Novice::ScreenPrintf(600, 360, "push SPACE to GameStart");

}



InGame::InGame(const int windowWidth, const int windowHeight)
{
	enemyRespawnTime = 0;
	//プレーヤー初期
	m_player = new player({ 300.f, 300.f }, BLUE);
	//敵の初期
	for (int i = 0; i < 12; i++)
	{
		Random ePosY(0.f, (float)windowHeight);
		Random ePosX((float)windowWidth, (float)windowWidth + (float)windowWidth / 2.f);
		Random coolTime(60.f, 360.f);
		m_enemy.push_back(std::make_unique<Enemies>(Vector2(ePosX.Rand(), ePosY.Rand()), (int)coolTime.Rand(), RED));
	}
}

InGame::~InGame()
{
	delete m_player;
	m_enemy.clear();

}
void InGame::UpDate(const int WindowWidth, const int WindowHeight, char* k, char* pk)
{
	WindowHeight;
	WindowWidth;
	if (!k || !pk)
	{
		return;
	}
	//再生成タイマー
	enemyRespawnTime++;
	if (enemyRespawnTime >= 180)
	{
		for (int i = 0; i < 6; i++)//再生成
		{
			Random ePosY(0.f, (float)WindowHeight);
			Random ePosX((float)WindowWidth, (float)WindowWidth + (float)WindowWidth / 2.f);
			Random coolTime(60.f, 360.f);
			m_enemy.push_back(std::make_unique<Enemies>(Vector2(ePosX.Rand(), ePosY.Rand()), (int)coolTime.Rand(), RED));
		}
		enemyRespawnTime = 0;
	}
	m_player->UpDate(WindowWidth, WindowHeight, k, pk);
	for (auto it = m_enemy.begin(); it != m_enemy.end();)
	{
		auto& e = *it;
		e->UpDate(WindowWidth, WindowHeight);

		//敵とプレーヤーの当たり判定
		if (IsCircleColliding(e->getPos(), e->getSize(), m_player->getPos(), m_player->getSize()) && e->getState() == State::ALIVE)
		{
			m_player->isDamage();
			e->setState(State::DEADENTER);
		}
		for (auto enemy_bullet_it = e->getBullet().begin(); enemy_bullet_it != e->getBullet().end(); ++enemy_bullet_it)
		{
			auto& eb = *enemy_bullet_it;
			//プレーヤーと敵の弾の当たり判定
			if (eb->getState() == State::ALIVE && IsCircleColliding(eb->getPos(), eb->getSize(), m_player->getPos(), m_player->getSize()))
			{
				eb->setState(State::DEADENTER);
				m_player->isDamage();
				break;
			}
		}

		for (auto player_bullet_it = m_player->getBullet().begin(); player_bullet_it != m_player->getBullet().end(); ++player_bullet_it)
		{
			//プレーヤーの弾と敵の当たり判定
			auto& pb = *player_bullet_it;
			if (e->getState() == State::ALIVE && pb->getState() == State::ALIVE && IsCircleColliding(pb->getPos(), pb->getSize(), e->getPos(), e->getSize()))
			{
				pb->setState(State::DEADENTER);
				e->setState(State::DEADENTER);
			}
		}
		if (e->getState() == State::DEAD)//敵の消す処理
		{
			it = m_enemy.erase(it);
		}
		else {
			++it;
		}
	}
	if (m_player->getHp() == 0)//プレーヤーが死んだらゲームオーバーへ
	{
		sceneManager->ChangeScene(new Over);
	}

}
void InGame::Draw()
{
	Novice::ScreenPrintf(0, 0, "isGame");
	m_player->Draw();
	for (const auto& e : m_enemy) {
		e->Draw();
	}
	Novice::ScreenPrintf(0, 20, "player hp : %d", m_player->getHp());

}
Over::Over()
{
}

Over::~Over()
{
}

void Over::UpDate(const int WindowWidth, const int WindowHeight, char* k, char* pk)
{
	WindowHeight;
	WindowWidth;
	if (!k || !pk)
	{
		return;
	}if (k[DIK_SPACE] && !pk[DIK_SPACE])
	{
		sceneManager->ChangeScene(new TITLE);//タイトルへ
	}
}

void Over::Draw()
{
	Novice::ScreenPrintf(0, 0, "isOver");
	Novice::ScreenPrintf(600, 360, "push SPACE to Bake TITLE");

}
