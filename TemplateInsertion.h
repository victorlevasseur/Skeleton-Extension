#ifndef TEMPLATEINSERTION_H
#define TEMPLATEINSERTION_H

#ifdef GD_IDE_ONLY

//(*Headers(TemplateInsertion)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)
#include <wx/propgrid/propgrid.h>

#include "Template.h"
#include "Animation.h"
#include "Skeleton.h"

class TemplateInsertion: public wxDialog
{
	public:

		TemplateInsertion(wxWindow* parent, Sk::Anim::Animation *animation, Sk::Skeleton *skeleton, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~TemplateInsertion();

		//(*Declarations(TemplateInsertion)
		wxFlexGridSizer* propertyGridSizer;
		wxPanel* propertyGridPanel;
		wxStaticText* descriptionLabel;
		wxStaticText* StaticText1;
		wxButton* cancelBt;
		wxStaticLine* StaticLine1;
		wxButton* validBt;
		//*)

	protected:

		//(*Identifiers(TemplateInsertion)
		static const long ID_STATICTEXT2;
		static const long ID_STATICLINE1;
		static const long ID_STATICTEXT1;
		static const long ID_PANEL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(TemplateInsertion)
		void OnvalidBtClick(wxCommandEvent& event);
		void OncancelBtClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

		wxPropertyGrid *m_grid;
		wxArrayString boneNamesList;

		Sk::Anim::Template m_template;
		Sk::Anim::Animation *m_animation;
};

#endif

#endif
