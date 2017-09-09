#ifndef DEBUG    /* Guard against multiple inclusion */
#define DEBUG

#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
    
void dbgOutputVal(unsigned char outVal);

void dbgUARTVal(unsigned char outVal);

void dbgOutputLoc(unsigned char outVal);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
