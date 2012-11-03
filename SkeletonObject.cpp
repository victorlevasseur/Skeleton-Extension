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

#if defined(GD_IDE_ONLY)
#include <wx/wx.h> //Must be placed first, otherwise we get errors relative to "cannot convert 'const TCHAR*'..." in wx/msw/winundef.h
#endif

#include "SkeletonObject.h"

#include <SFML/Graphics.hpp>
#include "GDL/Object.h"
#include "GDL/ImageManager.h"
#include "GDL/tinyxml/tinyxml.h"
#include "GDL/Position.h"
#include "GDL/CommonTools.h"
#include "GDL/Polygon.h"

#include "Skeleton.h"
#include "Bone.h"

#if defined(GD_IDE_ONLY)
#include "GDCore/IDE/Dialogs/MainFrameWrapper.h"
#include "GDCore/IDE/ArbitraryResourceWorker.h"
#include "GDCore/PlatformDefinition/Project.h"
#include "SkeletonObjectEditor.h"
#endif

SkeletonObject::SkeletonObject(std::string name_) :
Object(name_), skeleton(new Sk::Skeleton())
{

}

SkeletonObject::~SkeletonObject()
{
    delete skeleton;
}

void SkeletonObject::Init(const SkeletonObject &other)
{
    skeleton = new Sk::Skeleton(*other.skeleton);
}

Object* SkeletonObject::Clone() const
{
    return new SkeletonObject(*this);
}

SkeletonObject::SkeletonObject(const SkeletonObject &other) : Object(other)
{
    Init(other);
}

SkeletonObject& SkeletonObject::operator=(const SkeletonObject &other)
{
    if ( &other != this )
        Init(other);
    return *this;
}

void SkeletonObject::LoadFromXml(const TiXmlElement * elem)
{
    skeleton->Load(*elem);
}

#if defined(GD_IDE_ONLY)
void SkeletonObject::SaveToXml(TiXmlElement * elem)
{
    skeleton->Save(*elem);
}
#endif

bool SkeletonObject::LoadResources(const RuntimeScene & scene, const ImageManager & imageMgr )
{
    skeleton->ExposeResources();
    skeleton->LoadResources(scene, imageMgr);

    skeleton->GetAnimator().Reset();

    return true;
}

bool SkeletonObject::LoadRuntimeResources(const RuntimeScene & scene, const ImageManager & imageMgr )
{
    skeleton->ExposeResources();
    skeleton->LoadResources(scene, imageMgr);

    skeleton->GetAnimator().Reset();

    return true;
}

bool SkeletonObject::Draw( sf::RenderTarget& renderTarget )
{
    if ( hidden )
    {
        return true;
    }

    skeleton->Draw(renderTarget, sf::Vector2f(GetX(), GetY()), Sk::Bone::Sprites);
    return true;
}


#if defined(GD_IDE_ONLY)
/**
 * Render object at edittime
 */
bool SkeletonObject::DrawEdittime( sf::RenderTarget &renderTarget )
{
    sf::RectangleShape rectangle(sf::Vector2f(GetWidth(), GetHeight()));
    rectangle.setPosition(GetX(), GetY());
    rectangle.setFillColor(sf::Color(255, 255, 255, 0));
    rectangle.setOutlineColor(sf::Color(0, 0, 0, 255));
    rectangle.setOutlineThickness(2);

    renderTarget.draw(rectangle);

    skeleton->Draw(renderTarget, sf::Vector2f(GetX(), GetY()), Sk::Bone::Sprites);
    return true;
}

wxPanel * SkeletonObject::CreateInitialPositionPanel( wxWindow* parent, const Game & game_, const Scene & scene_, const InitialPosition & position )
{
    return NULL;
}

void SkeletonObject::ExposeResources(gd::ArbitraryResourceWorker & worker)
{
    skeleton->GetImageManager().ShowResourcesToGD(worker);
}

bool SkeletonObject::GenerateThumbnail(const gd::Project & project, wxBitmap & thumbnail)
{
    thumbnail = wxBitmap("res/Skeleton24.png", wxBITMAP_TYPE_ANY);
    return true;
}

void SkeletonObject::EditObject( wxWindow* parent, Game & game, gd::MainFrameWrapper & mainEditorCommand )
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

