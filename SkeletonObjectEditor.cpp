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

#include "SkeletonObjectEditor.h"

//(*InternalHeaders(SkeletonObjectEditor)
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)
#include <wx/colordlg.h>
#include <wx/filedlg.h>
#include <wx/dcbuffer.h>
#include <wx/textdlg.h>
#include <wx/msgdlg.h>
#include <wx/choicdlg.h>
#include <wx/arrstr.h>

#include "SkeletonAnimationSettings.h"
#include "SkeletonSettings.h"

#include "GDL/Game.h"
#include "SkeletonObject.h"
#include "InterpolationMethods.h"
#include "GDL/IDE/MainEditorCommand.h"
#include "GDCore/IDE/CommonBitmapManager.h"
#include "GDL/CommonTools.h"
#include "GDL/IDE/Dialogs/ResourcesEditor.h"
#include <algorithm>

#undef _
#define _(s)                     wxGetTranslation((L##s))

//(*IdInit(SkeletonObjectEditor)
const long SkeletonObjectEditor::ID_TOGGLEBUTTON1 = wxNewId();
const long SkeletonObjectEditor::ID_TOGGLEBUTTON2 = wxNewId();
const long SkeletonObjectEditor::ID_CHOICE1 = wxNewId();
const long SkeletonObjectEditor::ID_BITMAPBUTTON2 = wxNewId();
const long SkeletonObjectEditor::ID_BITMAPBUTTON4 = wxNewId();
const long SkeletonObjectEditor::ID_BITMAPBUTTON1 = wxNewId();
const long SkeletonObjectEditor::ID_BITMAPBUTTON3 = wxNewId();
const long SkeletonObjectEditor::ID_PANEL3 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON9 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON10 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON7 = wxNewId();
const long SkeletonObjectEditor::ID_PANEL5 = wxNewId();
const long SkeletonObjectEditor::ID_PANEL1 = wxNewId();
const long SkeletonObjectEditor::ID_PANEL4 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON2 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON4 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON6 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON5 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON1 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON3 = wxNewId();
const long SkeletonObjectEditor::ID_PANEL2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SkeletonObjectEditor,wxDialog)
	//(*EventTable(SkeletonObjectEditor)
	//*)
END_EVENT_TABLE()

