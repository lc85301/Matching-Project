#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

#include "SnP_reader.h"

void SnP_reader::init(string filename){
	n = parse_filename(filename);
	double freq;
	double rho;
	double theta;
	char first_char;
	string dump;

	ifstream infile(filename.c_str(), ifstream::in);
	if (!(infile.is_open())){
		cerr << "Cannot open file!" << endl;
		exit(EXIT_FAILURE);
	}

	while (infile.good()) {
		first_char = infile.peek();
		if (first_char == '!') {
			//skip comment line
			getline(infile, dump);
		} else if(first_char == '#'){
			//skip option line for now
			getline(infile, dump);
		} else {
			infile >> freq;
			vector<freq_response> data_set;
			for (int i = 0; i < n*n; ++i) {
				infile >> rho >> theta;
				freq_response data(freq, rho, theta);
				data_set.push_back(data);
			}
			freq_list.push_back(data_set);
		}
	}
	infile.close();
}

//********************************************
// Function: print()
// Description: dump all the data in the freq_list
//********************************************
void SnP_reader::print(){
	for(vector<vector<freq_response> >::iterator it = freq_list.begin(); it != freq_list.end(); ++it){
		for (vector<freq_response>::iterator it_it = it->begin(); it_it != it->end(); ++it_it) {
			cout << it_it->freq() << " "<< it_it->value() << "    "; 
		}
		cout << endl;
	}
}

//********************************************
// Function: parse_filename
// Description: parse filename like test.s2p and return 2
//********************************************
int SnP_reader::parse_filename(string &filename) const{	
	int get_n = 0;

	if (sscanf(filename.substr(filename.find_last_of(".")+1).c_str(), "s%dp", &get_n) != 0) {
		return get_n;
	} else {
		cerr << "invalid input filename;"<< filename << endl;
		exit(EXIT_FAILURE);
	}
}

//********************************************
// Function: dB2RI, MA2RI
// Description: transfer value to R, I by call-by-reference
//********************************************
void SnP_reader::dB2RI(double &dB, double &ang){
	dB = pow(10.0, dB/10);
	MA2RI(dB, ang);
}

void SnP_reader::MA2RI(double &mag, double &ang){
	double _mag = mag;
	double _ang = ang*M_PI/180;
	mag = _mag*cos(_ang);
	ang = _mag*sin(_ang);
}

//********************************************
// Function: get_data
// Description: receive a frequency data 
// directly modify the data_set into the request data
// return false if request_freq is lower than smallest freq or larger than largest
//********************************************
bool SnP_reader::get_data(double request_freq, vector<freq_response> &data_set){
	data_set.clear();
	for(vector<vector<freq_response> >::iterator it = freq_list.begin(); it != freq_list.end(); ++it){
		if (it->begin()->freq() >= request_freq) {
			if (it == freq_list.begin()) {
				data_set = freq_list[0];
				return false;
				//return freq_list[1];
			} else {
				for (vector<freq_response>::iterator it_it1 = it->begin(), it_it2 = (--it)->begin();
						it_it2 != it->end();
						++it_it1, ++it_it2 ) {
					freq_response data(request_freq, (it_it1->value() + it_it2->value())/2.0);
					data_set.push_back(data);
				}
				return true;
			}
			data_set = freq_list[freq_list.size()-1];
			return false;
		}
	}
}
