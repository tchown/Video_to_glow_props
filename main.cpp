#include "headers/bmploader.hpp"

using namespace std;

struct BMPHeader Header;
struct BMPInfo Info;
string input_file_name, output_file_name;
ifstream input_file;
ofstream output_file;
int user_option;
int radius;
int highest_frame;
int frame_counter;
int output_option;

int main()
{
	string file_name,  frame_as_string;
	int highest_frame;
	 cout << "\n\n";
    cout << "Enter file name (not including the number or .bmp): ";
    cin>>file_name;
	if(file_name.length()>7) {
		cout<<"file name can't be more than 7 charactors, remname the file with a shorter name"<<endl;
		exit(1);
	}

	 cout << "\n\n";
	cout<< "Enter the heighest frame: ";
	cin>>highest_frame;
	if (highest_frame >= 10000) {
		cout<<"highest frame number is 9999!";
		exit(1);
	}

    cout << "\n\n";
    cout <<"Enter 1 for rectangluar converter (e.g. poi),"<<endl;    
    cout <<"Enter 2 for circular converter (e.g. Umberlla),"<<endl;
   
    cin >> user_option;

	if(user_option==1) {
		output_file_name = file_name +".squ";
	}
	else if (user_option==2){
		cout << "\n\n";
		cout <<"Enter 1 for JELLY_FISH_V4 (120px radius)"<<endl;
		cout << "Enter 2 for UMBRELLA_V4 (96px radius)"<<endl;
		cout << " OR enter the radius you wish to convert for"<<endl;
		cin >> radius;
		if (radius == 1){
			radius=120;
			output_file_name = file_name+".Jcir";
		}
		else if(radius==2){
			radius =98; // two extra pixels as LEDs don't quite come to the centre
			output_file_name = file_name+".Ucir";
		} 
		else{
			output_file_name = file_name+".cir";

		}
	}
    else{
        cout<< "error invalied option";
        return 1;
    }


	for (frame_counter = 0; frame_counter <= highest_frame; frame_counter++) {
		
		frame_as_string = to_string(frame_counter);

		if (highest_frame < 10) {
			input_file_name = "BMPs/" + file_name + frame_as_string +".bmp";
    		cout<<input_file_name;
			bmploader();
		}

		else if ((highest_frame < 100)) {
			if (frame_counter < 10) {

				input_file_name = "BMPs/" + file_name + to_string(0)+ frame_as_string +".bmp";
			}
			else {
				input_file_name = "BMPs/" + file_name + frame_as_string +".bmp";
			}
    		cout<<input_file_name;

			bmploader();
		}

		else if ((highest_frame < 1000)) {
			if (frame_counter < 10) {

				input_file_name = "BMPs/" + file_name + to_string(0)+ to_string(0)+ frame_as_string +".bmp";
			}
			else if(frame_counter<100) {
				input_file_name = "BMPs/" + file_name +to_string(0)+ frame_as_string +".bmp";
			}
			else {
				input_file_name = "BMPs/" + file_name + frame_as_string +".bmp";
			}
    		cout<<input_file_name;

			bmploader();
		}

		else if ((highest_frame < 10000)) {
			
			if (frame_counter < 10) {

				input_file_name = "BMPs/" + file_name + to_string(0)+to_string(0)+to_string(0)+ frame_as_string +".bmp";
			}
			else if(frame_counter<100) {
				input_file_name = "BMPs/" + file_name +to_string(0)+to_string(0)+ frame_as_string +".bmp";
			}
			else if(frame_counter<1000) {
				input_file_name = "BMPs/" + file_name +to_string(0)+ frame_as_string +".bmp";
			}
			else {
				input_file_name = "BMPs/" + file_name + frame_as_string +".bmp";
			}
    		cout<<input_file_name;

			bmploader();
		}
		
	}
	

	

	return 0;
}