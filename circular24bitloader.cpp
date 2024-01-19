#include "headers\bmploader.hpp"

using namespace std;

int circularbmp24loader(void)
{

	FILE *fpout;
	FILE *fptxt;

	unsigned char value;

	int colour_lookup[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
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
						   222, 224, 227, 229, 231, 233, 235, 237, 239, 241, 244, 246, 248, 250, 252, 255};

	int width = Info.Width;
	int height = Info.Height;

	const int catherine_wheel = 1;
	const int umbrella = 2;
	const int holographic_spinner = 3;

	if (frame_counter == 0)
	{

		output_file.open(output_file_name, ios::out | ios::binary);
		if (!output_file.is_open())
		{
			cout << "Cannot create file .bin on frame " << frame_counter << " for output." << endl;
			exit(1);
		}

		int num_of_frames = highest_frame + 1;
		output_file.write(reinterpret_cast<char *>(&num_of_frames), sizeof(int));
		output_file.write(reinterpret_cast<char *>(&width), sizeof(int));
		output_file.write(reinterpret_cast<char *>(&height), sizeof(int));
		/*if (fopen_s(&fptxt, Ctext, "w")) {
			printf("cannot create file %s.txt on frame %d for output.\n", bmptext, frame_counter);
			exit(1);
		}
		fprintf(fptxt, "%d,", highest_frame);
		fprintf(fptxt, "%d,%d,\n", width, height);*/
	}
	else
	{
		output_file.open(output_file_name, ios::out | ios::binary | ios::app);
		if (!output_file.is_open())
		{
			cout << "Cannot open file .bin on frame " << frame_counter << " for output." << endl;
			exit(1);
		}

		/*if (fopen_s(&fptxt, Ctext, "a")) {
			printf("cannot open file .txt on frame %d for output.\n", frame_counter);
			exit(1);
		}*/
	}

	int row_padded = (width * 3 + 3) & (~3);
	unsigned char *data = new unsigned char[3];
	int summed_data[3];

	int rotation, distance;

	double centre_w = ((double)width / 2) - 0.5;
	double centre_h = ((double)height / 2) - 0.5;
	double smallest_dim = ((double)((width < height) ? width : height)) / 2;
	double exact_w, exact_h;
	int pixel_w, pixel_h;
	double sample_distance = 0.25;
	double sample_rotation = 0.25;
	for (rotation = 0; rotation < 512; rotation++)
	{

		for (distance = 1; distance < radius + 1; distance++)
		{
			summed_data[0] = 0;
			summed_data[1] = 0;
			summed_data[2] = 0;

			// take 16 samples around the distance and look for mode

			for (int sample_distance_num = 0; sample_distance_num < 4; sample_distance_num++)
			{
				for (int sample_rotation_num = 0; sample_rotation_num < 4; sample_rotation_num++)
				{
					exact_w = (smallest_dim * ((double)distance - sample_distance * sample_distance_num) / (radius + 1)) * sin(((double)rotation - sample_rotation * sample_rotation_num) * 3.14159 / 256);
					exact_h = (smallest_dim * ((double)distance - sample_distance * sample_distance_num) / (radius + 1)) * cos(((double)rotation - sample_rotation * sample_rotation_num) * 3.14159 / 256);
					pixel_w = (int)round(centre_w + exact_w);
					pixel_h = (int)round(centre_h + exact_h);

					input_file.seekg(Header.OffsetBits + (pixel_h * row_padded * sizeof(unsigned char)) + (pixel_w * 3 * sizeof(unsigned char)));
					input_file.read(reinterpret_cast<char *>(data), sizeof(unsigned char) * 3);

					// swap the colours for BGR to RGB as we add up all the pixel values around the polar coroditate we are interested in
					summed_data[0] += data[2];
					summed_data[1] += data[1];
					summed_data[2] += data[0];
				}
			}

			output_file << colour_lookup[summed_data[0] >> 4];
			output_file << colour_lookup[summed_data[1] >> 4];
			output_file << colour_lookup[summed_data[2] >> 4];

			// fprintf(fptxt, "%4d,", colour_lookup[summed_data[1] >> 4]);
		}
		// fprintf(fptxt, "\n");
	}
	// fprintf(fptxt, "\n"); fprintf(fptxt, "\n");

	output_file.close();
	// fclose(fptxt);

	return 1;
}
