//*************************************************
//  by Jorgemouse 2012/11/04
//
//  freq_response is a single frequency response profile
//  S2P_reader will read the input into a vector list of freq_response
//  You could use get_list() to obtain a reference of the vector list.
//*************************************************

#ifndef _S2P_READER_
#define _S2P_READER_

#include <iostream>
#include <vector>
#include <complex>
#include <math.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <cstring>
using namespace std;

class freq_response
{
    public:
        freq_response (double freq_, double rho_, double theta_){
            _freq = freq_;
            _S11 = complex<double>(rho_*cos(theta_*M_PI/180),rho_*sin(theta_*M_PI/180));
        };
        //~freq_response ();
        double freq(){ return _freq; };
        complex<double> S11(){ return _S11;};

    protected:
        double _freq;
        complex<double> _S11;
};

class S2P_reader
{
    public:
		S2P_reader (){};
        S2P_reader (string filename) {
            double freq;
            double rho;
            double theta;
            char buffer[50];

            _iFile = fopen (filename.c_str() , "r");
            if (_iFile == NULL){
                cerr << "Cannot open file!" << endl;
                exit(EXIT_FAILURE);
            }

            fgets( buffer, 50, _iFile);
            while( fscanf(_iFile, "%lf\t%lf / %lf", &freq, &rho, &theta) != EOF){
                freq_list.push_back(freq_response( freq, rho, theta));
            }
            fclose(_iFile);
        };
        //~S2P_reader();
        void print(){
            for(vector<freq_response>::iterator it = freq_list.begin();
                it != freq_list.end();
                ++it){
                cout << it->freq() << " " << it->S11() << endl;
            }
        };

        vector<freq_response>& get_list(){
            return freq_list;
        }

    protected:
        FILE * _iFile;
        vector<freq_response> freq_list;
};

#endif
