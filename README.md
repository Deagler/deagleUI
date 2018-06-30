# deagleUI
A UI Library for the Source Engine - Can be modified to work with DirectX/OpenGL as well.

This library was a recode of DUI v1 and was created in 2015.

## Usage:

Call `DUI::Init();` on inject 


Call `DUI::controlhandler::Paint();` in your paint hook/loop.

## Example Control Creation

```
DUI::controls::Frame *frame = DUI::Create::Frame();
frame->Center();

DUI::controls::Button *button = DUI::Create::Button(frame);
button->SetPos(300, 300);
button->SetText("Button");
button->evMouseLeftUp = [button](const MouseData &m) { toolkit::debug::Log(WHITE, "Button Clicked!"); };
```


![DeagleUI](http://i.imgur.com/n9Dlg3e.jpg)
