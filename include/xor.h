#include "Windows.h"

void xor_single_byte_key(IN PBYTE p_shellcode, IN SIZE_T s_shellcode_size, IN  BYTE key);

void xor_multi_byte_key(IN PBYTE p_shellcode, IN SIZE_T s_shellcode_size, IN  BYTE key, IN SIZE_T key_size);