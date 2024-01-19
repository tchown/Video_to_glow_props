#include "headers\bmploader.hpp"

int bmploader(void)
{

	input_file.open(input_file_name,ios::in | ios::binary);	
	if(!input_file.is_open()){
        cout<<"Error opening file"<<input_file_name<<endl;
        output_file.close();
        exit(1);
	}
	
	input_file.read((char*)&Header, sizeof(Header));
    input_file.read((char*)&Info, sizeof(Info));
   
	switch (Info.BitDepth) {
        case 24:
            
            cout<<" loading 24 bit bitmap \n";
            if(user_option==1) bmp24loader();
            if(user_option == 2) circularbmp24loader();
            break;

        default:
            cout<<"Must be 24 bit bitmap for videos";
            break;
	}

	input_file.close();

	return 0;


}

