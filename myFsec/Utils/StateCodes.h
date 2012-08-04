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
#define ERROR -1
#define ERROR_NOT_SUPPORTED -5
#define ERROR_WRONG_PASSWORD -2
#define ERROR_FILE_DOES_NOT_EXIST -3
#define ERROR_PASSWORDS_DONT_MATCH -4
#define ERROR_NOT_SUPPORTED_ENCRYPTION -6
#define ERROR_NOT_SUPPORTED_VERSION -7 
#define ERROR_PASSWORD -8 
#define ERROR_APPLICATION_BUSSY -9 
#define ERROR_UNKNOWN -10 
#define ERROR_CHOOSE_A_FILE -11 
#define CANCEL_PROCESS -12 
#define ERROR_READING_FILE -13 
#define FSEC_EXTENTION ".myfsec"


#define DECODE_MSG @"File Decoded Succesful!!"
#define ENCODED_MSG @"File Encoded Successfully!!"
#define ERROR_NOT_SUPPORTED_MSG @"File is not encoded buy us, choos another file!"
#define ERROR_WRONG_PASSWORD_MSG @"Wrong password!"
#define ERROR_FILE_DOES_NOT_EXIST_MSG @"The file does not exist or can't be open!"
#define ERROR_PASSWORDS_DONT_MATCH_MSG @"Passwords don't match, please verify your password"

#define ERROR_MSG @"ERROR"
#define ERROR_NOT_SUPPORTED_ENCRYPTION_MSG @"Not supported encryption type"
#define ERROR_NOT_SUPPORTED_VERSION_MSG @"The file is not supported by this program, try upgrading!!"
#define ERROR_PASSWORD_MSG @"Try with a different password!"
#define ERROR_APPLICATION_BUSSY_MSG @"Application is Bussy, please try again later"
#define ERROR_UNKNOWN_MSG @"Sorry, an unknown error happend!"
#define ERROR_CHOOSE_A_FILE_MSG @"Please choose a file!"
#define CANCEL_PROCESS_MSG @"Process has been canceled!"
#define ERROR_READING_FILE_MSG @"Error while reading file, make sure you have the rights to read it"

#endif
