//
// Generated file, do not edit! Created by nedtool 5.7 from veins/modules/messages/ADVMessage.msg.
//

#ifndef __VEINS_ADVMESSAGE_M_H
#define __VEINS_ADVMESSAGE_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0507
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif

// dll export symbol
#ifndef VEINS_API
#  if defined(VEINS_EXPORT)
#    define VEINS_API  OPP_DLLEXPORT
#  elif defined(VEINS_IMPORT)
#    define VEINS_API  OPP_DLLIMPORT
#  else
#    define VEINS_API
#  endif
#endif

// cplusplus {{
#include "veins/modules/messages/BaseFrame1609_4_m.h"
#include "veins/base/utils/SimpleAddress.h"
// }}


namespace veins {

/**
 * Class generated from <tt>veins/modules/messages/ADVMessage.msg:12</tt> by nedtool.
 * <pre>
 * packet ADVMessage extends BaseFrame1609_4
 * {
 *     int senderID;
 *     double senderSpeed;
 *     string senderEdge;
 *     string senderLane;
 *     double senderLanePosition;
 *     string senderDestination;
 *     simtime_t time;
 * }
 * </pre>
 */
class VEINS_API ADVMessage : public ::veins::BaseFrame1609_4
{
  protected:
    int senderID;
    double senderSpeed;
    ::omnetpp::opp_string senderEdge;
    ::omnetpp::opp_string senderLane;
    double senderLanePosition;
    ::omnetpp::opp_string senderDestination;
    ::omnetpp::simtime_t time;

  private:
    void copy(const ADVMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ADVMessage&);

  public:
    ADVMessage(const char *name=nullptr, short kind=0);
    ADVMessage(const ADVMessage& other);
    virtual ~ADVMessage();
    ADVMessage& operator=(const ADVMessage& other);
    virtual ADVMessage *dup() const override {return new ADVMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getSenderID() const;
    virtual void setSenderID(int senderID);
    virtual double getSenderSpeed() const;
    virtual void setSenderSpeed(double senderSpeed);
    virtual const char * getSenderEdge() const;
    virtual void setSenderEdge(const char * senderEdge);
    virtual const char * getSenderLane() const;
    virtual void setSenderLane(const char * senderLane);
    virtual double getSenderLanePosition() const;
    virtual void setSenderLanePosition(double senderLanePosition);
    virtual const char * getSenderDestination() const;
    virtual void setSenderDestination(const char * senderDestination);
    virtual ::omnetpp::simtime_t getTime() const;
    virtual void setTime(::omnetpp::simtime_t time);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ADVMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ADVMessage& obj) {obj.parsimUnpack(b);}

} // namespace veins

#endif // ifndef __VEINS_ADVMESSAGE_M_H

