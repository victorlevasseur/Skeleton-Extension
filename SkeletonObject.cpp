#include <SFML/Graphics.hpp>
#include "GDL/Object.h"

#include "GDL/ImageManager.h"
#include "GDL/tinyxml/tinyxml.h"
#include "GDL/Position.h"
#include "GDL/CommonTools.h"

#include "SkeletonObject.h"

#if defined(GD_IDE_ONLY)
#include <wx/wx.h>
#include "GDL/IDE/ArbitraryResourceWorker.h"
#include "GDL/IDE/MainEditorCommand.h"
#include "SkeletonObjectEditor.h"
#endif

SkeletonObject::SkeletonObject(std::string name_) :
Object(name_), skeleton()
{


    /*{
        Bone *newBone = new Bone("first", &bone);
        newBone->SetSize(100);
        newBone->SetRotation(20);
    }
    {
        Bone *newBone = new Bone("second", &bone);
        newBone->SetSize(150);
        newBone->SetRotation(45);

        {
            Bone *newBone2 = new Bone("subsecond", newBone);
            newBone2->SetSize(75);
            newBone2->SetRotation(10);
        }
    }*/



}

SkeletonObject::~SkeletonObject()
{

}

void SkeletonObject::Init(const SkeletonObject &other)
{
    skeleton = Skeleton(other.skeleton);
}

SkeletonObject::SkeletonObject(const SkeletonObject &other) : Object(other)
{
    Init(other);
}

SkeletonObject& SkeletonObject::operator=(const SkeletonObject &other)
{
    Init(other);
    return *this;
}

void SkeletonObject::LoadFromXml(const TiXmlElement * elem)
{
    TiXmlElement *boneElem = const_cast<TiXmlElement*>(elem->FirstChildElement("Bone"));

    if(boneElem)
    {
        skeleton.GetRoot()->LoadBone(*boneElem);
    }
}

#if defined(GD_IDE_ONLY)
void SkeletonObject::SaveToXml(TiXmlElement * elem)
{
    skeleton.GetRoot()->SaveBone(*elem);
}
#endif

bool SkeletonObject::LoadResources(const RuntimeScene & scene, const ImageManager & imageMgr )
{
    skeleton.GetRoot()->LoadTexture(imageMgr);

    return true;
}

bool SkeletonObject::LoadRuntimeResources(const RuntimeScene & scene, const ImageManager & imageMgr )
{
    skeleton.GetRoot()->LoadTexture(imageMgr);

    return true;
}

bool SkeletonObject::Draw( sf::RenderTarget& renderTarget )
{
    skeleton.Draw(renderTarget, sf::Vector2f(GetX(), GetY()), Bone::Sprites);

    return true;
}


#if defined(GD_IDE_ONLY)
/**
 * Render object at edittime
 */
bool SkeletonObject::DrawEdittime( sf::RenderTarget& renderTarget )
{
    skeleton.Draw(renderTarget, sf::Vector2f(GetX(), GetY()), Bone::Sprites);

    return true;
}

wxPanel * SkeletonObject::CreateInitialPositionPanel( wxWindow* parent, const Game & game_, const Scene & scene_, const InitialPosition & position )
{
    return NULL;
}

void SkeletonObject::ExposeResources(ArbitraryResourceWorker & worker)
{

}

bool SkeletonObject::GenerateThumbnail(const Game & game, wxBitmap & thumbnail)
{
    thumbnail = wxBitmap("res/Skeleton24.png", wxBITMAP_TYPE_ANY);
    return true;
}

void SkeletonObject::EditObject( wxWindow* parent, Game & game, MainEditorCommand & mainEditorCommand )
{
    SkeletonObjectEditor dialog(parent, game, *this, mainEditorCommand);
    dialog.ShowModal();
}

void SkeletonObject::GetPropertyForDebugger(unsigned int propertyNb, string & name, string & value) const
{
}

bool SkeletonObject::ChangeProperty(unsigned int propertyNb, string newValue)
{
    return true;
}

unsigned int SkeletonObject::GetNumberOfProperties() const
{
    return 0;
}
#endif

void SkeletonObject::OnPositionChanged()
{

}

float SkeletonObject::GetDrawableX() const
{
    return GetX();
}

float SkeletonObject::GetDrawableY() const
{
    return GetY();
}

float SkeletonObject::GetWidth() const
{
    return 32;
}

float SkeletonObject::GetHeight() const
{
    return 32;
}

float SkeletonObject::GetCenterX() const
{
    return 16;
}

float SkeletonObject::GetCenterY() const
{
    return 16;
}

void SkeletonObject::UpdateTime(float)
{
}

Skeleton SkeletonObject::GetSkeleton()
{
    return skeleton;
}

void SkeletonObject::SetSkeleton(Skeleton _ske)
{
    skeleton = Skeleton(_ske);
}

void DestroySkeletonObject(Object * object)
{
    delete object;
}

Object * CreateSkeletonObject(std::string name)
{
    return new SkeletonObject(name);
}
