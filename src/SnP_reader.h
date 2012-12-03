//*************************************************
//  by YodaLee 2012-11-25
//  based on the work SnP_reader done by Jorgemouse 
//
//  freq_response is a single frequency response profile
//  SnP_reader will read the input into a vector list of freq_response
//  You could use get_list() to obtain a reference of the vector list.
//*************************************************

#ifndef _SnP_READER_H_
#define _SnP_READER_H_

#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <string>
using namespace std;

class freq_response
{
    public:
		freq_response (){ set(0.0,0.0,0.0); }
        freq_response (double freq_, double rho_, double theta_){
			set(freq_, rho_, theta_);
        };
		freq_response (double freq_, complex<double> point){
			set(freq_, abs(point), arg(point)*180/M_PI);
		};
        //~freq_response ();
        void set(double freq_, double rho_, double theta_){
			_freq = freq_;
            _value = complex<double>(rho_*cos(theta_*M_PI/180),rho_*sin(theta_*M_PI/180));
		}
        double freq(){ return _freq; };
        complex<double> value(){ return _value;};

    protected:
        double _freq;
        complex<double> _value;
};

class SnP_reader
{
    public:
		SnP_reader (){};
        void init(string filename);

		void print();
		vector<vector<freq_response> >& get_list(){
			return freq_list;
		}
		bool get_data(double freq, vector<freq_response>&);
    protected:
		int n;
        vector< vector<freq_response> > freq_list;
	private:
		int parse_filename(string &) const;
		void MA2RI(double&, double&);
		void dB2RI(double &dB, double &ang);
};

#endif
