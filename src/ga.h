/***************************************************************************
 *   Copyright (C) 2004 by Tian-Li Yu                                      *
 *   tianliyu@cc.ee.ntu.edu.tw                                             *
 ***************************************************************************/

#ifndef GA_H
#define GA_H

#include "chromosome.h"
#include "statistics.h"
#include "myrand.h"
#include <string>
using namespace std;

class GA
{

    public:
        GA ();
        GA (int n_ell, int n_nInitial, int n_selectionPressure, double n_pc,
            double n_pm, double p_winner, int n_maxGen, int n_maxFe, string source_file, string target_file, string devicelist, double centerfreq);

        ~GA ();

        void init (int n_ell, int n_nInitial, int n_selectionPressure, double n_pc,
            double n_pm, double p_winner, int n_maxGen, int n_maxFe, string source_file, string target_file,string devicelist, double centerfreq);

        void initializePopulation ();
        void evaluate ();

        void selection ();

        /** tournament selection without replacement */
        void tournamentSelection ();

	/** Roulette wheel selection */
	void rwSelection ();

        void crossover ();
        void pairwiseXO (const Chromosome &, const Chromosome &, Chromosome &, Chromosome &);
	void onePointXO (const Chromosome &, const Chromosome &, Chromosome &, Chromosome &);
        void uniformXO (const Chromosome &, const Chromosome &, Chromosome &, Chromosome &, double);

        void mutation ();
        void simpleMutation ();
	void mutationClock ();

        void replacePopulation ();

        void showStatistics ();
        void oneRun (bool output = true);
        int doIt (bool output = true);

        bool shouldTerminate ();
        int getNextPopulation ();

        Statistics stFitness;

    protected:

        int ell;                 // chromosome length
        int nInitial;            // initial population size
        int nCurrent;            // current population size
        int nNextGeneration;     // population size for the next generation
        int selectionPressure;

        double pc;               // prob of XO
        double pm;               // prob of Mutation
        double p_winner;
        Chromosome *population;
        Chromosome *offspring;
        Chromosome *best_guy;
        int *selectionIndex;
        int maxGen;
        int maxFe;
        int repeat;
        int fe;
        int generation;
        int bestIndex;

        bool first_time;

};
#endif
