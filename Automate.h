
#ifndef Automate_H
#define AutomateV_H

#include <wx/string.h>
#include <wx/choice.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/radiobut.h>
#include <wx/button.h>
#include <wx/listbox.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/menu.h>
#include <wx/toolbar.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class vixivframe
///////////////////////////////////////////////////////////////////////////////
class vixivframe : public wxFrame 
{

	private:
	
	protected:
	
		wxChoice* wx_choice;
        wxRadioButton* wx_optionnon;
		wxRadioButton* wx_optiontop;
        wxRadioButton* wx_optionbot;
		wxRadioButton* wx_optionleft;
        wxRadioButton* wx_optionright;
        wxTextCtrl* wx_textadj;
		wxTextCtrl* wx_textbox;
        wxButton* wx_up;
		wxButton* wx_add;
		wxButton* wx_remove;
		wxButton* wx_run;
        wxButton* wx_down;
		wxListBox* wx_listbox;
		wxButton* wx_execute;		
		wxButton* wx_save;	
		vixivframe( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ViXiV Automate Basic"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,562 ), long style = wxMINIMIZE|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~vixivframe();
	
	public:

	
};


class ViXiVFrameBaseClass : public wxFrame
{
	virtual void OnSelect(wxCommandEvent& event) { event.Skip(); }
	virtual void OnSelectListBox(wxCommandEvent& event) { event.Skip(); }
    virtual void OnSelectListBoxDClick(wxCommandEvent& event) { event.Skip(); }
	virtual void OnClickExecute(wxCommandEvent& event) { event.Skip(); }
	virtual void OnClickSave(wxCommandEvent& event) { event.Skip(); }
    virtual void OnClickUp(wxCommandEvent& event) { event.Skip(); }
    virtual void OnClickDown(wxCommandEvent& event) { event.Skip(); }
	virtual void OnClickAdd(wxCommandEvent& event) { event.Skip(); }
	virtual void OnClickRemove(wxCommandEvent& event) { event.Skip(); }
	virtual void OnClickRun(wxCommandEvent& event) { event.Skip(); }
	
protected:
    wxPanel* m_mainPanel;
    wxMenuBar* m_menuBar;
    wxMenu* m_name6;  
    wxMenuItem* m_menuItem9;
	wxMenuItem* m_menuItemN;
	wxMenuItem* m_menuItemL;
	wxMenuItem* m_menuItemS;
    wxMenuItem* m_menuItemQ;
    wxMenu* m_name8;
    wxToolBar* m_mainToolbar;
	wxChoice* wx_choice;
	wxTextCtrl* wx_textbox;
    wxTextCtrl* wx_textadj;
    wxRadioButton* wx_optionnon;
	wxRadioButton* wx_optiontop;
    wxRadioButton* wx_optionbot;
	wxRadioButton* wx_optionleft;
    wxRadioButton* wx_optionright;
    wxButton* wx_up;
	wxButton* wx_run;	
	wxButton* wx_add;
	wxButton* wx_remove;
    wxButton* wx_down;
	wxListBox* wx_listbox;
	wxButton* wx_execute;
	wxButton* wx_save;
	
	virtual void OnNew(wxCommandEvent& event) { event.Skip(); }
	virtual void OnSave(wxCommandEvent& event) { event.Skip(); }
	virtual void OnLoad(wxCommandEvent& event) { event.Skip(); }
    virtual void OnExit(wxCommandEvent& event) { event.Skip(); }
    virtual void OnAbout(wxCommandEvent& event) { event.Skip(); }
	
	virtual void OnChoiceClick(wxCommandEvent& event) { event.Skip(); }

public:
	
	ViXiVFrameBaseClass(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ViXiV Automate Pro"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 443,562 ), long style = wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL );

    //ViXiVFrameBaseClass(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("ViXiV"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxCAPTION|wxRESIZE_BORDER|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxCLOSE_BOX);
    virtual ~ViXiVFrameBaseClass();
};

	
class ViXiVFrame : public ViXiVFrameBaseClass
{
private:
	int Execute_Find();
	
public:
    ViXiVFrame(wxWindow* parent);
    virtual ~ViXiVFrame();

	void OnSelect(wxCommandEvent& event);
	void OnSelectListBox(wxCommandEvent& event);
    void OnSelectListBoxDClick(wxCommandEvent& event);
	void OnClickExecute(wxCommandEvent& event);
	void OnClickSave(wxCommandEvent& event);
	void OnClickAdd(wxCommandEvent& event); 
    void OnClickUp(wxCommandEvent& event);
    void OnClickDown(wxCommandEvent& event);
	void OnClickRemove(wxCommandEvent& event); 
	void OnClickRun(wxCommandEvent& event);
	void OnNew(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
    void OnLoad(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
	int save_script();
};
#endif // Automate_H
