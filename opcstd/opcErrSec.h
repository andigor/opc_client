/*++

Module Name:
 OpcErrSec.h

Author:
OPC Security Task Force

Revision History:
Release 1.0 08/18/00
     OPC security HRESULTs
--*/

/*
Facility Code Assignments:
  0000 to 0200 are reserved for Microsoft use 
  (although some were inadvertently used for OPC 1.0 errors). 
  0200 to 8000 are reserved for future OPC use. 
  8000 to FFFF can be vendor specific.

*/

#ifndef __OPC_ERR_SEC_H
#define __OPC_ERR_SEC_H

//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//

// TODO/dj:  Although we believe there are no current conflicts, the 
// HRESULT values need to be coordinated with those of other OPC 
// specifications.

//
// MessageId: OPC_E_PRIVATE_ACTIVE
//
// MessageText:
//
//  OPC Security: A session using private OPC credentials is already active.
//
#define OPC_E_PRIVATE_ACTIVE            ((HRESULT)0xC0040301L)

//
// MessageId: OPC_E_LOW_IMPERS_LEVEL
//
// MessageText:
//
//  OPC Security: Server requires higher impersonation level to access secured data.
//
#define OPC_E_LOW_IMPERS_LEVEL          ((HRESULT)0xC0040302L)

//
// MessageId: OPC_S_LOW_AUTHN_LEVEL
//
// MessageText:
//
//  OPC Security: Server expected higher level of package privacy.
//
#define OPC_S_LOW_AUTHN_LEVEL           ((HRESULT)0x00040303L)


#endif // __OPC_ERR_SEC_H
