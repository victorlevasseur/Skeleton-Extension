﻿/*
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
#include <wx/textdlg.h>
#include <wx/msgdlg.h>
#include <wx/choicdlg.h>
#include <wx/arrstr.h>

#include "GDL/Game.h"
#include "SkeletonObject.h"
#include "interpolationMethods.h"
#include "GDL/IDE/MainEditorCommand.h"
#include "GDCore/IDE/CommonBitmapManager.h"
#include "GDL/CommonTools.h"
#include "GDL/IDE/Dialogs/ResourcesEditor.h"
#include <algorithm>

//(*IdInit(SkeletonObjectEditor)
const long SkeletonObjectEditor::ID_TOGGLEBUTTON1 = wxNewId();
const long SkeletonObjectEditor::ID_TOGGLEBUTTON2 = wxNewId();
const long SkeletonObjectEditor::ID_CHOICE1 = wxNewId();
const long SkeletonObjectEditor::ID_BITMAPBUTTON2 = wxNewId();
const long SkeletonObjectEditor::ID_BITMAPBUTTON3 = wxNewId();
const long SkeletonObjectEditor::ID_PANEL3 = wxNewId();
const long SkeletonObjectEditor::ID_STATICTEXT9 = wxNewId();
const long SkeletonObjectEditor::ID_TEXTCTRL8 = wxNewId();
const long SkeletonObjectEditor::ID_STATICTEXT10 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON9 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON10 = wxNewId();
const long SkeletonObjectEditor::ID_PANEL1 = wxNewId();
const long SkeletonObjectEditor::ID_STATICTEXT1 = wxNewId();
const long SkeletonObjectEditor::ID_TEXTCTRL1 = wxNewId();
const long SkeletonObjectEditor::ID_STATICTEXT2 = wxNewId();
const long SkeletonObjectEditor::ID_TEXTCTRL2 = wxNewId();
const long SkeletonObjectEditor::ID_BITMAPBUTTON4 = wxNewId();
const long SkeletonObjectEditor::ID_BITMAPBUTTON5 = wxNewId();
const long SkeletonObjectEditor::ID_BITMAPBUTTON8 = wxNewId();
const long SkeletonObjectEditor::ID_BITMAPBUTTON10 = wxNewId();
const long SkeletonObjectEditor::ID_STATICTEXT3 = wxNewId();
const long SkeletonObjectEditor::ID_STATICTEXT4 = wxNewId();
const long SkeletonObjectEditor::ID_TEXTCTRL3 = wxNewId();
const long SkeletonObjectEditor::ID_BITMAPBUTTON6 = wxNewId();
const long SkeletonObjectEditor::ID_BITMAPBUTTON7 = wxNewId();
const long SkeletonObjectEditor::ID_BITMAPBUTTON9 = wxNewId();
const long SkeletonObjectEditor::ID_BITMAPBUTTON11 = wxNewId();
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
const long SkeletonObjectEditor::ID_PANEL4 = wxNewId();
const long SkeletonObjectEditor::ID_BUTTON6 = wxNewId();
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
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer16;
	wxFlexGridSizer* FlexGridSizer10;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer7;
	wxFlexGridSizer* FlexGridSizer15;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer14;
	wxFlexGridSizer* FlexGridSizer13;
	wxFlexGridSizer* FlexGridSizer12;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer11;
	wxFlexGridSizer* FlexGridSizer17;

	Create(parent, wxID_ANY, _("Editer le squelette"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("wxID_ANY"));
	SetClientSize(wxSize(1089,606));
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
	FlexGridSizer11 = new wxFlexGridSizer(0, 5, 0, 0);
	ToggleButton1 = new wxToggleButton(Core, ID_TOGGLEBUTTON1, _("Edition des os"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TOGGLEBUTTON1"));
	ToggleButton1->SetValue(true);
	FlexGridSizer11->Add(ToggleButton1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ToggleButton2 = new wxToggleButton(Core, ID_TOGGLEBUTTON2, _("Animation"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TOGGLEBUTTON2"));
	FlexGridSizer11->Add(ToggleButton2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	AnimationCombobox = new wxChoice(Core, ID_CHOICE1, wxDefaultPosition, wxSize(167,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	FlexGridSizer11->Add(AnimationCombobox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BitmapButton2 = new wxBitmapButton(Core, ID_BITMAPBUTTON2, wxBitmap(wxImage(_T("res/addicon.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
	BitmapButton2->SetDefault();
	FlexGridSizer11->Add(BitmapButton2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BitmapButton3 = new wxBitmapButton(Core, ID_BITMAPBUTTON3, wxBitmap(wxImage(_T("res/deleteicon.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON3"));
	BitmapButton3->SetDefault();
	FlexGridSizer11->Add(BitmapButton3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(FlexGridSizer11, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer12 = new wxFlexGridSizer(0, 4, 0, 0);
	FlexGridSizer12->AddGrowableCol(0);
	Panel2 = new wxPanel(Core, ID_PANEL3, wxDefaultPosition, wxSize(725,85), wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	FlexGridSizer12->Add(Panel2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer13 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer14 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticText9 = new wxStaticText(Core, ID_STATICTEXT9, _("Periode :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer14->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	periodTextCtrl = new wxTextCtrl(Core, ID_TEXTCTRL8, _("0"), wxDefaultPosition, wxSize(39,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL8"));
	FlexGridSizer14->Add(periodTextCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText10 = new wxStaticText(Core, ID_STATICTEXT10, _("s"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer14->Add(StaticText10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer13->Add(FlexGridSizer14, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer15 = new wxFlexGridSizer(0, 2, 0, 0);
	Button4 = new wxButton(Core, ID_BUTTON9, _("Zoom +"), wxDefaultPosition, wxSize(64,23), 0, wxDefaultValidator, _T("ID_BUTTON9"));
	FlexGridSizer15->Add(Button4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button5 = new wxButton(Core, ID_BUTTON10, _("-"), wxDefaultPosition, wxSize(22,23), 0, wxDefaultValidator, _T("ID_BUTTON10"));
	FlexGridSizer15->Add(Button5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer13->Add(FlexGridSizer15, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer12->Add(FlexGridSizer13, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(FlexGridSizer12, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer6->Add(FlexGridSizer5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1 = new wxFlexGridSizer(1, 3, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, Core, _("Apercu"));
	Panel1 = new wxPanel(Core, ID_PANEL1, wxDefaultPosition, wxSize(457,373), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	StaticBoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, Core, _("Os selectionne"));
	FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2->AddGrowableCol(0);
	FlexGridSizer2->AddGrowableRow(0);
	FlexGridSizer4 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer4->AddGrowableCol(1);
	StaticText1 = new wxStaticText(Core, ID_STATICTEXT1, _("Nom :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer4->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	nameTextCtrl = new wxTextCtrl(Core, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer4->Add(nameTextCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(Core, ID_STATICTEXT2, _("Angle :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer4->Add(StaticText2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer16 = new wxFlexGridSizer(0, 5, 0, 0);
	FlexGridSizer16->AddGrowableCol(0);
	angleTextCtrl = new wxTextCtrl(Core, ID_TEXTCTRL2, _("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer16->Add(angleTextCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	angleCreateKeyFrameBt = new wxBitmapButton(Core, ID_BITMAPBUTTON4, wxBitmap(wxImage(_T("res\\icon-key.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON4"));
	angleCreateKeyFrameBt->SetToolTip(_("Créer une frame clée pour cette valeur"));
	FlexGridSizer16->Add(angleCreateKeyFrameBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	angleDeleteKeyFrameBt = new wxBitmapButton(Core, ID_BITMAPBUTTON5, wxBitmap(wxImage(_T("res\\icon-key-delete.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON5"));
	angleDeleteKeyFrameBt->SetToolTip(_("Supprimer la frame clée de cette valeur"));
	FlexGridSizer16->Add(angleDeleteKeyFrameBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	angleApplyToAllBt = new wxBitmapButton(Core, ID_BITMAPBUTTON8, wxBitmap(wxImage(_T("res\\icon-apply-to-all.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON8"));
	angleApplyToAllBt->SetToolTip(_("Appliquer la valeur sur toutes les animations\n(supprime toute les frames clés de l\'os concernant cette valeur)"));
	FlexGridSizer16->Add(angleApplyToAllBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	angleInterpolationBt = new wxBitmapButton(Core, ID_BITMAPBUTTON10, wxBitmap(wxImage(_T("res\\icon-interpolationtype.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON10"));
	angleInterpolationBt->SetDefault();
	angleInterpolationBt->SetToolTip(_("Changer la méthode d\'interpolation entre la frame clée actuelle et la suivante."));
	FlexGridSizer16->Add(angleInterpolationBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer4->Add(FlexGridSizer16, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer4->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(Core, ID_STATICTEXT3, _("relatif a l\'os parent."), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	wxFont StaticText3Font(wxDEFAULT,wxDEFAULT,wxFONTSTYLE_ITALIC,wxNORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText3->SetFont(StaticText3Font);
	FlexGridSizer4->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(Core, ID_STATICTEXT4, _("Longueur :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer4->Add(StaticText4, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer17 = new wxFlexGridSizer(0, 5, 0, 0);
	FlexGridSizer17->AddGrowableCol(0);
	lengthTextCtrl = new wxTextCtrl(Core, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	FlexGridSizer17->Add(lengthTextCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lengthCreateKeyFrameBt = new wxBitmapButton(Core, ID_BITMAPBUTTON6, wxBitmap(wxImage(_T("res\\icon-key.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON6"));
	lengthCreateKeyFrameBt->SetToolTip(_("Créer une frame clée pour cette valeur"));
	FlexGridSizer17->Add(lengthCreateKeyFrameBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	lengthDeleteKeyFrameBt = new wxBitmapButton(Core, ID_BITMAPBUTTON7, wxBitmap(wxImage(_T("res\\icon-key-delete.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON7"));
	lengthDeleteKeyFrameBt->SetToolTip(_("Supprimer la frame clée de cette valeur"));
	FlexGridSizer17->Add(lengthDeleteKeyFrameBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	lengthApplyToAllBt = new wxBitmapButton(Core, ID_BITMAPBUTTON9, wxBitmap(wxImage(_T("res\\icon-apply-to-all.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON9"));
	lengthApplyToAllBt->SetDefault();
	lengthApplyToAllBt->SetToolTip(_("Appliquer la valeur sur toutes les animations\n(supprime toute les frames clés de l\'os concernant cette valeur)"));
	FlexGridSizer17->Add(lengthApplyToAllBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	lengthInterpolationBt = new wxBitmapButton(Core, ID_BITMAPBUTTON11, wxBitmap(wxImage(_T("res\\icon-interpolationtype.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON11"));
	lengthInterpolationBt->SetDefault();
	lengthInterpolationBt->SetToolTip(_("Changer la méthode d\'interpolation entre la frame clée actuelle et la suivante."));
	FlexGridSizer17->Add(lengthInterpolationBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer4->Add(FlexGridSizer17, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	StaticText6 = new wxStaticText(Core, ID_STATICTEXT6, _("Decalage :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer4->Add(StaticText6, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9 = new wxFlexGridSizer(0, 3, 0, 0);
	offsetXTextCtrl = new wxTextCtrl(Core, ID_TEXTCTRL5, _("0"), wxDefaultPosition, wxSize(53,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	FlexGridSizer9->Add(offsetXTextCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(Core, ID_STATICTEXT7, _(";"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer9->Add(StaticText7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	offsetYTextCtrl = new wxTextCtrl(Core, ID_TEXTCTRL7, _("0"), wxDefaultPosition, wxSize(52,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
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
	addChildBoneBt = new wxButton(Core, ID_BUTTON2, _("Ajouter un os enfant"), wxDefaultPosition, wxSize(292,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer2->Add(addChildBoneBt, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	deleteBoneBt = new wxButton(Core, ID_BUTTON4, _("Supprimer"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer2->Add(deleteBoneBt, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel3 = new wxPanel(Core, ID_PANEL4, wxDefaultPosition, wxSize(350,405), wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	FlexGridSizer1->Add(Panel3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
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
	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&SkeletonObjectEditor::OnAnimationComboboxSelect);
	Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnBitmapButton2Click);
	Panel2->Connect(wxEVT_PAINT,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel2Paint,0,this);
	Panel2->Connect(wxEVT_ERASE_BACKGROUND,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel2EraseBackground,0,this);
	Panel2->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel2LeftDown,0,this);
	Panel2->Connect(wxEVT_RIGHT_DOWN,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel2RightDown,0,this);
	Panel2->Connect(wxEVT_RIGHT_UP,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel2RightUp,0,this);
	Panel2->Connect(wxEVT_MOUSEWHEEL,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel2MouseWheel,0,this);
	Connect(ID_TEXTCTRL8,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&SkeletonObjectEditor::OnTextCtrl1TextEnter);
	Connect(ID_TEXTCTRL8,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&SkeletonObjectEditor::OnTextCtrl1TextEnter);
	Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnButton4Click);
	Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnButton5Click);
	Panel1->Connect(wxEVT_PAINT,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1Paint,0,this);
	Panel1->Connect(wxEVT_ERASE_BACKGROUND,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1EraseBackground,0,this);
	Panel1->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1LeftDown,0,this);
	Panel1->Connect(wxEVT_RIGHT_DOWN,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1RightDown,0,this);
	Panel1->Connect(wxEVT_RIGHT_UP,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1RightUp,0,this);
	Panel1->Connect(wxEVT_MOTION,(wxObjectEventFunction)&SkeletonObjectEditor::OnPanel1MouseMove,0,this);
	Connect(ID_BITMAPBUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OncreateKeyFrameBtClick);
	Connect(ID_BITMAPBUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnremoveKeyFrameBtClick);
	Connect(ID_BITMAPBUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnangleApplyToAllBtClick);
	Connect(ID_BITMAPBUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnangleInterpolationBtClick);
	Connect(ID_BITMAPBUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnlengthCreateKeyFrameBtClick);
	Connect(ID_BITMAPBUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnlengthDeleteKeyFrameBtClick);
	Connect(ID_BITMAPBUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnlengthApplyToAllBtClick);
	Connect(ID_BITMAPBUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SkeletonObjectEditor::OnlengthInterpolationBtClick);
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
        Panel3, // parent
        GRIDID, // id
        wxDefaultPosition, // position
        wxSize(300,500), // size
        wxPG_SPLITTER_AUTO_CENTER |
        wxPG_DEFAULT_STYLE );

    m_grid->SetExtraStyle( wxPG_EX_HELP_AS_TOOLTIPS );
    //FlexGridSizer2->Add(, 1, wxALL|wxEXPAND, 5);

    //Create some stuff for property grid
    std::vector<std::string> listOfMethods = Sk::Interpolation::Get::Methods();
    wxArrayString interMethods;
    for(unsigned int a = 0; a < listOfMethods.size(); a++)
    {
        interMethods.Add(wxString(listOfMethods.at(a).c_str()));
    }

    //Creating all needed items
    m_grid->Append( new wxPropertyCategory(_(L"Identification")) );
    m_grid->Append( new wxStringProperty("Nom", "BoneName", "Bone") );

    m_grid->Append( new wxPropertyCategory(_(L"Propriétés")) );
    m_grid->Append( new wxFloatProperty("Angle", "BoneAngle", 0.f) );
    {
        m_grid->AppendIn("BoneAngle", new wxBoolProperty(_(L"Frame clée"), "BoneAngleKeyFrame", false));
        m_grid->AppendIn("BoneAngle", new wxEnumProperty(_(L"Type d'interpolation"), "BoneAngleInterpolation", interMethods));
    }

    m_grid->Append( new wxFloatProperty("Longueur", "BoneLength", 100.f) );
    {
        m_grid->AppendIn("BoneLength", new wxBoolProperty(_(L"Frame clée"), "BoneLengthKeyFrame", false));
        m_grid->AppendIn("BoneLength", new wxEnumProperty(_(L"Type d'interpolation"), "BoneLengthInterpolation", interMethods));
    }

    m_grid->Append( new wxStringProperty(_(L"Décalage"), "BoneOffset", "") );
    {
        m_grid->AppendIn("BoneOffset", new wxFloatProperty(_(L"X"), "BoneOffsetX", 0.f));
        m_grid->AppendIn("BoneOffset", new wxFloatProperty(_(L"Y"), "BoneOffsetY", 0.f));
        m_grid->AppendIn("BoneOffset", new wxBoolProperty(_(L"Frame clée"), "BoneOffsetKeyFrame", false));
        m_grid->AppendIn("BoneOffset", new wxEnumProperty(_(L"Type d'interpolation"), "BoneOffsetInterpolation", interMethods));
    }

    m_grid->Append( new wxStringProperty("Image", "BoneImage", "") );
    {
        m_grid->AppendIn("BoneImage", new wxBoolProperty(_(L"Frame clée"), "BoneImageKeyFrame", false));
    }

    m_grid->Append( new wxIntProperty("Plan", "BoneZOrder", 0) );
    {
        m_grid->AppendIn("BoneZOrder", new wxBoolProperty(_(L"Frame clée"), "BoneZOrderKeyFrame", false));
        m_grid->AppendIn("BoneZOrder", new wxEnumProperty(_(L"Type d'interpolation"), "BoneZOrderInterpolation", interMethods));
    }

    Connect(GRIDID, wxEVT_PG_CHANGING, (wxObjectEventFunction)&SkeletonObjectEditor::OnGridPropertyChanging);
    Connect(GRIDID, wxEVT_PG_CHANGED, (wxObjectEventFunction)&SkeletonObjectEditor::OnGridPropertyChanged);
}

void SkeletonObjectEditor::OnValidateButtonClick(wxCommandEvent& event)
{
    //skeleton.GetAnimator().SetCurrentAnimation("Initial");
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
    dc.SetBrush(gd::CommonBitmapManager::GetInstance()->transparentBg);
    dc.DrawRectangle(0,0, panelSize.GetWidth(), panelSize.GetHeight());

    skeleton.DrawWx(dc, offset);
}

void SkeletonObjectEditor::OnPanel1LeftDown(wxMouseEvent& event)
{
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

    Panel1->Refresh(); //Refresh
    Panel1->Update(); //Immediately

    Panel2->Refresh();
    Panel2->Update();

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
    Sk::Bone *newBone = skeleton.CreateBone("new bone");
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
        nameTextCtrl->SetValue(wxString(selectedBone->GetName()));
        angleTextCtrl->SetValue(wxString(ToString(selectedBone->GetRotation())));
        lengthTextCtrl->SetValue(wxString(ToString(selectedBone->GetSize())));
        offsetXTextCtrl->SetValue(wxString(ToString(selectedBone->GetOffset().x)));
        offsetYTextCtrl->SetValue(wxString(ToString(selectedBone->GetOffset().y)));
        imageTextCtrl->SetValue(wxString(selectedBone->GetTextureName()));
        zOrderTextCtrl->SetValue(wxString(ToString(selectedBone->GetZOrder())));

        m_grid->SetPropertyValue(_(L"Identification.BoneName"), wxString(selectedBone->GetName()));

        m_grid->SetPropertyValue(_(L"Propriétés.BoneAngle"), selectedBone->GetRotation());
        m_grid->SetPropertyValue(_(L"Propriétés.BoneLength"), selectedBone->GetSize());
        m_grid->SetPropertyValue(_(L"Propriétés.BoneOffset.BoneOffsetX"), selectedBone->GetOffset().x);
        m_grid->SetPropertyValue(_(L"Propriétés.BoneOffset.BoneOffsetY"), selectedBone->GetOffset().y);
        m_grid->SetPropertyValue(_(L"Propriétés.BoneImage"), wxString(selectedBone->GetTextureName()));
        m_grid->SetPropertyValue(_(L"Propriétés.BoneZOrder"), selectedBone->GetZOrder());

        if(mode == 1 && timeline_currentAnim)
        {

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

        m_grid->SetPropertyValue(_(L"Identification.BoneName"), wxString(""));

        m_grid->SetPropertyValue(_(L"Propriétés.BoneAngle"), 0.f);
        m_grid->SetPropertyValue(_(L"Propriétés.BoneLength"), 0.f);
        m_grid->SetPropertyValue(_(L"Propriétés.BoneOffset.BoneOffsetX"), 0.f);
        m_grid->SetPropertyValue(_(L"Propriétés.BoneOffset.BoneOffsetY"), 0.f);
        m_grid->SetPropertyValue(_(L"Propriétés.BoneImage"), wxString(""));
        m_grid->SetPropertyValue(_(L"Propriétés.BoneZOrder"), 0);
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

void SkeletonObjectEditor::OnnameTextCtrlText(wxCommandEvent& event)
{
    if(mode == 0)
    {
        if(selectedBone)
        {
            std::string oldname = selectedBone->GetName();

            if(skeleton.BoneNameAlreadyUsed(ToString(nameTextCtrl->GetValue())) && ToString(nameTextCtrl->GetValue()) != oldname)
            {
                wxMessageBox("Un os ayant ce nom existe déjà.\nModifiez le nom et cliquez sur Appliquer.", "Nom de l'os");
                return;
            }

            selectedBone->SetName(ToString(nameTextCtrl->GetValue()));
            skeleton.GetAnimator().NotifyBoneRenamed(oldname, selectedBone->GetName());

            selectedBone->SetRotation(ToFloat(ToString(angleTextCtrl->GetValue())));
            selectedBone->SetSize(ToFloat(ToString(lengthTextCtrl->GetValue())));
            selectedBone->SetTextureName(ToString(imageTextCtrl->GetValue()));
            selectedBone->SetOffset(ToFloat(ToString(offsetXTextCtrl->GetValue())),
                                    ToFloat(ToString(offsetYTextCtrl->GetValue())));
            selectedBone->SetZOrder(ToFloat(ToString(zOrderTextCtrl->GetValue())));

            selectedBone->Update();

            skeleton.GetAnimator().GetAnimation("Initial").SetPeriod(0);
            skeleton.GetAnimator().GetAnimation("Initial").SetKeyFrame(selectedBone->GetName(), Sk::AngleKeyFrame, 0, ToFloat(ToString(angleTextCtrl->GetValue())));
            skeleton.GetAnimator().GetAnimation("Initial").SetKeyFrame(selectedBone->GetName(), Sk::LengthKeyFrame, 0, ToFloat(ToString(lengthTextCtrl->GetValue())));
        }
    }
    else
    {
        if(selectedBone)
        {
            selectedBone->SetRotation(ToFloat(ToString(angleTextCtrl->GetValue())));
            selectedBone->SetSize(ToFloat(ToString(lengthTextCtrl->GetValue())));
            selectedBone->SetColor(wxColour(255, 0, 0));
            selectedBone->Update();
        }
    }

    Panel1->Refresh(); //Refresh
    Panel1->Update();
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

        nameTextCtrl->Enable(true);
        offsetXTextCtrl->Enable(true);
        offsetYTextCtrl->Enable(true);
        imageTextCtrl->Enable(true);
        BitmapButton1->Enable(true);
        zOrderTextCtrl->Enable(true);
        addChildBoneBt->Enable(true);
        deleteBoneBt->Enable(true);

        angleApplyToAllBt->Enable(true);
        lengthApplyToAllBt->Enable(true);

        BitmapButton2->Enable(false);
        BitmapButton3->Enable(false);
        AnimationCombobox->Enable(false);

        angleCreateKeyFrameBt->Enable(false);
        angleDeleteKeyFrameBt->Enable(false);
        lengthCreateKeyFrameBt->Enable(false);
        lengthDeleteKeyFrameBt->Enable(false);

        m_grid->GetProperty(_(L"Identification.BoneName"))->Enable(true);

        m_grid->GetProperty(_(L"Propriétés.BoneAngle.BoneAngleKeyFrame"))->Enable(false);
        m_grid->GetProperty(_(L"Propriétés.BoneAngle.BoneAngleInterpolation"))->Enable(false);

        m_grid->GetProperty(_(L"Propriétés.BoneLength.BoneLengthKeyFrame"))->Enable(false);
        m_grid->GetProperty(_(L"Propriétés.BoneLength.BoneLengthInterpolation"))->Enable(false);

        m_grid->GetProperty(_(L"Propriétés.BoneOffset.BoneOffsetKeyFrame"))->Enable(false);
        m_grid->GetProperty(_(L"Propriétés.BoneOffset.BoneOffsetInterpolation"))->Enable(false);

        m_grid->GetProperty(_(L"Propriétés.BoneImage.BoneImageKeyFrame"))->Enable(false);

        m_grid->GetProperty(_(L"Propriétés.BoneZOrder.BoneZOrderKeyFrame"))->Enable(false);
        m_grid->GetProperty(_(L"Propriétés.BoneZOrder.BoneZOrderInterpolation"))->Enable(false);
    }
    else
    {
        skeleton.GetAnimator().GetAnimation("Initial").SetPeriod(0);
        for(std::vector<Sk::Bone*>::const_iterator it = skeleton.GetListOfBones().begin(); it != skeleton.GetListOfBones().end(); it++)
        {
            skeleton.GetAnimator().GetAnimation("Initial").SetKeyFrame((*it)->GetName(), Sk::AngleKeyFrame, 0, (*it)->GetRotation());
            skeleton.GetAnimator().GetAnimation("Initial").SetKeyFrame((*it)->GetName(), Sk::LengthKeyFrame, 0, (*it)->GetSize());
        }
        skeleton.GetAnimator().Seek(0);

        ToggleButton1->SetValue(false);
        ToggleButton2->SetValue(true);

        nameTextCtrl->Enable(false);
        offsetXTextCtrl->Enable(false);
        offsetYTextCtrl->Enable(false);
        imageTextCtrl->Enable(false);
        BitmapButton1->Enable(false);
        zOrderTextCtrl->Enable(false);
        addChildBoneBt->Enable(false);
        deleteBoneBt->Enable(false);

        angleApplyToAllBt->Enable(false);
        lengthApplyToAllBt->Enable(false);

        BitmapButton2->Enable(true);
        BitmapButton3->Enable(true);
        AnimationCombobox->Enable(true);

        angleCreateKeyFrameBt->Enable(true);
        angleDeleteKeyFrameBt->Enable(true);
        lengthCreateKeyFrameBt->Enable(true);
        lengthDeleteKeyFrameBt->Enable(true);

        m_grid->GetProperty(_(L"Identification.BoneName"))->Enable(false);

        m_grid->GetProperty(_(L"Propriétés.BoneAngle.BoneAngleKeyFrame"))->Enable(true);
        m_grid->GetProperty(_(L"Propriétés.BoneAngle.BoneAngleInterpolation"))->Enable(true);

        m_grid->GetProperty(_(L"Propriétés.BoneLength.BoneLengthKeyFrame"))->Enable(true);
        m_grid->GetProperty(_(L"Propriétés.BoneLength.BoneLengthInterpolation"))->Enable(true);

        m_grid->GetProperty(_(L"Propriétés.BoneOffset.BoneOffsetKeyFrame"))->Enable(true);
        m_grid->GetProperty(_(L"Propriétés.BoneOffset.BoneOffsetInterpolation"))->Enable(true);

        m_grid->GetProperty(_(L"Propriétés.BoneImage.BoneImageKeyFrame"))->Enable(true);

        m_grid->GetProperty(_(L"Propriétés.BoneZOrder.BoneZOrderKeyFrame"))->Enable(true);
        m_grid->GetProperty(_(L"Propriétés.BoneZOrder.BoneZOrderInterpolation"))->Enable(true);

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

    if(timeline_currentAnim)
    {
        dc.SetPen(wxPen(wxColour(255, 255, 0)));
        dc.DrawLine(GetPositionFromTimeToPixel(timeline_currentAnim->GetPeriod()), 17, GetPositionFromTimeToPixel(timeline_currentAnim->GetPeriod()), panelSize.GetHeight());
    }

    //Each 5s and 10s lines
    for(int a = floor(timeline_offset / 10) - 1; a < floor(timeline_offset / 5) + floor(panelSize.GetWidth() / (timeline_scale * 10)) + 2;a++)
    {
        dc.DrawRotatedText(ToString(a * 10), (a * timeline_scale * 10) - (timeline_offset * timeline_scale) - 7, 2, 0);

        dc.SetPen(wxColour(170, 170, 170));

        dc.DrawLine((a * timeline_scale * 10 - 5 * timeline_scale) - (timeline_offset * timeline_scale), 17,
                    (a * timeline_scale * 10 - 5 * timeline_scale) - (timeline_offset * timeline_scale), panelSize.GetHeight() - 1);

        dc.SetPen(wxColour(130, 130, 130));

        dc.DrawLine((a * timeline_scale * 10) - (timeline_offset * timeline_scale), 17,
                    (a * timeline_scale * 10) - (timeline_offset * timeline_scale), panelSize.GetHeight() - 1);
    }

    if(timeline_currentAnim)
    {
        //Draw angle keyframes
        {
        std::vector<float> keyFrames = timeline_currentAnim->GetListOfKeyFramesTime("", Sk::AngleKeyFrame);
        for(unsigned int a = 0; a < keyFrames.size(); a++)
        {
            if(!selectedBone || !timeline_currentAnim->HasKeyFrame(selectedBone->GetName(), Sk::AngleKeyFrame, keyFrames.at(a)))
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
        std::vector<float> keyFrames = timeline_currentAnim->GetListOfKeyFramesTime("", Sk::LengthKeyFrame);
        for(unsigned int a = 0; a < keyFrames.size(); a++)
        {
            if(!selectedBone || !timeline_currentAnim->HasKeyFrame(selectedBone->GetName(), Sk::LengthKeyFrame, keyFrames.at(a)))
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

void SkeletonObjectEditor::UpdateAnimationsList()
{
    wxString selected = AnimationCombobox->GetString(AnimationCombobox->GetSelection());
    AnimationCombobox->Clear();

    std::vector<std::string> animations = skeleton.GetAnimator().GetListOfAnimations();

    for(unsigned int a = 0; a < animations.size(); a++)
    {
        if(animations.at(a) != "Initial")
            AnimationCombobox->AppendString(animations.at(a).c_str());
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

        periodTextCtrl->SetValue("0");

        Panel2->Refresh(); //Refresh
        Panel2->Update();

        return;
    }

    timeline_currentAnim = &(skeleton.GetAnimator().GetAnimation(name));
    skeleton.GetAnimator().SetCurrentAnimation(name);
    timeline_offset = 0;
    timeline_current = 0;

    periodTextCtrl->SetValue(ToString(timeline_currentAnim->GetPeriod()).c_str());

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
        if(skeleton.GetAnimator().GetAnimation(skeleton.GetAnimator().GetCurrentAnimation()).HasKeyFrame(skeleton.GetListOfBones().at(a)->GetName(), Sk::AngleKeyFrame, timeline_current) ||
           skeleton.GetAnimator().GetAnimation(skeleton.GetAnimator().GetCurrentAnimation()).HasKeyFrame(skeleton.GetListOfBones().at(a)->GetName(), Sk::LengthKeyFrame, timeline_current))
        {
            skeleton.GetListOfBones().at(a)->SetColor(wxColour(0, 255, 0));
        }
    }

    Panel2->Refresh(); //Refresh
    Panel2->Update();

    Panel1->Refresh(); //Refresh
    Panel1->Update();
}

int SkeletonObjectEditor::GetPositionFromTimeToPixel(float time)
{
    return (time * timeline_scale) - (timeline_offset * timeline_scale);
}

float SkeletonObjectEditor::GetPositionFromPixelToTime(int pixel)
{
    return (pixel) / timeline_scale + timeline_offset;
}

void SkeletonObjectEditor::OnAnimationComboboxSelect(wxCommandEvent& event)
{
    SelectAnimation(ToString(AnimationCombobox->GetString(AnimationCombobox->GetSelection())));
}

void SkeletonObjectEditor::OnTextCtrl1TextEnter(wxCommandEvent& event)
{
    if(!timeline_currentAnim)
        return;

    timeline_currentAnim->SetPeriod(ToFloat(ToString(periodTextCtrl->GetValue())));

    Panel2->Refresh(); //Refresh
    Panel2->Update();
}

void SkeletonObjectEditor::OnBitmapButton2Click(wxCommandEvent& event)
{
    //Add an animation
    wxTextEntryDialog dialog(this, _("Nom de l'animation"), _("Nouvelle animation"), "New Animation");
    dialog.ShowModal();

    skeleton.GetAnimator().CreateAnimation(std::string(dialog.GetValue().c_str()), "Initial");
    SelectAnimation(std::string(dialog.GetValue().c_str()));

    UpdateAnimationsList();
}

void SkeletonObjectEditor::UncolorizeBoneIfNecessary(Sk::Bone &bone)
{
    if(bone.GetRotation() != ToFloat(ToString(angleTextCtrl->GetValue())))
        return;
    if(bone.GetSize() != ToFloat(ToString(lengthTextCtrl->GetValue())))
        return;

    selectedBone->SetColor(wxColour(0, 255, 0));
}

void SkeletonObjectEditor::OncreateKeyFrameBtClick(wxCommandEvent& event)
{
    if(mode != 1)
        return;

    if(!timeline_currentAnim || !selectedBone)
        return;

    timeline_currentAnim->SetKeyFrame(selectedBone->GetName(), Sk::AngleKeyFrame, timeline_current, selectedBone->GetRotation());
    UncolorizeBoneIfNecessary(*selectedBone);

    Seek(timeline_current);

    Panel2->Refresh(); //Refresh
    Panel2->Update();
}

void SkeletonObjectEditor::OnremoveKeyFrameBtClick(wxCommandEvent& event)
{
    if(mode != 1)
        return;

    if(!timeline_currentAnim || !selectedBone)
        return;

    timeline_currentAnim->RemoveKeyFrame(selectedBone->GetName(), Sk::AngleKeyFrame, timeline_current);

    Seek(timeline_current);

    Panel2->Refresh(); //Refresh
    Panel2->Update();
}

void SkeletonObjectEditor::OnlengthCreateKeyFrameBtClick(wxCommandEvent& event)
{
    if(mode != 1)
        return;

    if(!timeline_currentAnim || !selectedBone)
        return;

    timeline_currentAnim->SetKeyFrame(selectedBone->GetName(), Sk::LengthKeyFrame, timeline_current, selectedBone->GetSize());
    UncolorizeBoneIfNecessary(*selectedBone);

    Seek(timeline_current);

    Panel2->Refresh(); //Refresh
    Panel2->Update();
}

void SkeletonObjectEditor::OnlengthDeleteKeyFrameBtClick(wxCommandEvent& event)
{
    if(mode != 1)
        return;

    if(!timeline_currentAnim || !selectedBone)
        return;

    timeline_currentAnim->RemoveKeyFrame(selectedBone->GetName(), Sk::LengthKeyFrame, timeline_current);

    Seek(timeline_current);

    Panel2->Refresh(); //Refresh
    Panel2->Update();
}

void SkeletonObjectEditor::OnangleApplyToAllBtClick(wxCommandEvent& event)
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

void SkeletonObjectEditor::OnangleInterpolationBtClick(wxCommandEvent& event)
{
    if(mode != 1)
        return;

    if(!selectedBone && !timeline_currentAnim)
        return;

    if(!timeline_currentAnim->HasKeyFrame(selectedBone->GetName(), Sk::AngleKeyFrame, timeline_current))
        return;

    std::string inter = ChooseInterpolationMethod(timeline_currentAnim->GetKeyFrameInterpolation(selectedBone->GetName(), Sk::AngleKeyFrame, timeline_current));

    timeline_currentAnim->SetKeyFrameInterpolation(selectedBone->GetName(), Sk::AngleKeyFrame, timeline_current, inter);
}

void SkeletonObjectEditor::OnlengthInterpolationBtClick(wxCommandEvent& event)
{
    if(mode != 1)
        return;

    if(!selectedBone && !timeline_currentAnim)
        return;

    if(!timeline_currentAnim->HasKeyFrame(selectedBone->GetName(), Sk::LengthKeyFrame, timeline_current))
        return;

    std::string inter = ChooseInterpolationMethod(timeline_currentAnim->GetKeyFrameInterpolation(selectedBone->GetName(), Sk::LengthKeyFrame, timeline_current));

    timeline_currentAnim->SetKeyFrameInterpolation(selectedBone->GetName(), Sk::LengthKeyFrame, timeline_current, inter);
}

void SkeletonObjectEditor::OnGridPropertyChanging(wxPropertyGridEvent& event)
{
    if(mode == 0 && selectedBone)
    {
        if(event.GetProperty()->GetBaseName() == _(L"BoneName"))
        {
            if(skeleton.BoneNameAlreadyUsed(ToString(event.GetPropertyValue().GetString())) && ToString(event.GetPropertyValue().GetString()) != selectedBone->GetName())
            {
                wxMessageBox("Un os ayant ce nom existe déjà.\nModifiez le nom et cliquez sur Appliquer.", "Nom de l'os");
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
        if(event.GetProperty()->GetBaseName() == _(L"BoneName"))
        {
            std::string oldName = selectedBone->GetName();
            selectedBone->SetName(ToString(event.GetPropertyValue().GetString()));
            skeleton.GetAnimator().NotifyBoneRenamed(oldName, selectedBone->GetName());
        }
    }
    else if(mode == 1 && selectedBone && timeline_currentAnim)
    {

    }

    Panel1->Refresh();
    Panel1->Update();
}

std::string SkeletonObjectEditor::ChooseInterpolationMethod(const std::string &inter)
{
    std::vector<std::string> listOfMethods = Sk::Interpolation::Get::Methods();
    wxString methods[listOfMethods.size()];
    for(unsigned int a = 0; a < listOfMethods.size(); a++)
    {
        methods[a] = wxString(listOfMethods.at(a).c_str());
    }

    wxSingleChoiceDialog dialog(this,
                                "Choisissez la methode d'interpolation qui sera utilisee\nentre la frame clee selectionnee et la frame clee suivante",
                                "Methode d'interpolation",
                                listOfMethods.size(),
                                methods);
    dialog.SetSelection(std::distance(listOfMethods.begin(), std::find(listOfMethods.begin(), listOfMethods.end(), inter)));

    dialog.ShowModal();

    return std::string(ToString(dialog.GetStringSelection()));
}

#endif
