#pragma once

#include "entity/components.h"
#include "rendering/renderer.h"

#include <vector>

#include <entt/signal/sigh.hpp>

namespace pac
{
namespace ui
{
class TilesetSelector
{
private:
    /* The tileset being edited */
    TextureID m_tileset;

    /* Current selected */
    unsigned m_selected = 0u;

public:
    TilesetSelector();
    TilesetSelector(TextureID texture);

    /*!
     * \brief update draws the UI and updates it
     * \param dt is delta time
     */
    void update(float dt);

    /*!
     * \brief set_selection sets the selection of this tileset selector
     * \param s is the new selection
     */
    void set_selection(unsigned s);

    /* Signal for when a tile is selected */
    entt::sigh<void(unsigned)> on_select_tile{};
};

class AnimationEditor
{
private:
    /*!
     * \brief The AnimData struct holds information about animations
     */
    struct AnimData
    {
        char texture_name[64] = {'\0'};
        int start_x = 0;
        int start_y = 0;
        int width = 0;
        int height = 0;
        int columns = 0;
        int length = 0;
    } m_current_anim{};

    /* Current animation as a texture handle */
    unsigned m_current_tex{};

    /* Number of frames in current tex */
    unsigned m_current_tex_frames{};

    /* Current frame */
    unsigned m_current_frame{};

    /* Frame timer for Animation */
    float m_frame_timer = 0.f;

public:
    AnimationEditor() = default;

    ~AnimationEditor() noexcept;

    /*!
     * \brief update draws the UI and updates it
     * \param dt is delta time
     */
    void update(float dt);
};

}  // namespace ui

}  // namespace pac