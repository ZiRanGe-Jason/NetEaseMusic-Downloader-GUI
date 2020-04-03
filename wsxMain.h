/***************************************************************
 * Name:      wsxMain.h
 * Purpose:   Defines Application Frame
 * Author:    ZiRanGe-Jason ()
 * Created:   2020-04-01
 * Copyright: ZiRanGe-Jason ()
 * License:
 **************************************************************/

#ifndef WSXMAIN_H
#define WSXMAIN_H

//(*Headers(wsxDialog)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class wsxDialog: public wxDialog
{
    public:

        wsxDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~wsxDialog();

    private:

        //(*Handlers(wsxDialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnTextCtrl2Text(wxCommandEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        //*)

        //(*Identifiers(wsxDialog)
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON1;
        static const long ID_STATICTEXT1;
        static const long ID_BUTTON2;
        static const long ID_TEXTCTRL2;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT3;
        static const long ID_TEXTCTRL3;
        //*)

        //(*Declarations(wsxDialog)
        wxButton* Button1;
        wxButton* Button2;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxTextCtrl* TextCtrl1;
        wxTextCtrl* TextCtrl2;
        wxTextCtrl* TextCtrl3;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // WSXMAIN_H
