#include "wx/wxprec.h"

// For compilers that support precompilation, includes "wx/wx.h".
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/filename.h"
#include "wx/statbmp.h"
#include "wx/stdpaths.h"
#include "wx/timer.h"

class MovingImagePanel : public wxPanel {
public:
  // wxWidgets library uses wxWindow* to refer to a window.
  MovingImagePanel(wxWindow *parent, const wxBitmap &bitmap)
      : wxPanel{parent}, bitmap_{bitmap} {
    Bind(wxEVT_PAINT, &MovingImagePanel::OnPaint, this);
    Bind(wxEVT_TIMER, &MovingImagePanel::OnTimer, this);

    timer_.SetOwner(this);
    timer_.Start(interval_);
  }

private:
  void OnPaint(wxPaintEvent &event) {
    // Bitmaps are drawable according to ChatGPT
    wxPaintDC dc{this};
    dc.DrawBitmap(bitmap_, xCoord, 0);
  }

  void OnTimer(wxTimerEvent &event) { // Update offset and redraw
    // The right edge of the bitmap touched the right edge of the window.
    if (xCoord + bitmap_.GetWidth() >= GetSize().GetWidth()) {
      direction_ = Direction::Left;
    }

    // The left edge of the bitmap touched the left edge of the window.
    if (xCoord <= 0) {
      direction_ = Direction::Right;
    }

    xCoord += static_cast<int>(direction_); // Move

    Refresh();
  }

  enum class Direction { Left = -1, Right = 1 };
  Direction direction_{Direction::Right};
  wxBitmap bitmap_;
  int xCoord{0};
  int interval_{10};
  wxTimer timer_;
};

class MyApp : public wxApp {
public:
  auto OnInit() -> bool override;
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

enum class ID { Hello = 1 };

wxIMPLEMENT_APP(MyApp);

auto MyApp::OnInit() -> bool {
  MyFrame *frame{new MyFrame()};
  frame->Show(true);
  return true;
}

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, wxT("Hello World")) {
  wxMenu *menuFile{new wxMenu};
  menuFile->Append(static_cast<int>(ID::Hello), wxT("&Hello...\tCtrl-H"),
                   wxT("Help string shown in status bar for this menu item"));
  menuFile->AppendSeparator();
  menuFile->Append(wxID_EXIT);

  wxMenu *menuHelp{new wxMenu};
  menuHelp->Append(wxID_ABOUT);

  wxMenuBar *menuBar{new wxMenuBar};
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuHelp, "&Help");

  SetMenuBar(menuBar);

  CreateStatusBar();
  SetStatusText(wxT("Welcome to wxWidgets!"));

  wxPanel *panel{new wxPanel(this, wxID_ANY)};

  wxButton *btn{
      new wxButton(panel, wxID_ANY, wxT("Click Me"), wxPoint(50, 50))};

  wxImage::AddHandler(new wxPNGHandler);

  // Use path to the executable because it is easier to manage image location
  // relative to the binary.
  wxFileName exe_path{wxStandardPaths::Get().GetExecutablePath()};

  // https://stackoverflow.com/questions/13360475/wxwidgets-are-there-functions-for-a-path-manipulation-split-to-subdirs-join
  wxFileName girl_path;
  girl_path.SetPath(exe_path.GetPath());
  girl_path.AppendDir("image");
  girl_path.SetName("girl");
  girl_path.SetExt("png");

  wxImage girl_image;

  if (girl_image.LoadFile(girl_path.GetFullPath(), wxBITMAP_TYPE_PNG)) {
    constexpr float percent{0.5};
    const int width{
        static_cast<int>(static_cast<float>(girl_image.GetWidth()) * percent)};
    const int height{
        static_cast<int>(static_cast<float>(girl_image.GetHeight()) * percent)};

    girl_image.Rescale(width, height);

    wxBitmap girl_bitmap(girl_image);

    new wxStaticBitmap(panel, wxID_ANY, girl_bitmap, wxPoint(150, 150),
                       wxSize(girl_bitmap.GetWidth(), girl_bitmap.GetHeight()));
  } else {
    wxMessageBox(wxT("Failed to load ") + girl_path.GetFullName(), wxT("Error"),
                 wxOK | wxICON_ERROR);
  }

  wxFileName guy_path;
  guy_path.SetPath(exe_path.GetPath());
  guy_path.AppendDir("image");
  guy_path.SetName("guy");
  guy_path.SetExt("png");

  wxImage guy_image;

  if (guy_image.LoadFile(guy_path.GetFullPath(), wxBITMAP_TYPE_PNG)) {
    constexpr float percent{0.1};
    const int width{
        static_cast<int>(static_cast<float>(guy_image.GetWidth()) * percent)};
    const int height{
        static_cast<int>(static_cast<float>(guy_image.GetHeight()) * percent)};

    guy_image.Rescale(width, height);

    wxBitmap guy_bitmap{guy_image};

    new wxStaticBitmap(panel, wxID_ANY, guy_bitmap, wxPoint(50, 100),
                       wxSize(guy_bitmap.GetWidth(), guy_bitmap.GetHeight()));
  } else {
    wxMessageBox(wxT("Failed to load ") + guy_path.GetFullName(), wxT("Error"),
                 wxOK | wxICON_ERROR);
  }

  // Wrap in lambda to make the functionality more distinguishable and make it
  // easier for removal.
  auto splitAndAnimate{[this, &panel, &girl_image]() {
    wxBoxSizer *sizer{new wxBoxSizer(wxHORIZONTAL)};
    // Image is convertible to bitmap
    MovingImagePanel *movingImagePanel{
        new MovingImagePanel{this, wxBitmap{girl_image}}};

    // Make the panels play together nicely
    sizer->Add(movingImagePanel, 1, wxEXPAND | wxALL, 5);
    sizer->Add(panel, 1, wxEXPAND | wxALL, 5);

    this->SetSizer(sizer);
  }};

  splitAndAnimate();

  Bind(wxEVT_BUTTON, &MyFrame::OnClick, this);
  Bind(wxEVT_MENU, &MyFrame::OnHello, this, static_cast<int>(ID::Hello));
  Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}

void MyFrame::OnExit(wxCommandEvent &event) { Close(true); }

void MyFrame::OnAbout(wxCommandEvent &event) {
  wxMessageBox(wxT("This is a wxWidgets Hello World example"),
               wxT("About Hello World"), wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent &event) {
  wxLogMessage(wxT("Hello world from wxWidgets!"));
}

void MyFrame::OnClick(wxCommandEvent &event) {
  wxMessageBox(wxT("Button Clicked!"), wxT("Information"),
               wxOK | wxICON_INFORMATION);
}
