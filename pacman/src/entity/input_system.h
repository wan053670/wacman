#pragma once

#include "system.h"
#include "events.h"

namespace pac
{
/*!
 * \brief The RenderingSystem class takes care of drawing and interpolating entities with sprite components
 */
class InputSystem : public System
{
private:
    /* Actions not yet processed */
    std::vector<Action> m_unprocessed_actions{};

public:
    InputSystem();

    ~InputSystem() noexcept override;

    void update(float dt, entt::registry& reg) override;

    /*!
     * \brief recieve
     * \param input
     */
    void recieve(const EvInput& input);
};
}  // namespace pac