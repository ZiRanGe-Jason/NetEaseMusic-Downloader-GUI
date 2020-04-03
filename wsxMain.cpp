/***************************************************************
 * Name:      wsxMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    ZiRanGe-Jason ()
 * Created:   2020-04-01
 * Copyright: ZiRanGe-Jason ()
 * License:
 **************************************************************/

#include "wsxMain.h"
#include<iostream>
#include<cstdio>
#include <regex>
#include <fstream>
#include<string>
#include<cstdlib>
#include <windows.h>
#include <shellapi.h>
using namespace std;
#include <wx/msgdlg.h>

//(*InternalHeaders(wsxDialog)
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(wsxDialog)
const long wsxDialog::ID_TEXTCTRL1 = wxNewId();
const long wsxDialog::ID_BUTTON1 = wxNewId();
const long wsxDialog::ID_STATICTEXT1 = wxNewId();
const long wsxDialog::ID_BUTTON2 = wxNewId();
const long wsxDialog::ID_TEXTCTRL2 = wxNewId();
const long wsxDialog::ID_STATICTEXT2 = wxNewId();
const long wsxDialog::ID_STATICTEXT3 = wxNewId();
const long wsxDialog::ID_TEXTCTRL3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wsxDialog,wxDialog)
    //(*EventTable(wsxDialog)
    //*)
END_EVENT_TABLE()

wsxDialog::wsxDialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(wsxDialog)
    Create(parent, id, _("NetEaseMusic-Downloader GUI"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxSize(431,105));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTION));
    TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("填入歌曲网页链接"), wxPoint(64,8), wxSize(256,22), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    Button1 = new wxButton(this, ID_BUTTON1, _("获取"), wxPoint(336,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Button1->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));
    Button1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_SCROLLBAR));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("链接"), wxPoint(16,8), wxSize(32,24), 0, _T("ID_STATICTEXT1"));
    Button2 = new wxButton(this, ID_BUTTON2, _("关于"), wxPoint(336,40), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Button2->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_SCROLLBAR));
    TextCtrl2 = new wxTextCtrl(this, ID_TEXTCTRL2, _(".\\music\\"), wxPoint(64,72), wxSize(256,22), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("保存位置"), wxPoint(8,72), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("歌曲名"), wxPoint(16,40), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    TextCtrl3 = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxPoint(64,40), wxSize(256,22), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    TextCtrl3->Disable();

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wsxDialog::OnButton1Click);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wsxDialog::OnButton2Click);
    Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&wsxDialog::OnTextCtrl2Text);
    //*)
}

wsxDialog::~wsxDialog()
{
    //(*Destroy(wsxDialog)
    //*)
}

void wsxDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

std::string __getlink(std::string address) {//获取链接核心算法（由BoringHacker编写）
	int pos = 0, mark = 0, length = address.size();;
	std::string result;
	for (; pos < length; ++pos) {
		if (address[pos] == '=') {
			mark = 1;
			continue;
		}
		if (mark == 1 && !isdigit(address[pos])) break;
		if (mark == 1) {
			result.push_back(address[pos]);
		}
	}
	return result + ".mp3";
}

std::string getlink(std::string address){

    return "http://music.163.com/song/media/outer/url?id="+__getlink(address);

}

wstring StringToLPCWSTR(string str) {//字符串转换

    int num = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    wchar_t *wide = new wchar_t[num];
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wide, num);
    std::wstring w_str(wide);
    delete[] wide;
    return w_str;
}

void download(string fil,string url){//调用CertUtil下载
	_wsystem(StringToLPCWSTR("certutil -urlcache -split -f "+url+" \""+fil+"\"").c_str());
	return;
}


void wsxDialog::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void wsxDialog::OnButton1Click(wxCommandEvent& event)
{
    //预处理
    system("del webside.html");
    wxString __address = this->TextCtrl1->GetValue(),__path=this->TextCtrl2->GetValue();
    std::string address=__address.ToStdString(),path=__path.ToStdString();

    //获取下载链
    std::string link=getlink(address);

    //爬虫获取歌曲名称
    download("webside.html",address);
    string html="",cache="",song="";
    ifstream infile;
	infile.open("webside.html");
	while(getline(infile,cache))html+=cache,html+='\n';
	infile.close();
	string pattern("<em class=\"f-ff2\">[^>]*</em>");
	regex r(pattern);
	for (sregex_iterator it(html.begin(), html.end(), r), end; it != end; ++it) {
		song = it->str();
		if(song!="")break;
	}
	song=song.substr(18,song.length()-23);
	this->TextCtrl3->SetValue(wxString(song+".mp3"));
	//if(this->TextCtrl3->GetValue()==NULL)return;

	//修正path
	//if(path[path.length()-1]!='\\')path+="\\";

	//下载歌曲
	download(path+song+".mp3",link);

	//提示
	wxMessageBox(wxString("已下载"),wxString("完成"));

}

void wsxDialog::OnTextCtrl2Text(wxCommandEvent& event)
{
}

void wsxDialog::OnButton2Click(wxCommandEvent& event)
{
    wxMessageBox(wxString("NetEaseMusic-Downloader GUI\n作者：ZiRanGe-Jason\n其开发离不开NetEaseMusic-Downloader（作者：BoringHacker）"),wxString("关于"));

}
