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
#include "TemplateInsertion.h"
#include "TreeItemInfos.h"

#include "GDL/Game.h"
#include "SkeletonObject.h"
#include "TemplateCreator.h"
#include "InterpolationMethods.h"
#include "GDCore/IDE/CommonBitmapManager.h"
#include "GDL/CommonTools.h"
#include "GDL/IDE/Dialogs/ResourcesEditor.h"
#include <algorithm>

#undef _
#define _(s)                     wxGetTranslation((L##s))

//(*IdInit(SkeletonObjectEditor)
const long SkeletonObjectEditor::ID_TOGGLEBUTTON1 = wxNewId();
const long SkeletonObjectEditor::ID_TOGGLEBUTTON2 = wxNewId();
const long SkeletonObjectEditor::ID_PANEL1 = wxNewId();
const long SkeletonObjectEditor::ID_PANEL2 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON6 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON5 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON1 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON3 = wxNewId();
const long SkeletonObjectEditor::ID_PANEL6 = wxNewId();
const long SkeletonObjectEditor::ID_PANEL4 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON2 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON4 = wxNewId();
const long SkeletonObjectEditor::ID_PANEL7 = wxNewId();
const long SkeletonObjectEditor::ID_CHOICE1 = wxNewId();
const long SkeletonObjectEditor::ID_BITMAPBUTTON2 = wxNewId();
const long SkeletonObjectEditor::ID_BITMAPBUTTON4 = wxNewId();
const long SkeletonObjectEditor::ID_BITMAPBUTTON6 = wxNewId();
const long SkeletonObjectEditor::ID_BITMAPBUTTON1 = wxNewId();
const long SkeletonObjectEditor::ID_BITMAPBUTTON3 = wxNewId();
const long SkeletonObjectEditor::ID_BITMAPBUTTON5 = wxNewId();
const long SkeletonObjectEditor::ID_PANEL3 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON9 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON10 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON7 = wxNewId();
const long SkeletonObjectEditor::ID_PANEL8 = wxNewId();
const long SkeletonObjectEditor::ID_TREECTRL1 = wxNewId();
const long SkeletonObjectEditor::ID_PANEL5 = wxNewId();
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
	wxFlexGridSizer* FlexGridSizer10;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer9;
	wxBoxSizer* BoxSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxGridSizer* GridSizer1;
	wxFlexGridSizer* FlexGridSizer8;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer13;
	wxFlexGridSizer* FlexGridSizer12;
	wxFlexGridSizer* FlexGridSizer6;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer11;

	Create(parent, wxID_ANY, _("Editeur de squelette"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxCLOSE_BOX|wxMAXIMIZE_BOX, _T("wxID_ANY"));
	FlexGridSizer3 = new wxFlexGridSizer(6, 1, 0, 0);
	FlexGridSizer3->AddGrowableCol(0);
	FlexGridSizer3->AddGrowableRow(0);
	Core = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	FlexGridSizer6 = new wxFlexGridSizer(2, 1, 0, 0);
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
	FlexGridSizer5->Add(FlexGridSizer11, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer6->Add(FlexGridSizer5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	FlexGridSizer1 = new wxFlexGridSizer(1, 3, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	Panel1 = new wxPanel(Core, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer6->Add(FlexGridSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	Core->SetSizer(FlexGridSizer6);
	FlexGridSizer6->Fit(Core);
	FlexGridSizer6->SetSizeHints(Core);
	FlexGridSizer3->Add(Core, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	Bottom = new wxPanel(this, ID_PANEL6, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL6"));
	FlexGridSizer9 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer9->AddGrowableCol(0);
	FlexGridSizer7 = new wxFlexGridSizer(0, 4, 0, 0);
	Button3 = new wxButton(Bottom, ID_BUTTON6, _("Banque d\'image"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
	FlexGridSizer7->Add(Button3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button1 = new wxButton(Bottom, ID_BUTTON5, _("Paramètres du squelette..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FlexGridSizer7->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ValidateButton = new wxButton(Bottom, ID_BUTTON1, _("Valider"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	ValidateButton->SetDefault();
	FlexGridSizer7->Add(ValidateButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button2 = new wxButton(Bottom, ID_BUTTON3, _("Annuler"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer7->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9->Add(FlexGridSizer7, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	Bottom->SetSizer(FlexGridSizer9);
	FlexGridSizer9->Fit(Bottom);
	FlexGridSizer9->SetSizeHints(Bottom);
	FlexGridSizer3->Add(Bottom, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoneProperties = new wxPanel(this, ID_PANEL7, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL7"));
	FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2->AddGrowableCol(0);
	FlexGridSizer2->AddGrowableRow(0);
	propertyGridPanel = new wxPanel(BoneProperties, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	propertyGridSizer = new wxFlexGridSizer(1, 1, 0, 0);
	propertyGridSizer->AddGrowableCol(0);
	propertyGridSizer->AddGrowableRow(0);
	propertyGridPanel->SetSizer(propertyGridSizer);
	propertyGridSizer->Fit(propertyGridPanel);
	propertyGridSizer->SetSizeHints(propertyGridPanel);
	FlexGridSizer2->Add(propertyGridPanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer4 = new wxFlexGridSizer(1, 2, 0, 0);
	FlexGridSizer4->AddGrowableCol(0);
	addChildBoneBt = new wxButton(BoneProperties, ID_BUTTON2, _("Ajouter un os enfant"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer4->Add(addChildBoneBt, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	deleteBoneBt = new wxButton(BoneProperties, ID_BUTTON4, _("Supprimer"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer4->Add(deleteBoneBt, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer2->Add(FlexGridSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoneProperties->SetSizer(FlexGridSizer2);
	FlexGridSizer2->Fit(BoneProperties);
	FlexGridSizer2->SetSizeHints(BoneProperties);
	FlexGridSizer3->Add(BoneProperties, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	Timeline = new wxPanel(this, ID_PANEL8, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL8"));
	FlexGridSizer12 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer12->AddGrowableCol(0);
	FlexGridSizer13 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer8 = new wxFlexGridSizer(0, 7, 0, 0);
	AnimationCombobox = new wxChoice(Timeline, ID_CHOICE1, wxDefaultPosition, wxSize(163,-1), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	FlexGridSizer8->Add(AnimationCombobox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BitmapButton2 = new wxBitmapButton(Timeline, ID_BITMAPBUTTON2, wxBitmap(wxImage(_T("res/addicon.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
	BitmapButton2->SetToolTip(_("Ajouter une animation"));
	BitmapButton2->SetHelpText(_("Ajouter une animation"));
	FlexGridSizer8->Add(BitmapButton2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BitmapButton4 = new wxBitmapButton(Timeline, ID_BITMAPBUTTON4, wxBitmap(wxImage(_T("res/copyIcon.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON4"));
	BitmapButton4->SetDefault();
	BitmapButton4->SetToolTip(_("Dupliquer l\'animation sélectionnée"));
	FlexGridSizer8->Add(BitmapButton4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	templateBt = new wxBitmapButton(Timeline, ID_BITMAPBUTTON6, wxBitmap(wxImage(_T("res\\bookmark.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON6"));
	templateBt->SetDefault();
	templateBt->SetToolTip(_("Appliquer un modèle à l\'animation courante."));
	FlexGridSizer8->Add(templateBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BitmapButton1 = new wxBitmapButton(Timeline, ID_BITMAPBUTTON1, wxBitmap(wxImage(_T("res/paraJeu16.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	BitmapButton1->SetDefault();
	BitmapButton1->SetToolTip(_("Configurer l\'animation..."));
	BitmapButton1->SetHelpText(_("Configurer l\'animation"));
	FlexGridSizer8->Add(BitmapButton1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BitmapButton3 = new wxBitmapButton(Timeline, ID_BITMAPBUTTON3, wxBitmap(wxImage(_T("res/deleteicon.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON3"));
	BitmapButton3->SetToolTip(_("Supprimer l\'animation"));
	BitmapButton3->SetHelpText(_("Supprimer l\'animation"));
	FlexGridSizer8->Add(BitmapButton3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	createTemplateBt = new wxBitmapButton(Timeline, ID_BITMAPBUTTON5, wxBitmap(wxImage(_T("res\\bookmark_add.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON5"));
	createTemplateBt->SetDefault();
	createTemplateBt->SetToolTip(_("Créer un modèle"));
	FlexGridSizer8->Add(createTemplateBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	FlexGridSizer13->Add(FlexGridSizer8, 0, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
	FlexGridSizer12->Add(FlexGridSizer13, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer10 = new wxFlexGridSizer(1, 2, 0, 0);
	FlexGridSizer10->AddGrowableCol(0);
	FlexGridSizer10->AddGrowableRow(0);
	Panel2 = new wxPanel(Timeline, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	FlexGridSizer10->Add(Panel2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer2 = new wxBoxSizer(wxVERTICAL);
	Button4 = new wxButton(Timeline, ID_BUTTON9, _("Zoomer"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON9"));
	BoxSizer2->Add(Button4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	Button5 = new wxButton(Timeline, ID_BUTTON10, _("Dézoomer"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON10"));
	BoxSizer2->Add(Button5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	Button6 = new wxButton(Timeline, ID_BUTTON7, _("Aller à..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
	BoxSizer2->Add(Button6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer10->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer12->Add(FlexGridSizer10, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	Timeline->SetSizer(FlexGridSizer12);
	FlexGridSizer12->Fit(Timeline);
	FlexGridSizer12->SetSizeHints(Timeline);
	FlexGridSizer3->Add(Timeline, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	KeyFrameTree = new wxPanel(this, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
	GridSizer1 = new wxGridSizer(1, 1, 0, 0);
	TreeCtrl1 = new wxTreeCtrl(KeyFrameTree, ID_TREECTRL1, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL1"));
	GridSizer1->Add(TreeCtrl1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	KeyFrameTree->SetSizer(GridSizer1);
	GridSizer1->Fit(KeyFrameTree);
	GridSizer1->SetSizeHints(KeyFrameTree);
	FlexGridSizer3->Add(KeyFrameTree, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(FlexGridSizer3);
	FlexGridSizer3->Fit(this);
	FlexGridSizer3->SetSizeHints(this);
	Center();

	Connect(ID_TOGGLEBUTTON1,wxEVT_COMMAND_TOGGLEBUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnToggleButton1Toggle);
	Connect(ID_TOGGLEBUTTON2,wxEVT_COMMAND_TOGGLEBUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnToggleButton2Toggle);
	Panel1->Connect(wxEVT_PAINT,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1Paint,0,this);
	Panel1->Connect(wxEVT_ERASE_BACKGROUND,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1EraseBackground,0,this);
	Panel1->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1LeftDown,0,this);
	Panel1->Connect(wxEVT_LEFT_UP,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1LeftUp,0,this);
	Panel1->Connect(wxEVT_RIGHT_DOWN,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1RightDown,0,this);
	Panel1->Connect(wxEVT_RIGHT_UP,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1RightUp,0,this);
	Panel1->Connect(wxEVT_MOTION,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1MouseMove,0,this);
	Panel1->Connect(wxEVT_SIZE,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1Resize,0,this);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnButton3Click);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnButton1Click1);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnValidateButtonClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnButton2Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnaddChildBoneBtClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OndeleteBoneBtClick);
	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&SkeletonObjectEditor::OnAnimationComboboxSelect);
	Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnBitmapButton2Click);
	Connect(ID_BITMAPBUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnBitmapButton4Click);
	Connect(ID_BITMAPBUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OntemplateBtClick);
	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnBitmapButton1Click);
	Connect(ID_BITMAPBUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnBitmapButton3Click);
	Connect(ID_BITMAPBUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OncreateTemplateBtClick);
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
	Connect(ID_TREECTRL1,wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&SkeletonObjectEditor::OnTreeCtrl1ItemRightClick);
	Connect(ID_TREECTRL1,wxEVT_COMMAND_TREE_SEL_CHANGED,(wxObjectEventFunction)&SkeletonObjectEditor::OnTreeCtrl1SelectionChanged);
	Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&SkeletonObjectEditor::OnInit);
	//*)

	resourcesEditor = new ResourcesEditor( this, game, mainEditorCommand );
    resourcesEditor->Refresh();

	m_mgr.SetManagedWindow( this );
    m_mgr.AddPane( Core, wxAuiPaneInfo().Name( wxT( "Core" ) ).Center().CaptionVisible(false) );
    m_mgr.AddPane( Bottom, wxAuiPaneInfo().Name( wxT( "Bottom" ) ).Bottom().DockFixed().CaptionVisible(false) );
    m_mgr.AddPane( BoneProperties, wxAuiPaneInfo().Name( wxT( "BP" ) ).Right().Caption( _T( "Propriétés des os" ) ).MaximizeButton( true ).MinimizeButton( false ).CloseButton(false).Show(true).MinSize(300, 100) );
    m_mgr.AddPane( KeyFrameTree, wxAuiPaneInfo().Name( wxT( "KFT" ) ).Right().Caption( _T( "Frames clés" ) ).MaximizeButton( true ).MinimizeButton( false ).CloseButton(false).Show(true).MinSize(300, 100) );
    m_mgr.AddPane( Timeline, wxAuiPaneInfo().Name( wxT( "Animation" ) ).Top().Caption( _T( "Animations" ) ).MaximizeButton( true ).MinimizeButton( false ).CloseButton(false).Show(true).MinSize(300, 115) );
    m_mgr.AddPane( resourcesEditor, wxAuiPaneInfo().Name( wxT( "EI" ) ).Left().Caption( _T( "Editeur de la banque d'images" ) ).MaximizeButton( true ).MinimizeButton( false ).Show(false).MinSize(150, 100) );
    m_mgr.SetFlags( wxAUI_MGR_ALLOW_FLOATING | wxAUI_MGR_ALLOW_ACTIVE_PANE | wxAUI_MGR_TRANSPARENT_HINT
                    | wxAUI_MGR_TRANSPARENT_DRAG | wxAUI_MGR_HINT_FADE | wxAUI_MGR_NO_VENETIAN_BLINDS_FADE );
    m_mgr.Update();

    m_imageList = new wxImageList(16, 16);
    wxBitmap iconBone("res/Skeleton16.png", wxBITMAP_TYPE_PNG);
    wxBitmap iconKey("res/icon-key.png", wxBITMAP_TYPE_PNG);
    wxBitmap iconKeyInactive("res/icon-key-inactive.png", wxBITMAP_TYPE_PNG);
    m_imageList->Add(iconBone);
    m_imageList->Add(iconKey);
    m_imageList->Add(iconKeyInactive);

    TreeCtrl1->SetImageList(m_imageList);

    PreparePropertyGrid();

    offset = sf::Vector2f(20, 20);
    isDragging = false;
    selectedBone = 0;

    timeline_current = 0;
    timeline_currentAnim = 0;
    timeline_offset = 0;
    timeline_scale = 5;

    isDraggingHandle = NotDragging;

    ToggleMode(0);
    UpdateAnimationsList();

    InitTreeMenu();

    skeleton.GetRootBone()->Update();
    SetSize(900,650); //Set a new default size as the size computed by wxWidgets is too small.
}

SkeletonObjectEditor::~SkeletonObjectEditor()
{
    delete treeKeyMenu;

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

    //Creating all needed items

    // Identification
    m_grid->Append( new wxPropertyCategory(_("Identification"), "Identification") );
    m_grid->Append( new wxStringProperty(_("Nom"), "BoneName", "Bone") );


    // Properties
    m_grid->Append( new wxPropertyCategory(_("Propriétés"), "Properties") );
    m_grid->Append( new wxFloatProperty(_("Angle"), "BoneAngle", 0.f) );
    m_grid->Append( new wxBoolProperty(_("Suivre l'angle du parent"), "BoneInheritAngle", true) );
    m_grid->Append( new wxFloatProperty(_("Longueur"), "BoneLength", 100.f) );
    m_grid->Append( new wxStringProperty(_("Décalage"), "BoneOffset", "") );
    {
        m_grid->AppendIn("BoneOffset", new wxFloatProperty(_("X"), "BoneOffsetX", 0.f));
        m_grid->AppendIn("BoneOffset", new wxFloatProperty(_("Y"), "BoneOffsetY", 0.f));
    }

    m_grid->Append( new wxStringProperty(_("Image"), "BoneImage", "") );
    m_grid->Append( new wxIntProperty(_("Plan"), "BoneZOrder", 0) );


    // Collision mask
    m_grid->Append( new wxPropertyCategory(_("Collision"), "Collision") );
    m_grid->Append( new wxBoolProperty(_("Activer le masque"), "HasHitBox", false));
    m_grid->Append( new wxStringProperty(_("Taille du masque"), "HitBox", "<composed>"));
    {
        m_grid->AppendIn("HitBox", new wxFloatProperty(_("Largeur"), "HitBoxWidth", 0.f));
        m_grid->AppendIn("HitBox", new wxFloatProperty(_("Hauteur"), "HitBoxHeight", 0.f));
    }

    m_grid->SetPropertyAttributeAll(wxPG_BOOL_USE_CHECKBOX, true);

    Connect(GRIDID, wxEVT_PG_CHANGING, (wxObjectEventFunction)&SkeletonObjectEditor::OnGridPropertyChanging);
    Connect(GRIDID, wxEVT_PG_CHANGED, (wxObjectEventFunction)&SkeletonObjectEditor::OnGridPropertyChanged);
}

void SkeletonObjectEditor::OnValidateButtonClick(wxCommandEvent& event)
{
    skeleton.GetAnimator().SetCurrentAnimationName("Initial");
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

    skeleton.DrawWx(dc, offset, selectedBone);
}

void SkeletonObjectEditor::OnPanel1LeftDown(wxMouseEvent& event)
{
    if(isDraggingHandle == NotDragging)
    {
        /*if(selectedBone && selectedBone->GetParentBone())
        {
            selectedBone->GetParentBone()->ShowMathsFrame(false);
        }*/

        if(selectedBone && selectedBone->IsOnAngleHandle(sf::Vector2f(event.GetPosition().x - offset.x, event.GetPosition().y - offset.y)))
        {
            draggingStartPosition = sf::Vector2f(event.GetPosition().x, event.GetPosition().y) - offset;
            isDraggingHandle = DraggingAngle;
        }

        //selectedBone = 0;

        sf::Vector2f mousePos(event.GetPosition().x, event.GetPosition().y);
        Sk::Bone *searched = FindBoneOnPosition(mousePos, skeleton.GetRootBone());

        if(searched)
        {
            //selectedBone = searched;
            SelectBone(searched);
            SelectBoneInTree(searched);
        }
        else
        {
            //selectedBone = 0;
            SelectBone(0);
        }

        UpdateForSelectedBone();
    }

    /*Panel1->Refresh(); //Refresh
    Panel1->Update(); //Immediately

    Panel2->Refresh();
    Panel2->Update();*/
}

void SkeletonObjectEditor::SelectBone(Sk::Bone *bone)
{
    if(selectedBone && selectedBone->GetParentBone())
    {
        selectedBone->GetParentBone()->ShowMathsFrame(false);
    }

    selectedBone = bone;

    UpdateForSelectedBone();

    Panel1->Refresh(); //Refresh
    Panel1->Update(); //Immediately

    Panel2->Refresh();
    Panel2->Update();
}

void SkeletonObjectEditor::OnPanel1LeftUp(wxMouseEvent& event)
{
    if(selectedBone && isDraggingHandle != NotDragging)
    {
        if(isDraggingHandle == DraggingAngle)
        {
            isDraggingHandle = NotDragging;
        }
    }

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

    if(selectedBone && isDraggingHandle != NotDragging)
    {
        if(isDraggingHandle == DraggingAngle)
        {
            float computedAngle;

            sf::Vector2f relativePosition = sf::Vector2f(event.GetPosition().x - offset.x,
                                                         event.GetPosition().y - offset.y)
                                            - selectedBone->GetBonePosition();

            computedAngle = (relativePosition.y >= 0 ? 1 : (-1)) * (acos((relativePosition.x)/(sqrt(relativePosition.x * relativePosition.x + relativePosition.y * relativePosition.y))) * 180) / M_PI;

            if(event.ShiftDown())
            {
                computedAngle = floor(computedAngle / 5) * 5;
            }

            if(selectedBone->GetParentBone())
            {
                while(computedAngle - selectedBone->GetParentBone()->GetAbsoluteAngle() <= -180)
                    computedAngle += 360;

                while(computedAngle - selectedBone->GetParentBone()->GetAbsoluteAngle() > 180)
                    computedAngle -= 360;

                computedAngle -= selectedBone->GetParentBone()->GetAbsoluteAngle();
            }
            else
            {
                while(computedAngle <= -180)
                    computedAngle += 360;

                while(computedAngle > 180)
                    computedAngle -= 360;

            }

            //Send the event to the propertyGrid handler to be sure to make the same operations on keyframes...
            wxPropertyGridEvent event;

            m_grid->SetPropertyValue(wxT("Properties.BoneAngle"), computedAngle);
            event.SetProperty(m_grid->GetProperty(wxT("Properties.BoneAngle")));
            event.SetPropertyValue(computedAngle);
            event.SetPropertyGrid(m_grid);

            OnGridPropertyChanged(event);

            selectedBone->Update();
            UpdateForSelectedBone();
        }
    }

    Panel1->Refresh(); //Refresh
    Panel1->Update(); //Immediately

    Panel2->Refresh();
    Panel2->Update();
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

    } while(skeleton.IsNameUsed(boneName));

    Sk::Bone *newBone = skeleton.CreateBone(boneName);
    selectedBone->AddBone(newBone);

    if(selectedBone && selectedBone->GetParentBone())
    {
        selectedBone->GetParentBone()->ShowMathsFrame(false);
    }

    selectedBone = newBone;
    selectedBone->Update();

    Panel1->Refresh(); //Refresh
    Panel1->Update(); //Immediately

    UpdateForSelectedBone();
}

void SkeletonObjectEditor::OndeleteBoneBtClick(wxCommandEvent& event)
{
    skeleton.GetRootBone()->RemoveBone(selectedBone);
    selectedBone = 0;

    Panel1->Refresh(); //Refresh
    Panel1->Update(); //Immediately

    UpdateForSelectedBone();
}

void SkeletonObjectEditor::UpdateForSelectedBone()
{
    if(selectedBone)
    {
        m_grid->SetPropertyValue(wxT("Identification.BoneName"), wxString(selectedBone->GetName()));

        m_grid->SetPropertyValue(wxT("Properties.BoneAngle"), selectedBone->GetAngle());
        m_grid->SetPropertyValue(wxT("Properties.BoneInheritAngle"), selectedBone->IsAngleInheritanceEnabled());
        m_grid->SetPropertyValue(wxT("Properties.BoneLength"), selectedBone->GetLength());
        m_grid->SetPropertyValue(wxT("Properties.BoneOffset.BoneOffsetX"), selectedBone->GetOffset().x);
        m_grid->SetPropertyValue(wxT("Properties.BoneOffset.BoneOffsetY"), selectedBone->GetOffset().y);
        m_grid->SetPropertyValue(wxT("Properties.BoneImage"), wxString(selectedBone->GetTextureName()));
        m_grid->SetPropertyValue(wxT("Properties.BoneZOrder"), selectedBone->GetZOrder());

        m_grid->SetPropertyValue(wxT("Collision.HasHitBox"), selectedBone->IsHitBoxEnabled());
        m_grid->SetPropertyValue(wxT("Collision.HitBox.HitBoxWidth"), selectedBone->GetHitBoxSize().x);
        m_grid->SetPropertyValue(wxT("Collision.HitBox.HitBoxHeight"), selectedBone->GetHitBoxSize().y);

        if(selectedBone->GetParentBone())
        {
            selectedBone->GetParentBone()->ShowMathsFrame(true);
        }
    }
    else
    {
        m_grid->SetPropertyValue(wxT("Identification.BoneName"), wxString(""));

        m_grid->SetPropertyValue(wxT("Properties.BoneAngle"), 0.f);
        m_grid->SetPropertyValue(wxT("Properties.BoneInheritAngle"), true);
        m_grid->SetPropertyValue(wxT("Properties.BoneLength"), 0.f);
        m_grid->SetPropertyValue(wxT("Properties.BoneOffset.BoneOffsetX"), 0.f);
        m_grid->SetPropertyValue(wxT("Properties.BoneOffset.BoneOffsetY"), 0.f);
        m_grid->SetPropertyValue(wxT("Properties.BoneImage"), wxString(""));
        m_grid->SetPropertyValue(wxT("Properties.BoneZOrder"), 0);

        m_grid->SetPropertyValue(wxT("Collision.HasHitBox"), false);
        m_grid->SetPropertyValue(wxT("Collision.HitBox.HitBoxWidth"), 0);
        m_grid->SetPropertyValue(wxT("Collision.HitBox.HitBoxHeight"), 0);
    }
}

Sk::Bone* SkeletonObjectEditor::FindBoneOnPosition(sf::Vector2f position, Sk::Bone *base)
{
    if(base->IsPointOnBone(position - offset))
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
    for(unsigned int a = 0; a < skeleton.GetBones().size(); a++)
    {
        skeleton.GetBones().at(a)->UnColorize();
    }

    if(_mode == 0)
    {
        m_mgr.GetPane("Animation").Hide();
        m_mgr.GetPane("KFT").Hide();

        skeleton.GetAnimator().SetCurrentAnimationName("Initial");
        skeleton.GetAnimator().Seek(0);

        timeline_currentAnim = 0;

        ToggleButton1->SetValue(true);
        ToggleButton2->SetValue(false);

        addChildBoneBt->Enable(true);
        deleteBoneBt->Enable(true);

        m_grid->GetProperty("Identification.BoneName")->Enable(true);
        m_grid->GetProperty("Properties.BoneInheritAngle")->Enable(true);
        m_grid->GetProperty("Collision.HasHitBox")->Enable(true);
        m_grid->GetProperty("Collision.HitBox.HitBoxWidth")->Enable(true);
        m_grid->GetProperty("Collision.HitBox.HitBoxHeight")->Enable(true);

        BitmapButton2->Enable(false);
        BitmapButton4->Enable(false);
        BitmapButton1->Enable(false);
        BitmapButton3->Enable(false);

        AnimationCombobox->Enable(false);
    }
    else
    {
        m_mgr.GetPane("Animation").Show();
        m_mgr.GetPane("KFT").Show();

        skeleton.GetAnimator().GetAnimation("Initial").SetPeriod(0);
        for(std::vector<Sk::Bone*>::const_iterator it = skeleton.GetBones().begin(); it != skeleton.GetBones().end(); it++)
        {
            skeleton.GetAnimator().GetAnimation("Initial").SetKeyFrame((*it)->GetName(), Sk::Anim::AngleKeyFrame, 0, (*it)->GetAngle());

            skeleton.GetAnimator().GetAnimation("Initial").SetKeyFrame((*it)->GetName(), Sk::Anim::LengthKeyFrame, 0, (*it)->GetLength());

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

        m_grid->GetProperty("Properties.BoneInheritAngle")->Enable(false);
        m_grid->GetProperty("Identification.BoneName")->Enable(false);
        m_grid->GetProperty("Collision.HasHitBox")->Enable(false);
        m_grid->GetProperty("Collision.HitBox.HitBoxWidth")->Enable(false);
        m_grid->GetProperty("Collision.HitBox.HitBoxHeight")->Enable(false);

        UpdateAnimationsList();
        SelectAnimation(ToString(AnimationCombobox->GetString(AnimationCombobox->GetSelection())));
    }
    mode = _mode;

    skeleton.ApplyAnimationToBones();

    UpdateKeyFrameTree();

    Panel1->Refresh();
    Panel1->Update();

    Panel2->Refresh(); //Refresh
    Panel2->Update();

    m_mgr.Update();
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
    for(int a = floor(timeline_offset / gradScale) - 1; a < floor(timeline_offset / (gradScale/2)) + floor(panelSize.GetWidth() / (timeline_scale * gradScale)) + 2;a++)
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

        if(GetPositionFromTimeToPixel(timeline_currentAnim->GetPeriod()) < panelSize.GetWidth())
        {
            dc.SetBrush(wxColour(60, 60, 60));
            dc.SetPen(wxPen(wxPENSTYLE_TRANSPARENT));

            dc.DrawRectangle(GetPositionFromTimeToPixel(timeline_currentAnim->GetPeriod()), 17, panelSize.GetWidth() - GetPositionFromTimeToPixel(timeline_currentAnim->GetPeriod()), panelSize.GetHeight() - 17);
        }
    }

    if(timeline_currentAnim)
    {
        //Draw angle keyframes
        {
        std::vector<float> keyFrames = timeline_currentAnim->GetKeyFramesTimes("", Sk::Anim::AngleKeyFrame);
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
        std::vector<float> keyFrames = timeline_currentAnim->GetKeyFramesTimes("", Sk::Anim::LengthKeyFrame);
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
        std::vector<float> keyFrames = timeline_currentAnim->GetKeyFramesTimes("", Sk::Anim::PositionXKeyFrame);
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
        std::vector<float> keyFrames = timeline_currentAnim->GetKeyFramesTimes("", Sk::Anim::ImageKeyFrame);
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

    std::vector<float> keyFrames = timeline_currentAnim->GetKeyFramesTimes();
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

    std::vector<std::string> animations = skeleton.GetAnimator().GetAnimations();

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
    for(unsigned int a = 0; a < skeleton.GetBones().size(); a++)
    {
        skeleton.GetBones().at(a)->UnColorize();
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
    skeleton.GetAnimator().SetCurrentAnimationName(name);
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
    for(unsigned int a = 0; a < skeleton.GetBones().size(); a++)
    {
        skeleton.GetBones().at(a)->UnColorize();
    }

    skeleton.GetAnimator().Seek(time);
    skeleton.ApplyAnimationToBones();

    timeline_current = time;

    for(unsigned int a = 0; a < skeleton.GetBones().size(); a++)
    {
        if(skeleton.GetAnimator().GetAnimation(skeleton.GetAnimator().GetCurrentAnimationName()).HasKeyFrame(skeleton.GetBones().at(a)->GetName(), Sk::Anim::AngleKeyFrame, timeline_current) ||
           skeleton.GetAnimator().GetAnimation(skeleton.GetAnimator().GetCurrentAnimationName()).HasKeyFrame(skeleton.GetBones().at(a)->GetName(), Sk::Anim::LengthKeyFrame, timeline_current) ||
           skeleton.GetAnimator().GetAnimation(skeleton.GetAnimator().GetCurrentAnimationName()).HasKeyFrame(skeleton.GetBones().at(a)->GetName(), Sk::Anim::PositionXKeyFrame, timeline_current) ||
           skeleton.GetAnimator().GetAnimation(skeleton.GetAnimator().GetCurrentAnimationName()).HasKeyFrame(skeleton.GetBones().at(a)->GetName(), Sk::Anim::ImageKeyFrame, timeline_current))
        {
            skeleton.GetBones().at(a)->SetColor(wxColour(0, 148, 255));
        }
    }

    Panel2->Refresh(); //Refresh
    Panel2->Update();

    Panel1->Refresh(); //Refresh
    Panel1->Update();

    UpdateKeyFrameTree();
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

void SkeletonObjectEditor::OntemplateBtClick(wxCommandEvent& event)
{
    if(!timeline_currentAnim)
        return;

    TemplateInsertion templDial(this);
    if(templDial.Init(timeline_currentAnim, &skeleton))
    {
        templDial.ShowModal();
    }
}

void SkeletonObjectEditor::OnBitmapButton3Click(wxCommandEvent& event)
{
    if(AnimationCombobox->GetSelection() == -1)
        return;

    int ret = wxMessageBox(_("Êtes-vous sûr(e) de vouloir supprimer l'animation sélectionnée ?"), _("Confirmation de suppression"), wxYES_NO);

    if(ret == wxYES)
        skeleton.GetAnimator().DeleteAnimation(ToString(AnimationCombobox->GetString(AnimationCombobox->GetSelection())));

    UpdateAnimationsList();
    timeline_currentAnim = 0;
}

void SkeletonObjectEditor::UncolorizeBoneIfNecessary(Sk::Bone &bone)
{
    selectedBone->SetColor(wxColour(0, 255, 0));
}

/*void SkeletonObjectEditor::OnangleApplyToAllBtClick(wxCommandEvent& event)
{
    if(mode != 0 || !selectedBone)
        return;

    std::vector<std::string> listOfAnim = skeleton.GetAnimator().GetAnimations();
    for(unsigned int a = 0; a < listOfAnim.size(); a++)
    {
        skeleton.GetAnimator().GetAnimation(listOfAnim.at(a)).ClearBoneKeyFrames(selectedBone->GetName(), Sk::AngleKeyFrame);
        skeleton.GetAnimator().GetAnimation(listOfAnim.at(a)).SetKeyFrame(selectedBone->GetName(), Sk::AngleKeyFrame, 0, selectedBone->GetAngle());
    }
}

void SkeletonObjectEditor::OnlengthApplyToAllBtClick(wxCommandEvent& event)
{
    if(mode != 0 || !selectedBone)
        return;

    std::vector<std::string> listOfAnim = skeleton.GetAnimator().GetAnimations();
    for(unsigned int a = 0; a < listOfAnim.size(); a++)
    {
        skeleton.GetAnimator().GetAnimation(listOfAnim.at(a)).ClearBoneKeyFrames(selectedBone->GetName(), Sk::LengthKeyFrame);
        skeleton.GetAnimator().GetAnimation(listOfAnim.at(a)).SetKeyFrame(selectedBone->GetName(), Sk::LengthKeyFrame, 0, selectedBone->GetLength());
    }
}
*/

void SkeletonObjectEditor::OnGridPropertyChanging(wxPropertyGridEvent& event)
{
    if(mode == 0 && selectedBone)
    {
        if(event.GetProperty()->GetBaseName() == "BoneName")
        {
            if(skeleton.IsNameUsed(ToString(event.GetPropertyValue().GetString())) && ToString(event.GetPropertyValue().GetString()) != selectedBone->GetName())
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
            selectedBone->SetAngle(event.GetPropertyValue().GetDouble());
            skeleton.GetAnimator().GetAnimation("Initial").SetKeyFrame(selectedBone->GetName(), Sk::Anim::AngleKeyFrame, 0, event.GetPropertyValue().GetDouble());
        }
        else if(event.GetProperty()->GetBaseName() == "BoneInheritAngle")
        {
            selectedBone->EnableAngleInheritance(event.GetPropertyValue().GetBool());
        }
        else if(event.GetProperty()->GetBaseName() == "BoneLength")
        {
            selectedBone->SetLength(event.GetPropertyValue().GetDouble());
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
        else if(event.GetProperty()->GetBaseName() == "HasHitBox")
        {
            selectedBone->EnableHitBox(event.GetProperty()->GetValue().GetBool());
        }
        else if(event.GetProperty()->GetBaseName() == "HitBoxWidth" || event.GetProperty()->GetBaseName() == "HitBoxHeight" || event.GetProperty()->GetBaseName() == "HitBox")
        {
            selectedBone->SetHitBoxSize(m_grid->GetPropertyValue(wxT("Collision.HitBox.HitBoxWidth")).GetDouble(),
                                               m_grid->GetPropertyValue(wxT("Collision.HitBox.HitBoxHeight")).GetDouble());
        }
    }
    else if(mode == 1 && selectedBone && timeline_currentAnim)
    {
        //When angle modified
        if(event.GetProperty()->GetBaseName() == "BoneAngle")
        {
            selectedBone->SetAngle(event.GetPropertyValue().GetDouble());
        }

        //When length modified
        if(event.GetProperty()->GetBaseName() == "BoneLength")
        {
            selectedBone->SetLength(event.GetPropertyValue().GetDouble());
        }

        //When offset modified
        if(event.GetProperty()->GetBaseName() == "BoneOffsetX" || event.GetProperty()->GetBaseName() == "BoneOffsetY")
        {
            selectedBone->SetOffset(m_grid->GetPropertyValue("Properties.BoneOffset.BoneOffsetX").GetDouble(),
                                    m_grid->GetPropertyValue("Properties.BoneOffset.BoneOffsetY").GetDouble());
        }

        //When image modified
        if(event.GetProperty()->GetBaseName() == "BoneImage")
        {
            selectedBone->SetTextureName(ToString(event.GetPropertyValue().GetString()));
        }

        //When ZOrder is modified
        if(event.GetProperty()->GetBaseName() == "BoneZOrder")
        {
            selectedBone->SetZOrder(event.GetPropertyValue().GetInteger());
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

void SkeletonObjectEditor::OncreateTemplateBtClick(wxCommandEvent& event)
{
    if(mode != 1 || !timeline_currentAnim)
        return;

    TemplateCreator templCreator(&skeleton, timeline_currentAnim, this);
    templCreator.ShowModal();
}

void SkeletonObjectEditor::UpdateKeyFrameTree()
{
    if(TreeCtrl1->GetRootItem().IsOk())
    {
        TreeCtrl1->Delete(TreeCtrl1->GetRootItem());
    }

    if(mode == 1 && timeline_currentAnim)
    {
        wxTreeItemId root = TreeCtrl1->AddRoot("",
                                               -1, -1,
                                               TreeItemInfo::Get()->SetItemType(TreeItemInfo::Time)
                                                                  ->SetItemTime(timeline_current)
                                                                  ->NotEditable()
                                               );

        UpdateTreeItem(root);

        for(unsigned int a = 0; a < skeleton.GetBones().size(); a++)
        {
            //Add the bone
            wxTreeItemId boneItem = TreeCtrl1->AppendItem(root, "",
                                                          0, 0,
                                                          TreeItemInfo::Get()->SetItemType(TreeItemInfo::Bone)
                                                                             ->SetItemBone(skeleton.GetBones().at(a)->GetName())
                                                                             ->SetItemTime(timeline_current)
                                                         );
            UpdateTreeItem(boneItem);

            //Adding corresponding TreeItems
            {
                wxTreeItemId keyItem = TreeCtrl1->AppendItem(boneItem, "",
                                                             1, 1,
                                                             TreeItemInfo::Get()->SetItemType(TreeItemInfo::Key)
                                                                                ->SetItemBone(skeleton.GetBones().at(a)->GetName())
                                                                                ->SetItemTime(timeline_current)
                                                                                ->SetItemKeyType(Sk::Anim::AngleKeyFrame)
                                                             );

                UpdateTreeItem(keyItem);
            }
            {
                wxTreeItemId keyItem = TreeCtrl1->AppendItem(boneItem, "",
                                                             1, 1,
                                                             TreeItemInfo::Get()->SetItemType(TreeItemInfo::Key)
                                                                                ->SetItemBone(skeleton.GetBones().at(a)->GetName())
                                                                                ->SetItemTime(timeline_current)
                                                                                ->SetItemKeyType(Sk::Anim::LengthKeyFrame)
                                                             );

                UpdateTreeItem(keyItem);
            }
            {
                wxTreeItemId keyItem = TreeCtrl1->AppendItem(boneItem, "",
                                                             1, 1,
                                                             TreeItemInfo::Get()->SetItemType(TreeItemInfo::Key)
                                                                                ->SetItemBone(skeleton.GetBones().at(a)->GetName())
                                                                                ->SetItemTime(timeline_current)
                                                                                ->SetItemKeyType(Sk::Anim::PositionXKeyFrame)
                                                             );

                UpdateTreeItem(keyItem);
            }
            {
                wxTreeItemId keyItem = TreeCtrl1->AppendItem(boneItem, "",
                                                             1, 1,
                                                             TreeItemInfo::Get()->SetItemType(TreeItemInfo::Key)
                                                                                ->SetItemBone(skeleton.GetBones().at(a)->GetName())
                                                                                ->SetItemTime(timeline_current)
                                                                                ->SetItemKeyType(Sk::Anim::PositionYKeyFrame)
                                                             );

                UpdateTreeItem(keyItem);
            }
            {
                wxTreeItemId keyItem = TreeCtrl1->AppendItem(boneItem, "",
                                                             1, 1,
                                                             TreeItemInfo::Get()->SetItemType(TreeItemInfo::Key)
                                                                                ->SetItemBone(skeleton.GetBones().at(a)->GetName())
                                                                                ->SetItemTime(timeline_current)
                                                                                ->SetItemKeyType(Sk::Anim::ImageKeyFrame)
                                                             );

                UpdateTreeItem(keyItem);
            }
            {
                wxTreeItemId keyItem = TreeCtrl1->AppendItem(boneItem, "",
                                                             1, 1,
                                                             TreeItemInfo::Get()->SetItemType(TreeItemInfo::Key)
                                                                                ->SetItemBone(skeleton.GetBones().at(a)->GetName())
                                                                                ->SetItemTime(timeline_current)
                                                                                ->SetItemKeyType(Sk::Anim::ZOrderKeyFrame)
                                                             );

                UpdateTreeItem(keyItem);
            }
        }
    }

    TreeCtrl1->ExpandAll();
}

void SkeletonObjectEditor::UpdateTreeItem(wxTreeItemId id)
{
    if(!id.IsOk())
        return;

    TreeItemInfo *info = dynamic_cast<TreeItemInfo*>(TreeCtrl1->GetItemData(id));
    if(!info)
        return;

    if(info->type == TreeItemInfo::Time)
    {
        TreeCtrl1->SetItemText(id, wxString(_("Position : ") + wxString(ToString(info->time).c_str()) + wxString("s")));
    }
    else if(info->type == TreeItemInfo::Bone)
    {
        TreeCtrl1->SetItemText(id, wxString(info->boneName));
    }
    else if(info->type == TreeItemInfo::Key)
    {
        wxString name = "";
        wxString unit = "";
        bool hasInterpolation = info->hasInterpolation;
        bool isString = info->keyType == Sk::Anim::ImageKeyFrame;

        bool exists = timeline_currentAnim->HasKeyFrame(ToString(info->boneName), info->keyType, info->time);

        if(info->keyType == Sk::Anim::AngleKeyFrame)
        {
            name = _("Angle");
            unit = _("°");
        }
        else if(info->keyType == Sk::Anim::LengthKeyFrame)
        {
            name = _("Taille");
            unit = _("px");
        }
        else if(info->keyType == Sk::Anim::PositionXKeyFrame)
        {
            name = _("Décalage X");
            unit = _("px");
        }
        else if(info->keyType == Sk::Anim::PositionYKeyFrame)
        {
            name = _("Décalage Y");
            unit = _("px");
        }
        else if(info->keyType == Sk::Anim::ImageKeyFrame)
        {
            name = _("Image");
        }
        else if(info->keyType == Sk::Anim::ZOrderKeyFrame)
        {
            name = _("Plan");
        }

        if(exists)
        {
            TreeCtrl1->SetItemTextColour(id, wxColour(0, 0, 0, 255));
            TreeCtrl1->SetItemImage(id, 1);

            if(!isString)
            {
                float value = timeline_currentAnim->GetKeyFrame(ToString(info->boneName), info->keyType, info->time).value;
                TreeCtrl1->SetItemText(id, name + " : " + wxString(ToString(value).c_str()) + " " + unit + (hasInterpolation ? " (" + wxString(timeline_currentAnim->GetKeyFrame(ToString(info->boneName), info->keyType, info->time).interpolation.c_str()) + ")" : ""));
            }
            else
            {
                std::string valueStr = timeline_currentAnim->GetKeyFrame(ToString(info->boneName), info->keyType, info->time).valueStr;
                TreeCtrl1->SetItemText(id, name + " : " + wxString(valueStr.c_str()) + " " + unit + (hasInterpolation ? " (" + wxString(timeline_currentAnim->GetKeyFrame(ToString(info->boneName), info->keyType, info->time).interpolation.c_str()) + ")" : ""));
            }
        }
        else
        {
            TreeCtrl1->SetItemTextColour(id, wxColour(120, 120, 120, 255));
            TreeCtrl1->SetItemImage(id, 2);
            TreeCtrl1->SetItemText(id, name + _(" (inexistante)"));
        }
    }
}

void SkeletonObjectEditor::OnTreeCtrl1SelectionChanged(wxTreeEvent& event)
{
    if(!event.GetItem().IsOk())
        return;

    TreeItemInfo *info = dynamic_cast<TreeItemInfo*>(TreeCtrl1->GetItemData(event.GetItem()));
    if(!info)
        return;

    if(!info->editable)
        return;

    if(info->type == TreeItemInfo::Bone || info->type == TreeItemInfo::Key)
    {
        SelectBone(skeleton.GetBone(ToString(info->boneName)));
    }
}

void SkeletonObjectEditor::OnTreeCtrl1ItemRightClick(wxTreeEvent& event)
{
    if(!event.GetItem().IsOk())
        return;

    TreeItemInfo *info = dynamic_cast<TreeItemInfo*>(TreeCtrl1->GetItemData(event.GetItem()));
    if(!info)
        return;

    if(!info->editable)
        return;

    TreeCtrl1->SelectItem(event.GetItem());

    if(info->type == TreeItemInfo::Key)
    {
        wxRect boundingRect;
        TreeCtrl1->GetBoundingRect(event.GetItem(), boundingRect, true);

        wxPoint position;
        position = boundingRect.GetBottomLeft();

        if(info->hasInterpolation)
            treeKeyInterpItem->Enable(true);
        else
            treeKeyInterpItem->Enable(false);

        int id = TreeCtrl1->GetPopupMenuSelectionFromUser(*treeKeyMenu, position);

        if(id == treeKeyResetItem_ID)
        {
            std::string interpMethod = timeline_currentAnim->GetKeyFrameInterpolation(ToString(info->boneName), info->keyType, info->time);

            Sk::Anim::KeyFrame keyFrame;
            keyFrame.time = info->time;

            if(interpMethod == "")
                interpMethod = "Linear";

            keyFrame.interpolation = interpMethod;

            if(info->keyType == Sk::Anim::AngleKeyFrame)
                keyFrame.value = selectedBone->GetAngle();
            else if(info->keyType == Sk::Anim::LengthKeyFrame)
                keyFrame.value = selectedBone->GetLength();
            else if(info->keyType == Sk::Anim::PositionXKeyFrame)
                keyFrame.value = selectedBone->GetOffset().x;
            else if(info->keyType == Sk::Anim::PositionYKeyFrame)
                keyFrame.value = selectedBone->GetOffset().y;
            else if(info->keyType == Sk::Anim::ImageKeyFrame)
                keyFrame.valueStr = selectedBone->GetTextureName();
            else if(info->keyType == Sk::Anim::ZOrderKeyFrame)
                keyFrame.value = selectedBone->GetZOrder();

            timeline_currentAnim->SetKeyFrame(ToString(info->boneName), info->keyType, keyFrame);
        }
        else if(id == treeKeyInterpItem_ID)
        {
            std::string interpMethod = timeline_currentAnim->GetKeyFrameInterpolation(ToString(info->boneName), info->keyType, info->time);

            std::vector<std::string> listOfMethods = Sk::Anim::Interp::Get::Methods();
            wxArrayString interMethods;
            for(unsigned int a = 0; a < listOfMethods.size(); a++)
            {
                interMethods.Add(wxString(listOfMethods.at(a).c_str()));
            }

            wxSingleChoiceDialog dialog(this, _("Choisissez une méthode d'interpolation"), _("Méthode d'interpolation"), interMethods);
            dialog.ShowModal();

            timeline_currentAnim->SetKeyFrameInterpolation(ToString(info->boneName), info->keyType, info->time, ToString(dialog.GetStringSelection()));
        }
        else if(id == treeKeyDeleteItem_ID)
        {
            timeline_currentAnim->RemoveKeyFrame(ToString(info->boneName), info->keyType, info->time);
        }

        UpdateTreeItem(event.GetItem());
    }
}

void SkeletonObjectEditor::SelectBoneInTree(Sk::Bone *bone, wxTreeItemId parent)
{
    if(!bone)
        return;

    TreeCtrl1->CollapseAll();
    TreeCtrl1->Expand(TreeCtrl1->GetRootItem());
    wxTreeItemId boneItem = FindTreeItem(timeline_current, bone->GetName(), TreeCtrl1->GetRootItem());

    if(boneItem.IsOk())
    {
        TreeCtrl1->SelectItem(boneItem);
        TreeCtrl1->Expand(boneItem);
    }
}

void SkeletonObjectEditor::InitTreeMenu()
{
    treeKeyMenu = new wxMenu();

    treeKeyResetItem_ID = wxNewId();
    treeKeyResetItem = new wxMenuItem(treeKeyMenu, treeKeyResetItem_ID, _("Mettre à jour"));

    treeKeyInterpItem_ID = wxNewId();
    treeKeyInterpItem = new wxMenuItem(treeKeyMenu, treeKeyInterpItem_ID, _("Changer l'interpolation"));

    treeKeyDeleteItem_ID = wxNewId();
    treeKeyDeleteItem = new wxMenuItem(treeKeyMenu, treeKeyInterpItem_ID, _("Supprimer la clé"));

    treeKeyMenu->Append(treeKeyResetItem);
    treeKeyMenu->Append(treeKeyInterpItem);
    treeKeyMenu->Append(treeKeyDeleteItem);
}

wxTreeItemId SkeletonObjectEditor::FindTreeItem(float time, wxTreeItemId parent)
{
    wxTreeItemIdValue cookie;

    if(!parent.IsOk())
        parent = TreeCtrl1->GetRootItem();

    TreeItemInfo *info = dynamic_cast<TreeItemInfo*>(TreeCtrl1->GetItemData(parent));
    if(info)
    {
        if(info->type == TreeItemInfo::Time && info->time == time)
            return parent;
    }

    for(wxTreeItemId child = TreeCtrl1->GetFirstChild(parent, cookie); child.IsOk(); child = TreeCtrl1->GetNextChild(parent, cookie))
    {
        wxTreeItemId searchedItem = FindTreeItem(time, child);
        if(searchedItem.IsOk())
            return searchedItem;
    }

    return wxTreeItemId();
}

wxTreeItemId SkeletonObjectEditor::FindTreeItem(float time, wxString boneName, wxTreeItemId parent)
{
    wxTreeItemIdValue cookie;

    if(!parent.IsOk())
        parent = TreeCtrl1->GetRootItem();

    TreeItemInfo *info = dynamic_cast<TreeItemInfo*>(TreeCtrl1->GetItemData(parent));
    if(info)
    {
        if(info->type == TreeItemInfo::Bone && info->time == time && info->boneName == boneName)
            return parent;
    }

    for(wxTreeItemId child = TreeCtrl1->GetFirstChild(parent, cookie); child.IsOk(); child = TreeCtrl1->GetNextChild(parent, cookie))
    {
        wxTreeItemId searchedItem = FindTreeItem(time, boneName, child);
        if(searchedItem.IsOk())
            return searchedItem;
    }

    return wxTreeItemId();
}

wxTreeItemId SkeletonObjectEditor::FindTreeItem(float time, wxString boneName, Sk::Anim::KeyFrameType keyType, wxTreeItemId parent)
{
    wxTreeItemIdValue cookie;

    if(!parent.IsOk())
        parent = TreeCtrl1->GetRootItem();

    TreeItemInfo *info = dynamic_cast<TreeItemInfo*>(TreeCtrl1->GetItemData(parent));
    if(info)
    {
        if(info->type == TreeItemInfo::Key && info->time == time && info->boneName == boneName && info->keyType == keyType)
            return parent;
    }

    for(wxTreeItemId child = TreeCtrl1->GetFirstChild(parent, cookie); child.IsOk(); child = TreeCtrl1->GetNextChild(parent, cookie))
    {
        wxTreeItemId searchedItem = FindTreeItem(time, boneName, keyType, child);
        if(searchedItem.IsOk())
            return searchedItem;
    }

    return wxTreeItemId();
}

#endif
