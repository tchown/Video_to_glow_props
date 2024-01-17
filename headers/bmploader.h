#include <stdio.h>                             // So we can use fopen and fread
#include <stdlib.h>
#include <string.h>
#include <math.h>

#pragma pack(1)
struct BMPHeader // BitmapFileHeader
{
	char         bmtype[2];     // 2 bytes - 'B' 'M'
	unsigned int FileSize;     // 4 bytes
	short int    reserved1;     // 2 bytes
	short int    reserved2;     // 2 bytes
	unsigned int OffsetBits;   // 4 bytes

};// End of stBMFH structure - size of 18 bytes
#pragma pack()

#pragma pack(1)
struct BMPInfo // BitmapInfoHeader
{
	unsigned int SizeHeader;    // 4 bytes - 40
	unsigned int Width;         // 4 bytes
	unsigned int Height;        // 4 bytes
	short int    Planes;        // 2 bytes
	short int    BitDepth;      // 2 bytes
	unsigned int Compression;    // 4 bytes
	unsigned int SizeImage;     // 4 bytes
	unsigned int XPixelsPerMeter; // 4 bytes
	unsigned int YPixelsPerMeter; // 4 bytes
	unsigned int ClrUsed;       // 4 bytes
	unsigned int ClrImportant;  // 4 bytes

};// End of stBMIF structure - size 40 bytes
#pragma pack()

struct Imagest
{
	unsigned int Width;
	unsigned int Height;
};

FILE* fp;
char readbuf[2]; // Temp Buffer
unsigned int Size; // 4 Bytes
struct BMPHeader Header;
struct BMPInfo Info;
struct Imagest Image;
int NumPaddedBytes;
int NumPaddedBits;
unsigned int  h, w, i, j;
unsigned char skip[4];
unsigned char r, g, b;
int hInverted;
char ch = 1;
int highest_frame;
char bmpname[80];
char bmpfile[80];
char bmpout[80];
char Ctext[80];
char Cbmpout[80];
char Utext[80];
char Ubmpout[80];
char Htext[80];
char Hbmpout[80];
char bmptext[80];
int header = 3 * sizeof(int);
int frame_counter;
int output_option;

#include "bmp24loader.h"
#include "circularbmp24loader.h"





int bmploader(void);
int bmp24loader(void);
int circularbmp24loader(void);

int bmploader(void)
{

	if (fopen_s(&fp, bmpfile, "rb")) {
		printf("cannot open file for reading.\n");
		exit(1);
	}

	fread(&Header, 1, sizeof(Header), fp);
	fread(&Info, 1, sizeof(Info), fp);


	



	switch (Info.BitDepth) {
		

	case 24:
		
		printf("loading 24 bit bitmap \n");
		if(output_option==1 || output_option == 3) bmp24loader();
		if(output_option == 2 || output_option == 3) circularbmp24loader();

		

		break;
	default:
		printf("Must be 24 bit bitmap for videos");
		break;
	}

	fclose(fp);



	return 0;


}

