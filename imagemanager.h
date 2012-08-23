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
