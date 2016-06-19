# deagleUI
A UI Library for the Source Engine - Can be modified to work with DirectX/OpenGL as well.

This library was a recode of DUI v1 and was created in 2015 but was never finished, It's a pretty decent base that with a bit of work can be completed. 


Unfortunatly I never got a chance to finish some things I wanted to like the ThemeManager and all the controls.

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


I don't have a screenshot of DUI v2 but here is one from DUI v1 that worked in pretty much the exact same way.

![DeagleUI v1](http://i.imgur.com/n9Dlg3e.jpg)