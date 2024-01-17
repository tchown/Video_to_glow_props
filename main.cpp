#include "headers/bmploader.h"





int main(int argc, char* argv[])
{
	if (argc != 4) {
		printf("please enter: input file (which must have no spaces) followed by highest frame number followed by the output opition (1 = rectaular e.g poi, cyr wheel... 2 = cirlular e.g. umbrella, Holographic spinner... 3 = both");
		exit(1);
	}

	output_option = atoi(argv[3]);
	if (output_option != 1 && output_option != 2 && output_option != 3) {
		printf("output option must = 1,2 or 3 (1 = rectaular e.g poi, cyr wheel... 2 = cirlular e.g.umbrella, Holographic spinner... 3 = both");
			exit(1);
	}

	highest_frame = atoi(argv[2]);
	if (highest_frame >= 10000) {
		printf("highest frame number is 9999!");
		exit(1);
	}
	strcpy_s(bmpname, argv[1]);
	if(strlen(bmpname)>7){
		printf("file name can't be more than 7 charactors, remname the file with a shorter name");
		exit(1);
	}
	//strcpy_s(bmpfile, bmpname);
	snprintf(bmpout, 80, "%s.squ", bmpname); // puts string into buffer
	snprintf(Cbmpout, 80, "%s.jel", bmpname); // puts string into buffer
	snprintf(Ctext, 80, "%sC.txt", bmpname); // puts string into buffer
	snprintf(Ubmpout, 80, "%sU.umb", bmpname); // puts string into buffer
	snprintf(Utext, 80, "%sU.txt", bmpname); // puts string into buffer
	snprintf(Hbmpout, 80, "%sH.bin", bmpname); // puts string into buffer
	snprintf(Htext, 80, "%sH.txt", bmpname); // puts string into buffer
	snprintf(bmptext, 80, "%s.txt", bmpname); // puts string into buffer


	for (frame_counter = 0; frame_counter <= highest_frame; frame_counter++) {
		if (highest_frame < 10) {
			snprintf(bmpfile, 80, "%s%d.bmp", bmpname, frame_counter); // puts string into buffer
			printf("%s ", bmpfile);

			bmploader();
		}

		else if ((highest_frame < 100)) {
			if (frame_counter < 10) {
				snprintf(bmpfile, 80, "%s0%d.bmp", bmpname, frame_counter); // puts string into buffer
			}
			else {
				snprintf(bmpfile, 80, "%s%d.bmp", bmpname, frame_counter); // puts string into buffer
			}
			printf("%s ", bmpfile);

			bmploader();
		}

		else if ((highest_frame < 1000)) {
			
			if (frame_counter < 10) {
				snprintf(bmpfile, 80, "%s00%d.bmp", bmpname, frame_counter); // puts string into buffer
			}
			else if (frame_counter < 100) {
				snprintf(bmpfile, 80, "%s0%d.bmp", bmpname, frame_counter); // puts string into buffer
			}
			else {
				snprintf(bmpfile, 80, "%s%d.bmp", bmpname, frame_counter); // puts string into buffer
			}
			printf("%s ", bmpfile);

			bmploader();
		}

		else if ((highest_frame < 10000)) {
			
			if (frame_counter < 10) {
				snprintf(bmpfile, 80, "%s000%d.bmp", bmpname, frame_counter); // puts string into buffer
			}
			else if (frame_counter < 100) {
				snprintf(bmpfile, 80, "%s00%d.bmp", bmpname, frame_counter); // puts string into buffer
			}
			else if (frame_counter < 1000) {
				snprintf(bmpfile, 80, "%s0%d.bmp", bmpname, frame_counter); // puts string into buffer
			}
			else {
				snprintf(bmpfile, 80, "%s%d.bmp", bmpname, frame_counter); // puts string into buffer
			}
			printf("%s ", bmpfile);

			bmploader();
		}
		
	}
	

	

	return 0;
}