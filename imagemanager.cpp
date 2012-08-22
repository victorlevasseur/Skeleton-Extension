#include "imagemanager.h"

#include "GDL/ImageManager.h"
#include "GDL/RuntimeScene.h"

namespace Sk
{

namespace Res
{

SkImageManager::SkImageManager()
{
    //ctor
}

SkImageManager::~SkImageManager()
{
    //dtor
}

void SkImageManager::UnloadAllImages()
{
    m_images.clear();
}

void SkImageManager::ExposeImage(const std::string &picture)
{
    m_needToBeLoaded.push(picture);
}

void SkImageManager::LoadResources(const RuntimeScene & scene, const ImageManager & imageMgr)
{
    UnloadAllImages();

    while(m_needToBeLoaded.size() > 0)
    {
        if(imageMgr.HasImage(m_needToBeLoaded.front()))
        {
            m_images[m_needToBeLoaded.front()] = imageMgr.GetSFMLTexture(m_needToBeLoaded.front());
        }

        m_needToBeLoaded.pop();
    }
}

boost::shared_ptr<SFMLTextureWrapper> SkImageManager::GetImage(const std::string &name)
{
    return m_images[name];
}

}

}
