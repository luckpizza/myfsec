//
//  StateCodes.h
//  myfsec
//
//  Created by Lucas Pizzagalli on 5/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef myfsec_StateCodes_h
#define myfsec_StateCodes_h

#define DECODED 3
#define OK 1
#define FILE_EXIST 4
#define ENCODED 2
#define ERROR -1  //todo: error msg
#define ERROR_NOT_SUPPORTED -5
#define ERROR_WRONG_PASSWORD -2
#define ERROR_FILE_DOES_NOT_EXIST -3
#define ERROR_PASSWORDS_DONT_MATCH -4
#define ERROR_NOT_SUPPORTED_ENCRYPTION -6 //todo:error msg
#define ERROR_NOT_SUPPORTED_VERSION -7 //todo:msg
#define ERROR_PASSWORD -8 //TODO: MSG
#define ERROR_APPLICATION_BUSSY -9
#define FSEC_EXTENTION ".myfsec"


#define  DECODE_MSG @"File Decoded Succesful!!"
#define  ENCODED_MSG @"File Encoded Successfully!!"
#define  ERROR_NOT_SUPPORTED_MSG @"File is not encoded buy us, choos another file!"
#define  ERROR_WRONG_PASSWORD_MSG @"Wrong password!"
#define  ERROR_FILE_DOES_NOT_EXIST_MSG @"The file does not exist or can't be open!"
#define  ERROR_PASSWORDS_DONT_MATCH_MSG @"Passwords don't match, please verify your password"


#endif
