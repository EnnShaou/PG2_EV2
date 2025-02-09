#include "Character.h"

Bullet::Bullet(Vector2 pos, Vector2 vel, unsigned int color) {
	m_pos = pos;
	m_size = { 16.f,4.f };
	m_vel = vel;
	m_state = State::ALIVE;
	deadTimer = 0;
	m_color = color;
}

void Bullet::UpDate(const int WindowWidth, const int WindowHeight)
{
	WindowHeight;
	WindowWidth;
	//移動処理
	m_pos += m_vel;
	//画面外に出ると死ぬ
	if (m_pos.x > (float)WindowWidth || m_pos.x < 0.f)
	{
		m_state = State::DEADENTER;
	}
	//時間立つと消す
	if (m_state == State::DEADENTER)
	{
		deadTimer++;
		if (deadTimer >= 120)
		{
			m_state = State::DEAD;
		}
	}

}

void Bullet::Draw()
{
	if (m_state == State::ALIVE)
	{
		Novice::DrawEllipse(
			static_cast<int>(m_pos.x),
			static_cast<int>(m_pos.y),
			static_cast<int>(m_size.x),
			static_cast<int>(m_size.y), 0.f, m_color, kFillModeSolid
		);
	}

}

player::player(Vector2 pos, unsigned int color) {
	m_pos = pos;
	m_size = { 16.f,16.f };
	m_vel = { 4.f,4.f };
	m_state = State::ALIVE;
	deadTimer = 0;
	hp = 5;
	m_color = color;
	shootCoolTime = 5;
}
player::~player()
{
}

void player::UpDate(const int WindowWidth, const int WindowHeight, char* k, char* pk)
{
	if (!k || !pk)
	{
		return;
	}

	if (k[DIK_SPACE])//ショット
	{
		if (shootCoolTime > 0) {
			shootCoolTime--;
		}
		else {
			shootCoolTime = 5;
		}
		if (shootCoolTime <= 0)
		{
			m_bullet.push_back(std::make_unique<Bullet>(m_pos, Vector2(16.f, 0.f), WHITE));//新しい弾プシュッ
		}
	}
	//弾の更新
	for (auto it = m_bullet.begin(); it != m_bullet.end();) {

		auto& b = *it;
		b->UpDate(WindowWidth, WindowHeight);
		if (b->getState() == State::DEAD)//dead状態になると消される。
		{
			it = m_bullet.erase(it);
		}
		else
		{
			++it;
		}
	}
	//移動
	if (k[DIK_W])
	{
		m_pos.y -= m_vel.y;
	}if (k[DIK_S])
	{
		m_pos.y += m_vel.y;

	}if (k[DIK_A])
	{
		m_pos.x -= m_vel.x;
	}if (k[DIK_D])
	{
		m_pos.x += m_vel.x;
	}
}

void player::Draw()
{
	for (const auto& b : m_bullet)
	{
		b->Draw();
	}
	Novice::DrawQuad(
		static_cast<int>(m_pos.x - m_size.x), static_cast<int>(m_pos.y + m_size.y),
		static_cast<int>(m_pos.x + m_size.x), static_cast<int>(m_pos.y),
		static_cast<int>(m_pos.x - m_size.x / 2.f), static_cast<int>(m_pos.y),
		static_cast<int>(m_pos.x - m_size.x), static_cast<int>(m_pos.y - m_size.y),
		0, 0, 0, 0, 0, m_color
	);
}
Enemies::Enemies(Vector2 pos, int timer, unsigned int color)
{

	m_pos = pos;
	m_size = { 16.f,16.f };
	m_vel = { -2.f,1.f };
	m_state = State::ALIVE;
	deadTimer = 0;
	m_moveTimerMax = timer;
	m_moveTimer = m_moveTimerMax;
	m_color = color;
}

Enemies::~Enemies()
{

}

void Enemies::UpDate(const int WindowWidth, const int WindowHeight)
{
	WindowHeight;
	WindowWidth;
	if (m_state == State::ALIVE)
	{
		m_pos += m_vel;
		m_moveTimer--;
		if (m_moveTimer <= 0)//時間が0になるとショットして移動の方向変え
		{
			m_bullet.push_back(std::make_unique<Bullet>(m_pos, Vector2(-16.f, 0.f), GREEN));
			m_moveTimer = m_moveTimerMax;
			m_vel.y *= -1.f;
		}
	}
	//弾の更新
	for (auto it = m_bullet.begin(); it != m_bullet.end();) {

		auto& b = *it;
		b->UpDate(WindowWidth, WindowHeight);
		if (b->getState() == State::DEAD)//dead状態になると消される。
		{
			it = m_bullet.erase(it);
		}
		else
		{
			++it;
		}

	}

	if (m_pos.y > (float)WindowHeight)
	{
		m_pos.y = (float)WindowHeight;
	}
	if (m_pos.y < 0.f)
	{
		m_pos.y = 0.f;
	}
	if (m_state == State::DEADENTER)
	{
		deadTimer++;
		if (deadTimer >= 120)
		{
			m_state = State::DEAD;
		}
	}
	if (m_pos.x < 0.f)
	{
		m_state = State::DEAD;
	}
}

void Enemies::Draw()
{

	for (const auto& b : m_bullet)
	{
		b->Draw();
	}

	if (m_state == State::ALIVE)
		Novice::DrawQuad(
			static_cast<int>(m_pos.x + m_size.x), static_cast<int>(m_pos.y + m_size.y),
			static_cast<int>(m_pos.x - m_size.x), static_cast<int>(m_pos.y),
			static_cast<int>(m_pos.x + m_size.x / 2.f), static_cast<int>(m_pos.y),
			static_cast<int>(m_pos.x + m_size.x), static_cast<int>(m_pos.y - m_size.y),
			0, 0, 0, 0, 0, m_color
		);
}