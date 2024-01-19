
#include <iostream>
#include <fstream>
#include <string>
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




using namespace std;

extern struct BMPHeader Header;
extern struct BMPInfo Info;

extern string input_file_name, output_file_name;
extern ifstream input_file;
extern ofstream output_file;
extern int user_option;
extern int radius;
extern int highest_frame;
extern int frame_counter;
extern int output_option;

int bmploader(void);
int bmp24loader(void);
int circularbmp24loader(void);

