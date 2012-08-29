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

#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <map>
#include <queue>
#include <string>

#include <boost/shared_ptr.hpp>
#include <SFML/Graphics/Texture.hpp>

class RuntimeScene;
class ImageManager;
class SFMLTextureWrapper;

namespace gd {class ArbitraryResourceWorker;}

namespace Sk
{
namespace Res
{

class SkImageManager
{
    public:
        SkImageManager();
        ~SkImageManager();

        void UnloadAllImages();
        void ExposeImage(const std::string &picture);

        void LoadResources(const RuntimeScene & scene, const ImageManager & imageMgr);

        boost::shared_ptr<SFMLTextureWrapper> GetImage(const std::string &name);

        #ifdef GD_IDE_ONLY
        void ShowResourcesToGD(gd::ArbitraryResourceWorker & worker);
        #endif

    protected:
    private:
        std::queue<std::string> m_needToBeLoaded;
        std::map<std::string, boost::shared_ptr<SFMLTextureWrapper> > m_images;
};

}

}

#endif // IMAGEMANAGER_H
