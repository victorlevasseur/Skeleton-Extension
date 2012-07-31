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

#ifndef SkeletonObject_H
#define SkeletonObject_H

#include "GDL/Object.h"
#include "GDL/ResourceWrapper.h"
#include "Skeleton.h"
#include "Bone.h"

#if defined(GD_IDE_ONLY)
#include "GDCore/IDE/ArbitraryResourceWorker.h"
#endif


class ImageManager;
class RuntimeScene;
class Object;
class ImageManager;
class InitialPosition;
#if defined(GD_IDE_ONLY)
namespace sf
{
    class Texture;
    class Sprite;
};
class wxBitmap;
class Game;
class wxWindow;
class MainEditorCommand;
class ResourcesMergingHelper;
#endif

class GD_EXTENSION_API SkeletonObject : public Object
{
    public :

        SkeletonObject(std::string name_);
        virtual ~SkeletonObject();

        void Init(const SkeletonObject &other);
        SkeletonObject(const SkeletonObject &other);
        SkeletonObject& operator=(const SkeletonObject &other);

        virtual Object* Clone() { return new SkeletonObject(*this);}

        virtual bool LoadResources(const RuntimeScene & scene, const ImageManager & imageMgr );
        virtual bool LoadRuntimeResources(const RuntimeScene & scene, const ImageManager & imageMgr );

        virtual bool Draw(sf::RenderTarget & renderTarget);

        #if defined(GD_IDE_ONLY)
        virtual bool DrawEdittime(sf::RenderTarget & renderTarget);
        virtual void ExposeResources(gd::ArbitraryResourceWorker & worker);
        virtual bool GenerateThumbnail(const Game & game, wxBitmap & thumbnail);

        virtual wxPanel * CreateInitialPositionPanel( wxWindow* parent, const Game & game_, const Scene & scene_, const InitialPosition & position );

        virtual void EditObject( wxWindow* parent, Game & game_, MainEditorCommand & mainEditorCommand_ );

        virtual void GetPropertyForDebugger (unsigned int propertyNb, std::string & name, std::string & value) const;
        virtual bool ChangeProperty(unsigned int propertyNb, std::string newValue);
        virtual unsigned int GetNumberOfProperties() const;
        #endif

        virtual void LoadFromXml(const TiXmlElement * elemScene);
        #if defined(GD_IDE_ONLY)
        virtual void SaveToXml(TiXmlElement * elemScene);
        #endif

        virtual void UpdateTime(float timeElapsed);

        virtual void OnPositionChanged();

        virtual float GetWidth() const;
        virtual float GetHeight() const;
        virtual void SetWidth(float ) {};
        virtual void SetHeight(float ) {};

        virtual float GetDrawableX() const;
        virtual float GetDrawableY() const;

        virtual float GetCenterX() const;
        virtual float GetCenterY() const;

        Sk::Skeleton GetSkeleton();
        void SetSkeleton(Sk::Skeleton _ske);

    private:
        Sk::Skeleton skeleton;
        //Bone bone;

};

void DestroySkeletonObject(Object * object);
Object * CreateSkeletonObject(std::string name);

#endif // SkeletonObject_H
