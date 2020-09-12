# 四象限事件管理器

## 说明

- 自开发自使用，用于提供接口以便于特定人群学习使用Qt

## 需求说明v0.1.1

### 功能需求

1. 添加、删除事项功能：用户能够通过一定的方式，添加所需做的事项，属性包括名称、事项紧急程度、时间（天），并且可以删除这个事项
2. 查看功能：打开软件就能查看当天的四象限以及各自的事项
3. 切换时间功能：可以切换时间（天），以便于对其他时间（天）的事项进行查看

### 可供学习功能

- 基于项目要求，需要能够提供代码接口，以便于不太会的同学往里面添加，只需要了解大致框架，方便添加标准C函数，而不用依赖C++库
- 基于上述要求，初步对于整体项目的要求为：
  1. 可以通过调用dll文件的方式调用此项目，目前只适用于在qt开发中调用
  2. 先提供接口为：可以设置点击某一栏放大，并且可以设置放大程度（大小）
  3. 其余功能暂不考虑，待一期交付后更新

## 后续可添加内容v0.1.1

- 需要基于qt开发，建议qt5.13以上

### 时间切换

- 可以设置日历，以便于查看往期或者未来所需完成的事项
- 在新建事项的界面，可以增加对于事项日期的编辑，以便于将事项分配于不同的日期

### 事项编辑功能

- 可以设置双击事项弹出窗口，在新窗口内可以对事项属性，名称以及日期编辑

### 事项排序功能

- 可以在新建与编辑事项时，增加安排事项完成时间的功能，在表格中可以对事项进行排序，以便于将早一点的事项排在前面

### 界面美化

1. 不同的窗口可以尝试使用不同的背景颜色，这一点需要使用qstylesheet函数实现
2. 每一个事项之后可以增加一个删除按钮以便于快速删除

### 运行环境

- 可以尝试对项目进行重构，使用qt for Android使得生成apk文件以便于可以在安卓系统上使用

## 功能说明v0.1.1

- 现版本已经可供使用，下载EXE压缩包之后，解压即可

### 功能

- 新建事项，可选择事项的等级
- 双击事项删除该事项
- 点击保存可以将目前的所有事项保存在本地Data.xml文件内，会2覆盖原有数据
- 点击导入会将事先保存的事项导入表格
- 实时显示时间

------

## 开发流程

### 8月13日

- 建立项目
- 思索开发方向

### 8月16日

- 说明：
  - 发现GitHub上没有可以很好参考的项目，故不再依赖GitHub
  - 今天在星巴克进行一些开发，14:00-18:00共4小时
- 预计目标
  1. 设计好整个开发所需的功能，界面等，完成大致的开发需求说明
  2. 完成界面开发以及其他部分功能
- 思路
  1. 需求文档写于上方
  2. 先正常开发功能，接口功能日后再加
  3. 建立窗口，横向分割，再对于每一个窗口纵向分割
- 预计明天
  - 做完，数据暂时使用txt文档存储

## 8月19日

- 说明
  - 下周一需要交付，所以这周工作日尽量完成，周末进行修改
- 预计目标
  - 完成，数据暂时使用txt文档存储
- 思路
  1. 先将新建事项的内容完成
     1. 菜单选择四种类型，点取消退出，点确认退出并添加
  2. 再进行存储设计，包括读取写入

### 8月21日

- 预计目标
- 预计明天
  - 上午：做完基本新建功能以及删除功能
  - 下午：完成数据存储等其余

### 8月22日

- 预计目标
  - 上午：完成基本功能以及删除功能
  - 下午：完成数据存储等其余功能
- 思路
  - 菜单选择四种类型，点取消退出，点确认退出并添加

### 8月23日

- 预计目标
  - 完成全部
- 思路
  - 先将基本功能完成，创建，添加，删除等
    - 测试：双击item弹出窗口，可编辑，可删除
    - 目前双击删除item
  - 再进行数据的存储功能
    - 先做保存数据的功能，使用xml文件保存数据
    - 再做读取数据的功能