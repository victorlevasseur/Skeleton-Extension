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
, m_mathsFrame(false)
, m_color(0, 0, 0)
#endif
, m_angle(0)
, m_length(100)
, m_offset(0, 0)
, m_zorder(0)
, m_inheritAngle(true)
, m_hasHitBox(false)
, m_hitBoxSize(0, 0)
, m_hitBox()
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
    m_angle = other.m_angle;
    m_length = other.m_length;
    m_offset = other.m_offset;
    m_textureName = other.m_textureName;
    m_texture = boost::shared_ptr<SFMLTextureWrapper>();
    m_name = other.m_name;
    m_zorder = other.m_zorder;
    m_inheritAngle = other.m_inheritAngle;
    m_hasHitBox = other.m_hasHitBox;
    m_hitBoxSize = other.m_hitBoxSize;
    #ifdef GD_IDE_ONLY
    m_color = wxColour(0, 0, 0);
    m_mathsFrame = other.m_mathsFrame;
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
        sf::VertexArray line(sf::Lines);

        line.append(sf::Vertex(sf::Vector2f(offset.x + m_tmp_position.x,
                                            offset.y + m_tmp_position.y),
                               sf::Color(255, 0, 0)));

        line.append(sf::Vertex(sf::Vector2f(offset.x + m_tmp_position.x + GetEndNodeRelativePosition().x,
                                            offset.y + m_tmp_position.y + GetEndNodeRelativePosition().y),
                               sf::Color(255, 0, 0)));

        target.draw(line);
    }
    else if(type == Sprites && m_texture != boost::shared_ptr<SFMLTextureWrapper>())
    {
        sf::Sprite sprite;

        sprite.setOrigin(m_texture->texture.getSize().x / 2, m_texture->texture.getSize().y / 2);
        sprite.setTexture(m_texture->texture);
        sprite.setPosition(offset.x + m_tmp_position.x + (GetEndNodeRelativePosition().x / 2),
                           offset.y + m_tmp_position.y + (GetEndNodeRelativePosition().y / 2));
        sprite.setRotation(m_tmp_totalAngle);

        target.draw(sprite);
    }
}

