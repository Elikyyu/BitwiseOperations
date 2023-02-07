//
//  main.c
//  BitwiseOp
//
//  Created by Eric LEFEUVRE on 06/01/2023.
//  Copyright (c) 2023 Eric LEFEUVRE. All rights reserved.
//

/*  Author : Eric LEFEUVRE
    Finished and uploaded on 2023-01-6 on Sololearn
    Early bits of code reused from old 2014-06-28 project

    * * Simple purpose of this simple app :
    *
    * Given 2 unsigned integers A and B as an input
    * (in supposed BITS as any sequence of 0 and 1)
    * output their value in decimal/hexa and apply main
    * bitwise operations ( & | ^ ) to themselves (A and B)
    * as well as their strict opposites (~A and ~B)
    *
    * User input is considered as follows :`
    *   => 0 and 1 stand for themselves (ZERO and ONE)
    *   => any number over 1 stands for ONE
    *   => anything else stands for ZERO
    *
    * The app is designed to work with unsigned 64 bits integers,
    * however for convenience (and test purpose) if your input
    * needs less bytes, the output will be adapted so that the
    * only useful number of bytes are keeped and outputed !
    *  
    * For coherence, the bitwise NOT operation will be done
    * only on the respective bytes outputed using a mask,
    * so it can make a big difference !
    *
    * If you want full resuts, you should enter full bit sequence :
    *
    *   37  submitted as the following input :
    *       100101
    *       will be computed using a single byte (8 bit mask)
    *
    *   255 submitted as the following input :
    *       0000 00000000 00000000 11111111
    *       will be computed using four bytes (32 bit mask)
    *
    *   3  submitted as the following input :
    *       00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000011
    *       will be computed using full eight bytes (no mask)
    *
    * Whitespaces are automatically trimmed so you can add
    * some or not, to your own convenience (up to 20 chars)
    *
    * Have fun and if any, please submit bug reports !
    *
    * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define DEFAULT_A "00000000 00000000 00000000 00000000 00110000 00000000 00000000 11111100"
//"qw 0  00000\t0000000 0 0 0000000 11111   111    "
//"z100010"
#define DEFAULT_B "110000 00000000 00000000 11111111"
//"  az e1zer5e   rzt87 dfg5   \r\n"
//"az23ez352qsd7"
#define SIZECHAR_UINT64 64
#define SIZESTR_UINT64 SIZECHAR_UINT64+21

void trim_input(char * str, uint8_t max)
{
    char * p2 = str, c;
        
    for ( int i = 0 ; i < max ; i++ )
    {
        c = *(str+i);
        
        switch (c)
        {
            case '\0': case '\r': case '\n':
                *p2 = '\0';
                return;
            
            case '\t': case ' ':
                continue;
            
            default:
                *(p2++) = c;
        }
    }
}

char binchar(char c)
{
    char r = c;

    switch (c)
    {
        case '0': case '1':
            break;
        case '\0': case '\r': case '\n':
            r = '\0';
            break;
        case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9':
            r = '1';
            break;
        default:
            r = '0';
    }
    
    return r;
}

char * bins_corr(char * s)
{
    int i = 0;

    while (s[i] != '\0') { s[i] = binchar(s[i]); i++; }

    return s;
}

char bins_check(char * s)
{
    int i = 0;

    while (s[i] != '\0') {
        if (s[i] != binchar(s[i])) return 0;
        i++; }

    return 1;
}

void mgetbins(char * s, int size)
{
    fgets(s, size, stdin);
}

uint64_t bitconv(char * s)
{
    uint64_t b = 1;
    uint64_t res = 0;
    
    for (int8_t i = strlen(s) - 1 ; i >= 0 ; i--)
    {
        /* ASCII 48 => '0' ; ASCII 49 => '1' */
        res += (s[i] - 48) * b;
        b <<= 1;
        /* trace for debug checkup only,
           you may uncomment if you like it verbose !
            printf("c[%c] b[%llu] >> %llu\t%llu\n", s[i], b, (s[i] - 48) * b, res); */
    }
    
    return res;
}

char * s_zerofill(char * s, uint8_t * size, uint8_t dest)
{
    uint8_t d = dest - *size;
    
    for ( int8_t i = dest + 1 ; i >= 0 ; i-- )
        s[i] = (i-d >=0) ? s[i-d] : '0';
    
    *size = dest;
    
    return s;
}

