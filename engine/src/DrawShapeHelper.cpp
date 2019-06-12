#include "DrawShapeHelper.h"

ATexture* DrawObjectStroke(ARenderer* renderer, FPolygon* target)
{
    // Create an empty texture the size of our polygon
    ATexture* result = renderer->CreateTexture();
    result->SetSolidColor(target->GetRectBounds().GetSize(), 0x00000000);

    int vertCount = 0;
    vec2** verts = target->GetVertices(&vertCount);

    float minX = verts[0]->x;
    float minY = verts[0]->y;

    // Find the largest X/Y we can subtract to each vertex by finding
    // the smallest x/y coordinate of the vertices.
    for(int i = 1; i < vertCount; i++)
    {
        if(verts[i]->x < minX)
        {
            minX = verts[i]->x;
        }
        if(verts[i]->y < minY)
        {
            minY = verts[i]->y;
        }
    }

    // Go through each vertex and subtract the min x and y to position the
    // polygon close to the (0, 0) position.
    for(int i = 0; i < vertCount; i++)
    {
        verts[i]->x -= minX;
        verts[i]->y -= minY;
    }

    // Draw a line between each vertex pair.
    for(int i = 1; i < vertCount; i++)
    {
        vec2* previous = verts[i - 1];
        vec2* current = verts[i];

        result->DrawLine(FPosition(*previous), FPosition(*current), 0xFF0000FF, 2);
    }

    vec2* last = verts[vertCount-1];
    vec2* first = verts[0];

    result->DrawLine(FPosition(*last), FPosition(*first), 0xFF0000FF, 2);

    return result;
}
