
#define PRINT_FLAG_HEX  0x01

void DWordToStr(U32 dwVal, U8* acStrBuf, U8 ucFlag )
{
    U8 i;
    char c;
    bit bHex = 0;
    U32 dwDivider;
    bit bNotZero = 0;

    if( dwVal == 0 )
    {
        acStrBuf[0] = '0';
        acStrBuf[1] = 0;
        return;
    }

    if( ucFlag&PRINT_FLAG_HEX ) // 16秈
        bHex = TRUE;

    i = 0;
    if( bHex )
        dwDivider = 0x10000000;
    else
        dwDivider = 1000000000;

#if 1
    for( ; dwDivider; )
    {
        c = dwVal/dwDivider;
        if( c )
            bNotZero = 1;

        if( bNotZero )
        {
            if( c > 9 )
                acStrBuf[i] = c - 10 + 'A';
            else
                acStrBuf[i] = c + '0';
            ++ i;
        }
        dwVal = dwVal%dwDivider;

        if( bHex )
            dwDivider /= 0x10;
        else
            dwDivider /= 10;
    }
    acStrBuf[i] = 0;

#endif
}

void printU32(U32 dwVal, U8 ucFlag)
{
    U8 acStrBuf[11];
    U8 i;

    DWordToStr( dwVal, acStrBuf, ucFlag );
    for( i = 0; acStrBuf[i]!=0; ++ i )
        uart_putc(acStrBuf[i]);
}






void printf_U32(char *pFmt, U32 dwVal)
{
    U8 ucBff;

    //if( 0 == g_UART_bEnablePrint )
    //    return;

#if 1
    //while( ucBff = *(pFmt++) )
    while(1)
    {
        ucBff = *(pFmt++);
        if( ucBff == 0 )
            break;

        if( ucBff == '%' ) // check special case
        {
            switch( *(pFmt++) ) // check next character
            {
                case 'x': // hexadecimal number
                case 'X':
                    printU32(dwVal, PRINT_FLAG_HEX);
                    break;
                case 'd': // decimal number
                case 'i':
                case 'u':
                //case 'U':
                    printU32(dwVal,0);
                    break;

                case 'U':
                    printU32(dwVal,0);
                    //putstr("(0x");
                    uart_putc('(');
                    uart_putc('0');
                    uart_putc('x');
                    printU32(dwVal, PRINT_FLAG_HEX);
                    uart_putc(')');
                    break;
            } // switch
        }
        /*else if( ucBff == '\r' )// general
        {}
        else if( ucBff == '\n' )
        {
            putchar('\r'); // put a character
            putchar('\n'); // put a character
        }
        else // general
        {
            putchar(ucBff); // put a character
        } */
        else
        {
            uart_putc_2(ucBff); // put a character
        }
    } // while}

#endif

}
