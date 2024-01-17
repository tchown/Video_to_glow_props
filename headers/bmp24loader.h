#include <stdio.h>                             // So we can use fopen and fread
#include <stdlib.h>
#include <string.h>

int bmp24loader(void) {

	FILE* fpout;
	FILE* fptxt;
	unsigned char value;

	int colour_lookup[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2,
		2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5,
		6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 11, 11,
		11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18,
		19, 19, 20, 21, 21, 22, 22, 23, 23, 24, 25, 25, 26, 27, 27, 28,
		29, 29, 30, 31, 31, 32, 33, 34, 34, 35, 36, 37, 37, 38, 39, 40,
		40, 41, 42, 43, 44, 45, 46, 46, 47, 48, 49, 50, 51, 52, 53, 54,
		55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
		71, 72, 73, 74, 76, 77, 78, 79, 80, 81, 83, 84, 85, 86, 88, 89,
		90, 91, 93, 94, 95, 96, 98, 99, 100, 102, 103, 104, 106, 107, 109, 110,
		111, 113, 114, 116, 117, 119, 120, 121, 123, 124, 126, 128, 129, 131, 132, 134,
		135, 137, 138, 140, 142, 143, 145, 146, 148, 150, 151, 153, 155, 157, 158, 160,
		162, 163, 165, 167, 169, 170, 172, 174, 176, 178, 179, 181, 183, 185, 187, 189,
		191, 193, 194, 196, 198, 200, 202, 204, 206, 208, 210, 212, 214, 216, 218, 220,
		222, 224, 227, 229, 231, 233, 235, 237, 239, 241, 244, 246, 248, 250, 252, 255
	};

	int width = Info.Width;
	int height = Info.Height;

	//fopen_s(fpout, bmpout, "w");
	if (frame_counter == 0) {
		if (fopen_s(&fpout, bmpout, "wb")) {
			printf("cannot create file .bin on frame for output.\n", frame_counter);
			exit(1);
		}
		int num_of_frames = highest_frame+1;
		fwrite(&num_of_frames, sizeof(int), 1, fpout);
		fwrite(&width, sizeof(int), 1, fpout);
		fwrite(&height, sizeof(int), 1, fpout);
		
		/*if (fopen_s(&fptxt, bmptext, "w")) {
			printf("cannot create file %s.txt on frame %d for output.\n", bmptext, frame_counter);
			exit(1);
		}
		fprintf(fptxt, "%d,", highest_frame);
		fprintf(fptxt, "%d,%d,\n", width, height);
		*/
	
	}
	else {
		if (fopen_s(&fpout, bmpout, "ab")) {
			printf("cannot open file .bin on frame %d for output.\n", frame_counter);
			exit(1);
		}

		/*if (fopen_s(&fptxt, bmptext, "a")) {
			printf("cannot open file .txt on frame %d for output.\n", frame_counter);
			exit(1);
		}*/
	}

	

	int row_padded = (width * 3 + 3) & (~3);
	unsigned char* data = new unsigned char[3];
	
	for (int j = 0; j < width * 3; j += 3)
	{
		for (int i = 0; i < height; i++)
		{
			fseek(fp, Header.OffsetBits + (i * row_padded * sizeof(unsigned char)) + (j * sizeof(unsigned char)), SEEK_SET);
			fread(data, sizeof(unsigned char), 3, fp);

			// Convert (B, G, R) to (R, G, B)

			fwrite(&colour_lookup[data[2]], 1, 1, fpout);
			fwrite(&colour_lookup[data[1]], 1, 1, fpout);
			fwrite(&colour_lookup[data[0]], 1, 1, fpout);
			//fprintf(fptxt, "%4d,", colour_lookup[data[1]]);
		}


		//fprintf(fptxt, "\n");
	}
	//fclose(fp);
	fclose(fpout);
	//fclose(fptxt);

	return 1;
}
