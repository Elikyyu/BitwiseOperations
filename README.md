# BitwiseOperations
Simple exercice program en C to apply bitwise operations to two numbers up to 64 bits

Created by Eric RIOUALEC LEFEUVRE on 06/01/2023.

Finished and uploaded on 2023-01-6 on Sololearn
Early bits of code reused from old 2014-06-28 project

Simple purpose of this simple app :

Given 2 unsigned integers A and B as an input (in supposed BITS as any sequence of 0 and 1)
output their value in decimal/hexa and apply main bitwise operations ( & | ^ )
to themselves (A and B) as well as their strict opposites (~A and ~B)

User input is considered as follows :
   => 0 and 1 stand for themselves (ZERO and ONE)
   => any number over 1 stands for ONE
   => anything else stands for ZERO

The app is designed to work with unsigned 64 bits integers, however for convenience
(and test purpose) if your input needs less bytes, the output will be adapted so that
the only useful number of bytes are keeped and outputed !

For coherence, the bitwise NOT operation will be done only on the respective bytes outputed
using a mask, so it can make a big difference !

If you want full resuts, you should enter full bit sequence :

 * 37  submitted as the following input :
       100101
       will be computed using a single byte (8 bit mask)

 * 255 submitted as the following input :
       0000 00000000 00000000 11111111
       will be computed using four bytes (32 bit mask)

  * 3  submitted as the following input :
       00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000011
       will be computed using full eight bytes (no mask)

Whitespaces are automatically trimmed so you can add some or not, to your own convenience
(up to 20 chars)

Have fun and if any, please submit bug reports !

END DOC
