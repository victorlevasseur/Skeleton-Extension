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
#include "GDL/tinyxml/tinyxml.h"

class ImageManager;
class wxBufferedPaintDC;

namespace Sk
{

class Skeleton;

class Bone
{
    friend struct ZOrderFunctor;
    friend class Skeleton;
    friend class Animation;

    public:

        enum DrawType
        {
            Lines,
            Sprites
        };

        ~Bone();

        void Draw(sf::RenderTarget &target, sf::Vector2f offset, DrawType);
        #ifdef GD_IDE_ONLY
        void DrawWx(wxBufferedPaintDC &dc, sf::Vector2f offset);

        bool IsSelected() {return m_selected;};
        void Select(bool is) {m_selected = is;};
        void UnselectAllChilds();

        void SetColor(wxColour color);
        void UnColorize();
        #endif

        void SaveBone(TiXmlElement &saveIn); ///Save the bone as a subnode of "saveIn"
        void LoadBone(TiXmlElement &boneElement); /// "boneElement" is the node representing the bone.

        bool IsOnPosition(sf::Vector2f position);

        void Update();
        void UpdateTextureTransform();
        sf::Vector2f GetEndNodeRelativePosition() const;

        void SetName(const std::string &string) {m_name = string;};
        std::string GetName() const {return m_name;};
        void SetSize(float size);
        float GetSize() const;
        void SetRotation(float rotation);
        float GetRotation() const;
        void SetOffset(float x, float y);
        sf::Vector2f GetOffset() const;

        void AddBone(Bone *bone);
        bool RemoveBone(Bone *bone);

        void ResetOwner(Skeleton *ske);

        void SetZOrder(int zorder);
        int GetZOrder() const;

        void SetTextureName(const std::string &textureName);
        std::string GetTextureName() const;
        void LoadTexture(const ImageManager & imageMgr);

        std::vector<Bone*> const & GetChildrenBones() const;

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
        bool m_selected;
        wxColour m_color;
        #endif

        float m_size;
        float m_relativeRotation;
        sf::Vector2f m_offset;

        int m_zorder;

        //Pre-calculated members for absolute position and rotation (updated each time the bone is moved : its size, rotation changes, or its parent changes)
        sf::Vector2f m_tmp_position;
        float m_tmp_absoluteRotation;

        //Texture to be draw on the bone
        std::string m_textureName;
        boost::shared_ptr<SFMLTextureWrapper> m_texture;
};

}

#endif // BONE_H
