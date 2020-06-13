# TP Snake! Version 2.0 使用指南

## 关于游戏与作者

作者开发游戏经历了很长时间，学习了很多相关知识，查阅了大量资料，自学`EasyX`库的文档，自学堆排序算法，多次修改和测试程序，坚持朝着`bug-free`（无bug）的方向前进，努力做到评分标准下的满分要求。

欢迎您在我的代码的基础上进一步修改，或借鉴学习，做出更优秀的作品。感谢您的耐心阅读和支持！希望您能给我打满分啦！ヾ(≧▽≦*)o

![QQ图片20200527132002.gif](https://i.loli.net/2020/05/31/LECUgWtrQanZzos.gif)

## 关于如何搭建开发环境

首先请按照`高级语言程序设计实验大作业反思报告（最终版）.doc`中的简单教程安装`Visual Studio 2019`（可以使用试用版，也可以用微软账号登录使用），并安装好`EasyX`图形库。

解压该目录下的压缩文件`Snake!.rar`，双击进入解压得到的文件夹`Snake!`，双击打开`Snake!.sln`，进入`Visual Studio 2019`编辑器界面，按下`F5`键编译运行。

![Snake.png](https://i.loli.net/2020/05/31/kDwbsqxcIMe6fih.png)

每次游戏生成的`排行榜.txt`文件位于目录`/Snake!/Snake!/`下，程序所使用的音效`GrazetheRoof.mp3`也位于相同的目录下；程序使用的图标文`snake.ico`件位于目录`/Snake!/`下。注意在游戏过程中不要打开`排行榜.txt`文件，而要等到游戏结束后再打开。

![Snake!-Snake!-.png](https://i.loli.net/2020/05/31/KtPqa2IHexcvW57.png)

> 如果您不能成功地搭建开发环境或依然不知道应该如何操作，或者你就是想直接体验游戏，请看下一点：**关于直接体验游戏**

## 关于直接体验游戏

出于某些原因，可能是您无法成功搭建开发环境，或者是您希望减少操作步骤，直接体验游戏，具体的方法如下（很简单！）：

> 开始游戏前请先把输入法换成英语键盘，如图：

![微信截图_20200531162243.png](https://i.loli.net/2020/05/31/OK7IrMzQWUhxlc5.png)

### 直接体验TP Snake! Version 2.0（最终版）

1. 打开此文件目录下的`TPS V2.0`文件夹，双击运行`TP Snake! Version 2.0.exe`（如图）

   ![1590556998475.png](https://i.loli.net/2020/05/31/pi2fPoVuYICnG5h.png)

2. **Enjoy!**

### 体验单人版游戏（非最终版）

> 在开发早期，我还做了一个较为简单的单人版游戏，功能相对较少，但也拥有贪吃蛇游戏的基本特点，健壮性很高。

1. 打开此文件目录下的`SPS V1.1`文件夹，双击运行`SP Snake! Version 1.1.exe`（如图）

   ![1590556353322.png](https://i.loli.net/2020/05/31/8UApIDCMdeY9vz3.png)

2. **Enjoy!**（按键为↑↓←→）

## 关于堆排序

在选择分数排序算法的时候我选择了堆排序，因为堆排序的时间复杂度（O(nlogn)）比冒泡排序、插入排序、选择排序等（O(n^2)）都要小，且不需要太多额外的内存花销。

堆排序是一种基于完全二叉树的排序算法，其利用了二叉堆中任何一个父节点的值都大于（最大堆）或小于（最小堆）的性质，通过构建二叉堆，依次取出堆顶元素并调整二叉堆实现一串数字的大小排序。在大作业反思报告`word`文档中，我给出了两幅描述堆排序的流程图。如果您想进一步了解堆排序的原理，请访问以下两个网站：

- **漫画：什么是堆排序**：https://blog.csdn.net/libaineu2004/article/details/82820822
- **漫画：什么是二叉堆？（修正版）**：https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653195207&idx=2&sn=12689c6c1a92e7ec3cce4d423019ec2a&chksm=8c99f91dbbee700b8e760d06b27582037ab0713295dacf2b5a7a7f954c0032fe860aa0bf8b74&scene=21#wechat_redirect

## 关于版权

整个项目的代码和资源文件已经在`github`和`码云`上开源，遵守`MIT`开源协议，欢迎自由下载！

- `github`地址：https://github.com/G-SS-Hacker/TP-Snake-Version-2.0
- `码云`地址：https://gitee.com/G-SS-Hacker/TP-Snake-Version-2.0

项目中除代码以外的文字内容，其中`高级语言程序设计实验大作业反思报告（最终版）.doc`作者保留所有权利，不得转载；其他文字内容一律遵守知识共享协议`cc BY-NC-SA 4.0`，可以自由转载，不得商用。

程序使用的图标`snake.ico`文件和程序使用的音频文件`GrazatheRoof.mp3`均来源网络，作者不拥有版权，在此声明。

------

<font face=serif>每天进步一点点 ヾ(≧▽≦*)o，Peace</font>

