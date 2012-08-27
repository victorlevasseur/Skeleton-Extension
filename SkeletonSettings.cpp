#ifdef GD_IDE_ONLY

#include "SkeletonSettings.h"

//(*InternalHeaders(SkeletonSettings)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "Skeleton.h"
#include "SkeletonAnimator.h"
#include "GDL/CommonTools.h"

#undef _
#define _(s)                     wxGetTranslation((L##s))

//(*IdInit(SkeletonSettings)
const long SkeletonSettings::ID_STATICTEXT1 = wxNewId();
const long SkeletonSettings::ID_TEXTCTRL1 = wxNewId();
const long SkeletonSettings::ID_BUTTON1 = wxNewId();
const long SkeletonSettings::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SkeletonSettings,wxDialog)
	//(*EventTable(SkeletonSettings)
	//*)
END_EVENT_TABLE()

SkeletonSettings::SkeletonSettings(wxWindow* parent, Sk::Skeleton *ske, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(SkeletonSettings)
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;
	
	Create(parent, id, _("Paramètre du squelette"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(301,84));
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer2->AddGrowableCol(1);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Délai entre calculs :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	delayCalculationTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL1, _("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer2->Add(delayCalculationTextCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer3->Add(-1,-1,1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button1 = new wxButton(this, ID_BUTTON1, _("Ok"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer3->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button2 = new wxButton(this, ID_BUTTON2, _("Annuler"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer3->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->SetSizeHints(this);
	Center();
	
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonSettings::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonSettings::OnButton2Click);
	//*)

	skeleton = ske;

	delayCalculationTextCtrl->SetValue(ToString(skeleton->GetAnimator().GetDelayBetweenCalculations()));
}

SkeletonSettings::~SkeletonSettings()
{
	//(*Destroy(SkeletonSettings)
	//*)
}


void SkeletonSettings::OnButton1Click(wxCommandEvent& event)
{
    skeleton->GetAnimator().SetDelayBetweenCalculations(ToFloat(ToString(delayCalculationTextCtrl->GetValue())));

    EndModal(1);
}

void SkeletonSettings::OnButton2Click(wxCommandEvent& event)
{
    EndModal(0);
}

#endif
