#include "veins/modules/application/traci/MyVeinsApp.h"

#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"

using namespace veins;

Define_Module(veins::MyVeinsApp);

void MyVeinsApp::initialize(int stage)
{
    ECODEBaseApplLayer::initialize(stage);
    if (stage == 0)
    {
        sentMessage = false;
        lastDroveAt = simTime();
        currentSubscribedServiceId = -1;
    }
    simtime_t time = 0;
    lastSentADV = 0;
}

void MyVeinsApp::onWSM(BaseFrame1609_4* frame)
{
    // TraCIDemo11pMessage* wsm = check_and_cast<TraCIDemo11pMessage*>(frame);
    // if (mobility->getRoadId()[0] != ':')
    // {
    //     traciVehicle->changeRoute(wsm->getDemoData(), 9999);
    // }
    // if (!sentMessage)
    // {
    //     sentMessage = true;
    //     // repeat the received traffic update once in 2 seconds plus some random delay
    //     wsm->setSenderAddress(myId);
    //     wsm->setSerial(3);
    //     scheduleAt(simTime() + 2 + uniform(0.01, 0.2), wsm->dup());
    // }
}

void MyVeinsApp::handleSelfMsg(cMessage* msg)
{
    if (TraCIDemo11pMessage* wsm = dynamic_cast<TraCIDemo11pMessage*>(msg))
    {
        // send this message on the service channel until the counter is 3 or higher.
        // this code only runs when channel switching is enabled
        sendDown(wsm->dup());
        wsm->setSerial(wsm->getSerial() + 1);
        if (wsm->getSerial() >= 3) {
            // stop service advertisements
            delete (wsm);
        }
        else {
            scheduleAt(simTime() + 1, wsm);
        }
    }
    else
    {
        ECODEBaseApplLayer::handleSelfMsg(msg);
    }
}

void MyVeinsApp::populateADV(ADVMessage* adv)
{
    adv->setSenderID(id);
    adv->setSenderSpeed(speed);
    adv->setSenderPos(position);
    adv->setSenderDirection(direction);
    adv->setSenderDestination(destination.c_str());
    adv->setSimTime(time);
}

void MyVeinsApp::handlePositionUpdate(cObject* obj)
{
    ECODEBaseApplLayer::handlePositionUpdate(obj);

    id = mobility->getId();
    speed = mobility->getSpeed();
    position = mobility->getPositionAt(simTime());
    direction = mobility->getCurrentDirection();
    destination = traciVehicle->getPlannedRoadIds().back();
    time = simTime();

    if (time - lastSentADV > 2.0)
    {
        lastSentADV = time;
        std::cout << mobility->getId() << " enviando ADV!" << std::endl;
        ADVMessage* adv = new ADVMessage();
        populateWSM(adv);
        populateADV(adv);
        sendDown(adv);
        std::cout << destination << std::endl;
    }



}
