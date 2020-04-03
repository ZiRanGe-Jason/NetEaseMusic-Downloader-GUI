/***************************************************************
 * Name:      wsxApp.cpp
 * Purpose:   Code for Application Class
 * Author:    ZiRanGe-Jason ()
 * Created:   2020-04-01
 * Copyright: ZiRanGe-Jason ()
 * License:
 **************************************************************/

#include "wsxApp.h"

//(*AppHeaders
#include "wsxMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(wsxApp);

bool wsxApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	wsxDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
