/***************************************************************************
 *   Copyright (C) 2004 by Tian-Li Yu                                      *
 *   tianliyu@cc.ee.ntu.edu.tw                                             *
 ***************************************************************************/

#ifndef S_GA_H
#define S_GA_H

#include <string>
#include "s-chromosome.h"
#include "statistics.h"
#include "myrand.h"

using namespace std;

class S_GA
{

    public:
        S_GA ();
        S_GA (int _max_stage, int _s_nInitial, int _s_selectionPressure, double _s_pc, double _s_pm, double _s_p_winner, int _s_maxGen, int _s_maxFe, int _best_th,
            int _nInitial, int _selectionPressure, double _pc, double _pm, double _p_winner, int _maxGen, int _maxFe,
            string _source_file, string _target_file, double _centerfreq, double _up_freq, double _down_freq_, int _RL, bool _RTR_on, int _RTR_th);

        ~S_GA ();

        void init ( int _max_stage, int _s_nInitial, int _s_selectionPressure, double _s_pc, double _s_pm, double _s_p_winner, int _s_maxGen, int _s_maxFe, int _best_th,
                    int _nInitial, int _selectionPressure, double _pc, double _pm, double _p_winner, int _maxGen, int _maxFe,
                    string _source_file, string _target_file, double _centerfreq, double _up_freq, double _down_freq_, int _RL, bool _RTR_on, int _RTR_th);

        void initializePopulation ();
        void evaluate ();

        void selection ();
        /** tournament selection without replacement */
        void tournamentSelection ();

        void crossover ();
        void pairwiseXO (const S_Chromosome &, const S_Chromosome &, S_Chromosome &, S_Chromosome &);
        void onePointXO (const S_Chromosome &, const S_Chromosome &, S_Chromosome &, S_Chromosome &);

        //void mutation ();
        //void simpleMutation ();
        //void mutationClock ();

        void replacePopulation ();

        void showStatistics ();
        void oneRun ();
        int doIt ();

        bool shouldTerminate ();
        int getNextPopulation ();

        Statistics stFitness;

    protected:

        int max_stage;
        int nInitial;            // initial population size
        int nCurrent;            // current population size
        int nNextGeneration;     // population size for the next generation
        int selectionPressure;

        double pc;               // prob of XO
        double pm;               // prob of Mutation
        double p_winner;

        S_Chromosome *population;
        S_Chromosome *offspring;
        S_Chromosome best_guy;
        int *selectionIndex;
        bool *isSelected;
        int maxGen;
        int maxFe;
        int fe;
        int generation;

        int bestIndex;
        int best_counter;
        int best_th;
        bool first_time;
        bool any_within_constraint;
};
#endif
