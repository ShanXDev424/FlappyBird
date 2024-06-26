#include "Bird.h"
#include "ResLoader.h"


Bird::Bird()
{
	living = true;
	speed = 0;

	// 创建帧动画，0.1f 秒切换一次
	animation = gcnew Animation(0.1f);
	// 随机小鸟颜色
	int mode = Random::range(0, 2);
	// 为不同颜色的小鸟加载不同的帧动画
	if (mode == 0)
	{
		this->open(ResLoader::getImage(L"bird0_0"));
		animation->add(ResLoader::getImage(L"bird0_0"));
		animation->add(ResLoader::getImage(L"bird0_1"));
		animation->add(ResLoader::getImage(L"bird0_2"));
		animation->add(ResLoader::getImage(L"bird0_1"));
	}
	else if (mode == 1)
	{
		this->open(ResLoader::getImage(L"bird1_0"));
		animation->add(ResLoader::getImage(L"bird1_0"));
		animation->add(ResLoader::getImage(L"bird1_1"));
		animation->add(ResLoader::getImage(L"bird1_2"));
		animation->add(ResLoader::getImage(L"bird1_1"));
	}
	else
	{
		this->open(ResLoader::getImage(L"bird2_0"));
		animation->add(ResLoader::getImage(L"bird2_0"));
		animation->add(ResLoader::getImage(L"bird2_1"));
		animation->add(ResLoader::getImage(L"bird2_2"));
		animation->add(ResLoader::getImage(L"bird2_1"));
	}
	// 循环运行帧动画
	this->runAction(gcnew Loop(gcnew Animate(animation)));

	// 初始化飞翔动画（上下微微浮动）
	auto moveBy = gcnew MoveBy(0.4f, Vector2(0, 8));
	fly = gcnew Loop(gcnew Sequence({ moveBy, moveBy->reverse() }));
	// 初始化旋转动画（小鸟坠落时，先抬头，后低头）
	rotate = gcnew Sequence({
		//====================修改=============
		gcnew RotateTo(0.2f, 0),	// 0.2f 秒内旋转至 0度
		gcnew Delay(0.2f),			// 等待 0.2f 秒
		gcnew RotateTo(0.5f, 1080)	// 0.5f 秒内旋转至 360 度（小鸟头朝下）
		//====================修改=============
		});
	// 保留这个动画，防止引擎自动回收
	rotate->retain();

	// 设置初始化状态为 1
	this->setStatus(Status::Idle);
}

Bird::~Bird()
{
	// 释放曾经保留的动画
	rotate->release();
}

void Bird::setStatus(Status status)
{
	switch (status)
	{
	case Status::Still:
	{
		this->stopAllActions();
		break;
	}
	case Status::Idle:
	{
		this->runAction(fly);
		break;
	}
	case Status::StartToFly:
	{
		fly->stop();						// 停止上下晃动动画
		animation->setInterval(0.5f);		// 加速小鸟扇动翅膀的速度
		// break;
	}
	case Status::Fly:
	{
		this->stopAction(L"rotate");		// 停止前一个旋转动作

		auto newRotate = rotate->clone();
		newRotate->setName(L"rotate");
		this->runAction(newRotate);
		break;
	}
	default:
		break;
	}
}
