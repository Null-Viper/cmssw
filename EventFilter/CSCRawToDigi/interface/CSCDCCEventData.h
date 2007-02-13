/// 01/20/05 A.Tumanov

#ifndef CSCDCCEventData_h
#define CSCDCCEventData_h

#include <vector>
#include "EventFilter/CSCRawToDigi/interface/CSCDDUEventData.h"
#include "EventFilter/CSCRawToDigi/interface/CSCDCCHeader.h"
#include "EventFilter/CSCRawToDigi/interface/CSCDCCTrailer.h"

class BitVector;

class CSCDCCEventData {
public:
  CSCDCCEventData(int sourceId, int nDDUs, int bx, int l1a);
  /// buf may need to stay pinned in memory as long
  /// as this data is used.  Not sure
  explicit CSCDCCEventData(unsigned short *buf);

  ~CSCDCCEventData();

  static void setDebug(bool value) {debug = value;} 
 
  /// accessor to dduData
  const std::vector<CSCDDUEventData> & dduData() const {return theDDUData;}
  std::vector<CSCDDUEventData> & dduData() {return theDDUData;}

  CSCDCCHeader dccHeader() const {return theDCCHeader;}
  CSCDCCTrailer dccTrailer() const {return theDCCTrailer;}


  /// for making events.  Sets the bxnum and lvl1num inside the chamber event
  //void add(CSCEventData &);

  bool check() const;

  /// prints out the error associated with this status 
  /// from the header or trailer
  int sizeInWords() const {return theSizeInWords;}

  BitVector pack();  

  static bool debug;


protected:
  void unpack_data(unsigned short * buf);
  CSCDCCHeader theDCCHeader;
  // DDUData is unpacked and stored in this vector
  std::vector<CSCDDUEventData> theDDUData;
  CSCDCCTrailer theDCCTrailer;
  int theSizeInWords;
};

#endif
