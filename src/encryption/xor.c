#include "Windows.h"
#include <stdio.h>


void xor_single_byte_key(IN PBYTE p_shellcode, IN SIZE_T s_shellcode_size, IN  BYTE key){
    for (size_t i = 0; i < s_shellcode_size; i++){
        p_shellcode[i] = p_shellcode[i] ^ key;
    }
}


void xor_multi_byte_key(IN PBYTE p_shellcode, IN SIZE_T s_shellcode_size, IN  PBYTE key, IN SIZE_T key_size){
    for (size_t i = 0, j = 0; i < s_shellcode_size; i++, j++){
        if (j >= key_size){
            j = 0;
        }
        p_shellcode[i] = p_shellcode[i] ^ key[j];
    }
}