/*
 * Name:        src/installer.cpp
 * Purpose:     Installer source code
 * Author:      Raphael G. Grubbauer
 * Created:     16.02.2024
 * Copyright:   (c) 2025 Raphael G. Grubbauer / GSP
 * License:     MathOrDeath EULA
*/

#include "wx/wx.h"

class MyApp : public wxApp {
  public:
  virtual bool OnInit();
};

class MyFrame : public wxFrame {
  public:
  MyFrame();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
  MyFrame *frame = new MyFrame();
  frame->Show(true);
  return true;
}

MyFrame::MyFrame() :
  wxFrame(nullptr, wxID_ANY, "MathOrDeath Installer", wxDefaultPosition,
          wxSize(400, 300)) {}
