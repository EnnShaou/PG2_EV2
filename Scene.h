#pragma once
#include"Tool/Camera.h"
#include"obj.h"
#include"Character.h"
/// <summary>
/// シーンマネージャー前方宣言
/// </summary>
class SceneManager;
/// <summary>
/// シーン基底クラス
/// </summary>
class Scene {
public:
	Scene() : sceneManager(nullptr) {}
	virtual ~Scene() = default;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="WindowWidth">画面横幅</param>
	/// <param name="WindowHeight">画面縦幅</param>
	/// <param name="k">キー</param>
	/// <param name="pk">プレキー</param>
	virtual void UpDate(const int WindowWidth, const int WindowHeight, char* k, char* pk) = 0;
	virtual void Draw() = 0;
	/// <summary>
	/// シーンマネージャーを設定する
	/// </summary>
	/// <param name="sceneManager_"></param>
	void setSceneManager(SceneManager* sceneManager_) { sceneManager = sceneManager_; }

protected:
	SceneManager* sceneManager;
};

/// <summary>
/// タイトル
/// </summary>
class TITLE :public Scene
{
public:
	TITLE();
	~TITLE();
	void UpDate(const int WindowWidth, const int WindowHeight, char* k, char* pk)override;
	void Draw()override;
private:

};


/// <summary>
/// ゲーム
/// </summary>
class InGame :public Scene
{
public:
	InGame(const int windowWidth, const int windowHeight);
	~InGame();

	void UpDate(const int WindowWidth, const int WindowHeight, char* k, char* pk)override;
	void Draw()override;
private:
	//敵の再生成タイマー
	int enemyRespawnTime;
	//プレーヤー
	player* m_player;
	//敵
	std::vector<std::unique_ptr<Enemies>> m_enemy;

};

/// <summary>
/// 終了
/// </summary>
class Over :public Scene
{
public:
	Over();
	~Over();
	void UpDate(const int WindowWidth, const int WindowHeight, char* k, char* pk)override;
	void Draw()override;
private:

};


/// <summary>
/// シーンマネージャー
/// </summary>
class SceneManager {
public:
	SceneManager() : currentScene(nullptr) {
		ChangeScene(new TITLE());
	}

	~SceneManager() {
		if (currentScene) {
			delete currentScene;
		}
	}
	/// <summary>
	/// 更新
	/// </summary>
	void UpDate(int WindowWidth, int WindowHeight, char* k, char* pk) {
		if (currentScene) {
			currentScene->UpDate(WindowWidth, WindowHeight, k, pk);
		}
	}
	/// <summary>
	/// 描画
	/// </summary>
	void Draw() {
		if (currentScene) {
			currentScene->Draw();
		}
	}
	/// <summary>
	/// シーン切替
	/// </summary>
	void ChangeScene(Scene* newScene) {
		if (newScene == nullptr) return;

		if (currentScene) {
			delete currentScene;
		}

		currentScene = newScene;
		currentScene->setSceneManager(this);
	}

private:
	Scene* currentScene;
};
