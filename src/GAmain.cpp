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

#include "statistics.h"
#include "ga.h"
#include "chromosome.h"
#include "global.h"

#define GENE_LENGTH 7

using namespace std;

double getnumber(string out_string, double default_value);

int main (int argc, char *argv[])
{
	int ell, nInitial, selectionPressure, maxGen, maxFe, repeat;
    string source_file="source", target_file="target", device_list="";
	double pc, pm, center_freq;

	ell = int(getnumber("please input the problem size", 1));
	nInitial = int(getnumber("please input the poulation size", 10000));
	selectionPressure = int(getnumber("please input the selection pressure", 2));
	pc = getnumber("please input the probability of crossover", 1);
	pm = getnumber("please input the probability of mutation", 0);
	maxGen = int(getnumber("please input the max generation", 20));
	maxFe = int(getnumber("please input the max fe", 10));
	repeat = int(getnumber("please input the times of repeat", 20));

    cout << "please input the device structure." << endl;
    cin >> device_list;

    //if (argc != 9) {
    //    printf ("GA ell nInitial selectionPressure pc pm maxGen maxFe repeat\n");
    //    return -1;
    //}

    //int ell = atoi (argv[1]);    // problem size
    //                             // initial population size
    //int nInitial = atoi (argv[2]);
    //                             // selection pressure
    //int selectionPressure = atoi (argv[3]);
    //double pc = atof (argv[4]);  // pc
    //double pm = atof (argv[5]);  // pm
    //int maxGen = atoi (argv[6]); // max generation
    //int maxFe = atoi (argv[7]);  // max fe
    //int repeat = atoi (argv[8]); // how many time to repeat

    int i;

    Statistics stGenS, stGenF;
    int usedGen;

    int failNum = 0;

    for (i = 0; i < repeat; i++) {

        GA ga ( ell*GENE_LENGTH, nInitial, selectionPressure, pc, pm, maxGen, maxFe, source_file, target_file, device_list, center_freq);

        if (repeat == 1)
            usedGen = ga.doIt (true);
        else
            usedGen = ga.doIt (false);

        Chromosome ch(ell);
        if (ga.stFitness.getMax() < ch.getMaxFitness()) {
            printf ("-");
            failNum++;
            stGenF.record (usedGen);
        }
        else {
            printf ("+");
            stGenS.record (usedGen);
        }

        fflush (NULL);

    }

    printf ("\nAverage Gen of Success: %f\n", stGenS.getMean());
    printf ("Average Gen of Failure: %f\n", stGenF.getMean());
    printf ("Total number of Failure: %d\n", failNum);

    return EXIT_SUCCESS;
}

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
