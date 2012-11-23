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

using namespace std;

double getnumber(string out_string, double default_value);

int main (int argc, char *argv[])
{
    int ell, nInitial=0, selectionPressure=2, maxGen=200, maxFe=-1;
    string source_file="source", target_file="target", device_list="O";
    double pc=1, pm=1.0E-6, center_freq=2.4E9, p_winner=1.0;
    bool RTR_on = false;

    char c;
    while((c=getopt(argc, argv, "hn:s:m:G:c:i:o:d:w:r")) != -1)
    {
        switch(c)
        {
            case 'h':
                printf ("usage:\n GA -n nInitial -s sPressure -w p_win -m pm -G maxGen -c center_freq -d device_structure -i source_file -o target_file -r\ndefault:\n s=2, maxGen=200, maxFe=-1, cent_freq=2.4E9, pc=1, pm=1.0E-6, p_win=1.0\n device_struct: O, source: source, target: target\n -r option is for RTR\n");
                return 0;
            case 'n':
                nInitial = atoi(optarg);
                break;
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
                break;
            case 'w':
                p_winner = atof(optarg);
                break;
            case 'r':
                RTR_on = true;
                break;
            default:
                puts("wrong command");
                return 0;
        }
    };

    ell = device_list.length();
    if(nInitial==0) nInitial = (int)ceil((double)ell*log((double)ell)+0.5);
    cout << "ell: " <<ell<< " nInitial:" <<nInitial<< " struct:" <<device_list<< endl;

    for (unsigned i=0;i<device_list.length();++i)
        if(device_list[i]!='S' && device_list[i]!='s' &&
           device_list[i]!='T' && device_list[i]!='t' &&
           device_list[i]!='O' && device_list[i]!='o' &&
           device_list[i]!='C' && device_list[i]!='c'){
            printf("wrong device!\n");
            return 0;
        }

    Statistics stGenS, stGenF;
	GA ga ( ell, nInitial, selectionPressure, pc, pm, p_winner, maxGen, maxFe, source_file, target_file, device_list, center_freq, RTR_on);
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
