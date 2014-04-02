//
//  iePredefined.h
//  ieCore
//
//  Created by Sergey Sergeev on 4/2/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef ieCore_iePredefined_h
#define ieCore_iePredefined_h

#include "ieCommon.h"

class ieTexture;
typedef std::shared_ptr<ieTexture> ieSharedTexture;
typedef const ieSharedTexture& ieSharedTextureRef;

class ieShader;
typedef std::shared_ptr<ieShader> ieSharedShader;
typedef const ieSharedShader& ieSharedShaderRef;

class ieMaterial;
typedef std::shared_ptr<ieMaterial> ieSharedMaterial;
typedef const ieSharedMaterial& ieSharedMaterialRef;

class ieColor;
typedef std::shared_ptr<ieColor> ieSharedColor;
typedef const ieSharedColor& ieSharedColorRef;

class ieShape;
typedef std::shared_ptr<ieShape> ieSharedShape;
typedef const ieSharedShape& ieSharedShapeRef;

#endif
