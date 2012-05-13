#ifndef SKELETON_H
#define SKELETON_H

#include <string>
#include <vector>

#include "Bone.h"

#ifdef GD_IDE_ONLY
#include <wx/dcbuffer.h>
#endif

class Bone;

class Skeleton
{
    friend class Bone;

    public:
        Skeleton();
        Skeleton(const Skeleton &other);
        ~Skeleton();

        void Draw(sf::RenderTarget &target, sf::Vector2f offset, Bone::DrawType);
        #ifdef GD_IDE_ONLY
        void DrawWx(wxBufferedPaintDC &dc, sf::Vector2f offset);
        #endif

        Bone* CreateBone(const std::string &name);
        void DestroyBone(Bone *bone);

        void RegisterBone(Bone *bone);
        void UnRegisterBone(Bone *bone);

        void ReorderByZOrder();

        Bone* GetRoot();

    protected:
    private:
        Bone *m_root;
        std::vector<Bone*> m_bones;
};

struct ZOrderFunctor
{
    friend class Bone;

    bool operator() (Bone *left, Bone *right) {return (left->m_zorder < right->m_zorder);};
};

#endif // SKELETON_H
