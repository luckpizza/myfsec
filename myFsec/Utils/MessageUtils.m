//
//  MessageUtils.m
//  myFsec
//
//  Created by Lucas Pizzagalli on 04/08/12.
//
//

#import "MessageUtils.h"
#import "StateCodes.h"
@implementation MessageUtils

+(NSString *) getEncodeMessage:(int) msgCode
{
    NSString * retMsg = @"ERROR";
    switch (msgCode) {
        case DECODED:
            retMsg = NSLocalizedStringFromTable (DECODE_MSG, @"Localizable", @"A comment");
            break;
        case ENCODED:
            retMsg = NSLocalizedStringFromTable (ENCODED_MSG, @"Localizable", @"A comment");
            break;
        case  ERROR_NOT_SUPPORTED:
            retMsg =  NSLocalizedStringFromTable (ERROR_NOT_SUPPORTED_MSG, @"Custom", @"A comment");
            break;
        case ERROR_WRONG_PASSWORD:
            retMsg =  NSLocalizedStringFromTable (ERROR_WRONG_PASSWORD_MSG, @"Custom", @"A comment");
            break;
        case ERROR_FILE_DOES_NOT_EXIST:
            retMsg = NSLocalizedStringFromTable (ERROR_FILE_DOES_NOT_EXIST_MSG, @"Custom", @"A comment");
            break;
        case ERROR_PASSWORDS_DONT_MATCH:
            retMsg = NSLocalizedStringFromTable (ERROR_PASSWORDS_DONT_MATCH_MSG, @"Custom", @"A comment");
            break;
        case ERROR:
            retMsg = NSLocalizedStringFromTable (ERROR_MSG, @"Localizable", @"A comment");
            break;
        case ERROR_NOT_SUPPORTED_ENCRYPTION:
            retMsg = NSLocalizedStringFromTable (ERROR_NOT_SUPPORTED_ENCRYPTION_MSG, @"Localizable", @"A comment");
            break;
        case  ERROR_NOT_SUPPORTED_VERSION:
            retMsg =  NSLocalizedStringFromTable (ERROR_NOT_SUPPORTED_VERSION_MSG, @"Custom", @"A comment");
            break;
        case ERROR_PASSWORD:
            retMsg =  NSLocalizedStringFromTable (ERROR_PASSWORD_MSG, @"Custom", @"A comment");
            break;
        case ERROR_APPLICATION_BUSSY:
            retMsg = NSLocalizedStringFromTable (ERROR_APPLICATION_BUSSY_MSG, @"Custom", @"A comment");
            break;
        case ERROR_UNKNOWN:
            retMsg = NSLocalizedStringFromTable (ERROR_UNKNOWN_MSG, @"Custom", @"A comment");
            break;
        case ERROR_CHOOSE_A_FILE:
            retMsg = NSLocalizedStringFromTable (ERROR_CHOOSE_A_FILE_MSG, @"Localizable", @"A comment");
            break;
        case CANCEL_PROCESS:
            retMsg = NSLocalizedStringFromTable (CANCEL_PROCESS_MSG, @"Localizable", @"A comment");
            break;
        case  ERROR_READING_FILE:
            retMsg =  NSLocalizedStringFromTable (ERROR_READING_FILE_MSG, @"Custom", @"A comment");
            break;
        default:
            break;
    }
    return retMsg;
    
}
@end
