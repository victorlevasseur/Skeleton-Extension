/*
Copyright (C) 2012 Victor Levasseur

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
  */

#if defined(GD_IDE_ONLY)

#ifndef SKELETONANIMATIONSETTINGS_H
#define SKELETONANIMATIONSETTINGS_H

//(*Headers(SkeletonAnimationSettings)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

#include "Animation.h"

class SkeletonAnimationSettings: public wxDialog
{
	public:

		SkeletonAnimationSettings(wxWindow* parent, Sk::Anim::Animation *animation, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~SkeletonAnimationSettings();

		//(*Declarations(SkeletonAnimationSettings)
		wxTextCtrl* periodTextCtrl;
		wxButton* Button1;
		wxStaticText* StaticText1;
		wxButton* Button2;
		//*)

	protected:

		//(*Identifiers(SkeletonAnimationSettings)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(SkeletonAnimationSettings)
		void OnClose(wxCloseEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		//*)

		Sk::Anim::Animation *m_animation;

		DECLARE_EVENT_TABLE()
};

#endif

#endif
