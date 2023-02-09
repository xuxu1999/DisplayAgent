# dispalyAgent学习记录

* WinBase

![image-20230206184051538](./assets/image-20230206184051538.png)



* 字符集问题 解决办法https://blog.csdn.net/kieson_uabc/article/details/109672682

  ![image-20230206185350283](./assets/image-20230206185350283.png)

Q：窗口关闭后，进程并未结束

## 字符编码

## 窗口

> * 注册窗口类
> * 窗口创建

## 消息

> * 消息基础
> * 创建消息



# 项目问题

![image-20230209223408260](./assets/image-20230209223408260.png)

```c
BOOL CALLBACK DialogProc(HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam);
```

64位返回值用 LRESULT ,32位用BOOL

> ![image-20230209223716217](./assets/image-20230209223716217.png)



Dialog

> ![image-20230210002204808](./assets/image-20230210002204808.png)

![image-20230210011026549](./assets/image-20230210011026549.png)

* 2023.2.10
* ![image-20230210013534516](./assets/image-20230210013534516.png)

> 目前只是一个静态界面