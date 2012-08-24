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

#include "Bone.h"

#include <algorithm>
#include "GDL/ImageManager.h"
#include <SFML/Graphics.hpp>
#include "Skeleton.h"
#include "ImageManager.h"

namespace Sk
{

Bone::Bone(std::string name, Skeleton *owner) : m_owner(owner), m_parentBone(0), m_name(name)
#ifdef GD_IDE_ONLY
, m_selected(false)
, m_color(0, 0, 0)
#endif
, m_size(100)
, m_relativeRotation(0)
, m_offset(0, 0)
, m_zorder(0)
{
    m_texture = boost::shared_ptr<SFMLTextureWrapper>();
}

Bone::Bone(const Bone &other)
{
    Init(other);
}

Bone& Bone::operator=(const Bone &other)
{
    Init(other);

    return *this;
}

void Bone::Init(const Bone &other)
{
    m_owner = other.m_owner;
    m_parentBone = other.m_parentBone;
    m_size = other.m_size;
    m_relativeRotation = other.m_relativeRotation;
    m_offset = other.m_offset;
    m_textureName = other.m_textureName;
    m_texture = boost::shared_ptr<SFMLTextureWrapper>();
    m_name = other.m_name;
    m_zorder = other.m_zorder;
    #ifdef GD_IDE_ONLY
    m_selected = false;
    m_color = wxColour(0, 0, 0);
    #endif

    for(unsigned int a = 0; a < other.m_childBones.size(); a++)
    {
        Bone *newBone = new Bone(*other.m_childBones.at(a));
        m_childBones.push_back(newBone);
        newBone->m_parentBone = this;
    }

    Update();
}

Bone::~Bone()
{
    m_owner->UnRegisterBone(this);
}

void Bone::Draw(sf::RenderTarget &target, sf::Vector2f offset, Bone::DrawType type)
{
    if(type == Lines)
    {
        sf::Shape line = sf::Shape::Line(offset.x + m_tmp_position.x,
                                        offset.y + m_tmp_position.y,
                                        offset.x + m_tmp_position.x + GetEndNodeRelativePosition().x,
                                        offset.y + m_tmp_position.y + GetEndNodeRelativePosition().y,
                                        2,
                                        sf::Color(255, 0, 0));

        target.Draw(line);
    }
    else if(type == Sprites && m_texture != boost::shared_ptr<SFMLTextureWrapper>())
    {
        sf::Sprite sprite;

        sprite.SetOrigin(m_texture->texture.GetWidth() / 2, m_texture->texture.GetHeight() / 2);
        sprite.SetTexture(m_texture->texture);
        sprite.SetPosition(offset.x + m_tmp_position.x + (GetEndNodeRelativePosition().x / 2),
                           offset.y + m_tmp_position.y + (GetEndNodeRelativePosition().y / 2));
        sprite.SetRotation(m_tmp_absoluteRotation);

        target.Draw(sprite);
    }
}

#ifdef GD_IDE_ONLY
void Bone::DrawWx(wxBufferedPaintDC &dc, sf::Vector2f offset)
{
    dc.SetPen(wxPen(m_selected ? wxColour(0, 0, 255) : m_color));

    dc.DrawLine(floor(offset.x + m_tmp_position.x),
                floor(offset.y + m_tmp_position.y),
                floor(offset.x + m_tmp_position.x + GetEndNodeRelativePosition().x),
                floor(offset.y + m_tmp_position.y + GetEndNodeRelativePosition().y));

    dc.DrawCircle(floor(offset.x + m_tmp_position.x + GetEndNodeRelativePosition().x),
                  floor(offset.y + m_tmp_position.y + GetEndNodeRelativePosition().y),
                  4);

    dc.DrawRotatedText(m_name, offset.x + m_tmp_position.x + GetEndNodeRelativePosition().x / 2.5,
                               offset.y + m_tmp_position.y + GetEndNodeRelativePosition().y / 2.5,
                               360 - m_tmp_absoluteRotation);

}

void Bone::UnselectAllChilds()
{
    Select(false);
    for(std::vector<Bone*>::iterator it = m_childBones.begin(); it != m_childBones.end(); it++)
    {
        (*it)->UnselectAllChilds();
    }
}

void Bone::SetColor(wxColour color)
{
    m_color = color;
}

void Bone::UnColorize()
{
    m_color = wxColour(0, 0, 0);
}
#endif

void Bone::Update()
{
    if(m_parentBone)
    {
        m_tmp_position = m_parentBone->m_tmp_position + m_parentBone->GetEndNodeRelativePosition();
        m_tmp_absoluteRotation = (m_parentBone->m_tmp_absoluteRotation + m_relativeRotation);

        m_tmp_position += sf::Vector2f(cos((m_parentBone->m_tmp_absoluteRotation * M_PI) / 180.f) * m_offset.x,
                                       sin((m_parentBone->m_tmp_absoluteRotation * M_PI) / 180.f) * m_offset.x);

        m_tmp_position += sf::Vector2f(cos(((m_parentBone->m_tmp_absoluteRotation + 90) * M_PI) / 180.f) * m_offset.y,
                                       sin(((m_parentBone->m_tmp_absoluteRotation + 90) * M_PI) / 180.f) * m_offset.y);


        while(m_tmp_absoluteRotation >= 360) //Simplify the angle
            m_tmp_absoluteRotation -= 360;
        while(m_tmp_absoluteRotation < 0)
            m_tmp_absoluteRotation += 360;
    }
    else
    {
        m_tmp_position = sf::Vector2f(0, 0);
        m_tmp_absoluteRotation = m_relativeRotation;

        m_tmp_position += sf::Vector2f(m_offset.x, m_offset.y);
    }

    for(std::vector<Bone*>::iterator it = m_childBones.begin(); it != m_childBones.end(); it++)
    {
        (*it)->Update();
    }

    UpdateTextureTransform();
}

void Bone::UpdateTextureTransform()
{

}

void Bone::ResetOwner(Skeleton *ske)
{
    m_owner = ske;
    m_owner->RegisterBone(this);

    for(unsigned int a = 0; a < m_childBones.size(); a++)
    {
        m_childBones.at(a)->ResetOwner(ske);
    }

}

std::vector<Bone*> const & Bone::GetChildrenBones() const
{
    return m_childBones;
}

sf::Vector2f Bone::GetEndNodeRelativePosition() const
{
    return sf::Vector2f(cos((m_tmp_absoluteRotation * M_PI) / 180.f) * m_size,
                         sin((m_tmp_absoluteRotation * M_PI) / 180.f) * m_size);
}

void Bone::SetSize(float size)
{
    m_size = size;

    Update();
}

float Bone::GetSize() const
{
    return m_size;
}

void Bone::SetRotation(float rotation)
{
    m_relativeRotation = rotation;
}

float Bone::GetRotation() const
{
    return m_relativeRotation;
}

void Bone::SetOffset(float x, float y)
{
    m_offset.x = x;
    m_offset.y = y;

    Update();
}

sf::Vector2f Bone::GetOffset() const
{
    return m_offset;
}

void Bone::AddBone(Bone *bone)
{
    m_childBones.push_back(bone);
    bone->m_parentBone = this;
    bone->Update();
}

bool Bone::RemoveBone(Bone *bone)
{
    std::vector<Bone*>::iterator it = std::find(m_childBones.begin(), m_childBones.end(), bone);

    if(it != m_childBones.end())
    {
        m_owner->DestroyBone((*it));
        m_childBones.erase(it);
        return true;
    }

    for(unsigned int a = 0; a < m_childBones.size(); a++)
    {
        if(m_childBones.at(a)->RemoveBone(bone))
            return true;
    }

    return false;
}

void Bone::SetZOrder(int zorder)
{
    m_zorder = zorder;

    if(m_owner)
        m_owner->ReorderByZOrder();
}

int Bone::GetZOrder() const
{
    return m_zorder;
}

void Bone::SetTextureName(const std::string &textureName)
{
    m_textureName = textureName;
}

std::string Bone::GetTextureName() const
{
    return m_textureName;
}

void Bone::LoadTexture(Res::SkImageManager & imageMgr)
{
    m_texture = imageMgr.GetImage(m_textureName);
}

bool Bone::IsOnPosition(sf::Vector2f position)
{
    float xRatio = (position.x - m_tmp_position.x) / GetEndNodeRelativePosition().x;
    float yRatio = (position.y - m_tmp_position.y) / GetEndNodeRelativePosition().y;

    if(((position.x > m_tmp_position.x - 2 && position.x < m_tmp_position.x + GetEndNodeRelativePosition().x + 2) || (position.x < m_tmp_position.x + 2 && position.x > m_tmp_position.x + GetEndNodeRelativePosition().x - 2))
       && ((position.y > m_tmp_position.y - 2 && position.y < m_tmp_position.y + GetEndNodeRelativePosition().y + 2) || (position.y < m_tmp_position.y + 2 && position.y > m_tmp_position.y + GetEndNodeRelativePosition().y - 2)))
    {
           if(xRatio > yRatio - 0.3 && xRatio < yRatio + 0.3)
           {
               return true;
           }
           //if(m_tmp_position.x > GetEndNodeRelativePosition().x - 0.5 && m_tmp_position.x < GetEndNodeRelativePosition().x + 0.5)
           if((m_tmp_absoluteRotation > 88 && m_tmp_absoluteRotation < 92) || (m_tmp_absoluteRotation > 268 && m_tmp_absoluteRotation < 272)
               || (m_tmp_absoluteRotation > -2 && m_tmp_absoluteRotation < 2)  || (m_tmp_absoluteRotation > 178 && m_tmp_absoluteRotation < 182)
               || (m_tmp_absoluteRotation > 358 && m_tmp_absoluteRotation < 362))
           {
               return true;
           }
    }

    return false;
}

void Bone::SaveBone(TiXmlElement &saveIn)
{
    TiXmlElement *boneElement = new TiXmlElement("Bone");
    saveIn.LinkEndChild(boneElement);

    boneElement->SetAttribute("name", GetName().c_str());
    boneElement->SetAttribute("texturename", GetTextureName().c_str());
    boneElement->SetDoubleAttribute("size", GetSize());
    boneElement->SetDoubleAttribute("angle", GetRotation());

    boneElement->SetDoubleAttribute("offsetX", GetOffset().x);
    boneElement->SetDoubleAttribute("offsetY", GetOffset().y);

    boneElement->SetDoubleAttribute("zOrder", GetZOrder());

    for(unsigned int a = 0; a < m_childBones.size(); a++)
    {
        m_childBones.at(a)->SaveBone(*boneElement);
    }
}

void Bone::LoadBone(TiXmlElement &boneElement)
{
    SetName(boneElement.Attribute("name"));
    SetTextureName(boneElement.Attribute("texturename"));

    float size = 100;
    boneElement.QueryFloatAttribute("size", &size);
    SetSize(size);

    float angle = 0;
    boneElement.QueryFloatAttribute("angle", &angle);
    SetRotation(angle);

    float offsetX(0), offsetY(0), zorder(0);
    boneElement.QueryFloatAttribute("offsetX", &offsetX);
    boneElement.QueryFloatAttribute("offsetY", &offsetY);
    boneElement.QueryFloatAttribute("zOrder", &zorder);
    SetOffset(offsetX, offsetY);
    SetZOrder(zorder);

    TiXmlNode *child;
    for( child = boneElement.FirstChild(); child; child = child->NextSibling() )
    {
        Bone *newBone = m_owner->CreateBone("tmp");
        AddBone(newBone);
        if(child->ToElement())
        {
            newBone->LoadBone(*child->ToElement());
        }
    }

    Update();
}

}
