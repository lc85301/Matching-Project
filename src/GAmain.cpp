/***************************************************************************
 *   Copyright (C) 2004 by Tian-Li Yu                                      *
 *   tianliyu@cc.ee.ntu.edu.tw                                             *
 *                                                                         *
 *   You can redistribute it and/or modify it as you like                  *
 ***************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <unistd.h>

#include "statistics.h"
#include "s-ga.h"
#include "s-chromosome.h"
#include "global.h"

using namespace std;

int main (int argc, char *argv[])
{
    // structure layer GA parameter
    int max_stage=7, s_nInitial=20, s_selectionPressure=2, s_maxGen=50, s_maxFe=-1, best_th=5;
    double s_pc=1, s_pm=1.0E-6, s_p_winner=1.0;
    // fitness layer GA parameter
    int nInitial=30, selectionPressure=2, maxGen=200, maxFe=-1, RTR_th=30, RL=-10;
    string source_file="source", target_file="target";
    double pc=1, pm=1.0E-6, center_freq=2.4E9, up_freq=2.4E9, down_freq=2.4E9, p_winner=1.0;
    bool RTR_on = true;

    char c;
    while((c=getopt(argc, argv, "hN:S:W:M:G:T:n:s:w:m:g:c:i:o:u:d:R:t:r")) != -1)
    {
        switch(c)
        {
            case 'h':
                printf ("usage:\n GA -n nInitial -s sPressure -w p_win -m pm -g maxGen \n -c center_freq -u up_freq -d down_freq -i source_file -o target_file -R RL -t RTR_threshold -r\n -N s_nInitial -S s_sPressure -W s_p_win -M s_pm -G s_maxGen -T best_th_for_s(RTR)\ndefault:\n --parameter lyaer\n nInitial=30, s=2, maxGen=200, maxFe=-1, pc=1, pm=1.0E-6, p_win=1.0, RTR_th=30\n cent_freq=up_freq=down_freq=2.4E9, -r RTR_on(true)\n --structure layer\n max_stage=7, s_nInitial=20, s_sPressure=2, s_maxGen=50, s_maxFe=-1,\n best_th=5, s_pc=1, s_pm=1.0E-6, s_p_winner=1.0;\n");
                return 0;
            case 'N':
                s_nInitial = atoi(optarg);
                break;
            case 'S':
                s_selectionPressure = atoi(optarg);
                break;
            case 'W':
                s_p_winner = atof(optarg);
                break;
            case 'M':
                s_pm = atof(optarg);
                break;
            case 'G':
                s_maxGen = atoi(optarg);
                break;
            case 'T':
                best_th = atoi(optarg);
                break;
            case 'n':
                nInitial = atoi(optarg);
                break;
            case 's':
                selectionPressure = atoi (optarg);  // selection pressure
                break;
            case 'w':
                p_winner = atof(optarg);
                break;
            case 'm':
                pm = atof (optarg);
                break;
            case 'g':
                maxGen = atoi (optarg); // max generation
                break;
            case 'c':
                center_freq = atof (optarg); // how many time to repeat
                break;
            case 'i':
                source_file = optarg;
                break;
            case 'o':
                target_file = optarg;
                break;
            case 't':
                RTR_th = atoi(optarg);
                break;
            case 'u':
                up_freq = atof(optarg);
                break;
            case 'd':
                down_freq = atof(optarg);
                break;
            case 'R':
                RL = atoi(optarg);
                break;
            case 'r':
                RTR_on = true;
                break;
            default:
                puts("wrong command");
                return 0;
        }
    };


    S_GA ga ( max_stage, s_nInitial, s_selectionPressure, s_pc, s_pm, s_p_winner, s_maxGen, s_maxFe, best_th,
             nInitial, selectionPressure, pc, pm, p_winner, maxGen, maxFe,
            source_file, target_file, center_freq, up_freq, down_freq, RL, RTR_on, RTR_th);
    ga.doIt ();
    fflush (NULL);

    return EXIT_SUCCESS;
}
