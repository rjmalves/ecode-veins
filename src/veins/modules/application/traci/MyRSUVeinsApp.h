#pragma once

#include "veins/modules/application/ecode/ECODEBaseApplLayer.h"

namespace veins {

/**
 * Small RSU Demo using 11p
 */
class VEINS_API MyRSUVeinsApp : public ECODEBaseApplLayer {
protected:
    void onWSM(BaseFrame1609_4* wsm) override;
};

} // namespace veins
