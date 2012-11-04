#ifndef TEMPLATECREATOR_H
#define TEMPLATECREATOR_H

#ifdef GD_IDE_ONLY

//(*Headers(TemplateCreator)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

#include <wx/aui/aui.h>
#include <wx/propgrid/propgrid.h>

namespace Sk
{
    class Skeleton;
    namespace Anim
    {
        class Animation;
    }
}

class TemplateCreator: public wxDialog
{
	public:

		TemplateCreator(Sk::Skeleton *ske, Sk::Anim::Animation *anim, wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~TemplateCreator();

		//(*Declarations(TemplateCreator)
		wxPanel* Core;
		wxFlexGridSizer* propertyGridSizer;
		wxPanel* propertyGridPanel;
		wxCheckBox* saveImageKeyFrames;
		wxTextCtrl* descriptionTextCtrl;
		wxCheckBox* saveLengthKeyFrames;
		wxCheckBox* saveAngleKeyFrames;
		wxButton* saveButton;
		wxStaticText* StaticText1;
		wxCheckBox* saveOffsetKeyFrames;
		wxButton* cancelButton;
		//*)

	protected:

		//(*Identifiers(TemplateCreator)
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT1;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_PANEL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_PANEL2;
		//*)

	private:

		//(*Handlers(TemplateCreator)
		void OnsaveButtonClick(wxCommandEvent& event);
		void OncancelButtonClick(wxCommandEvent& event);
		//*)

		Sk::Skeleton *m_ske;
		Sk::Anim::Animation *m_anim;

        wxAuiManager m_mgr;
		wxPropertyGrid *m_grid;

		DECLARE_EVENT_TABLE()
};

#endif

#endif
