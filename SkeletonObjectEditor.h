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

//(*Headers(SkeletonObjectEditor)
#include <wx/treectrl.h>
#include <wx/sizer.h>
#include <wx/tglbtn.h>
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)
#include <wx/aui/aui.h>
#include <wx/propgrid/propgrid.h>
#include <wx/imaglist.h>

#include "GDCore/IDE/Dialogs/MainFrameWrapper.h"

#include "Bone.h"
#include "Skeleton.h"

class Game;
class SkeletonObject;
class ResourcesEditor;
class MainEditorCommand;

class SkeletonObjectEditor: public wxDialog
{
	public:

        enum DragType
        {
            NotDragging,
            DraggingAngle
        };

		SkeletonObjectEditor( wxWindow* parent, Game & game_, SkeletonObject & object_, gd::MainFrameWrapper & mainEditorCommand_ );
		virtual ~SkeletonObjectEditor();

		//(*Declarations(SkeletonObjectEditor)
		wxPanel* Core;
		wxToggleButton* ToggleButton2;
		wxPanel* Timeline;
		wxButton* ValidateButton;
		wxButton* Button4;
		wxFlexGridSizer* propertyGridSizer;
		wxPanel* propertyGridPanel;
		wxButton* Button1;
		wxToggleButton* ToggleButton1;
		wxBitmapButton* BitmapButton2;
		wxPanel* Panel1;
		wxFlexGridSizer* FlexGridSizer2;
		wxBitmapButton* BitmapButton1;
		wxButton* Button2;
		wxButton* Button6;
		wxButton* Button5;
		wxButton* Button3;
		wxPanel* Bottom;
		wxTreeCtrl* TreeCtrl1;
		wxChoice* AnimationCombobox;
		wxBitmapButton* BitmapButton4;
		wxBitmapButton* BitmapButton3;
		wxBitmapButton* createTemplateBt;
		wxPanel* Panel2;
		wxPanel* KeyFrameTree;
		wxButton* addChildBoneBt;
		wxButton* deleteBoneBt;
		wxPanel* BoneProperties;
		wxBitmapButton* templateBt;
		//*)

	protected:

		//(*Identifiers(SkeletonObjectEditor)
		static const long ID_TOGGLEBUTTON1;
		static const long ID_TOGGLEBUTTON2;
		static const long ID_PANEL1;
		static const long ID_PANEL2;
		static const long ID_BUTTON6;
		static const long ID_BUTTON5;
		static const long ID_BUTTON1;
		static const long ID_BUTTON3;
		static const long ID_PANEL6;
		static const long ID_PANEL4;
		static const long ID_BUTTON2;
		static const long ID_BUTTON4;
		static const long ID_PANEL7;
		static const long ID_CHOICE1;
		static const long ID_BITMAPBUTTON2;
		static const long ID_BITMAPBUTTON4;
		static const long ID_BITMAPBUTTON6;
		static const long ID_BITMAPBUTTON1;
		static const long ID_BITMAPBUTTON3;
		static const long ID_BITMAPBUTTON5;
		static const long ID_PANEL3;
		static const long ID_BUTTON9;
		static const long ID_BUTTON10;
		static const long ID_BUTTON7;
		static const long ID_PANEL8;
		static const long ID_TREECTRL1;
		static const long ID_PANEL5;
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
		void OnPanel2Paint(wxPaintEvent& event);
		void OnPanel2EraseBackground(wxEraseEvent& event);
		void OnBitmapButton2Click(wxCommandEvent& event);
		void OnAnimationComboboxSelect(wxCommandEvent& event);
		void OnPanel2LeftDown(wxMouseEvent& event);
		void OnPanel2MouseWheel(wxMouseEvent& event);
		void OnButton4Click(wxCommandEvent& event);
		void OnButton5Click(wxCommandEvent& event);
		void OnPanel2RightDown(wxMouseEvent& event);
		void OnPanel2RightUp(wxMouseEvent& event);
		void OnangleApplyToAllBtClick(wxCommandEvent& event);
		void OnlengthApplyToAllBtClick(wxCommandEvent& event);
		void OnPanel3Resize(wxSizeEvent& event);
		void OnPanel2Resize(wxSizeEvent& event);
		void OnPanel1Resize(wxSizeEvent& event);
		void OnBitmapButton3Click(wxCommandEvent& event);
		void OnInit(wxInitDialogEvent& event);
		void OnBitmapButton1Click(wxCommandEvent& event);
		void OnBitmapButton4Click(wxCommandEvent& event);
		void OnButton1Click1(wxCommandEvent& event);
		void OnButton6Click(wxCommandEvent& event);
		void OnPanel1LeftUp(wxMouseEvent& event);
		void OncreateTemplateBtClick(wxCommandEvent& event);
		void OntemplateBtClick(wxCommandEvent& event);
		void OnTreeCtrl1ItemRightClick(wxTreeEvent& event);
		void OnTreeCtrl1SelectionChanged(wxTreeEvent& event);
		//*)
		void OnGridPropertyChanging(wxPropertyGridEvent& event);
		void OnGridPropertyChanged(wxPropertyGridEvent& event);

		void PreparePropertyGrid();

		Sk::Bone *FindBoneOnPosition(sf::Vector2f position, Sk::Bone *base);
		void UpdateForSelectedBone();
		void ToggleMode(char _mode); //0 => Edition, 1 => Animation

		void SelectBone(Sk::Bone *bone);
		void SelectBoneInTree(Sk::Bone *bone, wxTreeItemId parent = wxTreeItemId());

		void UpdateAnimationsList();
		void SelectAnimation(const std::string &name);
		void Seek(float time);

        void UncolorizeBoneIfNecessary(Sk::Bone &bone);

		int GetPositionFromTimeToPixel(float time) const;
		float GetPositionFromPixelToTime(int pixel) const;

		float GetGraduationScale(float width, float scale) const;

		void UpdateKeyFrameTree();
		void UpdateTreeItem(wxTreeItemId id);

        wxTreeItemId FindTreeItem(float time, wxTreeItemId parent = wxTreeItemId());
        wxTreeItemId FindTreeItem(float time, wxString boneName, wxTreeItemId parent = wxTreeItemId());
		wxTreeItemId FindTreeItem(float time, wxString boneName, Sk::Anim::KeyFrameType keyType, wxTreeItemId parent = wxTreeItemId());

		void InitTreeMenu();

		Game & game;
		gd::MainFrameWrapper & mainEditorCommand;
		SkeletonObject & object;
		wxAuiManager m_mgr;
		wxPropertyGrid *m_grid;
		wxImageList *m_imageList;

		Sk::Skeleton skeleton;
		Sk::Bone *selectedBone;
		Sk::Anim::Animation* timeline_currentAnim;

		sf::Vector2f offset;
		bool isDragging;

		sf::Vector2f lastPos;
		char mode;

        float timeline_current;
		float timeline_scale; //Size of one second
		float timeline_offset; //Offset as time
		int timeline_tmp_dragbegan;

		DragType isDraggingHandle;
		sf::Vector2f draggingStartPosition;

		wxMenu *treeKeyMenu;
            wxMenuItem *treeKeyResetItem;
            long treeKeyResetItem_ID;
            wxMenuItem *treeKeyInterpItem;
            long treeKeyInterpItem_ID;
            wxMenuItem *treeKeyDeleteItem;
            long treeKeyDeleteItem_ID;

		DECLARE_EVENT_TABLE()
};

#endif
#endif
