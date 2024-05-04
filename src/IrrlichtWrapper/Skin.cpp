#include "Skin.h"

void setSkinTransparency(s32 alpha, irr::gui::IGUISkin* skin)
{
    for (s32 i = 0; i < irr::gui::EGDC_COUNT; ++i)
    {
        video::SColor col = skin->getColor((EGUI_DEFAULT_COLOR)i);
        col.setAlpha(alpha);
        skin->setColor((EGUI_DEFAULT_COLOR)i, col);
    }
}