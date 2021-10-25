//
// Generated file, do not edit! Created by nedtool 5.7 from veins/modules/messages/DemoSafetyMessage.msg.
//

#ifndef __VEINS_DEMOSAFETYMESSAGE_M_H
#define __VEINS_DEMOSAFETYMESSAGE_M_H

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
#include "veins/base/utils/Coord.h"
#include "veins/modules/messages/BaseFrame1609_4_m.h"
#include "veins/base/utils/SimpleAddress.h"
// }}


namespace veins {

/**
 * Class generated from <tt>veins/modules/messages/DemoSafetyMessage.msg:35</tt> by nedtool.
 * <pre>
 * packet DemoSafetyMessage extends BaseFrame1609_4
 * {
 *     Coord senderPos;
 *     Coord senderSpeed;
 * }
 * </pre>
 */
class VEINS_API DemoSafetyMessage : public ::veins::BaseFrame1609_4
{
  protected:
    Coord senderPos;
    Coord senderSpeed;

  private:
    void copy(const DemoSafetyMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const DemoSafetyMessage&);

  public:
    DemoSafetyMessage(const char *name=nullptr, short kind=0);
    DemoSafetyMessage(const DemoSafetyMessage& other);
    virtual ~DemoSafetyMessage();
    DemoSafetyMessage& operator=(const DemoSafetyMessage& other);
    virtual DemoSafetyMessage *dup() const override {return new DemoSafetyMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual Coord& getSenderPos();
    virtual const Coord& getSenderPos() const {return const_cast<DemoSafetyMessage*>(this)->getSenderPos();}
    virtual void setSenderPos(const Coord& senderPos);
    virtual Coord& getSenderSpeed();
    virtual const Coord& getSenderSpeed() const {return const_cast<DemoSafetyMessage*>(this)->getSenderSpeed();}
    virtual void setSenderSpeed(const Coord& senderSpeed);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const DemoSafetyMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, DemoSafetyMessage& obj) {obj.parsimUnpack(b);}

} // namespace veins

#endif // ifndef __VEINS_DEMOSAFETYMESSAGE_M_H

