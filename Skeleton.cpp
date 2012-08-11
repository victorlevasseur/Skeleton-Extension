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

#ifdef GD_IDE_ONLY
#include <wx/dcbuffer.h>
#endif

#include "Skeleton.h"

#include "GDL/tinyxml/tinyxml.h"

namespace Sk
{

Skeleton::Skeleton() : m_root(new Bone("root", this))
{
    RegisterBone(m_root);
}

Skeleton::Skeleton(const Skeleton &other)
{
    m_bones.clear();

    m_root = new Bone(*other.m_root);
    m_root->ResetOwner(this);

    m_skeAnim = other.m_skeAnim;

    //m_root->Update();
}

Skeleton::~Skeleton()
{
    //dtor
}

void Skeleton::Draw(sf::RenderTarget &target, sf::Vector2f offset, Bone::DrawType type)
{
    for(unsigned int a = 0; a < m_bones.size(); a++)
    {
        m_bones.at(a)->Draw(target, offset, type);
    }
}

#ifdef GD_IDE_ONLY

void Skeleton::DrawWx(wxBufferedPaintDC &dc, sf::Vector2f offset)
{
    for(unsigned int a = 0; a < m_bones.size(); a++)
    {
        m_bones.at(a)->DrawWx(dc, offset);
    }
}

#endif

Bone* Skeleton::CreateBone(const std::string &name)
{
    Bone *newbone = new Bone(name, this);
    RegisterBone(newbone);

    return newbone;
}

void Skeleton::DestroyBone(Bone *bone)
{
    for(unsigned int a = 0; a < bone->GetChildrenBones().size(); a++)
    {
        DestroyBone(bone->GetChildrenBones().at(a));
    }
    UnRegisterBone(bone);
    delete bone;
}

void Skeleton::RegisterBone(Bone *bone)
{
    m_bones.push_back(bone);

    ReorderByZOrder();
}

void Skeleton::UnRegisterBone(Bone *bone)
{
    std::vector<Bone*>::iterator it = std::find(m_bones.begin(), m_bones.end(), bone);

    if(it == m_bones.end())
        return;

    m_bones.erase(it);
}

Bone* Skeleton::GetRoot()
{
    return m_root;
}

bool Skeleton::BoneNameAlreadyUsed(const std::string &name)
{
    for(std::vector<Bone*>::iterator it = m_bones.begin(); it != m_bones.end(); it++)
    {
        if((*it)->GetName() == name)
            return true;
    }

    return false;
}

void Skeleton::ReorderByZOrder()
{
    ZOrderFunctor functor;
    std::sort(m_bones.begin(), m_bones.end(), functor);
}

void Skeleton::ApplyAnimationToBones()
{
    m_skeAnim.ApplyToSkeleton(m_bones);
    m_root->Update();
}

void Skeleton::Save(TiXmlElement &elem)
{
    GetRoot()->SaveBone(elem);

    TiXmlElement *animationsElem = new TiXmlElement("Animations");
    elem.LinkEndChild(animationsElem);
    GetAnimator().SaveToXml(animationsElem);
}

void Skeleton::Load(const TiXmlElement &elem)
{
    TiXmlElement *boneElem = const_cast<TiXmlElement*>(elem.FirstChildElement("Bone"));
    if(boneElem)
    {
        GetRoot()->LoadBone(*boneElem);
    }

    TiXmlElement *animationsElem = const_cast<TiXmlElement*>(elem.FirstChildElement("Animations"));
    if(animationsElem)
    {
        GetAnimator().LoadFromXml(animationsElem);
    }
}

}
