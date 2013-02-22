#ifndef TREEITEMINFOS_H
#define TREEITEMINFOS_H

#ifdef GD_IDE_ONLY

#include <wx/treebase.h>
#include "GlobalDefs.h"

class TreeItemInfo : public wxTreeItemData
{
public:

    enum ItemType
    {
        Time,
        Bone,
        Key
    };

    virtual ~TreeItemInfo();
    static TreeItemInfo* Get();

    TreeItemInfo* SetItemType(ItemType _type);
    TreeItemInfo* SetItemBone(wxString _name);
    TreeItemInfo* SetItemTime(float _time);
    TreeItemInfo* SetItemKeyType(Sk::Anim::KeyFrameType _keyType);

    TreeItemInfo* NotEditable();
    TreeItemInfo* NotInterpolationCapable();

    ItemType type;

    wxString boneName;
    float time;
    Sk::Anim::KeyFrameType keyType;

    bool editable;
    bool hasInterpolation;

protected:
    TreeItemInfo();
};

#endif

#endif // TREEITEMINFOS_H
