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

#include "SkeletonAnimationSettings.h"

//(*InternalHeaders(SkeletonAnimationSettings)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "GDL/CommonTools.h"

#undef _
#define _(s)                     wxGetTranslation((L##s))

//(*IdInit(SkeletonAnimationSettings)
const long SkeletonAnimationSettings::ID_STATICTEXT1 = wxNewId();
const long SkeletonAnimationSettings::ID_TEXTCTRL1 = wxNewId();
const long SkeletonAnimationSettings::ID_BUTTON1 = wxNewId();
const long SkeletonAnimationSettings::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SkeletonAnimationSettings,wxDialog)
	//(*EventTable(SkeletonAnimationSettings)
	//*)
END_EVENT_TABLE()

SkeletonAnimationSettings::SkeletonAnimationSettings(wxWindow* parent, Sk::Anim::Animation *animation, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(SkeletonAnimationSettings)
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _("Paramètres de l\'animation"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer2->AddGrowableCol(1);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Période :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	periodTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL1, _("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer2->Add(periodTextCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer3->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button1 = new wxButton(this, ID_BUTTON1, _("Ok"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer3->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button2 = new wxButton(this, ID_BUTTON2, _("Annuler"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer3->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	Center();

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonAnimationSettings::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonAnimationSettings::OnButton2Click);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&SkeletonAnimationSettings::OnClose);
	//*)

	m_animation = animation;

	periodTextCtrl->SetValue(ToString(m_animation->GetPeriod()).c_str());
}

SkeletonAnimationSettings::~SkeletonAnimationSettings()
{
	//(*Destroy(SkeletonAnimationSettings)
	//*)
}

void SkeletonAnimationSettings::OnClose(wxCloseEvent& event)
{
}

void SkeletonAnimationSettings::OnButton1Click(wxCommandEvent& event)
{
    m_animation->SetPeriod(ToFloat(ToString(periodTextCtrl->GetValue())));

    EndModal(1);
}

void SkeletonAnimationSettings::OnButton2Click(wxCommandEvent& event)
{
    EndModal(0);
}

#endif
