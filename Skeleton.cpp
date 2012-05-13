#include "Skeleton.h"

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
