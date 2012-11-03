#include "TemplateInsertion.h"

//(*InternalHeaders(TemplateInsertion)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/filedlg.h>

#include "GDL/CommonTools.h"

//(*IdInit(TemplateInsertion)
const long TemplateInsertion::ID_STATICTEXT1 = wxNewId();
const long TemplateInsertion::ID_PANEL1 = wxNewId();
const long TemplateInsertion::ID_BUTTON1 = wxNewId();
const long TemplateInsertion::ID_BUTTON2 = wxNewId();
//*)

#undef _
#define _(s)                     wxGetTranslation((L##s))

BEGIN_EVENT_TABLE(TemplateInsertion,wxDialog)
	//(*EventTable(TemplateInsertion)
	//*)
END_EVENT_TABLE()

TemplateInsertion::TemplateInsertion(wxWindow* parent, Sk::Anim::Animation *animation, Sk::Skeleton *skeleton, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(TemplateInsertion)
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _("Créer une animation à partir d\'un modèle"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(400,329));
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(1);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Définition du rôle des os du squelette :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	propertyGridPanel = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(274,178), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	propertyGridSizer = new wxFlexGridSizer(0, 3, 0, 0);
	propertyGridSizer->AddGrowableCol(0);
	propertyGridSizer->AddGrowableRow(0);
	propertyGridPanel->SetSizer(propertyGridSizer);
	propertyGridSizer->SetSizeHints(propertyGridPanel);
	FlexGridSizer1->Add(propertyGridPanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	validBt = new wxButton(this, ID_BUTTON1, _("Insérer"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer3->Add(validBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cancelBt = new wxButton(this, ID_BUTTON2, _("Annuler"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer3->Add(cancelBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->SetSizeHints(this);
	//*)

	wxFileDialog openFileDialog(this, _("Sélectionner un modèle"), "", "", "Skeleton templates (*.skt)|*.skt", wxFD_OPEN);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        EndModal(0);     // the user changed idea...

    m_template.LoadFromFile(ToString(openFileDialog.GetPath()));
    m_animation = animation;

    m_grid = new wxPropertyGrid(
        propertyGridPanel, // parent
        wxNewId(), // id
        wxDefaultPosition, // position
        wxDefaultSize, // size
        wxPG_SPLITTER_AUTO_CENTER |
        wxPG_DEFAULT_STYLE );

    m_grid->SetExtraStyle( wxPG_EX_HELP_AS_TOOLTIPS );
    propertyGridSizer->Add(m_grid, 1, wxALL|wxEXPAND, 0);

    m_grid->Append( new wxPropertyCategory(_("Affectation des os"), "Bones") );

    //Request the list of all current skeleton's bones
    std::vector<Sk::Bone*> skeletonBoneList = skeleton->GetBones();
    wxArrayString boneNamesList;
    boneNamesList.Add("");
    for(unsigned int a = 0; a < skeletonBoneList.size(); a++)
    {
        boneNamesList.Add(wxString(skeletonBoneList.at(a)->GetName().c_str()));
    }

    //Create properties for each descriptions
    const std::vector<std::pair<std::string, std::string> > bonesDescList = m_template.GetDescriptions();
    for(unsigned int a = 0; a < bonesDescList.size(); a++)
    {
        m_grid->AppendIn("Bones", new wxEnumProperty(bonesDescList.at(a).second, bonesDescList.at(a).first, boneNamesList));
    }

    SetSize(700,500);
}

TemplateInsertion::~TemplateInsertion()
{
	//(*Destroy(TemplateInsertion)
	//*)
}

