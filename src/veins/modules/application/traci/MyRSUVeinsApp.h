#pragma once

#include "veins/modules/application/ecode/ECODEBaseApplLayer.h"
#include "veins/modules/messages/TMRMessage_m.h"
#include <map>
#include "veins/modules/application/ecode/TSTable.h"

namespace veins {

/**
 * Small RSU Demo using 11p
 */
class VEINS_API MyRSUVeinsApp : public ECODEBaseApplLayer {
public:
    void initialize(int stage) override;
protected:
    std::map<std::string, TSTableEntry*> ts;
protected:
    void onWSM(BaseFrame1609_4* wsm) override;
};

} // namespace veins
