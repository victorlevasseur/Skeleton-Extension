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

#ifndef SkeletonObjectEDITOR_H
#define SkeletonObjectEDITOR_H

#include "Bone.h"
#include "Skeleton.h"

//(*Headers(SkeletonObjectEditor)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/tglbtn.h>
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)
#include <wx/aui/aui.h>

class Game;
class SkeletonObject;
class ResourcesEditor;
class MainEditorCommand;

class SkeletonObjectEditor: public wxDialog
{
	public:

		SkeletonObjectEditor( wxWindow* parent, Game & game_, SkeletonObject & object_, MainEditorCommand & mainEditorCommand_ );
		virtual ~SkeletonObjectEditor();

		//(*Declarations(SkeletonObjectEditor)
		wxPanel* Core;
		wxToggleButton* ToggleButton2;
		wxButton* ValidateButton;
		wxTextCtrl* offsetYTextCtrl;
		wxStaticText* StaticText2;
		wxButton* Button1;
		wxStaticText* StaticText6;
		wxStaticText* StaticText8;
		wxTextCtrl* lengthTextCtrl;
		wxToggleButton* ToggleButton1;
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		wxTextCtrl* offsetXTextCtrl;
		wxStaticText* StaticText3;
		wxBitmapButton* BitmapButton1;
		wxButton* Button2;
		wxTextCtrl* nameTextCtrl;
		wxTextCtrl* angleTextCtrl;
		wxTextCtrl* imageTextCtrl;
		wxButton* Button3;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxTextCtrl* zOrderTextCtrl;
		wxButton* addChildBoneBt;
		wxButton* deleteBoneBt;
		wxStaticText* StaticText4;
		//*)

	protected:

		//(*Identifiers(SkeletonObjectEditor)
		static const long ID_TOGGLEBUTTON1;
		static const long ID_TOGGLEBUTTON2;
		static const long ID_PANEL1;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_TEXTCTRL3;
		static const long ID_STATICTEXT6;
		static const long ID_TEXTCTRL5;
		static const long ID_STATICTEXT7;
		static const long ID_TEXTCTRL7;
		static const long ID_STATICTEXT5;
		static const long ID_TEXTCTRL4;
		static const long ID_BITMAPBUTTON1;
		static const long ID_STATICTEXT8;
		static const long ID_TEXTCTRL6;
		static const long ID_BUTTON5;
		static const long ID_BUTTON2;
		static const long ID_BUTTON4;
		static const long ID_BUTTON6;
		static const long ID_BUTTON1;
		static const long ID_BUTTON3;
		static const long ID_PANEL2;
		//*)
		ResourcesEditor * resourcesEditor;

	private:

		//(*Handlers(SkeletonObjectEditor)
		void OnValidateButtonClick(wxCommandEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnPanel1Paint(wxPaintEvent& event);
		void OnPanel1LeftDown(wxMouseEvent& event);
		void OnnameTextCtrlText(wxCommandEvent& event);
		void OnToggleButton1Toggle(wxCommandEvent& event);
		void OnToggleButton2Toggle(wxCommandEvent& event);
		void OnButton3Click(wxCommandEvent& event);
		void OnaddChildBoneBtClick(wxCommandEvent& event);
		void OndeleteBoneBtClick(wxCommandEvent& event);
		void OnPanel1RightDown(wxMouseEvent& event);
		void OnPanel1MouseMove(wxMouseEvent& event);
		void OnPanel1RightUp(wxMouseEvent& event);
		void OnPanel1EraseBackground(wxEraseEvent& event);
		//*)

		Game & game;
		MainEditorCommand & mainEditorCommand;
		SkeletonObject & object;
		wxAuiManager m_mgr;

		Skeleton skeleton;
		Bone *selectedBone;

		Bone *FindBoneOnPosition(sf::Vector2f position, Bone *base);
		void UpdateForSelectedBone();
		void ToggleMode(char _mode); //0 => Edition, 1 => Animation

		sf::Vector2f offset;
		bool isDragging;

		sf::Vector2f lastPos;
		char mode;

		DECLARE_EVENT_TABLE()
};

#endif
#endif
