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

#include "Skeleton.h"

#ifdef GD_IDE_ONLY
#include <wx/dcbuffer.h>
#endif

Skeleton::Skeleton() : m_root(new Bone("root", this))
{
    RegisterBone(m_root);
}

Skeleton::Skeleton(const Skeleton &other)
{
    m_bones.clear();

    m_root = new Bone(*other.m_root);
    m_root->ResetOwner(this);

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

void Skeleton::ReorderByZOrder()
{
    ZOrderFunctor functor;
    std::sort(m_bones.begin(), m_bones.end(), functor);
}
