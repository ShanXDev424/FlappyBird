# FlappyBird理解

### 1.理解该项目的面向对象编程思想

在一款游戏当中，游戏的模型可能是独立的，但是配套的AI，行为，逻辑都不是单独做出来的。

试想一款大游戏当中，如果开发者要亲自编写每一个角色，在一个上亿玩家的游戏中工作量太大了，根本无法操作。那要如何实现呢？

这时候就要使用到**面向对象编程思想**来进行操作

首先我们 建立起了class module，在这款游戏中，我们建立了诸如**StartScene类，Bird类，Ground类**等，当一个类模块建立起来之后，我们就可以在程序其他窗体中，定义一个类的实例，然后就像使用一个对象一样访问它的属性，调用它的方法，对象是类的一个实例，有状态和行为。

例如StartScene类，就具有开始场景下，地面，标题，小鸟，按钮等一系列特征

对象的属性和行为看成一个密不可分的整体，将这两者“封装”在一个不可分割的独立单元(即对象)中；另一层含义指“信息隐藏”，把不需要让外界知道的信息隐藏起来，有些对象的属性及行为允许外界用户知道或使用，但不允许更改，而另一些属性或行为，则不允许外界知晓，或只允许使用对象的功能，而尽可能隐藏对象的功能实现细节。

正如看到的，我们会把小鸟的基础属性设置出来。但是如果不进行封装，属性就需要不停的定义新变量，显然不现实。同时我们创建的各种类可以自由修改，在封装的过程中，我们也可以对成员变量进行更加精确的控制，譬如不同颜色小鸟的帧动画 ，小鸟的飞翔姿态。完全不用去理相对于面向过程的三个步骤，因为这三个步骤已经被对象封装起来了，我们只需要调用这个对象所封装的方法即可，不需要关心具体是如何实现的。

### 2.每个具体cpp文件的作用

#### **场景：**

**a.Gameoverlayer.cpp**

 显示game over界面及其界面上的相关内容，加载一个新的游戏开始界面

**b.GameScene.cpp**

添加游戏的背景，水管，小鸟，地面，得分等基本属性，以及小鸟动起来后场景的变化

**c.Ground.cpp**

实现地面的运动

**d.main.cpp**

初始化窗口，加载资源，进入Splash场景开始游戏

**e.Pipe.cpp**

创建水管，确定水管位置

**f.Pipes.cpp**

确定水管的移动方式，管理水管的运动

**g.ResLoader.cpp**

资源管理工具，实现预加载

**h.Startscene.cpp**

开始场景

**对象：**

**a.Bird.cpp**

 bird类，为不同的小鸟确定不同的帧动画，并合适的保留动画，设计小鸟的颜色，它初始的飞行姿态，以及飞行时候的旋转动作

**b.Number.cpp**

数字类，显示得分时，用于将int型数字转化为图片的类，处理图片和数字

**c.GameoverLayer.cpp**

Gameoverlayer类，有关游戏结束后加载的界面类

**d.GameScene.cpp**

游戏背景类

**e.Ground.cpp**

地面类，游戏中下方一直向左移的地面

**f.main.cpp**

游戏类，游戏控制

**g.Pipe.cpp**

水管类，游戏中小鸟碰到会死亡的水管

**h.Pipes.cpp**

管理水管的运动类

**i.R **

开始场景类

**工具：**

**a.main.cpp**  easy2d

**b.ResLoader.cpp**  加载音频，图片

**c.bird.cpp**   加载帧动画

### 3.树形结构图

FlappyBird

​    |  ——场景

​    |   Gameover.cpp

​    |   GameoverLayer.cpp

​    |   GameScene.cpp

​    |   Ground.cpp

​    |   main.cpp    

​    |   Pipe.cpp

​    |  Pipes.cpp

​    |  ResLoader.cpp

​    |  Startscene.cpp

​    |——对象

​    |  Bird.cpp

​    |  Number.cpp

​    |  GameoverLayer.cpp

​    |  GameScene.cpp

​    |   Ground.cpp

​    |   main.cpp

​    |   Pipes.cpp

​    |    Pipes.cpp

​    |  ResLoader.cpp

​    |    Startscene.cpp

​    |——工具

​    |  main.cpp

​    | ResLoader.cpp

​    |  Number.cpp

​    |  Bird.h

​    |  Ground.h

​    |  resource.h

​    | Startscene.h

​    |——资源

​    |  atlast.txt

