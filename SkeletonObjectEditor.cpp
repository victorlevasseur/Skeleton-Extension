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
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)
#include <wx/colordlg.h>
#include <wx/filedlg.h>
#include <wx/dcbuffer.h>

#include "GDL/Game.h"
#include "SkeletonObject.h"
#include "GDL/IDE/MainEditorCommand.h"
#include "GDCore/IDE/CommonBitmapManager.h"
#include "GDL/CommonTools.h"
#include "GDL/IDE/Dialogs/ResourcesEditor.h"

//(*IdInit(SkeletonObjectEditor)
const long SkeletonObjectEditor::ID_TOGGLEBUTTON1 = wxNewId();
const long SkeletonObjectEditor::ID_TOGGLEBUTTON2 = wxNewId();
const long SkeletonObjectEditor::ID_PANEL1 = wxNewId();
const long SkeletonObjectEditor::ID_STATICTEXT1 = wxNewId();
const long SkeletonObjectEditor::ID_TEXTCTRL1 = wxNewId();
const long SkeletonObjectEditor::ID_STATICTEXT2 = wxNewId();
const long SkeletonObjectEditor::ID_TEXTCTRL2 = wxNewId();
const long SkeletonObjectEditor::ID_STATICTEXT3 = wxNewId();
const long SkeletonObjectEditor::ID_STATICTEXT4 = wxNewId();
const long SkeletonObjectEditor::ID_TEXTCTRL3 = wxNewId();
const long SkeletonObjectEditor::ID_STATICTEXT6 = wxNewId();
const long SkeletonObjectEditor::ID_TEXTCTRL5 = wxNewId();
const long SkeletonObjectEditor::ID_STATICTEXT7 = wxNewId();
const long SkeletonObjectEditor::ID_TEXTCTRL7 = wxNewId();
const long SkeletonObjectEditor::ID_STATICTEXT5 = wxNewId();
const long SkeletonObjectEditor::ID_TEXTCTRL4 = wxNewId();
const long SkeletonObjectEditor::ID_BITMAPBUTTON1 = wxNewId();
const long SkeletonObjectEditor::ID_STATICTEXT8 = wxNewId();
const long SkeletonObjectEditor::ID_TEXTCTRL6 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON5 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON2 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON4 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON6 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON1 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON3 = wxNewId();
const long SkeletonObjectEditor::ID_PANEL2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SkeletonObjectEditor,wxDialog)
	//(*EventTable(SkeletonObjectEditor)
	//*)
END_EVENT_TABLE()

