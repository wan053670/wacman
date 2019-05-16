#include "movement_system.h"
#include "components.h"
#include "level.h"

#include <gfx.h>

namespace pac
{
void MovementSystem::update(float dt, entt::registry& reg)
{
    auto movement_group = reg.group<CPosition, CMovement>(entt::get<CCollision>);
    movement_group.each([dt, this](uint32_t e, CPosition& pos, CMovement& mov, CCollision& col) {
        /* Check if we can move towards desired direction and switch it if possible */
        if (mov.desired_direction != mov.current_direction && !m_level.will_collide(pos.position, mov.desired_direction) &&
            mov.progress < 0.4f)
        {
            if (glm::distance(glm::vec2(mov.current_direction), glm::vec2(mov.desired_direction)) == 2)
            {
                mov.progress = 0.f;
            }
            else
            {
                mov.progress += 0.25f;
            }

            mov.current_direction = mov.desired_direction;
        }

        /* If we will collide in current direction then just skip any other logic */
        if (m_level.will_collide(pos.position, mov.current_direction))
        {
            mov.progress = 0.f;
            return;
        }

        /* Update the progress based on speed */
        mov.progress += dt * mov.speed;

        /* When we reach a new tile, then reset progress and update position (required component) */
        if (mov.progress >= 1.f)
        {
            mov.progress = 0.f;
            pos.position += mov.current_direction;

            /* If an AI owns this movement component, feed a new path now that we reached next step */
            if(reg.has<CAI>(e))
            {
                mov.desired_direction = reg.get<CAI>(e).path->get();
            }
        }
    });
}

}  // namespace pac
