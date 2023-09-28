# StartPoint
SP Game Engine

## Editor界面
<div align = center>
<img src="https://github.com/CsbDontLikeCode/StartPoint/blob/main/imgs/Editor.png" width="800">
</div>


## StartPoint游戏引擎简介
1.StartPoint引擎使用ImGUI(Docking)版本制作GUI，任意子窗口都可以附着在主窗体中并随意改变宽度或者高度以适配整体界面。<br>
2.StartPoint引擎对OpenGL图形API进行了封装，提供的接口可支持用户进行图形绘制，只需要调用对应函数并配以简单参数即可在渲染界面中看到对应的图形。<br>
3.StartPoint引擎采用游戏对象组件化管理，任何创建的游戏对象通过添加组件来进行不断完善。<br>
4.StartPoint引擎支持2D物理模拟。<br>

## StartPoint编辑器支持如下功能
1.新建场景/保存场景<br>
2.快捷添加与删除游戏实体<br>
3.快捷添加与删除选中的游戏实体的组件(包括Transform，相机，色彩/纹理，刚体，碰撞检测等)。<br>
4.渲染界面物体快速选取、拖拽、缩放、旋转，渲染界面视角转换<br>
5.资源浏览器，可快速查看当前项目所包含的资源，可以将资源直接拖拽至渲染界面中或是拖拽至游戏对象控件中。<br>
6.支持编辑模式与运行模式，运行模式下会自动进行2D物理模拟。<br>
7.当前场景渲染状态显示，包括被选中物体信息，当前场景绘制面数信息等。<br>

## 快捷键功能
1.ctrl + shift + d => 快捷复制当前选中游戏实体 <br>