SkeletonObjectEditor::SkeletonObjectEditor( wxWindow* parent, Game & game_, SkeletonObject & object_, MainEditorCommand & mainEditorCommand_ ) :
game(game_),
mainEditorCommand(mainEditorCommand_),
object(object_),
skeleton(object.GetSkeleton()),
mode(0)
{
	//(*Initialize(SkeletonObjectEditor)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer10;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, _("Editer le squelette"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("wxID_ANY"));
	SetClientSize(wxSize(752,489));
	FlexGridSizer3 = new wxFlexGridSizer(1, 1, 0, 0);
	FlexGridSizer3->AddGrowableCol(0);
	FlexGridSizer3->AddGrowableRow(0);
	Core = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	FlexGridSizer6 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer5 = new wxFlexGridSizer(0, 3, 0, 0);
	ToggleButton1 = new wxToggleButton(Core, ID_TOGGLEBUTTON1, _("Edition des os"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TOGGLEBUTTON1"));
	ToggleButton1->SetValue(true);
	FlexGridSizer5->Add(ToggleButton1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ToggleButton2 = new wxToggleButton(Core, ID_TOGGLEBUTTON2, _("Animation"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TOGGLEBUTTON2"));
	FlexGridSizer5->Add(ToggleButton2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(FlexGridSizer5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1 = new wxFlexGridSizer(1, 2, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, Core, _("Aperçu"));
	Panel1 = new wxPanel(Core, ID_PANEL1, wxDefaultPosition, wxSize(453,373), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	StaticBoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, Core, _("Os sélectionné"));
	FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer4 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText1 = new wxStaticText(Core, ID_STATICTEXT1, _("Nom :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer4->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	nameTextCtrl = new wxTextCtrl(Core, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(142,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer4->Add(nameTextCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(Core, ID_STATICTEXT2, _("Angle :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer4->Add(StaticText2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	angleTextCtrl = new wxTextCtrl(Core, ID_TEXTCTRL2, _("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer4->Add(angleTextCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(Core, ID_STATICTEXT3, _("relatif à l\'os parent."), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	wxFont StaticText3Font(wxDEFAULT,wxDEFAULT,wxFONTSTYLE_ITALIC,wxNORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText3->SetFont(StaticText3Font);
	FlexGridSizer4->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(Core, ID_STATICTEXT4, _("Longueur :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer4->Add(StaticText4, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	lengthTextCtrl = new wxTextCtrl(Core, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	FlexGridSizer4->Add(lengthTextCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(Core, ID_STATICTEXT6, _("Décalage :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer4->Add(StaticText6, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9 = new wxFlexGridSizer(0, 3, 0, 0);
	offsetXTextCtrl = new wxTextCtrl(Core, ID_TEXTCTRL5, _("0"), wxDefaultPosition, wxSize(62,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	FlexGridSizer9->Add(offsetXTextCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(Core, ID_STATICTEXT7, _(";"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer9->Add(StaticText7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	offsetYTextCtrl = new wxTextCtrl(Core, ID_TEXTCTRL7, _("0"), wxDefaultPosition, wxSize(63,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
	FlexGridSizer9->Add(offsetYTextCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(FlexGridSizer9, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	StaticText5 = new wxStaticText(Core, ID_STATICTEXT5, _("Image :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer4->Add(StaticText5, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer8->AddGrowableCol(0);
	imageTextCtrl = new wxTextCtrl(Core, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	FlexGridSizer8->Add(imageTextCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BitmapButton1 = new wxBitmapButton(Core, ID_BITMAPBUTTON1, wxBitmap(wxImage(_T("res/addfromimagebanque.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	FlexGridSizer8->Add(BitmapButton1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(FlexGridSizer8, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	StaticText8 = new wxStaticText(Core, ID_STATICTEXT8, _("Plan :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer4->Add(StaticText8, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer10 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer10->AddGrowableCol(0);
	zOrderTextCtrl = new wxTextCtrl(Core, ID_TEXTCTRL6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
	FlexGridSizer10->Add(zOrderTextCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(FlexGridSizer10, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer4->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button1 = new wxButton(Core, ID_BUTTON5, _("Appliquer"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FlexGridSizer4->Add(Button1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(FlexGridSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	addChildBoneBt = new wxButton(Core, ID_BUTTON2, _("Ajouter un os enfant"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer2->Add(addChildBoneBt, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	deleteBoneBt = new wxButton(Core, ID_BUTTON4, _("Supprimer"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer2->Add(deleteBoneBt, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(FlexGridSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7 = new wxFlexGridSizer(0, 4, 0, 0);
	Button3 = new wxButton(Core, ID_BUTTON6, _("Banque d\'image"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
	FlexGridSizer7->Add(Button3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ValidateButton = new wxButton(Core, ID_BUTTON1, _("Valider"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer7->Add(ValidateButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button2 = new wxButton(Core, ID_BUTTON3, _("Annuler"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer7->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(FlexGridSizer7, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	Core->SetSizer(FlexGridSizer6);
	FlexGridSizer6->Fit(Core);
	FlexGridSizer6->SetSizeHints(Core);
	FlexGridSizer3->Add(Core, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(FlexGridSizer3);
	FlexGridSizer3->SetSizeHints(this);
	Center();

	Connect(ID_TOGGLEBUTTON1,wxEVT_COMMAND_TOGGLEBUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnToggleButton1Toggle);
	Connect(ID_TOGGLEBUTTON2,wxEVT_COMMAND_TOGGLEBUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnToggleButton2Toggle);
	Panel1->Connect(wxEVT_PAINT,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1Paint,0,this);
	Panel1->Connect(wxEVT_ERASE_BACKGROUND,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1EraseBackground,0,this);
	Panel1->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1LeftDown,0,this);
	Panel1->Connect(wxEVT_RIGHT_DOWN,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1RightDown,0,this);
	Panel1->Connect(wxEVT_RIGHT_UP,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1RightUp,0,this);
	Panel1->Connect(wxEVT_MOTION,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1MouseMove,0,this);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnnameTextCtrlText);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnaddChildBoneBtClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OndeleteBoneBtClick);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnButton3Click);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnValidateButtonClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnButton2Click);
	//*)

	resourcesEditor = new ResourcesEditor( this, game, mainEditorCommand );
    resourcesEditor->Refresh();

	m_mgr.SetManagedWindow( this );
    m_mgr.AddPane( Core, wxAuiPaneInfo().Name( wxT( "Core" ) ).Center().CaptionVisible(false) );
    m_mgr.AddPane( resourcesEditor, wxAuiPaneInfo().Name( wxT( "EI" ) ).Left().Caption( _T( "Editeur de la banque d'images" ) ).MaximizeButton( true ).MinimizeButton( false ).Show(false).MinSize(150, 100) );
    m_mgr.SetFlags( wxAUI_MGR_ALLOW_FLOATING | wxAUI_MGR_ALLOW_ACTIVE_PANE | wxAUI_MGR_TRANSPARENT_HINT
                    | wxAUI_MGR_TRANSPARENT_DRAG | wxAUI_MGR_HINT_FADE | wxAUI_MGR_NO_VENETIAN_BLINDS_FADE );
    m_mgr.Update();

    offset = sf::Vector2f(20, 20);
    isDragging = false;
    selectedBone = 0;

    skeleton.GetRoot()->Update();
}

SkeletonObjectEditor::~SkeletonObjectEditor()
{
    m_mgr.UnInit();
	//(*Destroy(SkeletonObjectEditor)
	//*)
}

void SkeletonObjectEditor::OnValidateButtonClick(wxCommandEvent& event)
{
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
    dc.SetBrush(gd::CommonBitmapManager::GetInstance()->transparentBg);
    dc.DrawRectangle(0,0, panelSize.GetWidth(), panelSize.GetHeight());

    skeleton.DrawWx(dc, offset);
}

void SkeletonObjectEditor::OnPanel1LeftDown(wxMouseEvent& event)
{
    skeleton.GetRoot()->UnselectAllChilds();
    selectedBone = 0;

    sf::Vector2f mousePos(event.GetPosition().x, event.GetPosition().y);

    Bone *searched = FindBoneOnPosition(mousePos, skeleton.GetRoot());

    if(searched)
    {
        selectedBone = searched;
        searched->Select(true);
    }
    else
    {
        selectedBone = 0;
    }

    Panel1->Refresh(); //Refresh
    Panel1->Update(); //Immediately

    UpdateForSelectedBone();
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
    Bone *newBone = skeleton.CreateBone("new bone");
    selectedBone->AddBone(newBone);

    skeleton.GetRoot()->UnselectAllChilds();

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
        if(mode == 0)
        {
            nameTextCtrl->SetValue(wxString(selectedBone->GetName()));
            angleTextCtrl->SetValue(wxString(ToString(selectedBone->GetRotation())));
            lengthTextCtrl->SetValue(wxString(ToString(selectedBone->GetSize())));
            offsetXTextCtrl->SetValue(wxString(ToString(selectedBone->GetOffset().x)));
            offsetYTextCtrl->SetValue(wxString(ToString(selectedBone->GetOffset().y)));
            imageTextCtrl->SetValue(wxString(selectedBone->GetTextureName()));
            zOrderTextCtrl->SetValue(wxString(ToString(selectedBone->GetZOrder())));
        }
    }
    else
    {
        nameTextCtrl->SetValue("");
        angleTextCtrl->SetValue("");
        lengthTextCtrl->SetValue("");
        offsetXTextCtrl->SetValue("");
        offsetYTextCtrl->SetValue("");
        imageTextCtrl->SetValue("");
        zOrderTextCtrl->SetValue("");
    }
}

Bone* SkeletonObjectEditor::FindBoneOnPosition(sf::Vector2f position, Bone *base)
{
    if(base->IsOnPosition(position - offset))
        return base;

    for(unsigned int a = 0; a < base->GetChildrenBones().size(); a++)
    {
        Bone *searched = FindBoneOnPosition(position, base->GetChildrenBones().at(a));
        if(searched)
            return searched;
    }

    return 0;
}

void SkeletonObjectEditor::OnnameTextCtrlText(wxCommandEvent& event)
{
    if(mode == 0)
    {
        if(selectedBone)
        {
            selectedBone->SetName(ToString(nameTextCtrl->GetValue()));
            selectedBone->SetRotation(ToFloat(ToString(angleTextCtrl->GetValue())));
            selectedBone->SetSize(ToFloat(ToString(lengthTextCtrl->GetValue())));
            selectedBone->SetTextureName(ToString(imageTextCtrl->GetValue()));
            selectedBone->SetOffset(ToFloat(ToString(offsetXTextCtrl->GetValue())),
                                    ToFloat(ToString(offsetYTextCtrl->GetValue())));
            selectedBone->SetZOrder(ToFloat(ToString(zOrderTextCtrl->GetValue())));

            selectedBone->Update();

            if(skeleton.GetAnimator().GetAnimation("").GetBoneKeyFrames(selectedBone->GetName()).size() == 0)
                skeleton.GetAnimator().GetAnimation("").GetBoneKeyFrames(selectedBone->GetName()).push_back(TimeFloat());

            skeleton.GetAnimator().GetAnimation("").GetBoneKeyFrames(selectedBone->GetName()).at(0).time = 0;
            skeleton.GetAnimator().GetAnimation("").GetBoneKeyFrames(selectedBone->GetName()).at(0).value = ToFloat(ToString(angleTextCtrl->GetValue()));
        }

        Panel1->Refresh(); //Refresh
        Panel1->Update(); //Immediately
    }
}

void SkeletonObjectEditor::ToggleMode(char _mode)
{
    if(_mode == 0)
    {
        ToggleButton1->SetValue(true);
        ToggleButton2->SetValue(false);

        nameTextCtrl->Enable(true);
        addChildBoneBt->Enable(true);
        deleteBoneBt->Enable(true);
    }
    else
    {
        ToggleButton1->SetValue(false);
        ToggleButton2->SetValue(true);

        nameTextCtrl->Enable(false);
        addChildBoneBt->Enable(false);
        deleteBoneBt->Enable(false);
    }
    mode = _mode;
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

#endif

