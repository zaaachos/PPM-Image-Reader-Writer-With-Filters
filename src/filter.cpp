#include <iostream>
#include <sstream>
#include "filter.h"
using namespace std;
using namespace image;
using namespace filter;


int main(int argc, char * argv[]) {
	

	string* data = nullptr;		//Data to store all words given in console

	//Gets the string we give in the console with the filters.
	if (string(argv[argc-1]).find(".ppm") == std::string::npos) {
		printf("No .ppm file found in your given string. Try again.\n");
		system("PAUSE");
		return 1;
	}

	//Store all arguments given in console, in order to find all '-f' chars.
	string inputs = "";

	data = new string[argc];				//Initilize the size 

	//Save the argumentes into the string data
	for (int i = 0; i < argc; i++) {
		data[i] = argv[i];
		inputs += argv[i];
		
	}
	
	int f_index = 0;			//Store current index of '-f'.

	string f = "-f";

	string filtered = "filtered_" + data[argc - 1];			//Save the new filename.
	
	//Initiliaze a image pointer to -> at an Image Object. This will help us to modify the filtered_ images again.
	Image* pointer;
	Image image = Image();
	pointer = &image;

	pointer->load(data[argc - 1], "ppm");				//Load the file ,which console read, at the end of arguments we gave.
	pointer->setPixels();
	Image filt(image);							//Store the filtered image.
	
	FilterLinear lin(*pointer);							//Initiliaze our 2 filters with the pointer.
	FilterGamma gam(*pointer);
	FilterBlur blur(*pointer);

	

	

	//Check if the string given has the arg 'filter'. If not close the program.
	if (data[0] == "filter" || data[0] == "filterd") {
		f_index++;
		size_t found = inputs.find(f);				//Find the first '-f' char.
		if (data[1] != "-f") {
			printf("Not valid syntax. Try: 'filter -f ( linear / gamma )...' \n");
			system("PAUSE");
			return 1;
		}
		
		//While we don't reach at the end of the inputs, apply all filters given in the arguments.
		while (found < inputs.length()) {
			found = inputs.find(f,found+1);			//Next '-f' char in the inputs.
			
			if (data[f_index] == "-f") {			//Begin to apply filters from the -f index.

				//If the amount of filters are more than 1, try to modify the filtered_ image again ( on top of it ).
				if (f_index > 2) {		
					
					lin = FilterLinear(*pointer);			//The filters now will modify the filtered_ image.
					gam = FilterGamma(*pointer);
					blur = FilterBlur(*pointer);

				}
				
				//Case: Linear
				if (data[f_index + 1] == "linear") {
					//Try block in order to check if some numbers are missing from the arguments.
					try {
						stof(data[f_index + 2]);
						stof(data[f_index + 3]);
						stof(data[f_index + 4]);
						stof(data[f_index + 5]);
						stof(data[f_index + 6]);
						stof(data[f_index + 7]);
					}
					catch (exception & e) {
						cout << "Some parameters are missing. Linear filter needs 6 parameters ( numbers )." << endl;
						return 1;
					}
					
					lin.setParameterA(stof(data[f_index + 2]), stof(data[f_index + 3]), stof(data[f_index + 4]));			//Set a and c parameters of FilterLinear class.
					lin.setParameterC(stof(data[f_index + 5]), stof(data[f_index + 6]), stof(data[f_index + 7]));
					filt = (lin << *pointer);				//Save the filtered_ image.
					f_index = f_index + 8;			//Go to the next -f char.

				}

				//Case: Linear
				else if (data[f_index + 1] == "blur") {
					//Try block in order to check if some numbers are missing from the arguments.
					try {
						stof(data[f_index + 2]);
						
					}
					catch (exception & e) {
						cout << "Some parameters are missing. Blur filter needs 1 parameter ( number )." << endl;
						return 1;
					}

					blur.setN(stof(data[f_index + 2]));
					filt = (blur << *pointer);				//Save the filtered_ image.
					f_index = f_index + 3;			//Go to the next -f char.

				}
				//Case: Gamma
				else if (data[f_index + 1] == "gamma") {
					//Try block in order to check if some numbers are missing from the arguments.
					try {
						stof(data[f_index + 2]);
					}
					catch (exception & e) {
						cout << "Some parameters are missing. Gamma filter needs 1 parameter ( number )." << endl;
						return 1;
					}
					
					gam.setParameterY(stof(data[f_index + 2]));					//Set y parameter of FilterGamma class.
					filt = (gam << *pointer);				//Save the filtered_ image.
					f_index = f_index + 3;				//Go to the next -f char.
				}
				//Case: No filter found.
				else {
					printf("Given Filter is not valid / No filter given. Try: 'linear' or 'gamma' \n");
					system("PAUSE");
					return 1;
				}
					


			}
			//If the next string of filter is not '-f' exit.
			else {
				printf("Not valid syntax. Try: 'filter -f ( linear / gamma )...' \n");
				system("PAUSE");
				break;
				return 1;
			}
		}
		filt.save(filtered, "ppm");					//Now save the final filtered image.
		
	}
	//If no string "filter" given in the arguments exit.
	else {
		printf("No 'filter' argument given! Try: 'filter -f ( linear / gamma )...' \n");
		return 1;
	}

	system("PAUSE");
	return 0;

}


