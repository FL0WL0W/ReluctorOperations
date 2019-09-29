
#include "Packed.h"

namespace Reluctor
{
    PACK(struct ReluctorResult
    {
        float Position;
        float PositionDot;
        bool Synced;
    });
}