char * old_aff_bin(uint8_t x)
{
    char * strbyte = malloc(9 * sizeof(unsigned char));
    
    if (strbyte == NULL)
    {
        perror("sbyte");
        exit(-1);
    }
    
    for (char i = 0 ; i < 8 ; i++)
    {
        strbyte[7-i] = (x & (1 << i)) ? '1' : '0';
    }
    
    strbyte[8] = '\0';
    
    return strbyte;
}

char * old_aff_lbin(uint64_t x, uint8_t bytes)
{
    uint8_t * p_byte = (uint8_t *)&x;
    char * tc[bytes];
    
    char * strbin = malloc( 9 * bytes * sizeof(unsigned char));
    
    if (strbin == NULL)
    {
        perror("sbin");
        exit(-1);
    }
    
    for (uint8_t i = 0 ; i < bytes ; i++)
    {
        tc[i] = old_aff_bin(*(p_byte + i));
    }
    
    switch (bytes)
    {
        case 1 :
            sprintf(strbin, "%s\n", tc[0]);
            break;
        case 2 :
            sprintf(strbin, "%s %s\n", tc[1], tc[0]);
            break;         
        case 3 :
            sprintf(strbin, "%s %s %s\n", tc[2], tc[1], tc[0]);
            break;
        case 4 :
            sprintf(strbin, "%s %s %s %s\n", tc[3], tc[2], tc[1], tc[0]);
            break;
        case 5 :
            sprintf(strbin, "%s %s %s %s %s\n", tc[4], tc[3], tc[2], tc[1], tc[0]);
            break;
        case 6 :
            sprintf(strbin, "%s %s %s %s %s %s\n", tc[5], tc[4], tc[3], tc[2], tc[1], tc[0]);
            break;
        case 7 :
            sprintf(strbin, "%s %s %s %s %s %s %s\n", tc[6], tc[5], tc[4], tc[3], tc[2], tc[1], tc[0]);
            break;
        case 8 :
            sprintf(strbin, "%s %s %s %s %s %s %s %s\n", tc[7], tc[6], tc[5], tc[4], tc[3], tc[2], tc[1], tc[0]);
            break;
    }
    
    for (uint8_t i = 0 ; i < bytes ; i++) free(tc[i]);
    
    return strbin;
}

void print_bin_byte(uint8_t x, char * str_p)
{
    for (char i = 0 ; i < 8 ; i++)
    {
        /* printing from left to right : higher bits => lower bits */
        *(str_p + (7-i)) = (x & (1 << i)) ? '1' : '0';
    }
    
    *(str_p + 8) = ' ';
}

char * print_lbin(uint64_t x, uint8_t bytes)
{
    uint8_t * p_byte = (uint8_t *)&x;
    
    char * strbin = malloc( 9 * bytes * sizeof(unsigned char));
    
    if (strbin == NULL)
    {
        perror("sbin");
        exit(-1);
    }
    
    for (uint8_t i = 0 ; i < bytes ; i++)
    {
        /* printing from left to right : higher bytes => lower bytes */
        print_bin_byte(*(p_byte + i), (strbin+(bytes-i-1)*9));
    }
    
    *(strbin+bytes*9-1) = '\0';
    
    return strbin;
}

void number_detail (char *c, uint64_t num, uint8_t len)
{
    char * strt = print_lbin(num, len);
    
    printf("%s >>\tHex : 0x%llx\n", c, num);
    printf("%s >>\tNum : %llu\n", c, num);
    printf("%s >>\tBin : %s\n", c, strt);
    
    free(strt);
}

void do_bitwiseop_for(uint64_t a, uint64_t b, char *ref_a, char *ref_b, uint8_t len_a, uint8_t len_b)
{
    uint64_t c = a | b;
    uint64_t d = a & b;
    uint64_t e = a ^ b;
    char *var_a, *var_b, *var_c, *var_d, *var_e;
    
    var_a = malloc(6 * sizeof(char));
    var_b = malloc(6 * sizeof(char));
    var_c = malloc(9 * sizeof(char));
    var_d = malloc(9 * sizeof(char));
    var_e = malloc(9 * sizeof(char));
    
    if (var_a == NULL || var_b == NULL || var_c == NULL || var_d == NULL || var_e == NULL)
    {
        perror("sbin");
        exit(-1);
    }
    
    sprintf(var_a, "{%s} \t\t", ref_a);
    sprintf(var_b, "{%s} \t\t", ref_b);
    sprintf(var_c, "{%s | %s} \t", ref_a, ref_b);
    sprintf(var_d, "{%s & %s} \t", ref_a, ref_b);
    sprintf(var_e, "{%s ^ %s} \t", ref_a, ref_b);
    
    uint8_t len_ab = len_a >= len_b ? len_a : len_b;
    
    number_detail(var_a, a, len_a);
    number_detail(var_b, b, len_b);
    number_detail(var_c, c, len_ab);
    number_detail(var_d, d, len_ab);
    number_detail(var_e, e, len_ab);
    
    free(var_a);
    free(var_b);
    free(var_c);
    free(var_d);
    free(var_e);
}

