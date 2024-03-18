#include "GameScene.h"
#include "ResLoader.h"
#include "GameOverLayer.h"

GameScene::GameScene()
{
	// 添加背景
	auto background = gcnew Sprite(ResLoader::getImage(L"bg_day"));
	background->setAnchor(0, 0);
	this->addChild(background);

	// 添加水管
	pipes = gcnew Pipes();
	this->addChild(pipes);

	// 添加小鸟
	bird = gcnew Bird();
	bird->setPos(60, Window::getHeight() / 2);
	this->addChild(bird);

	// 添加地面
	ground = gcnew Ground();
	this->addChild(ground);

	// 添加得分
	scoreImage = gcnew Number();
	scoreImage->setPos(Window::getWidth() / 2, 50);
	scoreImage->setNumber(0);
	this->addChild(scoreImage);

	// 添加 ready 图片
	ready = gcnew Sprite(ResLoader::getImage(L"text_ready"));
	ready->setPos(Window::getWidth() / 2, Window::getHeight() / 2 - 70);
	this->addChild(ready);

	// 添加教程图片
	tutorial = gcnew Sprite(ResLoader::getImage(L"tutorial"));
	tutorial->setPos(Window::getWidth() / 2, Window::getHeight() / 2 + 30);
	this->addChild(tutorial);

	started = false;
	score = 0;
}

void GameScene::onEnter()
{
	// 进入场景时播放音效
	ResLoader::playMusic(MusicType::Swoosh);
}
//=========================修改==================== 
int n = 0;
//=========================修改====================
void GameScene::onUpdate()
{
	//=========================修改========================
	// 按下鼠标左键或按下空格键
	if (Input::isPress(MouseCode::Left) ||
		Input::isPress(KeyCode::Space))
	//=========================修改========================
	{
		this->jump();
	}
	//=========================新增========================
	if (Input::isPress(KeyCode::P)	)
	{
		Game::pause();//按下p键会停止游戏
	}
	//========================新增===========================
	
	// 判断游戏是否已经开始
	if (started)
	{
		// 模拟小鸟下落
		bird->movePosY(bird->speed);
		// 模拟小鸟所受重力
		//=================修改====================
		bird->speed += 0.5f;
		//=================修改====================
        // 若小鸟纵坐标小于 0，限制它继续往上飞
		if (bird->getPosY() < 0)
		{
			bird->setPosY(0);
			bird->speed = 0;
		}
		//=========================修改========================
		// 判断小鸟是否飞过了水管
		if(!pipes->pipes[0]->scored &&
			pipes->pipes[0]->getPosX() >= bird->getPosX())
		//=========================修改========================
		{
			// 加分
			//=========================修改====================
			n++;
			score+=n;
			//=========================修改====================
			scoreImage->setNumber(score);
			// 标记
			pipes->pipes[0]->scored = true;
			// 播放音效
			ResLoader::playMusic(MusicType::Point);
		}

		// 判断碰撞
		if (bird->living)
		{
			for (auto pipe : pipes->pipes)
			{
				auto box = bird->getBoundingBox();  // 获取小鸟外包围盒
				for (auto child : pipe->getAllChildren())
				{
					if (child->getBoundingBox().intersects(box))
					{  // 判断小鸟包围盒是否和水管相交
						this->die();
					}
				}
			}
		}

		// 若小鸟纵坐标小于地面，游戏结束
		if (Window::getHeight() - bird->getPosY() <= 123)
		{
			this->die();
			// 让小鸟停止
			bird->setPosY(Window::getHeight() - 123);
			bird->setStatus(Bird::Status::Still);
			// 让小鸟脸朝下
			bird->setRotation(90);
			// 显示游戏结束界面
			this->gameover();
		}
	}
}

void GameScene::start()
{
	// 隐藏 ready 图片
	ready->runAction(gcnew FadeOut(0.4f));
	tutorial->runAction(gcnew FadeOut(0.4f));
	// 开始移动水管
	pipes->start();
	// 设置小鸟状态
	bird->setStatus(Bird::Status::StartToFly);
}

void GameScene::jump()
{
	if (!started)
	{
		// 若游戏还没有开始，开始游戏
		started = true;
		start();
	}
	if (bird->living)
	{
		// 如果小鸟还活着，给小鸟一个向上的速度
		//================修改=================
		bird->speed = -4.0f;
		//================修改=================
		// 设置小鸟状态
		bird->setStatus(Bird::Status::Fly);
		// 播放音效
		ResLoader::playMusic(MusicType::Fly);
	}
}

void GameScene::die()
{
	if (!bird->living) return;

	// 小鸟死亡
	bird->living = false;
	// 播放音效
	ResLoader::playMusic(MusicType::Hit);
	// 停止地面
	ground->stop();
	// 停止水管
	pipes->stop();
	// 隐藏得分
	scoreImage->runAction(gcnew FadeOut(0.5f));
	// 闪动白屏
	auto white = gcnew Sprite(ResLoader::getImage(L"white"));
	white->setAnchor(0, 0);
	white->setOpacity(0);
	white->setScale(16, 16);
	white->runAction(gcnew Sequence({ gcnew FadeIn(0.1f), gcnew FadeOut(0.1f) }));
	this->addChild(white);
	//=========================修改====================
	n = 0;
	//=========================修改====================
}

void GameScene::gameover()
{
	started = false;
	this->setAutoUpdate(false);
	// 显示得分面板
	this->addChild(gcnew GameOverLayer(score));
}