#ifdef GD_IDE_ONLY
void Bone::DrawWx(wxBufferedPaintDC &dc, sf::Vector2f offset, bool selected)
{
    if(selected && m_hasHitBox && m_hitBox.vertices.size() == 4)
    {
        dc.SetPen(wxPen(wxColour(255, 255, 255)));
        dc.SetBrush(wxBrush(wxColour(160, 160, 160), wxBRUSHSTYLE_BDIAGONAL_HATCH ));

        wxPoint colPointList[4];
        colPointList[3] = wxPoint(m_hitBox.vertices.at(0).x + offset.x, m_hitBox.vertices.at(0).y + offset.y);
        colPointList[2] = wxPoint(m_hitBox.vertices.at(1).x + offset.x, m_hitBox.vertices.at(1).y + offset.y);
        colPointList[1] = wxPoint(m_hitBox.vertices.at(2).x + offset.x, m_hitBox.vertices.at(2).y + offset.y);
        colPointList[0] = wxPoint(m_hitBox.vertices.at(3).x + offset.x, m_hitBox.vertices.at(3).y + offset.y);

        dc.DrawPolygon(4, colPointList);
    }

    dc.SetPen(wxPen(selected ? wxColour(0, 0, 255) : m_color));
    dc.SetBrush(wxBrush(selected ? wxColour(100, 192, 255) : wxColour(220, 220, 220)));

    dc.DrawCircle(floor(offset.x + m_tmp_position.x),
                  floor(offset.y + m_tmp_position.y),
                  4);

    wxPoint startPoint(floor(m_tmp_position.x), floor(m_tmp_position.y));
    wxPoint sidePoint1(floor(m_tmp_position.x + GetEndNodeRelativePosition().x + cos(((m_tmp_totalAngle + (500/m_length)) * M_PI) / 180.f) * (-m_length * 0.9)),
                       floor(m_tmp_position.y + GetEndNodeRelativePosition().y + sin(((m_tmp_totalAngle + (500/m_length)) * M_PI) / 180.f) * (-m_length * 0.9)));
    wxPoint sidePoint2(floor(m_tmp_position.x + GetEndNodeRelativePosition().x + cos(((m_tmp_totalAngle - (500/m_length)) * M_PI) / 180.f) * (-m_length * 0.9)),
                       floor(m_tmp_position.y + GetEndNodeRelativePosition().y + sin(((m_tmp_totalAngle - (500/m_length)) * M_PI) / 180.f) * (-m_length * 0.9)));
    wxPoint endPoint(floor(m_tmp_position.x + GetEndNodeRelativePosition().x),
                     floor(m_tmp_position.y + GetEndNodeRelativePosition().y));

    wxPoint pointList[4];
    pointList[0] = startPoint;
    pointList[1] = sidePoint1;
    pointList[2] = endPoint;
    pointList[3] = sidePoint2;

    dc.DrawPolygon(4, pointList, offset.x, offset.y);



    dc.DrawCircle(floor(offset.x + m_tmp_position.x + GetEndNodeRelativePosition().x),
                  floor(offset.y + m_tmp_position.y + GetEndNodeRelativePosition().y),
                  4);

    dc.DrawRotatedText(m_name, offset.x + m_tmp_position.x + GetEndNodeRelativePosition().x / 2.5,
                               offset.y + m_tmp_position.y + GetEndNodeRelativePosition().y / 2.5,
                               360 - m_tmp_totalAngle);


    if(selected)
    {
        wxPoint handleCenter(offset.x + (startPoint.x + endPoint.x)/2,
                             offset.y + (startPoint.y + endPoint.y)/2);

        dc.SetPen(wxPen(wxColour(0, 0, 0)));
        dc.SetBrush(wxBrush(wxColour(255, 255, 255)));

        dc.DrawCircle(handleCenter, 4);
    }

    if(m_mathsFrame)
    {
        wxPoint frameOrigin(floor(offset.x + m_tmp_position.x + GetEndNodeRelativePosition().x),
                            floor(offset.y + m_tmp_position.y + GetEndNodeRelativePosition().y));

        wxPoint frameEndX(floor(offset.x + m_tmp_position.x + GetEndNodeRelativePosition().x + cos((m_tmp_totalAngle * M_PI) / 180.f) * (400.f)),
                          floor(offset.y + m_tmp_position.y + GetEndNodeRelativePosition().y + sin((m_tmp_totalAngle * M_PI) / 180.f) * (400.f)));

        wxPoint frameEndY(floor(offset.x + m_tmp_position.x + GetEndNodeRelativePosition().x + cos(((m_tmp_totalAngle + 90) * M_PI) / 180.f) * (400.f)),
                          floor(offset.y + m_tmp_position.y + GetEndNodeRelativePosition().y + sin(((m_tmp_totalAngle + 90) * M_PI) / 180.f) * (400.f)));

        dc.SetPen(wxPen(wxColour(255, 0, 0)));
        dc.DrawLine(frameOrigin, frameEndX);

        dc.SetPen(wxPen(wxColour(0, 0, 255)));
        dc.DrawLine(frameOrigin, frameEndY);
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

void Bone::ShowMathsFrame(bool show)
{
    m_mathsFrame = show;
}

#endif

void Bone::Update()
{
    if(m_parentBone)
    {
        m_tmp_position = m_parentBone->m_tmp_position + m_parentBone->GetEndNodeRelativePosition();
        m_tmp_totalAngle = (m_inheritAngle ? m_parentBone->m_tmp_totalAngle : 0) + m_angle;

        m_tmp_position += sf::Vector2f(cos((m_parentBone->m_tmp_totalAngle * M_PI) / 180.f) * m_offset.x,
                                       sin((m_parentBone->m_tmp_totalAngle * M_PI) / 180.f) * m_offset.x);

        m_tmp_position += sf::Vector2f(cos(((m_parentBone->m_tmp_totalAngle + 90) * M_PI) / 180.f) * m_offset.y,
                                       sin(((m_parentBone->m_tmp_totalAngle + 90) * M_PI) / 180.f) * m_offset.y);


        while(m_tmp_totalAngle >= 360) //Simplify the angle
            m_tmp_totalAngle -= 360;
        while(m_tmp_totalAngle < 0)
            m_tmp_totalAngle += 360;
    }
    else
    {
        m_tmp_position = sf::Vector2f(0, 0);
        m_tmp_totalAngle = m_angle;

        m_tmp_position += sf::Vector2f(m_offset.x, m_offset.y);
    }

    for(std::vector<Bone*>::iterator it = m_childBones.begin(); it != m_childBones.end(); it++)
    {
        (*it)->Update();
    }

    UpdateHitBox();
}

void Bone::UpdateHitBox()
{
    m_hitBox = Polygon2d::CreateRectangle(m_hitBoxSize.x, m_hitBoxSize.y);
    m_hitBox.Rotate(-m_tmp_totalAngle/180*3.14159);
    m_hitBox.Move(m_tmp_position.x + (GetEndNodeRelativePosition().x)/2,
                         m_tmp_position.y + (GetEndNodeRelativePosition().y)/2);
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
    return sf::Vector2f(cos((m_tmp_totalAngle * M_PI) / 180.f) * m_length,
                         sin((m_tmp_totalAngle * M_PI) / 180.f) * m_length);
}

void Bone::SetLength(float size)
{
    m_length = size;

    Update();
}

float Bone::GetLength() const
{
    return m_length;
}

void Bone::SetAngle(float rotation)
{
    m_angle = rotation;
}

float Bone::GetAngle() const
{
    return m_angle;
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
        m_owner->SortBones();
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

void Bone::SetHitBoxSize(float width, float height)
{
    m_hitBoxSize.x = width;
    m_hitBoxSize.y = height;

    UpdateHitBox();
}

const sf::Vector2f& Bone::GetHitBoxSize() const
{
    return m_hitBoxSize;
}

void Bone::LoadTexture(Res::SkImageManager & imageMgr)
{
    m_texture = imageMgr.GetImage(m_textureName);
}

#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

bool Bone::IsPointOnBone(sf::Vector2f position)
{
    std::vector<sf::Vector2f> poly;
    poly.push_back(sf::Vector2f(floor(m_tmp_position.x), floor(m_tmp_position.y)));
    poly.push_back(sf::Vector2f(floor(m_tmp_position.x + GetEndNodeRelativePosition().x + cos(((m_tmp_totalAngle + (500/m_length)) * M_PI) / 180.f) * (-m_length * 0.9)),
                                floor(m_tmp_position.y + GetEndNodeRelativePosition().y + sin(((m_tmp_totalAngle + (500/m_length)) * M_PI) / 180.f) * (-m_length * 0.9))));
    poly.push_back(sf::Vector2f(floor(m_tmp_position.x + GetEndNodeRelativePosition().x),
                                floor(m_tmp_position.y + GetEndNodeRelativePosition().y)));
    poly.push_back(sf::Vector2f(floor(m_tmp_position.x + GetEndNodeRelativePosition().x + cos(((m_tmp_totalAngle - (500/m_length)) * M_PI) / 180.f) * (-m_length * 0.9)),
                                floor(m_tmp_position.y + GetEndNodeRelativePosition().y + sin(((m_tmp_totalAngle - (500/m_length)) * M_PI) / 180.f) * (-m_length * 0.9))));

    int counter = 0;
    int i;
    double xinters;
    sf::Vector2f p1,p2;

    p1 = poly[0];
    for (i=1;i<=4;i++)
    {
        p2 = poly[i % 4];
        if (position.y > MIN(p1.y,p2.y))
        {
            if (position.y <= MAX(p1.y,p2.y))
            {
                if (position.x <= MAX(p1.x,p2.x))
                {
                    if (p1.y != p2.y)
                    {
                        xinters = (position.y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
                        if (p1.x == p2.x || position.x <= xinters)
                            counter++;
                    }
                }
            }
        }
        p1 = p2;
    }

    if (counter % 2 == 0)
        return false;
    else
        return true;
}

bool Bone::IsOnAngleHandle(sf::Vector2f position)
{
    sf::Vector2f startPoint(floor(m_tmp_position.x), floor(m_tmp_position.y));

    sf::Vector2f endPoint(floor(m_tmp_position.x + GetEndNodeRelativePosition().x),
                          floor(m_tmp_position.y + GetEndNodeRelativePosition().y));

    sf::Vector2f handleCenter((startPoint.x + endPoint.x)/2,
                              (startPoint.y + endPoint.y)/2);

    if(position.x > handleCenter.x - 4 && position.x < handleCenter.x + 4 &&
       position.y > handleCenter.y - 4 && position.y < handleCenter.y + 4)
        return true;
    else
        return false;
}

void Bone::SaveBone(TiXmlElement &saveIn)
{
    TiXmlElement *boneElement = new TiXmlElement("Bone");
    saveIn.LinkEndChild(boneElement);

    boneElement->SetAttribute("name", GetName().c_str());
    boneElement->SetAttribute("texturename", GetTextureName().c_str());
    boneElement->SetDoubleAttribute("size", GetLength());
    boneElement->SetDoubleAttribute("angle", GetAngle());

    boneElement->SetDoubleAttribute("offsetX", GetOffset().x);
    boneElement->SetDoubleAttribute("offsetY", GetOffset().y);

    boneElement->SetDoubleAttribute("zOrder", GetZOrder());

    boneElement->SetDoubleAttribute("inheritRotation", (double)IsAngleInheritanceEnabled());

    boneElement->SetDoubleAttribute("hasHitBox", (double)IsHitBoxEnabled());
    boneElement->SetDoubleAttribute("hitBoxWidth", GetHitBoxSize().x);
    boneElement->SetDoubleAttribute("hitBoxHeight", GetHitBoxSize().y);

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
    SetLength(size);

    float angle = 0;
    boneElement.QueryFloatAttribute("angle", &angle);
    SetAngle(angle);

    float offsetX(0), offsetY(0), zorder(0);
    boneElement.QueryFloatAttribute("offsetX", &offsetX);
    boneElement.QueryFloatAttribute("offsetY", &offsetY);
    boneElement.QueryFloatAttribute("zOrder", &zorder);
    SetOffset(offsetX, offsetY);
    SetZOrder(zorder);

    int hasInheritRotation = true;
    boneElement.QueryIntAttribute("inheritRotation", &hasInheritRotation);
    EnableAngleInheritance((bool)hasInheritRotation);

    int hasCollision = false;
    boneElement.QueryIntAttribute("hasHitBox", &hasCollision);
    EnableHitBox((bool)hasCollision);

    float colWidth(0), colHeight(0);
    boneElement.QueryFloatAttribute("hitBoxWidth", &colWidth);
    boneElement.QueryFloatAttribute("hitBoxHeight", &colHeight);
    SetHitBoxSize(colWidth, colHeight);

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
