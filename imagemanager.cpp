#include "imagemanager.h"

#include "GDL/ImageManager.h"
#include "GDL/RuntimeScene.h"

#if defined(GD_IDE_ONLY)
#include "GDCore/IDE/ArbitraryResourceWorker.h"
#endif

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

#ifdef GD_IDE_ONLY
void SkImageManager::ShowResourcesToGD(gd::ArbitraryResourceWorker & worker)
{
    std::map<std::string, boost::shared_ptr<SFMLTextureWrapper> >::iterator it = m_images.begin();

    for(; it != m_images.end(); it++)
    {
        worker.ExposeImage(const_cast<std::string&>(it->first));
    }

    for(unsigned int a = 0; a < m_needToBeLoaded.size(); a++)
    {
        std::string value = m_needToBeLoaded.front();
        m_needToBeLoaded.pop();
        m_needToBeLoaded.push(value);

        worker.ExposeImage(value);
    }
}
#endif

}

}
