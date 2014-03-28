//
//  ieTileset.cpp
//  ieEngine
//
//  Created by sergey.sergeev on 3/28/14.
//  Copyright (c) 2014 sergey.sergeev. All rights reserved.
//

#include "ieTileset.h"
#include "ieTile.h"
#include "ieImage.h"

ieTileset::ieTileset(const std::string& imageFilename,
          const glm::ivec2& tileSize)
{
    std::shared_ptr<ieImage> image = std::make_shared<ieImage>(imageFilename);
    ui32 tilesetWidth = image->getWidth();
    ui32 tilesetHeight = image->getHeight();
    if(tilesetWidth % tileSize.x != 0 ||
       tilesetHeight % tileSize.y != 0)
    {
        assert(false);
        return;
    }
    ui32 numTilesRows = tilesetWidth / tileSize.x;
    ui32 numTilesCells = tilesetHeight / tileSize.y;
    
    for(ui32 i = 0; i < numTilesRows; ++i)
    {
        for(ui32 j = 0; j < numTilesCells; ++j)
        {
            glm::vec4 tileTexCoordFrame = glm::vec4(i * tileSize.x,
                                                    j * tileSize.y,
                                                    tileSize.x,
                                                    tileSize.y);
            std::shared_ptr<ieTile> tile = std::make_shared<ieTile>(imageFilename,
                                                                    glm::vec4(0, 0, tileSize.x, tileSize.y),
                                                                    tileTexCoordFrame);
            m_tiles.push_back(tile);
        }
    }
}

ieTileset::~ieTileset(void)
{
    
}

std::shared_ptr<ieTile> ieTileset::getTileAtIndex(ui32 index) const
{
    assert(index < m_tiles.size());
    if(index < m_tiles.size())
    {
        return m_tiles[index];
    }
    return nullptr;
}

ui32 ieTileset::getTilesCount(void) const
{
    return m_tiles.size();
}
