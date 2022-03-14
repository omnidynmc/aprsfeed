#ifndef LIBOPENFRAME_FLAG_H
#define LIBOPENFRAME_FLAG_H

namespace openframe {
/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/

  class Flag {
    public:
      // ### Type Definitions ###
      typedef unsigned int flagType;

      Flag() { myFlags = 0; }
      virtual ~Flag() {}

      const virtual bool addFlag(const flagType addMe) {
        if (myFlags & addMe) return false;
        myFlags |= addMe;
        return true;
      } // addFlag

      inline virtual const bool removeFlag(const flagType removeMe) {
        if (!(myFlags & removeMe)) return false;
        myFlags &= ~removeMe;
        return true;
      } // removeFlag

      inline virtual const bool findFlag(const flagType findMe) const {
        return myFlags & findMe ? true : false;
      } // findFlag

      const flagType getFlags() const { return myFlags; }

    protected:
    private:
      flagType myFlags;				// Variable to store my flags.
  };

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/
} // namespace openframe
#endif
