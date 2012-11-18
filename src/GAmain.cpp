/***************************************************************************
 *   Copyright (C) 2004 by Tian-Li Yu                                      *
 *   tianliyu@cc.ee.ntu.edu.tw                                             *
 *                                                                         *
 *   You can redistribute it and/or modify it as you like                  *
 ***************************************************************************/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <unistd.h>

#include "statistics.h"
#include "ga.h"
#include "chromosome.h"
#include "global.h"

#define GENE_LENGTH 7

using namespace std;

double getnumber(string out_string, double default_value);

int main (int argc, char *argv[])
{
    int ell, nInitial, selectionPressure=2, maxGen=200, maxFe=-1;
    string source_file="source", target_file="target", device_list="O";
    double pc=1, pm=1.0E-6, center_freq=2.4E9;

    char c;
    while((c=getopt(argc, argv, "hs:m:G:c:i:o:d:")) != -1)
    {
        switch(c)
        {
            case 'h':
                printf ("usage:\n GA -s sPressure -m pm -G maxGen -c center_freq -d device_structure -i source_file -o target_file\n default: s=2, maxGen=200, maxFe=-1, cent_freq=2.4E9, pc=1, pm=1.0E-6, device_struct: O, source: source, target: target\n");
                return 0;
            case 's':
                selectionPressure = atoi (optarg);  // selection pressure
                break;
            case 'm':
                pm = atof (optarg);
                break;
            case 'G':
                maxGen = atoi (optarg); // max generation
                break;
            case 'c':
                center_freq = atof (optarg); // how many time to repeat
                break;
            case 'd':
                device_list = optarg;
            case 'i':
                source_file = optarg;
                break;
            case 'o':
                target_file = optarg;
            default:
                puts("wrong command");
                return 0;
        }
    };

    ell = device_list.length() * GENE_LENGTH;
    nInitial = (int)ceil((double)ell*log((double)ell)+0.5);
    cout << "ell: " <<ell<< " nInitial:" <<nInitial<< " struct" <<device_list<< endl;

    Statistics stGenS, stGenF;
    int failNum = 0;

	GA ga ( ell, nInitial, selectionPressure, pc, pm, maxGen, maxFe, source_file, target_file, device_list, center_freq);
	ga.doIt (false);
	fflush (NULL);

    return EXIT_SUCCESS;
}
/*
double getnumber(string out_string, double default_value){
	cout << out_string << "(default = " << default_value << ")\n";
	string input;
	double number = default_value;
	getline(cin, input);
	if (!input.empty()) {
		istringstream stream(input);
		stream >> number;
	}
	return number;
}
*/