SkeletonObjectEditor::SkeletonObjectEditor( wxWindow* parent, Game & game_, SkeletonObject & object_, gd::MainFrameWrapper & mainEditorCommand_ ) :
game(game_),
mainEditorCommand(mainEditorCommand_),
object(object_),
skeleton(object.GetSkeleton()),
mode(0)
{
	//(*Initialize(SkeletonObjectEditor)
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxBoxSizer* BoxSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxFlexGridSizer* FlexGridSizer8;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer12;
	wxFlexGridSizer* FlexGridSizer6;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer11;

	Create(parent, wxID_ANY, _("Editeur de squelette"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxCLOSE_BOX|wxMAXIMIZE_BOX, _T("wxID_ANY"));
	FlexGridSizer3 = new wxFlexGridSizer(1, 1, 0, 0);
	FlexGridSizer3->AddGrowableCol(0);
	FlexGridSizer3->AddGrowableRow(0);
	Core = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	FlexGridSizer6 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer6->AddGrowableCol(0);
	FlexGridSizer6->AddGrowableRow(1);
	FlexGridSizer5 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer5->AddGrowableCol(0);
	FlexGridSizer5->AddGrowableRow(1);
	FlexGridSizer11 = new wxFlexGridSizer(0, 6, 0, 0);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	ToggleButton1 = new wxToggleButton(Core, ID_TOGGLEBUTTON1, _("Editeur d\'os"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TOGGLEBUTTON1"));
	ToggleButton1->SetValue(true);
	ToggleButton1->SetToolTip(_("L\'éditeur d\'os permet de créer des os, de les lier ainsi que de définir leur état initial."));
	BoxSizer1->Add(ToggleButton1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, -1);
	ToggleButton2 = new wxToggleButton(Core, ID_TOGGLEBUTTON2, _("Editeur d\'animations"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TOGGLEBUTTON2"));
	ToggleButton2->SetToolTip(_("L\'éditeur d\'animation permet de gérer et de créer des animations en utilisant les os du squelette."));
	BoxSizer1->Add(ToggleButton2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer11->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8 = new wxFlexGridSizer(0, 5, 0, 0);
	AnimationCombobox = new wxChoice(Core, ID_CHOICE1, wxDefaultPosition, wxSize(163,-1), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	FlexGridSizer8->Add(AnimationCombobox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BitmapButton2 = new wxBitmapButton(Core, ID_BITMAPBUTTON2, wxBitmap(wxImage(_T("res/addicon.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
	BitmapButton2->SetToolTip(_("Ajouter une animation"));
	BitmapButton2->SetHelpText(_("Ajouter une animation"));
	FlexGridSizer8->Add(BitmapButton2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BitmapButton4 = new wxBitmapButton(Core, ID_BITMAPBUTTON4, wxBitmap(wxImage(_T("res/copyIcon.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON4"));
	BitmapButton4->SetDefault();
	BitmapButton4->SetToolTip(_("Dupliquer l\'animation sélectionnée"));
	FlexGridSizer8->Add(BitmapButton4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BitmapButton1 = new wxBitmapButton(Core, ID_BITMAPBUTTON1, wxBitmap(wxImage(_T("res/paraJeu16.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	BitmapButton1->SetDefault();
	BitmapButton1->SetToolTip(_("Configurer l\'animation..."));
	BitmapButton1->SetHelpText(_("Configurer l\'animation"));
	FlexGridSizer8->Add(BitmapButton1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BitmapButton3 = new wxBitmapButton(Core, ID_BITMAPBUTTON3, wxBitmap(wxImage(_T("res/deleteicon.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON3"));
	BitmapButton3->SetToolTip(_("Supprimer l\'animation"));
	BitmapButton3->SetHelpText(_("Supprimer l\'animation"));
	FlexGridSizer8->Add(BitmapButton3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer11->Add(FlexGridSizer8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(FlexGridSizer11, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	timelinePanel = new wxPanel(Core, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
	FlexGridSizer12 = new wxFlexGridSizer(0, 4, 0, 0);
	FlexGridSizer12->AddGrowableCol(0);
	Panel2 = new wxPanel(timelinePanel, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	FlexGridSizer12->Add(Panel2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer2 = new wxBoxSizer(wxVERTICAL);
	Button4 = new wxButton(timelinePanel, ID_BUTTON9, _("Zoomer"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON9"));
	BoxSizer2->Add(Button4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	Button5 = new wxButton(timelinePanel, ID_BUTTON10, _("Dézoomer"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON10"));
	BoxSizer2->Add(Button5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	Button6 = new wxButton(timelinePanel, ID_BUTTON7, _("Aller à..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
	BoxSizer2->Add(Button6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer12->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	timelinePanel->SetSizer(FlexGridSizer12);
	FlexGridSizer12->Fit(timelinePanel);
	FlexGridSizer12->SetSizeHints(timelinePanel);
	FlexGridSizer5->Add(timelinePanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer6->Add(FlexGridSizer5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	FlexGridSizer1 = new wxFlexGridSizer(1, 3, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	Panel1 = new wxPanel(Core, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2->AddGrowableCol(0);
	FlexGridSizer2->AddGrowableRow(0);
	propertyGridPanel = new wxPanel(Core, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	propertyGridSizer = new wxFlexGridSizer(1, 1, 0, 0);
	propertyGridSizer->AddGrowableCol(0);
	propertyGridSizer->AddGrowableRow(0);
	propertyGridPanel->SetSizer(propertyGridSizer);
	propertyGridSizer->Fit(propertyGridPanel);
	propertyGridSizer->SetSizeHints(propertyGridPanel);
	FlexGridSizer2->Add(propertyGridPanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer4 = new wxFlexGridSizer(1, 2, 0, 0);
	addChildBoneBt = new wxButton(Core, ID_BUTTON2, _("Ajouter un os enfant"), wxDefaultPosition, wxSize(292,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer4->Add(addChildBoneBt, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	deleteBoneBt = new wxButton(Core, ID_BUTTON4, _("Supprimer"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer4->Add(deleteBoneBt, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer2->Add(FlexGridSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	FlexGridSizer6->Add(FlexGridSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	FlexGridSizer7 = new wxFlexGridSizer(0, 4, 0, 0);
	Button3 = new wxButton(Core, ID_BUTTON6, _("Banque d\'image"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
	FlexGridSizer7->Add(Button3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button1 = new wxButton(Core, ID_BUTTON5, _("Paramètres du squelette..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FlexGridSizer7->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ValidateButton = new wxButton(Core, ID_BUTTON1, _("Valider"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	ValidateButton->SetDefault();
	FlexGridSizer7->Add(ValidateButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button2 = new wxButton(Core, ID_BUTTON3, _("Annuler"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer7->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(FlexGridSizer7, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	Core->SetSizer(FlexGridSizer6);
	FlexGridSizer6->Fit(Core);
	FlexGridSizer6->SetSizeHints(Core);
	FlexGridSizer3->Add(Core, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	SetSizer(FlexGridSizer3);
	FlexGridSizer3->Fit(this);
	FlexGridSizer3->SetSizeHints(this);
	Center();

	Connect(ID_TOGGLEBUTTON1,wxEVT_COMMAND_TOGGLEBUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnToggleButton1Toggle);
	Connect(ID_TOGGLEBUTTON2,wxEVT_COMMAND_TOGGLEBUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnToggleButton2Toggle);
	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&SkeletonObjectEditor::OnAnimationComboboxSelect);
	Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnBitmapButton2Click);
	Connect(ID_BITMAPBUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnBitmapButton4Click);
	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnBitmapButton1Click);
	Connect(ID_BITMAPBUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnBitmapButton3Click);
	Panel2->Connect(wxEVT_PAINT,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel2Paint,0,this);
	Panel2->Connect(wxEVT_ERASE_BACKGROUND,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel2EraseBackground,0,this);
	Panel2->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel2LeftDown,0,this);
	Panel2->Connect(wxEVT_RIGHT_DOWN,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel2RightDown,0,this);
	Panel2->Connect(wxEVT_RIGHT_UP,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel2RightUp,0,this);
	Panel2->Connect(wxEVT_MOUSEWHEEL,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel2MouseWheel,0,this);
	Panel2->Connect(wxEVT_SIZE,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel2Resize,0,this);
	Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnButton4Click);
	Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnButton5Click);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnButton6Click);
	Panel1->Connect(wxEVT_PAINT,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1Paint,0,this);
	Panel1->Connect(wxEVT_ERASE_BACKGROUND,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1EraseBackground,0,this);
	Panel1->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1LeftDown,0,this);
	Panel1->Connect(wxEVT_RIGHT_DOWN,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1RightDown,0,this);
	Panel1->Connect(wxEVT_RIGHT_UP,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1RightUp,0,this);
	Panel1->Connect(wxEVT_MOTION,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1MouseMove,0,this);
	Panel1->Connect(wxEVT_SIZE,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1Resize,0,this);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnaddChildBoneBtClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OndeleteBoneBtClick);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnButton3Click);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnButton1Click1);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnValidateButtonClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnButton2Click);
	Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&SkeletonObjectEditor::OnInit);
	//*)

	resourcesEditor = new ResourcesEditor( this, game, mainEditorCommand );
    resourcesEditor->Refresh();

	m_mgr.SetManagedWindow( this );
    m_mgr.AddPane( Core, wxAuiPaneInfo().Name( wxT( "Core" ) ).Center().CaptionVisible(false) );
    m_mgr.AddPane( resourcesEditor, wxAuiPaneInfo().Name( wxT( "EI" ) ).Left().Caption( _T( "Editeur de la banque d'images" ) ).MaximizeButton( true ).MinimizeButton( false ).Show(false).MinSize(150, 100) );
    m_mgr.SetFlags( wxAUI_MGR_ALLOW_FLOATING | wxAUI_MGR_ALLOW_ACTIVE_PANE | wxAUI_MGR_TRANSPARENT_HINT
                    | wxAUI_MGR_TRANSPARENT_DRAG | wxAUI_MGR_HINT_FADE | wxAUI_MGR_NO_VENETIAN_BLINDS_FADE );
    m_mgr.Update();

    PreparePropertyGrid();

    offset = sf::Vector2f(20, 20);
    isDragging = false;
    selectedBone = 0;

    timeline_current = 0;
    timeline_currentAnim = 0;
    timeline_offset = 0;
    timeline_scale = 5;

    ToggleMode(0);
    UpdateAnimationsList();

    skeleton.GetRoot()->Update();
    SetSize(900,650); //Set a new default size as the size computed by wxWidgets is too small.
}

SkeletonObjectEditor::~SkeletonObjectEditor()
{
    m_mgr.UnInit();
	//(*Destroy(SkeletonObjectEditor)
	//*)
}

void SkeletonObjectEditor::PreparePropertyGrid()
{
    long GRIDID = wxNewId();

    m_grid = new wxPropertyGrid(
        propertyGridPanel, // parent
        GRIDID, // id
        wxDefaultPosition, // position
        wxSize(300,340), // size
        wxPG_SPLITTER_AUTO_CENTER |
        wxPG_DEFAULT_STYLE );

    m_grid->SetExtraStyle( wxPG_EX_HELP_AS_TOOLTIPS );
    propertyGridSizer->Add(m_grid, 1, wxALL|wxEXPAND, 0);

    //Create some stuff for property grid
    std::vector<std::string> listOfMethods = Sk::Anim::Interp::Get::Methods();
    wxArrayString interMethods;
    for(unsigned int a = 0; a < listOfMethods.size(); a++)
    {
        interMethods.Add(wxString(listOfMethods.at(a).c_str()));
    }

    //Creating all needed items
    m_grid->Append( new wxPropertyCategory(_("Identification")) );
    m_grid->Append( new wxStringProperty("Nom", "BoneName", "Bone") );

    m_grid->Append( new wxPropertyCategory(_("Propriétés"), "Properties") );
    m_grid->Append( new wxFloatProperty("Angle", "BoneAngle", 0.f) );
    {
        m_grid->AppendIn("BoneAngle", new wxBoolProperty(_("Frame clée"), "BoneAngleKeyFrame", false));
        m_grid->AppendIn("BoneAngle", new wxEnumProperty(_("Type d'interpolation"), "BoneAngleInterpolation", interMethods));
    }

    m_grid->Append( new wxFloatProperty("Longueur", "BoneLength", 100.f) );
    {
        m_grid->AppendIn("BoneLength", new wxBoolProperty(_("Frame clée"), "BoneLengthKeyFrame", false));
        m_grid->AppendIn("BoneLength", new wxEnumProperty(_("Type d'interpolation"), "BoneLengthInterpolation", interMethods));
    }

    m_grid->Append( new wxStringProperty(_("Décalage"), "BoneOffset", "") );
    {
        m_grid->AppendIn("BoneOffset", new wxFloatProperty(_("X"), "BoneOffsetX", 0.f));
        m_grid->AppendIn("BoneOffset", new wxFloatProperty(_("Y"), "BoneOffsetY", 0.f));
        m_grid->AppendIn("BoneOffset", new wxBoolProperty(_("Frame clée"), "BoneOffsetKeyFrame", false));
        m_grid->AppendIn("BoneOffset", new wxEnumProperty(_("Type d'interpolation"), "BoneOffsetInterpolation", interMethods));
    }

    m_grid->Append( new wxStringProperty("Image", "BoneImage", "") );
    {
        m_grid->AppendIn("BoneImage", new wxBoolProperty(_("Frame clée"), "BoneImageKeyFrame", false));
    }

    m_grid->Append( new wxIntProperty("Plan", "BoneZOrder", 0) );
    {
        m_grid->AppendIn("BoneZOrder", new wxBoolProperty(_("Frame clée"), "BoneZOrderKeyFrame", false));
        m_grid->AppendIn("BoneZOrder", new wxEnumProperty(_("Type d'interpolation"), "BoneZOrderInterpolation", interMethods));
    }

    m_grid->SetPropertyAttributeAll(wxPG_BOOL_USE_CHECKBOX, true);

    Connect(GRIDID, wxEVT_PG_CHANGING, (wxObjectEventFunction)&SkeletonObjectEditor::OnGridPropertyChanging);
    Connect(GRIDID, wxEVT_PG_CHANGED, (wxObjectEventFunction)&SkeletonObjectEditor::OnGridPropertyChanged);
}

void SkeletonObjectEditor::OnValidateButtonClick(wxCommandEvent& event)
{
    //skeleton.GetAnimator().SetCurrentAnimation("Initial");
    ToggleMode(1);
    ToggleMode(0);
    skeleton.GetAnimator().Reset();
    skeleton.ApplyAnimationToBones();
    object.SetSkeleton(skeleton);

    EndModal(1);
}

void SkeletonObjectEditor::OnButton2Click(wxCommandEvent& event)
{
    EndModal(0);
}

void SkeletonObjectEditor::OnButton1Click(wxCommandEvent& event)
{

}

void SkeletonObjectEditor::OnPanel1Paint(wxPaintEvent& event)
{
    wxBufferedPaintDC dc(Panel1);
    wxSize panelSize = Panel1->GetSize();

    //Draw background
    dc.SetBrush(wxColour(255, 255, 255));
    dc.DrawRectangle(0,0, panelSize.GetWidth(), panelSize.GetHeight());

    //Draw a line each 50px (on X and Y)
    {
        dc.SetPen(wxColour(210, 210, 210));
        int colsBegin = (int(offset.x) % 50);
        for(unsigned int a = 0; a < (unsigned int)(panelSize.GetWidth() / 50 + 1); a++)
        {
            dc.DrawLine(colsBegin + a * 50, 0,
                        colsBegin + a * 50, panelSize.GetHeight());
        }

        int rowsBegin = (int(offset.y) % 50);
        for(unsigned int b = 0; b < (unsigned int)(panelSize.GetHeight() / 50 + 1); b++)
        {
            dc.DrawLine(0, rowsBegin + b * 50,
                        panelSize.GetWidth(), rowsBegin + b * 50);
        }
    }

    //Draw a line each 100px (on X and Y)
    {
        dc.SetPen(wxColour(180, 180, 180));
        int colsBegin = (int(offset.x) % 100);
        for(unsigned int a = 0; a < (unsigned int)(panelSize.GetWidth() / 100 + 1); a++)
        {
            dc.DrawLine(colsBegin + a * 100, 0,
                        colsBegin + a * 100, panelSize.GetHeight());
        }

        int rowsBegin = (int(offset.y) % 100);
        for(unsigned int b = 0; b < (unsigned int)(panelSize.GetHeight() / 100 + 1); b++)
        {
            dc.DrawLine(0, rowsBegin + b * 100,
                        panelSize.GetWidth(), rowsBegin + b * 100);
        }
    }

    skeleton.DrawWx(dc, offset);
}

void SkeletonObjectEditor::OnPanel1LeftDown(wxMouseEvent& event)
{
    if(selectedBone && selectedBone->GetParentBone())
    {
        selectedBone->GetParentBone()->ShowMathsFrame(false);
    }

    skeleton.GetRoot()->UnselectAllChilds();
    selectedBone = 0;

    sf::Vector2f mousePos(event.GetPosition().x, event.GetPosition().y);

    Sk::Bone *searched = FindBoneOnPosition(mousePos, skeleton.GetRoot());

    if(searched)
    {
        selectedBone = searched;
        searched->Select(true);
    }
    else
    {
        selectedBone = 0;
    }

    UpdateForSelectedBone();

    Panel1->Refresh(); //Refresh
    Panel1->Update(); //Immediately

    Panel2->Refresh();
    Panel2->Update();
}

void SkeletonObjectEditor::OnPanel1RightDown(wxMouseEvent& event)
{
    lastPos = sf::Vector2f(event.GetPosition().x, event.GetPosition().y);

    isDragging = true;
}

void SkeletonObjectEditor::OnPanel1RightUp(wxMouseEvent& event)
{
    isDragging = false;
}

void SkeletonObjectEditor::OnPanel1MouseMove(wxMouseEvent& event)
{
    if(isDragging)
    {
        sf::Vector2f newPosDiff = sf::Vector2f(event.GetPosition().x, event.GetPosition().y) - lastPos;

        offset += newPosDiff;

        lastPos = sf::Vector2f(event.GetPosition().x, event.GetPosition().y);

        Panel1->Refresh(); //Refresh
        Panel1->Update(); //Immediately
    }
}

void SkeletonObjectEditor::OnaddChildBoneBtClick(wxCommandEvent& event)
{
    if ( !selectedBone ) return;

    std::string boneName;
    do
    {
        wxTextEntryDialog dialog(this, _("Nom du nouvel os"), _("Nouvel os"), "New bone");
        dialog.ShowModal();

        boneName = ToString(dialog.GetValue());

    } while(skeleton.BoneNameAlreadyUsed(boneName));

    Sk::Bone *newBone = skeleton.CreateBone(boneName);
    selectedBone->AddBone(newBone);

    skeleton.GetRoot()->UnselectAllChilds();

    if(selectedBone && selectedBone->GetParentBone())
    {
        selectedBone->GetParentBone()->ShowMathsFrame(false);
    }

    selectedBone = newBone;
    selectedBone->Update();
    selectedBone->Select(true);

    Panel1->Refresh(); //Refresh
    Panel1->Update(); //Immediately

    UpdateForSelectedBone();
}

void SkeletonObjectEditor::OndeleteBoneBtClick(wxCommandEvent& event)
{
    skeleton.GetRoot()->RemoveBone(selectedBone);
    selectedBone = 0;

    skeleton.GetRoot()->UnselectAllChilds();

    Panel1->Refresh(); //Refresh
    Panel1->Update(); //Immediately

    UpdateForSelectedBone();
}

void SkeletonObjectEditor::UpdateForSelectedBone()
{
    if(selectedBone)
    {
        m_grid->SetPropertyValue(wxT("Identification.BoneName"), wxString(selectedBone->GetName()));

        m_grid->SetPropertyValue(wxT("Properties.BoneAngle"), selectedBone->GetRotation());
        m_grid->SetPropertyValue(wxT("Properties.BoneLength"), selectedBone->GetSize());
        m_grid->SetPropertyValue(wxT("Properties.BoneOffset.BoneOffsetX"), selectedBone->GetOffset().x);
        m_grid->SetPropertyValue(wxT("Properties.BoneOffset.BoneOffsetY"), selectedBone->GetOffset().y);
        m_grid->SetPropertyValue(wxT("Properties.BoneImage"), wxString(selectedBone->GetTextureName()));
        m_grid->SetPropertyValue(wxT("Properties.BoneZOrder"), selectedBone->GetZOrder());

        if(mode == 1 && timeline_currentAnim)
        {
            if(timeline_currentAnim->HasKeyFrame(selectedBone->GetName(), Sk::Anim::AngleKeyFrame, timeline_current))
            {
                m_grid->SetPropertyValue(wxT("Properties.BoneAngle.BoneAngleKeyFrame"), true);
                m_grid->SetPropertyValue(wxT("Properties.BoneAngle.BoneAngleInterpolation"), wxString(timeline_currentAnim->GetKeyFrameInterpolation(selectedBone->GetName(), Sk::Anim::AngleKeyFrame, timeline_current).c_str()));
            }
            else
            {
                m_grid->SetPropertyValue(wxT("Properties.BoneAngle.BoneAngleKeyFrame"), false);
            }

            if(timeline_currentAnim->HasKeyFrame(selectedBone->GetName(), Sk::Anim::LengthKeyFrame, timeline_current))
            {
                m_grid->SetPropertyValue(wxT("Properties.BoneLength.BoneLengthKeyFrame"), true);
                m_grid->SetPropertyValue(wxT("Properties.BoneLength.BoneLengthInterpolation"), wxString(timeline_currentAnim->GetKeyFrameInterpolation(selectedBone->GetName(), Sk::Anim::LengthKeyFrame, timeline_current).c_str()));
            }
            else
            {
                m_grid->SetPropertyValue(wxT("Properties.BoneLength.BoneLengthKeyFrame"), false);
            }

            if(timeline_currentAnim->HasKeyFrame(selectedBone->GetName(), Sk::Anim::PositionXKeyFrame, timeline_current))
            {
                m_grid->SetPropertyValue(wxT("Properties.BoneOffset.BoneOffsetKeyFrame"), true);
                m_grid->SetPropertyValue(wxT("Properties.BoneOffset.BoneOffsetInterpolation"), wxString(timeline_currentAnim->GetKeyFrameInterpolation(selectedBone->GetName(), Sk::Anim::PositionXKeyFrame, timeline_current).c_str()));
            }
            else
            {
                m_grid->SetPropertyValue(wxT("Properties.BoneOffset.BoneOffsetKeyFrame"), false);
            }

            if(timeline_currentAnim->HasKeyFrame(selectedBone->GetName(), Sk::Anim::ImageKeyFrame, timeline_current))
            {
                m_grid->SetPropertyValue(wxT("Properties.BoneImage.BoneImageKeyFrame"), true);
            }
            else
            {
                m_grid->SetPropertyValue(wxT("Properties.BoneImage.BoneImageKeyFrame"), false);
            }
        }

        if(selectedBone->GetParentBone())
        {
            selectedBone->GetParentBone()->ShowMathsFrame(true);
        }
    }
    else
    {
        m_grid->SetPropertyValue(wxT("Identification.BoneName"), wxString(""));

        m_grid->SetPropertyValue(wxT("Properties.BoneAngle"), 0.f);
        m_grid->SetPropertyValue(wxT("Properties.BoneLength"), 0.f);
        m_grid->SetPropertyValue(wxT("Properties.BoneOffset.BoneOffsetX"), 0.f);
        m_grid->SetPropertyValue(wxT("Properties.BoneOffset.BoneOffsetY"), 0.f);
        m_grid->SetPropertyValue(wxT("Properties.BoneImage"), wxString(""));
        m_grid->SetPropertyValue(wxT("Properties.BoneZOrder"), 0);
    }
}

Sk::Bone* SkeletonObjectEditor::FindBoneOnPosition(sf::Vector2f position, Sk::Bone *base)
{
    if(base->IsOnPosition(position - offset))
        return base;

    for(unsigned int a = 0; a < base->GetChildrenBones().size(); a++)
    {
        Sk::Bone *searched = FindBoneOnPosition(position, base->GetChildrenBones().at(a));
        if(searched)
            return searched;
    }

    return 0;
}

void SkeletonObjectEditor::ToggleMode(char _mode)
{
    for(unsigned int a = 0; a < skeleton.GetListOfBones().size(); a++)
    {
        skeleton.GetListOfBones().at(a)->UnColorize();
    }

    if(_mode == 0)
    {
        skeleton.GetAnimator().SetCurrentAnimation("Initial");
        skeleton.GetAnimator().Seek(0);

        timeline_currentAnim = 0;

        ToggleButton1->SetValue(true);
        ToggleButton2->SetValue(false);

        addChildBoneBt->Enable(true);
        deleteBoneBt->Enable(true);

        BitmapButton2->Enable(false);
        BitmapButton4->Enable(false);
        BitmapButton1->Enable(false);
        BitmapButton3->Enable(false);

        AnimationCombobox->Enable(false);

        m_grid->GetProperty("Identification.BoneName")->Enable(true);

        m_grid->GetProperty("Properties.BoneAngle.BoneAngleKeyFrame")->Enable(false);
        m_grid->GetProperty("Properties.BoneAngle.BoneAngleInterpolation")->Enable(false);

        m_grid->GetProperty("Properties.BoneLength.BoneLengthKeyFrame")->Enable(false);
        m_grid->GetProperty("Properties.BoneLength.BoneLengthInterpolation")->Enable(false);

        m_grid->GetProperty("Properties.BoneOffset.BoneOffsetKeyFrame")->Enable(false);
        m_grid->GetProperty("Properties.BoneOffset.BoneOffsetInterpolation")->Enable(false);

        m_grid->GetProperty("Properties.BoneImage.BoneImageKeyFrame")->Enable(false);

        m_grid->GetProperty("Properties.BoneZOrder.BoneZOrderKeyFrame")->Enable(false);
        m_grid->GetProperty("Properties.BoneZOrder.BoneZOrderInterpolation")->Enable(false);
    }
    else
    {
        skeleton.GetAnimator().GetAnimation("Initial").SetPeriod(0);
        for(std::vector<Sk::Bone*>::const_iterator it = skeleton.GetListOfBones().begin(); it != skeleton.GetListOfBones().end(); it++)
        {
            skeleton.GetAnimator().GetAnimation("Initial").SetKeyFrame((*it)->GetName(), Sk::Anim::AngleKeyFrame, 0, (*it)->GetRotation());

            skeleton.GetAnimator().GetAnimation("Initial").SetKeyFrame((*it)->GetName(), Sk::Anim::LengthKeyFrame, 0, (*it)->GetSize());

            skeleton.GetAnimator().GetAnimation("Initial").SetKeyFrame((*it)->GetName(), Sk::Anim::PositionXKeyFrame, 0, (*it)->GetOffset().x);
            skeleton.GetAnimator().GetAnimation("Initial").SetKeyFrame((*it)->GetName(), Sk::Anim::PositionYKeyFrame, 0, (*it)->GetOffset().y);

            skeleton.GetAnimator().GetAnimation("Initial").SetKeyFrame((*it)->GetName(), Sk::Anim::ImageKeyFrame, 0, (*it)->GetTextureName());
        }
        skeleton.GetAnimator().Seek(0);

        ToggleButton1->SetValue(false);
        ToggleButton2->SetValue(true);

        addChildBoneBt->Enable(false);
        deleteBoneBt->Enable(false);

        BitmapButton2->Enable(true);
        BitmapButton4->Enable(true);
        BitmapButton1->Enable(true);
        BitmapButton3->Enable(true);
        AnimationCombobox->Enable(true);

        m_grid->GetProperty("Identification.BoneName")->Enable(false);

        m_grid->GetProperty("Properties.BoneAngle.BoneAngleKeyFrame")->Enable(true);
        m_grid->GetProperty("Properties.BoneAngle.BoneAngleInterpolation")->Enable(true);

        m_grid->GetProperty("Properties.BoneLength.BoneLengthKeyFrame")->Enable(true);
        m_grid->GetProperty("Properties.BoneLength.BoneLengthInterpolation")->Enable(true);

        m_grid->GetProperty("Properties.BoneOffset.BoneOffsetKeyFrame")->Enable(true);
        m_grid->GetProperty("Properties.BoneOffset.BoneOffsetInterpolation")->Enable(true);

        m_grid->GetProperty("Properties.BoneImage.BoneImageKeyFrame")->Enable(true);

        m_grid->GetProperty("Properties.BoneZOrder.BoneZOrderKeyFrame")->Enable(true);
        m_grid->GetProperty("Properties.BoneZOrder.BoneZOrderInterpolation")->Enable(true);

        UpdateAnimationsList();
        SelectAnimation(ToString(AnimationCombobox->GetString(AnimationCombobox->GetSelection())));
    }
    mode = _mode;

    skeleton.ApplyAnimationToBones();

    Panel1->Refresh();
    Panel1->Update();

    Panel2->Refresh(); //Refresh
    Panel2->Update();
}

void SkeletonObjectEditor::OnToggleButton1Toggle(wxCommandEvent& event)
{
    ToggleMode(0);
}

void SkeletonObjectEditor::OnToggleButton2Toggle(wxCommandEvent& event)
{
    ToggleMode(1);
}

void SkeletonObjectEditor::OnButton3Click(wxCommandEvent& event)
{
    if ( !m_mgr.GetPane( resourcesEditor ).IsShown() )
        SetSize(GetSize().GetWidth()+150, GetSize().GetHeight());

    m_mgr.GetPane( resourcesEditor ).Show();
    m_mgr.Update();
}

void SkeletonObjectEditor::OnPanel1EraseBackground(wxEraseEvent& event)
{
}

#define ANGLE_RIBBON_HEIGHT 16
#define LENGTH_RIBBON_HEIGHT 16 + int((panelSize.GetHeight() - 16)/5) + 1
#define OFFSET_RIBBON_HEIGHT 16 + int((panelSize.GetHeight() - 16)/5)*2 + 1
#define IMAGE_RIBBON_HEIGHT 16 + int((panelSize.GetHeight() - 16)/5)*3 + 1
#define ZORDER_RIBBON_HEIGHT 16 + int((panelSize.GetHeight() - 16)/5)*4 + 1

void SkeletonObjectEditor::OnPanel2Paint(wxPaintEvent& event)
{
    wxBufferedPaintDC dc(Panel2);
    wxSize panelSize = Panel2->GetSize();

    dc.SetBrush(wxBrush(wxColour(255, 255, 255)));
    dc.DrawRectangle(0, 0, panelSize.GetWidth(), panelSize.GetHeight());

    if(mode == 0)
        return;

    dc.SetBrush(wxBrush(wxColour(110, 110, 110)));
    dc.DrawRectangle(0, 16, panelSize.GetWidth(), panelSize.GetHeight());

    dc.SetPen(wxPen(wxColour(0, 0, 0, 255)));

    //Draw Length Ribbon
    dc.SetBrush(wxBrush(wxColour(120, 120, 120)));
    dc.SetPen(wxPen(wxColour(120, 120, 120)));
    dc.DrawRectangle(0, LENGTH_RIBBON_HEIGHT, panelSize.GetWidth(), int((panelSize.GetHeight() - 16)/5));

    //Draw Image Ribbon
    dc.SetBrush(wxBrush(wxColour(120, 120, 120)));
    dc.SetPen(wxPen(wxColour(120, 120, 120)));
    dc.DrawRectangle(0, 16 + int((panelSize.GetHeight() - 16)/5) * 3 + 1, panelSize.GetWidth(), int((panelSize.GetHeight() - 16)/5));


    float gradScale = GetGraduationScale(panelSize.GetWidth(), timeline_scale);
    //Each 5s and 10s lines
    for(int a = floor(timeline_offset / gradScale) - 1; a < floor(timeline_offset / 5) + floor(panelSize.GetWidth() / (timeline_scale * gradScale)) + 2;a++)
    {
        dc.DrawRotatedText(ToString(a * gradScale), (a * timeline_scale * gradScale) - (timeline_offset * timeline_scale) - 7, 2, 0);

        //dc.SetPen(wxColour(170, 170, 170));

        /*dc.DrawLine((a * timeline_scale * 10 - 5 * timeline_scale) - (timeline_offset * timeline_scale), 17,
                    (a * timeline_scale * 10 - 5 * timeline_scale) - (timeline_offset * timeline_scale), panelSize.GetHeight() - 1);*/

        dc.SetPen(wxColour(130, 130, 130));

        dc.DrawLine((a * timeline_scale * gradScale) - (timeline_offset * timeline_scale), 17,
                    (a * timeline_scale * gradScale) - (timeline_offset * timeline_scale), panelSize.GetHeight() - 1);
    }

    if(timeline_currentAnim)
    {
        dc.SetPen(wxPen(wxColour(255, 255, 0)));
        dc.DrawLine(GetPositionFromTimeToPixel(timeline_currentAnim->GetPeriod()), 17, GetPositionFromTimeToPixel(timeline_currentAnim->GetPeriod()), panelSize.GetHeight());
    }

    if(timeline_currentAnim)
    {
        //Draw angle keyframes
        {
        std::vector<float> keyFrames = timeline_currentAnim->GetListOfKeyFramesTime("", Sk::Anim::AngleKeyFrame);
        for(unsigned int a = 0; a < keyFrames.size(); a++)
        {
            if(!selectedBone || !timeline_currentAnim->HasKeyFrame(selectedBone->GetName(), Sk::Anim::AngleKeyFrame, keyFrames.at(a)))
            {
                dc.SetPen(wxColour(0, 148, 255));
            }
            else
            {
                dc.SetPen(wxColour(0, 255, 255));
            }

            dc.DrawLine(GetPositionFromTimeToPixel(keyFrames.at(a)), ANGLE_RIBBON_HEIGHT,
                        GetPositionFromTimeToPixel(keyFrames.at(a)), LENGTH_RIBBON_HEIGHT);
            dc.DrawLine(GetPositionFromTimeToPixel(keyFrames.at(a)) - 1, ANGLE_RIBBON_HEIGHT,
                        GetPositionFromTimeToPixel(keyFrames.at(a)) - 1, LENGTH_RIBBON_HEIGHT);
        }
        }

        //Draw length keyframes
        {
        std::vector<float> keyFrames = timeline_currentAnim->GetListOfKeyFramesTime("", Sk::Anim::LengthKeyFrame);
        for(unsigned int a = 0; a < keyFrames.size(); a++)
        {
            if(!selectedBone || !timeline_currentAnim->HasKeyFrame(selectedBone->GetName(), Sk::Anim::LengthKeyFrame, keyFrames.at(a)))
            {
                dc.SetPen(wxColour(255, 0, 0));
            }
            else
            {
                dc.SetPen(wxColour(255, 100, 100));
            }

            dc.DrawLine(GetPositionFromTimeToPixel(keyFrames.at(a)) - 1, LENGTH_RIBBON_HEIGHT,
                        GetPositionFromTimeToPixel(keyFrames.at(a)) - 1, OFFSET_RIBBON_HEIGHT);
            dc.DrawLine(GetPositionFromTimeToPixel(keyFrames.at(a)), LENGTH_RIBBON_HEIGHT,
                        GetPositionFromTimeToPixel(keyFrames.at(a)), OFFSET_RIBBON_HEIGHT);
        }
        }

        //Draw offset keyframes (PositionXKeyFrame and PositionYKeyFrame are already defined for a same time amount)
        {
        std::vector<float> keyFrames = timeline_currentAnim->GetListOfKeyFramesTime("", Sk::Anim::PositionXKeyFrame);
        for(unsigned int a = 0; a < keyFrames.size(); a++)
        {
            if(!selectedBone || !timeline_currentAnim->HasKeyFrame(selectedBone->GetName(), Sk::Anim::PositionXKeyFrame, keyFrames.at(a)))
            {
                dc.SetPen(wxColour(168, 140, 0));
            }
            else
            {
                dc.SetPen(wxColour(255, 216, 0));
            }

            dc.DrawLine(GetPositionFromTimeToPixel(keyFrames.at(a)) - 1, OFFSET_RIBBON_HEIGHT,
                        GetPositionFromTimeToPixel(keyFrames.at(a)) - 1, IMAGE_RIBBON_HEIGHT);
            dc.DrawLine(GetPositionFromTimeToPixel(keyFrames.at(a)), OFFSET_RIBBON_HEIGHT,
                        GetPositionFromTimeToPixel(keyFrames.at(a)), IMAGE_RIBBON_HEIGHT);
        }
        }

        //Draw image keyframes
        {
        std::vector<float> keyFrames = timeline_currentAnim->GetListOfKeyFramesTime("", Sk::Anim::ImageKeyFrame);
        for(unsigned int a = 0; a < keyFrames.size(); a++)
        {
            if(!selectedBone || !timeline_currentAnim->HasKeyFrame(selectedBone->GetName(), Sk::Anim::ImageKeyFrame, keyFrames.at(a)))
            {
                dc.SetPen(wxColour(178, 0, 255));
            }
            else
            {
                dc.SetPen(wxColour(202, 90, 255));
            }

            dc.DrawLine(GetPositionFromTimeToPixel(keyFrames.at(a)) - 1, IMAGE_RIBBON_HEIGHT,
                        GetPositionFromTimeToPixel(keyFrames.at(a)) - 1, ZORDER_RIBBON_HEIGHT);
            dc.DrawLine(GetPositionFromTimeToPixel(keyFrames.at(a)), IMAGE_RIBBON_HEIGHT,
                        GetPositionFromTimeToPixel(keyFrames.at(a)), ZORDER_RIBBON_HEIGHT);
        }
        }
    }

    dc.SetPen(wxColour(91, 255, 91));

    dc.DrawLine(GetPositionFromTimeToPixel(timeline_current), 17,
                GetPositionFromTimeToPixel(timeline_current), panelSize.GetHeight() - 1);

    dc.DrawRotatedText(ToString(timeline_current), GetPositionFromTimeToPixel(timeline_current) + 5,
                16 + 4*(int((panelSize.GetHeight() - 16)/5)) + 1,
                0);
}

void SkeletonObjectEditor::OnPanel2EraseBackground(wxEraseEvent& event)
{
}

void SkeletonObjectEditor::OnPanel2LeftDown(wxMouseEvent& event)
{
    if(!timeline_currentAnim)
        return;

    float time = GetPositionFromPixelToTime(event.GetX());

    std::vector<float> keyFrames = timeline_currentAnim->GetListOfKeyFramesTime();
    for(unsigned int a = 0; a < keyFrames.size(); a++)
    {
        if(event.GetX() > GetPositionFromTimeToPixel(keyFrames.at(a)) - 4 && event.GetX() < GetPositionFromTimeToPixel(keyFrames.at(a)) + 4)
        {
            time = keyFrames.at(a);
        }
    }

    Seek(time);
    UpdateForSelectedBone();
}

void SkeletonObjectEditor::OnPanel2MouseWheel(wxMouseEvent& event)
{
//
}

void SkeletonObjectEditor::OnPanel2RightDown(wxMouseEvent& event)
{
    timeline_tmp_dragbegan = event.GetPosition().x;
}

void SkeletonObjectEditor::OnPanel2RightUp(wxMouseEvent& event)
{
    int newPosition = event.GetPosition().x;
    timeline_offset += (newPosition - timeline_tmp_dragbegan) / timeline_scale;

    if(timeline_offset < 0)
        timeline_offset = 0;

    Panel2->Refresh(); //Refresh
    Panel2->Update();
}

void SkeletonObjectEditor::OnButton4Click(wxCommandEvent& event)
{
    timeline_scale *= 2;

    Panel2->Refresh(); //Refresh
    Panel2->Update();
}

void SkeletonObjectEditor::OnButton5Click(wxCommandEvent& event)
{
    timeline_scale /= 2;

    Panel2->Refresh(); //Refresh
    Panel2->Update();
}

void SkeletonObjectEditor::OnButton6Click(wxCommandEvent& event)
{
    wxTextEntryDialog dialog(this, _("Aller à..."), _("Aller à un moment précis (secondes)"), "0");
    dialog.ShowModal();

    float time = ToFloat(ToString(dialog.GetValue()));

    Seek(time);

    Panel2->Refresh(); //Refresh
    Panel2->Update();
}

void SkeletonObjectEditor::UpdateAnimationsList()
{
    wxString selected = AnimationCombobox->GetString(AnimationCombobox->GetSelection());
    AnimationCombobox->Clear();

    std::vector<std::string> animations = skeleton.GetAnimator().GetListOfAnimations();

    for(unsigned int a = 0; a < animations.size(); a++)
    {
        if(animations.at(a) != "Initial")
            AnimationCombobox->Append(animations.at(a).c_str());
    }

    if(AnimationCombobox->FindString(selected, true) != -1)
        AnimationCombobox->Select(AnimationCombobox->FindString(selected, true));
}

void SkeletonObjectEditor::SelectAnimation(const std::string &name)
{
    for(unsigned int a = 0; a < skeleton.GetListOfBones().size(); a++)
    {
        skeleton.GetListOfBones().at(a)->UnColorize();
    }

    if(name == "")
    {
        timeline_currentAnim = 0;
        timeline_offset = 0;
        timeline_current = 0;

        Panel2->Refresh(); //Refresh
        Panel2->Update();

        return;
    }

    timeline_currentAnim = &(skeleton.GetAnimator().GetAnimation(name));
    skeleton.GetAnimator().SetCurrentAnimation(name);
    timeline_offset = 0;
    timeline_current = 0;

    skeleton.ApplyAnimationToBones();

    Seek(0);

    Panel2->Refresh(); //Refresh
    Panel2->Update();

    if(ToString(AnimationCombobox->GetString(AnimationCombobox->GetSelection())) != name)
    {
        if(AnimationCombobox->FindString(name, true) != -1)
            AnimationCombobox->Select(AnimationCombobox->FindString(name, true));
    }
}

void SkeletonObjectEditor::Seek(float time)
{
    for(unsigned int a = 0; a < skeleton.GetListOfBones().size(); a++)
    {
        skeleton.GetListOfBones().at(a)->UnColorize();
    }

    skeleton.GetAnimator().Seek(time);
    skeleton.ApplyAnimationToBones();

    timeline_current = time;

    for(unsigned int a = 0; a < skeleton.GetListOfBones().size(); a++)
    {
        if(skeleton.GetAnimator().GetAnimation(skeleton.GetAnimator().GetCurrentAnimation()).HasKeyFrame(skeleton.GetListOfBones().at(a)->GetName(), Sk::Anim::AngleKeyFrame, timeline_current) ||
           skeleton.GetAnimator().GetAnimation(skeleton.GetAnimator().GetCurrentAnimation()).HasKeyFrame(skeleton.GetListOfBones().at(a)->GetName(), Sk::Anim::LengthKeyFrame, timeline_current) ||
           skeleton.GetAnimator().GetAnimation(skeleton.GetAnimator().GetCurrentAnimation()).HasKeyFrame(skeleton.GetListOfBones().at(a)->GetName(), Sk::Anim::PositionXKeyFrame, timeline_current))
        {
            skeleton.GetListOfBones().at(a)->SetColor(wxColour(0, 148, 255));
        }
    }

    Panel2->Refresh(); //Refresh
    Panel2->Update();

    Panel1->Refresh(); //Refresh
    Panel1->Update();
}

int SkeletonObjectEditor::GetPositionFromTimeToPixel(float time) const
{
    return (time * timeline_scale) - (timeline_offset * timeline_scale);
}

float SkeletonObjectEditor::GetPositionFromPixelToTime(int pixel) const
{
    return (pixel) / timeline_scale + timeline_offset;
}

void SkeletonObjectEditor::OnAnimationComboboxSelect(wxCommandEvent& event)
{
    SelectAnimation(ToString(AnimationCombobox->GetString(AnimationCombobox->GetSelection())));
}

void SkeletonObjectEditor::OnBitmapButton2Click(wxCommandEvent& event)
{
    //Add an animation
    wxTextEntryDialog dialog(this, _("Nom de l'animation"), _("Nouvelle animation"), "New Animation");
    dialog.ShowModal();

    skeleton.GetAnimator().CreateAnimation(std::string(dialog.GetValue().c_str()), "Initial");

    UpdateAnimationsList();
    SelectAnimation(std::string(dialog.GetValue().c_str()));
}

void SkeletonObjectEditor::OnBitmapButton4Click(wxCommandEvent& event)
{
    if(AnimationCombobox->GetSelection() == -1)
        return;

    //Add an animation
    wxTextEntryDialog dialog(this, _("Nom de l'animation copiée"), _("Nouvelle animation"), "New Animation");
    dialog.ShowModal();

    skeleton.GetAnimator().CreateAnimation(std::string(dialog.GetValue().c_str()), ToString(AnimationCombobox->GetString(AnimationCombobox->GetSelection())));

    UpdateAnimationsList();
    SelectAnimation(std::string(dialog.GetValue().c_str()));
}

void SkeletonObjectEditor::OnBitmapButton1Click(wxCommandEvent& event)
{
    if(!timeline_currentAnim)
        return;

    SkeletonAnimationSettings dialog(this, timeline_currentAnim);
    dialog.ShowModal();
}

void SkeletonObjectEditor::OnBitmapButton3Click(wxCommandEvent& event)
{
    if(AnimationCombobox->GetSelection() == -1)
        return;

    int ret = wxMessageBox(_("Êtes-vous sûr(e) de vouloir supprimer l'animation sélectionnée ?"), _("Confirmation de suppression"), wxYES_NO);

    if(ret == wxYES)
        skeleton.GetAnimator().DeleteAnimation(ToString(AnimationCombobox->GetString(AnimationCombobox->GetSelection())));

    UpdateAnimationsList();
}

void SkeletonObjectEditor::UncolorizeBoneIfNecessary(Sk::Bone &bone)
{
    selectedBone->SetColor(wxColour(0, 255, 0));
}

/*void SkeletonObjectEditor::OnangleApplyToAllBtClick(wxCommandEvent& event)
{
    if(mode != 0 || !selectedBone)
        return;

    std::vector<std::string> listOfAnim = skeleton.GetAnimator().GetListOfAnimations();
    for(unsigned int a = 0; a < listOfAnim.size(); a++)
    {
        skeleton.GetAnimator().GetAnimation(listOfAnim.at(a)).ClearKeyFrame(selectedBone->GetName(), Sk::AngleKeyFrame);
        skeleton.GetAnimator().GetAnimation(listOfAnim.at(a)).SetKeyFrame(selectedBone->GetName(), Sk::AngleKeyFrame, 0, selectedBone->GetRotation());
    }
}

void SkeletonObjectEditor::OnlengthApplyToAllBtClick(wxCommandEvent& event)
{
    if(mode != 0 || !selectedBone)
        return;

    std::vector<std::string> listOfAnim = skeleton.GetAnimator().GetListOfAnimations();
    for(unsigned int a = 0; a < listOfAnim.size(); a++)
    {
        skeleton.GetAnimator().GetAnimation(listOfAnim.at(a)).ClearKeyFrame(selectedBone->GetName(), Sk::LengthKeyFrame);
        skeleton.GetAnimator().GetAnimation(listOfAnim.at(a)).SetKeyFrame(selectedBone->GetName(), Sk::LengthKeyFrame, 0, selectedBone->GetSize());
    }
}
*/

void SkeletonObjectEditor::OnGridPropertyChanging(wxPropertyGridEvent& event)
{
    if(mode == 0 && selectedBone)
    {
        if(event.GetProperty()->GetBaseName() == "BoneName")
        {
            if(skeleton.BoneNameAlreadyUsed(ToString(event.GetPropertyValue().GetString())) && ToString(event.GetPropertyValue().GetString()) != selectedBone->GetName())
            {
                wxMessageBox(_("Un os ayant ce nom existe déjà.\nModifiez le nom et cliquez sur Appliquer."), "Nom de l'os");
                event.Veto(true);
            }
        }
    }
    else if(mode == 1 && selectedBone && timeline_currentAnim)
    {

    }
    else
    {
        event.Veto(true);
    }
}

void SkeletonObjectEditor::OnGridPropertyChanged(wxPropertyGridEvent& event)
{
    if(event.WasVetoed())
        return;

    if(mode == 0 && selectedBone)
    {
        skeleton.GetAnimator().GetAnimation("Initial").SetPeriod(0);

        if(event.GetProperty()->GetBaseName() == "BoneName")
        {
            std::string oldName = selectedBone->GetName();
            selectedBone->SetName(ToString(event.GetPropertyValue().GetString()));
            skeleton.GetAnimator().NotifyBoneRenamed(oldName, selectedBone->GetName());
        }
        else if(event.GetProperty()->GetBaseName() == "BoneAngle")
        {
            selectedBone->SetRotation(event.GetPropertyValue().GetDouble());
            skeleton.GetAnimator().GetAnimation("Initial").SetKeyFrame(selectedBone->GetName(), Sk::Anim::AngleKeyFrame, 0, event.GetPropertyValue().GetDouble());
        }
        else if(event.GetProperty()->GetBaseName() == "BoneLength")
        {
            selectedBone->SetSize(event.GetPropertyValue().GetDouble());
            skeleton.GetAnimator().GetAnimation("Initial").SetKeyFrame(selectedBone->GetName(), Sk::Anim::LengthKeyFrame, 0, event.GetPropertyValue().GetDouble());
        }
        else if(event.GetProperty()->GetBaseName() == "BoneOffsetX" || event.GetProperty()->GetBaseName() == "BoneOffsetY")
        {
            selectedBone->SetOffset(m_grid->GetPropertyValue(wxT("Properties.BoneOffset.BoneOffsetX")).GetDouble(),
                                    m_grid->GetPropertyValue(wxT("Properties.BoneOffset.BoneOffsetY")).GetDouble());

            skeleton.GetAnimator().GetAnimation("Initial").SetKeyFrame(selectedBone->GetName(), Sk::Anim::PositionXKeyFrame, 0, m_grid->GetPropertyValue(wxT("Properties.BoneOffset.BoneOffsetX")).GetDouble());
            skeleton.GetAnimator().GetAnimation("Initial").SetKeyFrame(selectedBone->GetName(), Sk::Anim::PositionYKeyFrame, 0, m_grid->GetPropertyValue(wxT("Properties.BoneOffset.BoneOffsetY")).GetDouble());
        }
        else if(event.GetProperty()->GetBaseName() == "BoneImage")
        {
            selectedBone->SetTextureName(ToString(event.GetPropertyValue().GetString()));
            skeleton.GetAnimator().GetAnimation("Initial").SetKeyFrame(selectedBone->GetName(), Sk::Anim::ImageKeyFrame, 0, ToString(event.GetPropertyValue().GetString()));
        }
        else if(event.GetProperty()->GetBaseName() == "BoneZOrder")
        {
            selectedBone->SetZOrder(event.GetPropertyValue().GetInteger());
        }
    }
    else if(mode == 1 && selectedBone && timeline_currentAnim)
    {
        //When angle modified
        if(event.GetProperty()->GetBaseName() == "BoneAngle")
        {
            selectedBone->SetRotation(event.GetPropertyValue().GetDouble());

            //When angle keyframe is already checked, modification applied
            if(m_grid->GetPropertyValueAsBool("Properties.BoneAngle.BoneAngleKeyFrame"))
            {
                timeline_currentAnim->SetKeyFrame(selectedBone->GetName(), Sk::Anim::AngleKeyFrame, timeline_current, event.GetPropertyValue().GetDouble());
                timeline_currentAnim->SetKeyFrameInterpolation(selectedBone->GetName(), Sk::Anim::AngleKeyFrame, timeline_current,
                                                               ToString(m_grid->GetPropertyValueAsString("Properties.BoneAngle.BoneAngleInterpolation")));
            }
        }
        //When check/uncheck keyframe for angle
        else if(event.GetProperty()->GetBaseName() == "BoneAngleKeyFrame")
        {
            if(event.GetPropertyValue().GetBool())
            {
                timeline_currentAnim->SetKeyFrame(selectedBone->GetName(), Sk::Anim::AngleKeyFrame, timeline_current,
                                                  m_grid->GetPropertyValueAsDouble("Properties.BoneAngle"));
                timeline_currentAnim->SetKeyFrameInterpolation(selectedBone->GetName(), Sk::Anim::AngleKeyFrame, timeline_current,
                                                               ToString(m_grid->GetPropertyValueAsString("Properties.BoneAngle.BoneAngleInterpolation")));
            }
            else
            {
                timeline_currentAnim->RemoveKeyFrame(selectedBone->GetName(), Sk::Anim::AngleKeyFrame, timeline_current);
            }
        }
        //When we change keyframe interpolation
        else if(event.GetProperty()->GetBaseName() == _("BoneAngleInterpolation"))
        {
            timeline_currentAnim->SetKeyFrameInterpolation(selectedBone->GetName(), Sk::Anim::AngleKeyFrame, timeline_current,
                                                           ToString(m_grid->GetPropertyValueAsString("Properties.BoneAngle.BoneAngleInterpolation")));
        }


        //When length modified
        if(event.GetProperty()->GetBaseName() == "BoneLength")
        {
            selectedBone->SetSize(event.GetPropertyValue().GetDouble());

            //When offset keyframe is already checked, modification applied
            if(m_grid->GetPropertyValueAsBool("Properties.BoneLength.BoneLengthKeyFrame"))
            {
                timeline_currentAnim->SetKeyFrame(selectedBone->GetName(), Sk::Anim::LengthKeyFrame, timeline_current, event.GetPropertyValue().GetDouble());
                timeline_currentAnim->SetKeyFrameInterpolation(selectedBone->GetName(), Sk::Anim::LengthKeyFrame, timeline_current,
                                                               ToString(m_grid->GetPropertyValueAsString("Properties.BoneLength.BoneLengthInterpolation")));
            }
        }
        //When check/uncheck keyframe for length
        else if(event.GetProperty()->GetBaseName() == "BoneLengthKeyFrame")
        {
            if(event.GetPropertyValue().GetBool())
            {
                timeline_currentAnim->SetKeyFrame(selectedBone->GetName(), Sk::Anim::LengthKeyFrame, timeline_current,
                                                  m_grid->GetPropertyValueAsDouble("Properties.BoneLength"));
                timeline_currentAnim->SetKeyFrameInterpolation(selectedBone->GetName(), Sk::Anim::LengthKeyFrame, timeline_current,
                                                               ToString(m_grid->GetPropertyValueAsString("Properties.BoneLength.BoneLengthInterpolation")));
            }
            else
            {
                timeline_currentAnim->RemoveKeyFrame(selectedBone->GetName(), Sk::Anim::LengthKeyFrame, timeline_current);
            }
        }
        //When we change keyframe interpolation
        else if(event.GetProperty()->GetBaseName() == "BoneLengthInterpolation")
        {
            timeline_currentAnim->SetKeyFrameInterpolation(selectedBone->GetName(), Sk::Anim::LengthKeyFrame, timeline_current,
                                                           ToString(m_grid->GetPropertyValueAsString("Properties.BoneLength.BoneLengthInterpolation")));
        }


        //When offset modified
        if(event.GetProperty()->GetBaseName() == "BoneOffsetX" || event.GetProperty()->GetBaseName() == "BoneOffsetY")
        {
            selectedBone->SetOffset(m_grid->GetPropertyValue("Properties.BoneOffset.BoneOffsetX").GetDouble(),
                                    m_grid->GetPropertyValue("Properties.BoneOffset.BoneOffsetY").GetDouble());

            //When offset keyframe is already checked, modification applied
            if(m_grid->GetPropertyValueAsBool("Properties.BoneOffset.BoneOffsetKeyFrame"))
            {
                timeline_currentAnim->SetKeyFrame(selectedBone->GetName(), Sk::Anim::PositionXKeyFrame, timeline_current, m_grid->GetPropertyValue("Properties.BoneOffset.BoneOffsetX").GetDouble());
                timeline_currentAnim->SetKeyFrameInterpolation(selectedBone->GetName(), Sk::Anim::PositionXKeyFrame, timeline_current,
                                                               ToString(m_grid->GetPropertyValueAsString("Properties.BoneOffset.BoneOffsetInterpolation")));

                timeline_currentAnim->SetKeyFrame(selectedBone->GetName(), Sk::Anim::PositionYKeyFrame, timeline_current, m_grid->GetPropertyValue("Properties.BoneOffset.BoneOffsetY").GetDouble());
                timeline_currentAnim->SetKeyFrameInterpolation(selectedBone->GetName(), Sk::Anim::PositionYKeyFrame, timeline_current,
                                                               ToString(m_grid->GetPropertyValueAsString("Properties.BoneOffset.BoneOffsetInterpolation")));
            }
        }
        //When check/uncheck keyframe for offset
        else if(event.GetProperty()->GetBaseName() == "BoneOffsetKeyFrame")
        {
            if(event.GetPropertyValue().GetBool())
            {
                timeline_currentAnim->SetKeyFrame(selectedBone->GetName(), Sk::Anim::PositionXKeyFrame, timeline_current, m_grid->GetPropertyValue("Properties.BoneOffset.BoneOffsetX").GetDouble());
                timeline_currentAnim->SetKeyFrameInterpolation(selectedBone->GetName(), Sk::Anim::PositionXKeyFrame, timeline_current,
                                                               ToString(m_grid->GetPropertyValueAsString("Properties.BoneOffset.BoneOffsetInterpolation")));

                timeline_currentAnim->SetKeyFrame(selectedBone->GetName(), Sk::Anim::PositionYKeyFrame, timeline_current, m_grid->GetPropertyValue("Properties.BoneOffset.BoneOffsetY").GetDouble());
                timeline_currentAnim->SetKeyFrameInterpolation(selectedBone->GetName(), Sk::Anim::PositionYKeyFrame, timeline_current,
                                                               ToString(m_grid->GetPropertyValueAsString("Properties.BoneOffset.BoneOffsetInterpolation")));
            }
            else
            {
                timeline_currentAnim->RemoveKeyFrame(selectedBone->GetName(), Sk::Anim::PositionXKeyFrame, timeline_current);
                timeline_currentAnim->RemoveKeyFrame(selectedBone->GetName(), Sk::Anim::PositionYKeyFrame, timeline_current);
            }
        }
        //When we change keyframe interpolation
        else if(event.GetProperty()->GetBaseName() == "BoneOffsetInterpolation")
        {
            timeline_currentAnim->SetKeyFrameInterpolation(selectedBone->GetName(), Sk::Anim::PositionXKeyFrame, timeline_current,
                                                           ToString(m_grid->GetPropertyValueAsString("Properties.BoneOffset.BoneOffsetInterpolation")));
            timeline_currentAnim->SetKeyFrameInterpolation(selectedBone->GetName(), Sk::Anim::PositionYKeyFrame, timeline_current,
                                                           ToString(m_grid->GetPropertyValueAsString("Properties.BoneOffset.BoneOffsetInterpolation")));
        }

        //When image modified
        if(event.GetProperty()->GetBaseName() == "BoneImage")
        {
            selectedBone->SetTextureName(ToString(event.GetPropertyValue().GetString()));

            //When angle keyframe is already checked, modification applied
            if(m_grid->GetPropertyValueAsBool("Properties.BoneImage.BoneImageKeyFrame"))
            {
                timeline_currentAnim->SetKeyFrame(selectedBone->GetName(), Sk::Anim::ImageKeyFrame, timeline_current, ToString(event.GetPropertyValue().GetString()));
            }
        }
        //When check/uncheck keyframe for image
        else if(event.GetProperty()->GetBaseName() == "BoneImageKeyFrame")
        {
            if(event.GetPropertyValue().GetBool())
            {
                timeline_currentAnim->SetKeyFrame(selectedBone->GetName(), Sk::Anim::ImageKeyFrame, timeline_current,
                                                  ToString(m_grid->GetPropertyValueAsString("Properties.BoneImage")));
            }
            else
            {
                timeline_currentAnim->RemoveKeyFrame(selectedBone->GetName(), Sk::Anim::ImageKeyFrame, timeline_current);
            }
        }
    }

    selectedBone->Update();

    Panel1->Refresh();
    Panel1->Update();
}

void SkeletonObjectEditor::OnPanel2Resize(wxSizeEvent& event)
{
    Panel2->Refresh();
    Panel2->Update();
}

void SkeletonObjectEditor::OnPanel1Resize(wxSizeEvent& event)
{
    Panel1->Refresh();
    Panel1->Update();
}

void SkeletonObjectEditor::OnButton1Click1(wxCommandEvent& event)
{
    SkeletonSettings dialog(this, &skeleton);
    dialog.ShowModal();
}

void SkeletonObjectEditor::OnInit(wxInitDialogEvent& event)
{
}

float SkeletonObjectEditor::GetGraduationScale(float width, float scale) const
{
    float betweenGradDiff = 100000;
    while((betweenGradDiff * scale > 100 && betweenGradDiff > 1) || (betweenGradDiff * scale > 250 && betweenGradDiff <= 1))
    {
        betweenGradDiff /= 10;
    }

    return betweenGradDiff;
}

#endif
