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

#ifndef BONE_H
#define BONE_H

#if defined(GD_IDE_ONLY)
#include <wx/colour.h>
#endif

#include <cmath>
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "GDL/ImageManager.h"
#include "GDL/Polygon.h"
#include "GDL/tinyxml/tinyxml.h"

class ImageManager;
class Polygon2d;
class wxBufferedPaintDC;

namespace Sk
{

namespace Anim{class Animation;}
namespace Res{class SkImageManager;}

class Skeleton;

class Bone
{
    friend struct ZOrderFunctor;
    friend class Skeleton;
    friend class Sk::Anim::Animation;

    public:

        enum DrawType
        {
            Lines,
            Sprites
        };

        ~Bone();

        void Draw(sf::RenderTarget &target, sf::Vector2f offset, DrawType);
        #ifdef GD_IDE_ONLY
        void DrawWx(wxBufferedPaintDC &dc, sf::Vector2f offset, bool selected);

        void SetColor(wxColour color);
        void UnColorize();

        void ShowMathsFrame(bool show = true);
        #endif

        ///Save the bone as a subnode of "saveIn"
        void SaveBone(TiXmlElement &saveIn);
        /// "boneElement" is the node representing the bone.
        void LoadBone(TiXmlElement &boneElement);

        bool IsPointOnBone(sf::Vector2f position);

        void Update();
        void UpdateHitBox();

        sf::Vector2f GetBonePosition() const {return m_tmp_position;};
        sf::Vector2f GetEndNodeRelativePosition() const;

        void SetName(const std::string &string) {m_name = string;};
        std::string GetName() const {return m_name;};

        void SetLength(float size);
        float GetLength() const;

        void SetAngle(float rotation);
        float GetAngle() const;

        void SetOffset(float x, float y);
        sf::Vector2f GetOffset() const;

        void SetZOrder(int zorder);
        int GetZOrder() const;

        void EnableAngleInheritance(bool inherit) {m_inheritAngle = inherit; Update();};
        bool IsAngleInheritanceEnabled() const {return m_inheritAngle;};

        void SetHitBoxSize(float width, float height);
        const sf::Vector2f& GetHitBoxSize() const;

        inline bool IsHitBoxEnabled() const {return m_hasHitBox;};
        void EnableHitBox(bool enable) {m_hasHitBox = enable;};

        inline const Polygon2d& GetHitBox() const {return m_hitBox;};

        void AddBone(Bone *bone);
        bool RemoveBone(Bone *bone);

        void ResetOwner(Skeleton *ske);

        void SetTextureName(const std::string &textureName);
        std::string GetTextureName() const;
        void LoadTexture(Res::SkImageManager & imageMgr);

        std::vector<Bone*> const & GetChildrenBones() const;
        Bone* GetParentBone() const {return m_parentBone;};

    protected:
        Bone(std::string name, Skeleton *owner = 0);
        Bone(const Bone &other);
        Bone& operator=(const Bone &other);
        void Init(const Bone &other);

    private:
        Skeleton *m_owner;
        Bone *m_parentBone;
        std::vector<Bone*> m_childBones;

        std::string m_name;

        #ifdef GD_IDE_ONLY
        bool m_mathsFrame;
        wxColour m_color;
        #endif

        //Can be modified by keyframes
        float m_angle;
        float m_length;
        sf::Vector2f m_offset;
        int m_zorder;

        //Not editable with keyframe
        bool m_inheritAngle;

        bool m_hasHitBox;
        sf::Vector2f m_hitBoxSize;
        Polygon2d m_hitBox;

        //Pre-calculated members for absolute position and rotation (updated each time the bone is moved : its size, rotation changes, or its parent changes)
        sf::Vector2f m_tmp_position;
        float m_tmp_totalAngle;

        //Texture to be draw on the bone
        std::string m_textureName;
        boost::shared_ptr<SFMLTextureWrapper> m_texture;
};

}

#endif // BONE_H
