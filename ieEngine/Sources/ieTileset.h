//
//  ieTileset.h
//  ieEngine
//
//  Created by sergey.sergeev on 3/28/14.
//  Copyright (c) 2014 sergey.sergeev. All rights reserved.
//

#ifndef __ieEngine__ieTileset__
#define __ieEngine__ieTileset__

#include "ieCommon.h"

class ieTile;
class ieTileset
{
private:
    
protected:
    
    std::vector<std::shared_ptr<ieTile>> m_tiles;
    
public:
    ieTileset(const std::string& imageFilename,
              const glm::ivec2& tileSize);
    ~ieTileset(void);
    
    std::shared_ptr<ieTile> getTileAtIndex(ui32 index) const;
    ui32 getTilesCount(void) const;
};

#endif
