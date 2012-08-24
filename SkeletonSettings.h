#ifdef GD_IDE_ONLY

#ifndef SKELETONSETTINGS_H
#define SKELETONSETTINGS_H

//(*Headers(SkeletonSettings)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

namespace Sk{class Skeleton;}

class SkeletonSettings: public wxDialog
{
	public:

		SkeletonSettings(wxWindow* parent, Sk::Skeleton *ske, wxWindowID id=wxID_ANY, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize);
		virtual ~SkeletonSettings();

		//(*Declarations(SkeletonSettings)
		wxButton* Button1;
		wxStaticText* StaticText1;
		wxButton* Button2;
		wxTextCtrl* delayCalculationTextCtrl;
		//*)

	protected:

		//(*Identifiers(SkeletonSettings)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(SkeletonSettings)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		//*)

		Sk::Skeleton *skeleton;

		DECLARE_EVENT_TABLE()
};

#endif

#endif
