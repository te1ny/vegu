#include "tool.hpp"

#include "../viewport/viewport.hpp"

Tool::Tool(Viewport* viewport)
    : mViewport(viewport)
    , mScene(dynamic_cast<Scene*>(viewport->scene()))
{
}