void SkeletonObject::UpdateTime(float time)
{
    skeleton->GetAnimator().UpdateTime(time);
    skeleton->ApplyAnimationToBones();
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

std::vector<Polygon2d> SkeletonObject::GetHitBoxes() const
{
    std::vector<Polygon2d> hitBoxes;

    for(unsigned int a = 0; skeleton->GetBones().size(); a++)
    {
        if(skeleton->GetBones().at(a)->IsHitBoxEnabled())
            hitBoxes.push_back(skeleton->GetBones().at(a)->GetHitBox());
    }

    return hitBoxes;
}

Sk::Skeleton SkeletonObject::GetSkeleton()
{
    return *skeleton;
}

void SkeletonObject::SetSkeleton(Sk::Skeleton _ske)
{
    skeleton = new Sk::Skeleton(_ske);
}

void SkeletonObject::Play()
{
    skeleton->GetAnimator().Play();
}

void SkeletonObject::Pause()
{
    skeleton->GetAnimator().Pause();
}

void SkeletonObject::Stop()
{
    skeleton->GetAnimator().Stop();
}

void SkeletonObject::SetSpeedRatio(float ratio)
{
    skeleton->GetAnimator().SetSpeedRatio(ratio);
}

bool SkeletonObject::IsPlaying() const
{
    return skeleton->GetAnimator().IsPlaying();
}

bool SkeletonObject::IsPausing() const
{
    return skeleton->GetAnimator().IsPausing();
}

bool SkeletonObject::IsStopped() const
{
    return skeleton->GetAnimator().IsStopped();
}

float SkeletonObject::GetSpeedRatio() const
{
    return skeleton->GetAnimator().GetSpeedRatio();
}

void SkeletonObject::SetAnimation(const std::string &anim)
{
    skeleton->GetAnimator().SetCurrentAnimationName(anim);
}

const std::string& SkeletonObject::GetAnimation() const
{
    return skeleton->GetAnimator().GetCurrentAnimationName();
}

float SkeletonObject::GetPosition()
{
    return skeleton->GetAnimator().GetTime();
}

void SkeletonObject::Seek(float time)
{
    skeleton->GetAnimator().Seek(time);
}

void SkeletonObject::EnableAnimationSystem(bool enable)
{
    skeleton->EnableAnimationSystem(enable);
}

float SkeletonObject::GetBoneAngle(const std::string &boneName)
{
    Sk::Bone *bone = skeleton->GetBone(boneName);
    if(bone)
    {
        return bone->GetAngle();
    }

    return 0;
}

float SkeletonObject::GetBoneAbsoluteAngle(const std::string &boneName)
{
    Sk::Bone *bone = skeleton->GetBone(boneName);
    if(bone)
    {
        return bone->GetAbsoluteAngle();
    }

    return 0;
}

void SkeletonObject::SetBoneAngle(const std::string &boneName, float angle)
{
    Sk::Bone *bone = skeleton->GetBone(boneName);
    if(bone)
    {
        bone->SetAngle(angle);
        bone->Update();
    }
}

float SkeletonObject::GetBoneLength(const std::string &boneName)
{
    Sk::Bone *bone = skeleton->GetBone(boneName);
    if(bone)
    {
        return bone->GetLength();
    }

    return 0;
}

void SkeletonObject::SetBoneLength(const std::string &boneName, float length)
{
    Sk::Bone *bone = skeleton->GetBone(boneName);
    if(bone)
    {
        bone->SetLength(length);
    }
}

float SkeletonObject::GetBoneCenterX(const std::string &boneName)
{
    Sk::Bone *bone = skeleton->GetBone(boneName);
    if(bone)
    {
        return GetX() + bone->GetBonePosition().x + (bone->GetEndNodeRelativePosition().x)/2;
    }

    return 0;
}

float SkeletonObject::GetBoneCenterY(const std::string &boneName)
{
    Sk::Bone *bone = skeleton->GetBone(boneName);
    if(bone)
    {
        return GetY() + bone->GetBonePosition().y + (bone->GetEndNodeRelativePosition().y)/2;
    }

    return 0;
}

void DestroySkeletonObject(Object * object)
{
    delete object;
}

Object * CreateSkeletonObject(std::string name)
{
    return new SkeletonObject(name);
}
