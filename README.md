# 个人项目作业

#### 教学班级:006

#### 项目地址:<https://github.com/themaker123/intersect>



| 项目                                 | 内容                                                         |
| ------------------------------------ | ------------------------------------------------------------ |
| 这个作业属于哪个课程                 | [2020春季计算机学院软件工程(罗杰 任健)](https://edu.cnblogs.com/campus/buaa/BUAA_SE_2020_LJ/homework/10429) |
| 这个作业的要求在哪里                 | [个人项目作业](https://edu.cnblogs.com/campus/buaa/BUAA_SE_2020_LJ/homework/10414) |
| 我在这个课程的目标是                 | 学习工程化开发软件,体验团队开发和结队开发                    |
| 这个作业在哪个具体方面帮助我实现目标 | 通过个人项目作业体会PSP                      |

| PSP2.1                                | 	Personal Software Process Stages|预估耗时（分钟）|实际耗时（分钟）                                                         |
| ------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| Planning                | 计划 |||
|· Estimate                 |估计这个任务需要多少时间 |10|10|
|Development                | 开发                    |||
|· Analysis | · 需求分析 (包括学习新技术)                      |60|90|
|· Design Spec | 	生成设计文档                     |20|20|
| · Design Review | 设计复审 (和同事审核设计文档)                     |10|10|
| · Coding Standard |代码规范 (为目前的开发制定合适的规范)       |10|20|
| · Design | 具体设计                     |60|40|
| · Coding | 具体编码                      |120|160|
| · Code Review | 代码复审                      |30|20|
| · Test | 测试（自我测试，修改代码，提交修改）                      |60|240|
|Reporting | 报告                      |||
| ·Test Report | 测试报告                     |30|20|
| ·Size Measurement | 计算工作量                      |20|10|
| ·Postmortem & Process Improvement Plan | 事后总结, 并提出过程改进计划                     |20|10|
| ·Size Measurement | 合计                      |450|750|

### 解题思路:

- 分别求直线与直线的交点,直线与圆的交点,圆与圆的交点,然后每求出一个交点之后就将其加入到一个集合set中,保证不会重复,这样这个集合的大小就是所求的结果.
- 对于直线的交点采用公式: ``x = (b1*c2-b2*c1)/(a1*b2-a2*b1),y = (a2*c1-a1*c2)/(a1*b2-a2*b1)``
- 对于直线与圆的交点,首先将直线分为斜率不存在和斜率存在的两种情况,然后联立直线方程与圆的方程,就得到坐标,同时根据判别式也可以从中得到坐标的数量.
- 对于圆与圆的交点,两个圆的方程相减,得到一个直线方程,然后求这个直线与圆的交点坐标即可

### 设计实现过程(含代码分析):

- 总体考虑到项目本身的功能非常单一,实现也相对来说比较简单,所以整体只有两个文件``main.cpp``和头文件``global.h``,函数主要有计算直线交点的函数``calaIntersectLineOnly``,计算直线和圆交点的函数``calaIntersectLineCircle``,计算圆与圆交点的函数``calaIntersectCircleOnly``,同时三个累计求所有交点的函数,包括``lineOnly(), lineAndCircle(),  circleOnly();``,数据结构有``Line,dot``等

- 对于直线,首先使用``trans``函数将两个坐标转换为直线的一般表达式即``y = a*x+b*y+c``

  ```c++
  void trans(line &l,int x1,int y1,int x2,int y2) {
  	int a, b, c;
  	a = y1 - y2;
  	b = x2 - x1;
  	c = x1 * y2 - x2 * y1;
  	l.a = a;
  	l.b = b;
  	l.c = c;
  }
  ```

  

- 数据结构

  - 直线(一般表达式),由于圆的表达也是三个参数与直线高度重合,所以为了方便我们采取同样的数据结构来表示圆形.

    ```c++
    struct line {
    	double a;
    	double b;
    	double c;
    };
    ```

  - 交点:

    ```c++
    class dot {
    public:
    	double x;
    	double y;
    	
    	bool operator < (const dot& d)const
    	{
    		if (fabs(d.x - x) < 1e-7 && fabs(d.y - y) < 1e-7) return false;
    		else {
    			if (d.x > x) return true;
    			else if (d.x == x) {
    				if (d.y < y) return true;
    				else return false;
    			}
    			else return false;
    		}
    		
    	}
    };
    ```

- 对于求两个直线的交点,首先判断两个直线是否平行,如果平行则直接退出,否则根据公式求直线的交点,

  ```c++
  int calaIntersectLineOnly(line l0,line l1){
  	double x, y, k;
  	dot d;
  	k = l0.a * l1.b - l0.b * l1.a;//如果k==0则两直线平行
  	if (k == 0) return -1;//平行没有交点
  	d.x =  (l0.b * l1.c - l0.c * l1.b) / k;
  	d.y =  (l1.a * l0.c - l1.c * l0.a) / k;
  	dots.insert(d);
  	return 0;
  }
  ```

- 对于直线与圆的交点,我们首先设法将直线的一般方程转换为斜率式``y=k*x+b``,当然对于斜率不存在的情况,我们需要特殊考虑.然后将直线方程与圆的方程进行联立,得到一个一元二次方程,根据判别式``b^2-4ac``的符号判断交点的数量,如果小于0则没有交点,等于0一个交点,大于零两个交点

  ```c++
  int calaIntersectLineCircle(line l, line circle) {
  	double  a = 0, c = 0, r = 0 ;
  	dot d1, d2;
  	a = circle.a;
  	c = circle.b;
  	r = circle.c;
  	//如果斜率不存在
  	if (l.b == 0) {
  		double t;
  		t= -1 * l.c / l.a;
  		double delt;
  		delt = r * r - a * a - (l.c * l.c + 2 * l.c * a * l.a) / (l.a * l.a);
  		if (delt < 0) return -1;
  		double t1;
  		t1= sqrt(delt);
  		d1.x = t;
  		d1.y = c + t1;
  		d2.x = t;
  		d2.y = c - t1;
  		dots.insert(d1);
  		dots.insert(d2);
  	}
  	else {
  		double b_2 = l.b * l.b;
  		double a2 = b_2+l.a*l.a;
  		double b2 = -2*b_2*a + 2 * l.a * (l.c + l.b * c);
  		double c2 = a*a*b_2 + (l.c + l.b * c) * (l.c + l.b * c) - r*r*b_2;
  		double delt2;
  		delt2 = b2 * b2 - 4 * a2 * c2;
  		if (delt2 < 0) return -1;
  		double delt;
  		delt = sqrt(delt2);
  		d1.x = (-1 * b2 + delt) / (2 * a2);
  		d2.x = (-1 * b2 - delt) / (2 * a2);
  		d1.y = (-l.a*d1.x-l.c)/l.b;
  		d2.y = (-l.a * d2.x - l.c) / l.b;
  		dots.insert(d1);
  		dots.insert(d2);
  	}
  	return 0;
  }
  ```

- 对于圆与圆的交点,整体思路是求圆方程相减后的直线方程,然后这个直线与圆的交点即是两个圆的交点,通过这个转化,我们就不用再额外的计算圆与圆的交点,只需要利用直线与圆的交点的函数即可

  ```c++
  int calaIntersectCircleOnly(line c1, line c2) {
  	double a1 = c1.a, b1 = c1.b, r1 = c1.c;
  	double a2 = c2.a, b2 = c2.b, r2 = c2.c;
  	double a, b, c;
  	a = 2 * (a2 - a1);
  	b = 2 * (b2 - b1);
  	c = a1 * a1 + b1 * b1 - a2 * a2 - b2 * b2 + r2 * r2 - r1 * r1;
  	//得到两圆的交线的方程;
  	line l;
  	l.a = a;
  	l.b = b;
  	l.c = c;
  	if (a == 0 && b == 0) return -1;
  	//if ((a1 - a2) * (a1 - a2) + (b1 - b2) * (b1 - b2) - (r1-r2)*(r1-r2) < 0) return -1;
  	calaIntersectLineCircle(l,c1);
  	return 0;
  }
  ```

- 然后分别求直线与直线的交点,直线与圆的交点,圆与圆的交点,

  ```c++
  lineOnly();
  lineAndCircle();
  circleOnly();
  ```

- 本工程的核心是三个函数: 计算直线与直线交点函数,  计算直线与圆交点函数,  计算圆与圆交点函数, 所以单元测试的核心是以这三个函数为基础,分别测试只有直线的情况, 只有圆的情况, 直线与圆的情况.

  ![1583765018512](C:\Users\13086\AppData\Roaming\Typora\typora-user-images\1583765018512.png)

  

### 改进程序性能:

![1583760081182](C:\Users\13086\AppData\Roaming\Typora\typora-user-images\1583760081182.png)



从图中可以看出``calaIntersectLineCircle``函数占用的时间最多,而这个函数主要是用来计算直线与圆形的交点,

所以,而对这个函数主要进行了以下优化,判断交点的个数减少向set中加入新的dot的次数,因为在这个函数中,set,insert操作又占有相当大的时间.

### 代码风格检查:

![1583762901913](C:\Users\13086\AppData\Roaming\Typora\typora-user-images\1583762901913.png)

