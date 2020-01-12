#include "ppm.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

float* image::ReadPPM(const char* filename, int* w, int* h) {

	int max_size = 0;
	fstream PPM(filename, ios::in | ios::binary);
	bool pSix = false;
	string header;
	float* rgb;
	int* image_data = new int[3];
	image_data[0] = 0; image_data[1] = 0; image_data[2] = 0;
	unsigned char cur;

	cout << "Trying to open the PPM file: ";

	if (!PPM.is_open()) {
		printf("The PPM file didn't open.");
		return nullptr;
	}

	cout << "OK." << endl;

	string image_values = "";				//Variables to save the height, width, rgb range.

	int end_of_data = 1;
	getline(PPM, header);
	string line;
	stringstream ss(header);
	string word;
	string* data = new string[4];
	unsigned int word_count = 0;
	// extract all words from line
	while (ss >> word) {
		data[word_count] = word;
		// count word
		++word_count;
	}
	
	if (word_count < 1 || word_count == 2 || word_count == 3 || word_count > 4) {		//Case Invalid PPM Format
		printf("Not Valid PPM Format/Header.\nValids are:\nP6\tP6 1024 788 255\t\tP6\n1024\t\t\t\t1024 788\n788\t\t\t\t255\n255\n");			//print valid formats.
		return nullptr;
		PPM.close();
	}

	else if (word_count == 4) {							//Case Format: P6 1024 788 255
		int i = 0;
		if(data[i] != "P6"){
			printf("Not Valid PPM Format/Header.\n");
			return nullptr;
			PPM.close();
		}
		i = 1;
		for (i; i < 4; i++) {					//Store height,width,rgb range.
			image_data[i-1] = stoi(data[i]);
		}
		
	}
	
	else if (word_count <= 1) {							//Case Format: P6				P6
														//             1024 788			1024
														//			   255				788
														//								255
		if (!(data[0] == "P6")) {
			printf("Not Valid PPM Format/Header.\n");
			return nullptr;
			PPM.close();
		}
		else {
			pSix = true;
		}

		if (pSix) {			//Check the header of the PPM == "P6".
			int spaces = 0;
			
			while (PPM) {		//while PPM not EOF() and is_open().

				if (end_of_data > 3) {			//If we end with the data, break.
					break;
				}

				cur = PPM.get();
				

				while (cur >= 48 && cur <= 57) {			//The ASCII values from 0 to 9.
					image_values.append(1, cur);
					
					cur = PPM.get();
					
					if (cur == 32) {
						spaces += 1;
						image_data[end_of_data - 1] = stoi(image_values);
						if (spaces > 0 && image_data[2] != 0)
							break;
						end_of_data++;
						image_values = "";
						cur = PPM.get();
						
					}

				}
				
				if (image_data[2] != 0)									//If we took our data, break. Next step: Get RGB Values.
					break;
				image_data[end_of_data - 1] = stoi(image_values);				//Store our data.
				
				end_of_data++;
				image_values = "";
				
				continue;					//Continue to the next number.
			}
		}
	}


		if (image_data[0] <= 0 || image_data[1] <= 0 && image_data[2] != 255) {			//Check if data is valid.
			printf("The data is insufficient");
			return nullptr;
			PPM.close();
		}
		

		rgb = new float[image_data[0] * image_data[1] * 3];			//Width X Height trinity of float data, to save the rgb values.
		int k = 0;			//Current index of rgb array.
		cur = PPM.get();
		
		while (PPM) {				//while PPM not EOF() and is_open().

			if (cur > 255) {
				return nullptr;				
			}

			rgb[k] = ((float)cur) / 255.0;			//Save the 0-255 RGB values to the rgb array as PPM file values.

			k++;							//Next index of the rgb array.

			cur = PPM.get();				//Get the next char to get the RGB value.
		}
		
		

		*w = image_data[0];					//Save the width;
		*h = image_data[1];					//Save the height;

		PPM.close();
		delete[] image_data;				//Clear the memory we use for image data.
		return rgb;							//Return rgb values.

	}
	
bool image::WritePPM(const float* data, int w, int h, const char* filename) {

	bool done = true;				//bool variable to check if all is done.
			
	fstream PPM_writer(filename, ios::out | ios::binary);			//Stream to open a new file and write our text.
	string text;
	text = filename;
	cout << "Trying to write a PPM file with name " + text + ": "; 
	
	if (!PPM_writer.is_open()) {					//If the PPM file didn't open..
		printf("The PPM file didn't open to write..");
		done = false;
		return done;
	}
	

	text = "P6\n";									//Trying to write the data we had before from the PPM file we read.
	PPM_writer.write(text.c_str(), text.size());
	text = to_string(w) + "\n";
	PPM_writer.write(text.c_str(), text.size());
	text = to_string(h) +"\n";
	PPM_writer.write(text.c_str(), text.size());
	text = "255\n";
	PPM_writer.write(text.c_str(), text.size());

	int lines = w * h * 3;					//Lines at the PPM file.
	float rgb;
	
	for (int i = 0; i < lines; i++) {
		rgb = data[i] * 255;					//Convert again to RGB Values.
		PPM_writer.put(rgb);					//Write the rgb values in PPM file.
	}
	cout << "OK." << endl;
	PPM_writer.close();

	return done;							//Return done.
}




