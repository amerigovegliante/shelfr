#ifndef MEDIAOBSERVERINTERFACE_H
#define MEDIAOBSERVERINTERFACE

#include "media.h"

class MediaObserverInterface
{
    public:
        virtual ~MediaObserverInterface() = default;
        
        virtual void onMediaAdded(Media*) = 0;
        virtual void onMediaUpdated(Media*) = 0;
        virtual void onMediaDeleted(Media*) = 0;
};

#endif