//
//  DynamicProgrammingLCS.h
//  LCS
//
//  Created by Sun Kai on 5/11/14.
//  Copyright (c) 2014 Sun Kai. All rights reserved.
//

#ifndef LCS_DynamicProgrammingLCS_h
#define LCS_DynamicProgrammingLCS_h

// Copy from http://www.geeksforgeeks.org/longest-common-substring/
/* Returns length of longest common substring of X[0..m-1] and Y[0..n-1] */
std::size_t LCSubStr(const char *X, const char *Y, std::size_t m, std::size_t n)
{
    // Create a table to store lengths of longest common suffixes of
    // substrings.   Notethat LCSuff[i][j] contains length of longest
    // common suffix of X[0..i-1] and Y[0..j-1]. The first row and
    // first column entries have no logical meaning, they are used only
    // for simplicity of program
    std::size_t LCSuff[m+1][n+1];
    std::size_t result = 0;  // To store length of the longest common substring
    
    /* Following steps build LCSuff[m+1][n+1] in bottom up fashion. */
    for (std::size_t i=0; i<=m; i++)
    {
        for (std::size_t j=0; j<=n; j++)
        {
            if (i == 0 || j == 0)
                LCSuff[i][j] = 0;
            
            else if (X[i-1] == Y[j-1])
            {
                LCSuff[i][j] = LCSuff[i-1][j-1] + 1;
                result = std::max(result, LCSuff[i][j]);
            }
            else LCSuff[i][j] = 0;
        }
    }
    return result;
}

// Copy from http://www.geeksforgeeks.org/longest-common-substring/
/* Returns length of longest common substring of X[0..m-1] and Y[0..n-1] */
std::size_t LCSubStr_EX(const char *X, const char *Y, std::size_t m, std::size_t n, std::size_t *subStringStart)
{
    // Create a table to store lengths of longest common suffixes of
    // substrings.   Notethat LCSuff[i][j] contains length of longest
    // common suffix of X[0..i-1] and Y[0..j-1]. The first row and
    // first column entries have no logical meaning, they are used only
    // for simplicity of program
    std::size_t LCSuff[m+1][n+1];
    std::size_t result = 0;  // To store length of the longest common substring
    *subStringStart = 0;

    /* Following steps build LCSuff[m+1][n+1] in bottom up fashion. */
    for (std::size_t i=0; i<=m; i++)
    {
        for (std::size_t j=0; j<=n; j++)
        {
            if (i == 0 || j == 0)
            {
                LCSuff[i][j] = 0;
            }
            else if (X[i-1] == Y[j-1])
            {
                LCSuff[i][j] = LCSuff[i-1][j-1] + 1;
                if (result < LCSuff[i][j]) {
                    result = LCSuff[i][j];
                    *subStringStart = i - result;
//                    printf("%lu\n", result);
//                    for (size_t idx = *subStringStart; idx < *subStringStart + result; ++idx) {
//                        printf("%c", X[idx]);
//                    }
//                    printf("\n");
                }
            }
            else  {
                LCSuff[i][j] = 0;
            }
        }
    }
    return result;
}

// http://www.cnblogs.com/ider/p/longest-common-substring-problem-optimization.html
// Two rolling buffer, space complexity = 2 * (n + 1)
std::size_t LCSubStr_EX2(const char *X, const char *Y, std::size_t m, std::size_t n, std::size_t *subStringStart)
{
    std::size_t *LCSuff = new std::size_t[n + 1];
    std::size_t *LCSuff_S = new std::size_t[n + 1];
    memset(LCSuff, 0, (n + 1) * sizeof(std::size_t));
    memset(LCSuff_S, 0, (n + 1) * sizeof(std::size_t));
    
    std::size_t result = 0;  // To store length of the longest common substring
    *subStringStart = 0;
    
    for (std::size_t i = 0; i < m; ++i)
    {
        for (std::size_t j = 1; j <= n; ++j)
        {
            if (X[i] == Y[j - 1])
            {
                LCSuff[j] = LCSuff_S[j-1] + 1;
                if (result < LCSuff[j]) {
                    result = LCSuff[j];
                    *subStringStart = i + 1 - result;
                }
            }
            else  {
                LCSuff[j] = 0;
            }
        }
        
        using std::swap;
        swap(LCSuff_S, LCSuff);
    }
    
    delete [] LCSuff;
    delete [] LCSuff_S;
    
    return result;
}

// http://www.cnblogs.com/ider/p/longest-common-substring-problem-optimization.html
// One buffer plus two temp variables, space complexity = n + 1 + 2
std::size_t LCSubStr_EX3(const char *X, const char *Y, std::size_t m, std::size_t n, std::size_t *subStringStart)
{
    std::size_t LCSuff[n + 1];
    memset(LCSuff, 0, (n + 1) * sizeof(std::size_t));
    
    std::size_t result = 0;  // To store length of the longest common substring
    *subStringStart = 0;
    
    for (std::size_t i = 0; i < m; ++i)
    {
        std::size_t lastTmpVal = 0;
        for (std::size_t j = 1; j <= n; ++j)
        {
            std::size_t currentTmpVal;
            if (X[i] == Y[j - 1])
            {
                currentTmpVal = LCSuff[j - 1] + 1;
                if (result < currentTmpVal) {
                    result = currentTmpVal;
                    *subStringStart = i + 1 - result;
                }
            }
            else  {
                currentTmpVal = 0;
            }
            
            LCSuff[j - 1] = lastTmpVal;
            lastTmpVal = currentTmpVal;
        }
    }
    
    return result;
}


#endif
