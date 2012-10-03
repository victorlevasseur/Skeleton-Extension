#include "TemplateCreator.h"

#ifdef GD_IDE_ONLY

//(*InternalHeaders(TemplateCreator)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(TemplateCreator)
const long TemplateCreator::ID_STATICTEXT1 = wxNewId();
const long TemplateCreator::ID_CHECKBOX1 = wxNewId();
const long TemplateCreator::ID_CHECKBOX2 = wxNewId();
const long TemplateCreator::ID_CHECKBOX3 = wxNewId();
const long TemplateCreator::ID_CHECKBOX4 = wxNewId();
const long TemplateCreator::ID_PANEL1 = wxNewId();
const long TemplateCreator::ID_BUTTON1 = wxNewId();
const long TemplateCreator::ID_BUTTON2 = wxNewId();
const long TemplateCreator::ID_PANEL2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(TemplateCreator,wxDialog)
	//(*EventTable(TemplateCreator)
	//*)
END_EVENT_TABLE()

TemplateCreator::TemplateCreator(Sk::Skeleton *ske, Sk::Anim::Animation *anim, wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(TemplateCreator)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _("Créer un modèle"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(1, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	Core = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	FlexGridSizer5 = new wxFlexGridSizer(3, 1, 0, 0);
	FlexGridSizer5->AddGrowableCol(0);
	FlexGridSizer5->AddGrowableRow(1);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, Core, _("Type de frames clés"));
	FlexGridSizer2 = new wxFlexGridSizer(6, 1, 0, 0);
	StaticText1 = new wxStaticText(Core, ID_STATICTEXT1, _("Cochez les types de frame clés qui doivent être sauvegardés dans le modèle."), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	saveAngleKeyFrames = new wxCheckBox(Core, ID_CHECKBOX1, _("Angles des os"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	saveAngleKeyFrames->SetValue(true);
	FlexGridSizer2->Add(saveAngleKeyFrames, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	saveLengthKeyFrames = new wxCheckBox(Core, ID_CHECKBOX2, _("Longueurs des os"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	saveLengthKeyFrames->SetValue(true);
	FlexGridSizer2->Add(saveLengthKeyFrames, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	saveOffsetKeyFrames = new wxCheckBox(Core, ID_CHECKBOX3, _("Décalages des os"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	saveOffsetKeyFrames->SetValue(true);
	FlexGridSizer2->Add(saveOffsetKeyFrames, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	saveImageKeyFrames = new wxCheckBox(Core, ID_CHECKBOX4, _("Images des os"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	saveImageKeyFrames->SetValue(true);
	FlexGridSizer2->Add(saveImageKeyFrames, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer5->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, Core, _("Descriptions des os"));
	FlexGridSizer4 = new wxFlexGridSizer(1, 1, 0, 0);
	FlexGridSizer4->AddGrowableCol(0);
	FlexGridSizer4->AddGrowableRow(0);
	propertyGridPanel = new wxPanel(Core, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	propertyGridSizer = new wxFlexGridSizer(1, 1, 0, 0);
	propertyGridSizer->AddGrowableCol(0);
	propertyGridSizer->AddGrowableRow(0);
	propertyGridPanel->SetSizer(propertyGridSizer);
	propertyGridSizer->Fit(propertyGridPanel);
	propertyGridSizer->SetSizeHints(propertyGridPanel);
	FlexGridSizer4->Add(propertyGridPanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	StaticBoxSizer2->Add(FlexGridSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer5->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	saveButton = new wxButton(Core, ID_BUTTON1, _("Enregistrer..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer3->Add(saveButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cancelButton = new wxButton(Core, ID_BUTTON2, _("Annuler"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer3->Add(cancelButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(FlexGridSizer3, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	Core->SetSizer(FlexGridSizer5);
	FlexGridSizer5->Fit(Core);
	FlexGridSizer5->SetSizeHints(Core);
	FlexGridSizer1->Add(Core, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	//*)

	m_ske = ske;
	m_anim = anim;

	m_mgr.SetManagedWindow( this );
    m_mgr.AddPane( Core, wxAuiPaneInfo().Name( wxT( "Core" ) ).Center().CaptionVisible(false) );
    m_mgr.SetFlags( wxAUI_MGR_ALLOW_FLOATING | wxAUI_MGR_ALLOW_ACTIVE_PANE | wxAUI_MGR_TRANSPARENT_HINT
                    | wxAUI_MGR_TRANSPARENT_DRAG | wxAUI_MGR_HINT_FADE | wxAUI_MGR_NO_VENETIAN_BLINDS_FADE );
    m_mgr.Update();

	// Init PropertyGrid

    m_grid = new wxPropertyGrid(
        propertyGridPanel, // parent
        wxNewId(), // id
        wxDefaultPosition, // position
        wxDefaultSize, // size
        wxPG_SPLITTER_AUTO_CENTER |
        wxPG_DEFAULT_STYLE );

    m_grid->SetExtraStyle( wxPG_EX_HELP_AS_TOOLTIPS );
    propertyGridSizer->Add(m_grid, 1, wxALL|wxEXPAND, 0);

    m_grid->Append( new wxPropertyCategory(_("Identification"), "Identification") );

    SetSize(500,700);
}

TemplateCreator::~TemplateCreator()
{
    m_mgr.UnInit();
	//(*Destroy(TemplateCreator)
	//*)
}

#endif
