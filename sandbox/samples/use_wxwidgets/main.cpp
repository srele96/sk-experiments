// wxWidgets "Hello World" Program

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/filename.h"
#include "wx/statbmp.h"
#include "wx/stdpaths.h"

class MyApp : public wxApp {
public:
  virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
  MyFrame();

private:
  void OnHello(wxCommandEvent &event);
  void OnExit(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
  void OnClick(wxCommandEvent &event);
};

enum { ID_Hello = 1 };

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
  MyFrame *frame = new MyFrame();
  frame->Show(true);
  return true;
}

MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "Hello World") {
  wxMenu *menuFile = new wxMenu;
  menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                   "Help string shown in status bar for this menu item");
  menuFile->AppendSeparator();
  menuFile->Append(wxID_EXIT);

  wxMenu *menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);

  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuHelp, "&Help");

  SetMenuBar(menuBar);

  CreateStatusBar();
  SetStatusText("Welcome to wxWidgets!");

  wxPanel *panel{new wxPanel(this, wxID_ANY)};

  wxButton *btn{new wxButton(panel, wxID_ANY, "Click Me", wxPoint(50, 50))};

  wxImage::AddHandler(new wxPNGHandler);

  wxBitmap bitmap;
  // https://stackoverflow.com/questions/13360475/wxwidgets-are-there-functions-for-a-path-manipulation-split-to-subdirs-join
  wxFileName exePath{wxStandardPaths::Get().GetExecutablePath()};
  wxFileName girlPath;
  girlPath.SetPath(exePath.GetPath());
  girlPath.AppendDir("image");
  girlPath.SetName("girl");
  girlPath.SetExt("png");

  if (bitmap.LoadFile(girlPath.GetFullPath(), wxBITMAP_TYPE_PNG)) {
    new wxStaticBitmap(panel, wxID_ANY, bitmap, wxPoint(150, 150),
                       wxSize(bitmap.GetWidth(), bitmap.GetHeight()));
  } else {
    wxMessageBox("Failed to load " + girlPath.GetFullName(), "Error",
                 wxOK | wxICON_ERROR);
  }

  Bind(wxEVT_BUTTON, &MyFrame::OnClick, this);
  Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
  Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}

void MyFrame::OnExit(wxCommandEvent &event) { Close(true); }

void MyFrame::OnAbout(wxCommandEvent &event) {
  wxMessageBox("This is a wxWidgets Hello World example", "About Hello World",
               wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent &event) {
  wxLogMessage("Hello world from wxWidgets!");
}

void MyFrame::OnClick(wxCommandEvent &event) {
  wxMessageBox("Button Clicked!", "Information", wxOK | wxICON_INFORMATION);
}
