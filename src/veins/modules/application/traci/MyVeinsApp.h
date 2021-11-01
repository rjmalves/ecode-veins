#pragma once

#include <map>
#include "veins/modules/application/ecode/ECODEBaseApplLayer.h"
#include "veins/modules/application/ecode/NRTable.h"
#include "veins/modules/messages/ADVMessage_m.h"
#include "veins/modules/messages/NRMessage_m.h"

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
    std::string edge;
    std::string lane;
    double lanePosition;
    std::string destination;
    simtime_t time;
    simtime_t lastSentADV;

    // Propriedades para a mensagem NR
    std::map<int, NRTableEntry*> nr;
    simtime_t lastSentNR;

    // Propriedades para a mensagem TMR
    double edge_traffic_density;
    double edge_traffic_speed;
    double edge_travel_time;
    double edge_max_allowed_speed;
    simtime_t lastSentTMR;

protected:
    void onWSM(BaseFrame1609_4* wsm) override;

    void populateADV(ADVMessage* adv);
    void populateNR(NRMessage* nr);

    void handleSelfMsg(cMessage* msg) override;
    void handlePositionUpdate(cObject* obj) override;
};

} // namespace veins
