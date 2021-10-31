#pragma once

#include "veins/modules/application/ecode/ECODEBaseApplLayer.h"
#include <map>
#include "veins/modules/messages/ADVMessage_m.h"

namespace veins {

/**
 * @brief
 * A tutorial demo for TraCI. When the car is stopped for longer than 10 seconds
 * it will send a message out to other cars containing the blocked road id.
 * Receiving cars will then trigger a reroute via TraCI.
 * When channel switching between SCH and CCH is enabled on the MAC, the message is
 * instead send out on a service channel following a Service Advertisement
 * on the CCH.
 *
 * @author Christoph Sommer : initial DemoApp
 * @author David Eckhoff : rewriting, moving functionality to DemoBaseApplLayer, adding WSA
 *
 */

class VEINS_API MyVeinsApp : public ECODEBaseApplLayer
{
public:
    void initialize(int stage) override;

protected:
    simtime_t lastDroveAt;
    bool sentMessage;
    int currentSubscribedServiceId;

    // Propriedades para a mensagem ADV
    int id;
    double speed;
    Coord position;
    Coord direction;
    std::string destination;
    simtime_t time;
    simtime_t lastSentADV;

    // Propriedades para a mensagem NR
    std::map<int, ADVMessage*> NRtable;

protected:
    void onWSM(BaseFrame1609_4* wsm) override;

    void populateADV(ADVMessage* adv);

    void handleSelfMsg(cMessage* msg) override;
    void handlePositionUpdate(cObject* obj) override;
};

} // namespace veins