void prep_bitwiseop_for(uint64_t v1, uint64_t v2, char *ref1, char *ref2, uint8_t mask_size1, uint8_t mask_size2)
{
    printf("First pass :\n\n");
    
    do_bitwiseop_for (v1, v2, ref1, ref2, mask_size1 / 8, mask_size2 / 8);
    
    v1 = ~v1;
    v2 = ~v2;
    
    if ( mask_size1 < 64 )
    {
        // number_detail("~a", v1, 8); // full inversion on 64 bits
        v1 <<= (64-mask_size1);
        // number_detail("~a", v1, 8); // bitwise move to apply mask
        v1 >>= (64-mask_size1);
        // number_detail("~a", v1, 8); // bitwise restore to get result
    }
    
    if ( mask_size2 < 64 )
    {
        // number_detail("~b", v2, 8); // full inversion on 64 bits
        v2 <<= (64-mask_size2);
        // number_detail("~b", v2, 8); // bitwise move to apply mask
        v2 >>= (64-mask_size2);
        // number_detail("~b", v2, 8); // bitwise restore to get result
    }
    
    printf("Second pass :\n\n");
    
    char ref_i1[3], ref_i2[3];
    
    sprintf(ref_i1, "~%s", ref1);
    sprintf(ref_i2, "~%s", ref2);
    
    do_bitwiseop_for (v1, v2, ref_i1, ref_i2, mask_size1 / 8, mask_size2 / 8);
}

int main(int argc, const char * argv[])
{
    char str1[SIZESTR_UINT64] = "", str2[SIZESTR_UINT64] = "";

	printf("\n\n<Input first number {A} >");
	//mgetbins(str1, SIZESTR_UINT64);
    
	printf("\n\n<Input second number {B} >");
	//mgetbins(str2, SIZESTR_UINT64);
    
	printf("\n\nYou entered :");
	printf("\n\nString {A} : %s\nString {B} : %s\n", str1, str2);

    uint8_t len1 = strlen(str1), len2 = strlen(str2);

    if (!len1 || (len1 == 1 && str1[0] == '\n'))
    {
        printf("\n* * * Empty value for {A} * * *\n");
        strcpy(str1, DEFAULT_A);
        printf("\nAssuming default value {A} = \"%s\"\n",str1);
    }
    
    if (!len2 || (len2 == 1 && str2[0] == '\n'))
    {
        printf("\n* * * Empty value for {B} * * *\n");
        strcpy(str2, DEFAULT_B);
        printf("\nAssuming default value {B} = \"%s\"\n",str2);
    }
    
    printf("\n* * * Trimming input if necessary * * *\n");
    
    trim_input(str1,SIZESTR_UINT64);
	    printf("\nTrimmed input {A} : %s\n", str1);
    
    trim_input(str2,SIZESTR_UINT64);
	    printf("\nTrimmed input {B} : %s\n", str2);

    printf("\n* * * Checking non-binary characters in the intput * * *\n");

    if (!bins_check(str1))
	    printf("\nAdapted string {A} : %s\n", bins_corr(str1));
    
    if (!bins_check(str2))
	    printf("\nAdapted string {B} : %s\n", bins_corr(str2));
    
    printf("\n* * * Extending strings to the closest byte size * * *\n");
    
    len1 = strlen(str1);
    if ( len1 % 8 )
	    printf("\nFinal binary {A} : %s\n",s_zerofill(str1, &len1, len1 + (8 - len1 % 8)));
    else
	    printf("\nFinal binary {A} : %s\n",str1);
    
    len2 = strlen(str2);
    if ( len2 % 8 )
	    printf("\nFinal binary {B} : %s\n",s_zerofill(str2, &len2, len2 + (8 - len2 % 8)));
    else
	    printf("\nFinal binary {B} : %s\n",str2);
    
    printf("\n* * * Final binary size taken for computing * * *\n");
    
    printf("\nBinary length {A} : %d", len1);
    printf("\nBinary length {B} : %d\n", len2);
    
    printf("\n* * * Starting bitwise operations * * *\n\n");
    
    uint64_t v1 = bitconv(str1);
    uint64_t v2 = bitconv(str2);
    
    prep_bitwiseop_for(v1, v2, "A", "B", len1, len2);
    
    printf("Thanks for testing !\n");
    
	return 0;
}
