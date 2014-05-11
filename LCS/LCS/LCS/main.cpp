//
//  main.cpp
//  LCS
//
//  Created by Sun Kai on 5/11/14.
//  Copyright (c) 2014 Sun Kai. All rights reserved.
//

#include <iostream>
#include "DynamicProgrammingLCS.h"

#define MAXLEN 1024

using namespace std;

int main(int argc, const char * argv[])
{
    const char *str1 = "Thelongestcommonsubstringproblemisaclassicprobleminstringanalysis.";
    const char *str2 = "Thisisavariantoflongestcommonsubstring";

    size_t subStringLen = LCSubStr(str1, str2, strlen(str1), strlen(str2));
    cout << subStringLen << endl;
    
    size_t subStringStart = 0;
    subStringLen = LCSubStr_EX(str1, str2, strlen(str1), strlen(str2), &subStringStart);
    if (subStringLen > 0) {
        char subStringBuffer[MAXLEN];
        snprintf(subStringBuffer, subStringLen + 1, "%s", (str1 + subStringStart));
        cout << subStringBuffer << endl;
    }
    
    subStringStart = 0;
    subStringLen = LCSubStr_EX2(str1, str2, strlen(str1), strlen(str2), &subStringStart);
    if (subStringLen > 0) {
        char subStringBuffer[MAXLEN];
        snprintf(subStringBuffer, subStringLen + 1, "%s", (str1 + subStringStart));
        cout << subStringBuffer << endl;
    }
    
    subStringLen = LCSubStr_EX3(str1, str2, strlen(str1), strlen(str2), &subStringStart);
    if (subStringLen > 0) {
        char subStringBuffer[MAXLEN];
        snprintf(subStringBuffer, subStringLen + 1, "%s", (str1 + subStringStart));
        cout << subStringBuffer << endl;
    }

    
    return 0;
}

