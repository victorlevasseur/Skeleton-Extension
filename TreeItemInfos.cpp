#include "TreeItemInfos.h"

TreeItemInfo::TreeItemInfo() : wxTreeItemData(), time(0), editable(true), hasInterpolation(true)
{

}

TreeItemInfo::~TreeItemInfo()
{

}

TreeItemInfo* TreeItemInfo::Get()
{
    return new TreeItemInfo();
}

TreeItemInfo* TreeItemInfo::SetItemType(ItemType _type)
{
    type = _type;
    return this;
}

TreeItemInfo* TreeItemInfo::SetItemBone(wxString _name)
{
    boneName = _name;
    return this;
}

TreeItemInfo* TreeItemInfo::SetItemTime(float _time)
{
    time = _time;
    return this;
}

TreeItemInfo* TreeItemInfo::SetItemKeyType(Sk::Anim::KeyFrameType _keyType)
{
    keyType = _keyType;
    return this;
}

TreeItemInfo* TreeItemInfo::NotEditable()
{
    editable = false;
    return this;
}

TreeItemInfo* TreeItemInfo::NotInterpolationCapable()
{
    hasInterpolation = false;
    return this;
}
