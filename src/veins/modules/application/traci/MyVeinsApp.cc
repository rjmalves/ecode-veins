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
}

void MyVeinsApp::onWSM(BaseFrame1609_4* frame)
{
    TraCIDemo11pMessage* wsm = check_and_cast<TraCIDemo11pMessage*>(frame);
    if (mobility->getRoadId()[0] != ':')
    {
        traciVehicle->changeRoute(wsm->getDemoData(), 9999);
    }
    if (!sentMessage)
    {
        sentMessage = true;
        // repeat the received traffic update once in 2 seconds plus some random delay
        wsm->setSenderAddress(myId);
        wsm->setSerial(3);
        scheduleAt(simTime() + 2 + uniform(0.01, 0.2), wsm->dup());
    }
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

void MyVeinsApp::handlePositionUpdate(cObject* obj)
{
    ECODEBaseApplLayer::handlePositionUpdate(obj);

    std::cout << mobility->getId() << " se moveu!" << std::endl;
    // stopped for for at least 10s?
    if (mobility->getSpeed() < 1)
    {
        if (simTime() - lastDroveAt >= 10 && sentMessage == false)
        {
            sentMessage = true;

            TraCIDemo11pMessage* wsm = new TraCIDemo11pMessage();
            populateWSM(wsm);
            wsm->setDemoData(mobility->getRoadId().c_str());
            std::cout << "Criei: " << mobility->getId() << ": " << wsm->getDemoData() << std::endl;

            // host is standing still due to crash
            
            // send right away on CCH, because channel switching is disabled
            sendDown(wsm);
            
        }
    }
    else
    {
        lastDroveAt = simTime();
        sentMessage = false;
    }
}
