#pragma once

#include <libtech/geometry.h>

#include "Rendering/ARenderer.h"
#include "Rendering/ATexture.h"
#include "Rendering/RenderableObject.h"

ATexture* DrawObjectStroke(ARenderer* renderer, FPolygon* target);
