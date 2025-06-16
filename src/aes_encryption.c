#include <Windows.h>
#include <stdio.h>
#include "headers/aes.h"

//#define AES128 1
//#define AES192 1
#define AES256 1



#define KEYSIZE 32
#define IVSIZE 16

BOOL PaddBuffer(IN PBYTE InputBuffer, IN SIZE_T InputBufferSize, OUT PBYTE* OutputPaddedBuffer, OUT SIZE_T* OutputPaddedSize) {

	PBYTE	PaddedBuffer        = NULL;
	SIZE_T	PaddedSize          = NULL;

	// calculate the nearest number that is multiple of 16 and saving it to PaddedSize
	PaddedSize = InputBufferSize + 16 - (InputBufferSize % 16);
	// allocating buffer of size "PaddedSize"
	PaddedBuffer = (PBYTE)HeapAlloc(GetProcessHeap(), 0, PaddedSize);
	if (!PaddedBuffer){
		return FALSE;
	}
	// cleaning the allocated buffer
	ZeroMemory(PaddedBuffer, PaddedSize);
	// copying old buffer to new padded buffer
	memcpy(PaddedBuffer, InputBuffer, InputBufferSize);
	//saving results :
	*OutputPaddedBuffer = PaddedBuffer;
	*OutputPaddedSize   = PaddedSize;

	return TRUE;
}

// AES Encryption Function, 
char* AESEncrypt(unsigned char* Data, unsigned char* Mode){

// struct needed for Tiny-AES library
	struct AES_ctx ctx;


	BYTE pKey[KEYSIZE];                             // KEYSIZE is 32 bytes
	BYTE pIv[IVSIZE];                               // IVSIZE is 16 bytes
		

	srand(time(NULL));                              // the seed to generate the key
	GenerateRandomBytes(pKey, KEYSIZE);             // generating the key bytes
	
	srand(time(NULL) ^ pKey[0]);                    // The seed to generate the IV. Use the first byte of the key to add more randomness.
	GenerateRandomBytes(pIv, IVSIZE);               // Generating the IV

	// Prints both key and IV to the console
	PrintHexData("pKey", pKey, KEYSIZE);
	PrintHexData("pIv", pIv, IVSIZE);

	// Initializing the Tiny-AES Library
	AES_init_ctx_iv(&ctx, pKey, pIv);


	// Initializing variables that will hold the new buffer base address in the case where padding is required and its size
	PBYTE	PaddedBuffer        = NULL;
	SIZE_T	PAddedSize          = NULL;

	// Padding the buffer, if required
	if (sizeof(Data) % 16 != 0){
		PaddBuffer(Data, sizeof(Data), &PaddedBuffer, &PAddedSize);
		// Encrypting the padded buffer instead
		AES_CBC_encrypt_buffer(&ctx, PaddedBuffer, PAddedSize);
		// Printing the encrypted buffer to the console
		PrintHexData("CipherText", PaddedBuffer, PAddedSize);
	}
	// No padding is required, encrypt 'Data' directly
	else {
		AES_CBC_encrypt_buffer(&ctx, Data, sizeof(Data));
		// Printing the encrypted buffer to the console
		PrintHexData("CipherText", Data, sizeof(Data));
	}
	// Freeing PaddedBuffer, if necessary
	if (PaddedBuffer != NULL){
		HeapFree(GetProcessHeap(), 0, PaddedBuffer);
	}
	system("PAUSE");
	return 0;

}


int main(int argc, char *argv){

}