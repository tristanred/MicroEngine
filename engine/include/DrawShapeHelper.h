#pragma once

#include "Rendering/ATexture.h"
#include "Rendering/ARenderer.h"
#include "Rendering/RenderableObject.h"
#include <libtech/geometry.h>

ATexture* DrawObjectStroke(ARenderer* renderer, FPolygon* target);
