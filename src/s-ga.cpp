/***************************************************************************
 *   Copyright (C) 2004 by Tian-Li Yu                                      *
 *   tianliyu@cc.ee.ntu.edu.tw                                             *
 ***************************************************************************/

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <float.h>
#include <cmath>
#include <limits.h>
#include "global.h"
#include "statistics.h"
#include "myrand.h"
#include "s-ga.h"
using namespace std;

S_GA::S_GA ()
{
    max_stage = 0;
    nInitial = 0;
    nCurrent = 0;
    fe = 0;

    nNextGeneration = 0;
    maxGen = -1;
    maxFe = -1;

    population = NULL;
    offspring = NULL;
    selectionIndex = NULL;

}


S_GA::S_GA (int _max_stage, int _s_nInitial, int _s_selectionPressure, double _s_pc, double _s_pm, double _s_p_winner, int _s_maxGen, int _s_maxFe, int _best_th, int _nInitial, int _selectionPressure, double _pc, double _pm, double _p_winner, int _maxGen, int _maxFe, string _source_file, string _target_file, double _centerfreq, double _up_freq, double _down_freq_, int _RL, bool _RTR_on, int _RTR_th)
{
    init (_max_stage, _s_nInitial, _s_selectionPressure, _s_pc, _s_pm, _s_p_winner, _s_maxGen, _s_maxFe,  _best_th, _nInitial, _selectionPressure, _pc, _pm, _p_winner, _maxGen, _maxFe, _source_file, _target_file, _centerfreq, _up_freq, _down_freq_, _RL, _RTR_on, _RTR_th);
}


S_GA::~S_GA ()
{
    delete[]population;
    delete[]offspring;
    delete[]selectionIndex;
}


void
S_GA::init (int _max_stage, int _s_nInitial, int _s_selectionPressure, double _s_pc, double _s_pm, double _s_p_winner, int _s_maxGen, int _s_maxFe, int _best_th, int _nInitial, int _selectionPressure, double _pc, double _pm, double _p_winner, int _maxGen, int _maxFe, string _source_file, string _target_file, double _centerfreq, double _up_freq, double _down_freq_, int _RL, bool _RTR_on, int _RTR_th)
{
    max_stage = _max_stage;

    nInitial = _s_nInitial;
    nCurrent = nInitial;
    selectionPressure = _s_selectionPressure;
    pc = _s_pc;
    pm = _s_pm;
    p_winner = _s_p_winner;
    maxGen = _s_maxGen;
    maxFe = _s_maxFe;
    best_th = _best_th;

    //for sublayer GA
    S_Chromosome::nInitial = _nInitial;
    S_Chromosome::selectionPressure = _selectionPressure;
    S_Chromosome::pc = _pc;
    S_Chromosome::pm = _pm;
    S_Chromosome::p_winner = _p_winner;
    S_Chromosome::maxGen = _maxGen;
    S_Chromosome::maxFe = _maxFe;
    S_Chromosome::source_file = _source_file;
    S_Chromosome::target_file = _target_file;
    S_Chromosome::centerfreq = _centerfreq;
    S_Chromosome::RTR_on = _RTR_on;
    S_Chromosome::RTR_th = _RTR_th;
    Chromosome::center_freq = _centerfreq;
    Chromosome::source_list.init(_source_file);
    Chromosome::target_list.init(_target_file);
    Chromosome::up_freq = _up_freq;
    Chromosome::down_freq = _down_freq_;
    Chromosome::RL = pow( 10, (double)_RL/10);

    population = new S_Chromosome[nInitial];
    offspring = new S_Chromosome[nInitial];
    selectionIndex = new int[nInitial];
    isSelected = new bool[nInitial];

    /*
    for (int i = 0; i < nInitial; i++) {
        population[i].init ();
        offspring[i].init ();
    }
    best_guy->init();
    */

    initializePopulation ();
}

void S_GA::initializePopulation ()
{
    int i, j, X;
    char *temp;
    temp= new char[max_stage+1];
    temp[max_stage]='\0';

    for (i = 0; i < nInitial; i++){
        for (j = 0; j < max_stage; j++)
        {
            if(!j)  X = myRand.uniformInt( 1, 3);
            else    X = myRand.uniformInt( 0, 3);

            switch(X)
            {
                case 0:
                    temp[j]='\0';
                    break;
                case 1:
                    temp[j]='S';
                    break;
                case 2:
                    temp[j]='T';
                    break;
                case 3:
                    temp[j]='O';
                    break;
                case 4:
                    temp[j]='C';
                    break;
            }

            if(!X) break;
        }
        population[i].setVal(temp);
    }
}

// For now, assuming fixed population size
int S_GA::getNextPopulation ()
{
    return nCurrent;
}

void S_GA::selection ()
{
    //rwSelection ();
    tournamentSelection ();
}

// tournamentSelection without replacement
void S_GA::tournamentSelection ()
{

    int i, j;

    // Adjusting population size 
    nNextGeneration = getNextPopulation ();

    if (nNextGeneration != nCurrent) {
        delete[]selectionIndex;
        delete[]offspring;
        selectionIndex = new int[nNextGeneration];
        offspring = new S_Chromosome[nNextGeneration];
    }

    int randArray[selectionPressure * nNextGeneration];

    int q = (selectionPressure * nNextGeneration) / nCurrent;
    int r = (selectionPressure * nNextGeneration) % nCurrent;

    for (i = 0; i < q; i++)
        myRand.uniformArray (randArray + (i * nCurrent), nCurrent, 0, nCurrent - 1);

    myRand.uniformArray (randArray + (q * nCurrent), r, 0, nCurrent - 1);

    for (i = 0; i < nNextGeneration; i++) {

        int winner = 0;
        double winnerFitness = DBL_MAX;
        int opt_stage = max_stage;
        double temp = myRand.uniform();

        if(temp < p_winner){
            for (j = 0; j < selectionPressure; j++) {
                int challenger = randArray[selectionPressure * i + j];
                int challenger_stage = population[challenger].getLength();
                double challengerFitness = population[challenger].getFitness ();

                if( population[winner].isWithinConstraint() ) {
                    if( population[challenger].isWithinConstraint()) {
                        // case1: all in constraint
                        if( opt_stage > challenger_stage) {
                            winner = challenger;
                            winnerFitness = challengerFitness;
                            opt_stage = challenger_stage;
                        }
                        else if( opt_stage == challenger_stage && challengerFitness < winnerFitness) {
                            winner = challenger;
                            winnerFitness = challengerFitness;
                        }
                    }
                    else {
                        // case2: challenger not in constraint, skip
                        continue;
                    }
                }
                else {
                    if( population[challenger].isWithinConstraint()) {
                        // case3: challenger in constraint, replace
                            winner = challenger;
                            winnerFitness = challengerFitness;
                            opt_stage = challenger_stage;
                    }
                    else {
                        // case4: all not in constraint
                        if (challengerFitness < winnerFitness) {
                            winner = challenger;
                            winnerFitness = challengerFitness;
                            opt_stage = challenger_stage;
                        }
                    }
                }
            }
        }
        else{ // loser wins, selection doesn't consider constraint.
            for (j = 0; j < selectionPressure; j++) {
                int challenger = randArray[selectionPressure * i + j];
                double challengerFitness = population[challenger].getFitness ();

                if (challengerFitness > winnerFitness) {
                    winner = challenger;
                    winnerFitness = challengerFitness;
                }

            }

        }
        selectionIndex[i] = winner;
    }
}


void S_GA::crossover ()
{
    int i;

    if ((nNextGeneration & 0x1) == 0) { 
        // nNextGeneration is even

        for (i = 0; i < nNextGeneration; i += 2)
            pairwiseXO (population[selectionIndex[i]], population[selectionIndex[i + 1]],
                offspring[i], offspring[i + 1]);

    }
    else {
        for (i = 0; i < nNextGeneration - 1; i += 2) {
            pairwiseXO (population[selectionIndex[i]], population[selectionIndex[i + 1]],
                offspring[i], offspring[i + 1]);
        }
        offspring[nNextGeneration - 1] =
            population[selectionIndex[nNextGeneration - 1]];
    }

}


void S_GA::pairwiseXO (const S_Chromosome & p1, const S_Chromosome & p2, S_Chromosome & c1, S_Chromosome & c2)
{
    if (myRand.uniform () < pc) {
        onePointXO (p1, p2, c1, c2);
    }
    else {
        c1 = p1;
        c2 = p2;
    }
}

void S_GA::onePointXO (const S_Chromosome & p1, const S_Chromosome & p2, S_Chromosome & c1, S_Chromosome & c2)
{
    string s1, s2, o1, o2;
    s1 = p1.getVal();
    s2 = p2.getVal();
    int s1_length = s1.length(), s2_length = s2.length();
    int crossSite1, crossSite2, c1_length, c2_length;

    while(true) {
        crossSite1 = myRand.uniformInt(1, s1_length);
        crossSite2 = myRand.uniformInt(1, s2_length);
        c1_length = s1_length - crossSite1 + crossSite2;
        c2_length = s2_length + crossSite1 - crossSite2;
        if(c1_length <= max_stage && c2_length <= max_stage) break;
    }

    // four cases
    if( crossSite1 == s1_length && crossSite2 == s2_length ){
        o1 = s1;
        o2 = s2;
    }
    else if( crossSite1 == s1_length) {
        o1 = s1 + s2.substr(crossSite2);
        o2 = s2.substr(0, crossSite2);
    }
    else if( crossSite2 == s2_length) {
        o1 = s1.substr(0, crossSite1);
        o2 = s2 + s1.substr(crossSite1);
    }
    else {
        o1 = s1.substr(0, crossSite1) + s2.substr(crossSite2);
        o2 = s2.substr(0, crossSite2) + s1.substr(crossSite1);
    }
    /*
    cout << "before: " << s1 << "," << s2 << endl;
    cout << "cross: " << crossSite1 << "," << crossSite2 << endl;
    cout << "after: " << o1 << "," << o2 << endl;
    */
    c1.setVal (o1);
    c2.setVal (o2);
}

/*
void S_GA::mutation ()
{
    //simpleMutation ();
    mutationClock ();
}


void S_GA::simpleMutation ()
{
    int i, j;

    for (i = 0; i < nNextGeneration; i++)
        for (j = 0; j< offspring[i].getLength(); j++)
            if (myRand.flip(pm)) {
                offspring[i].setVal(j, );
            }
}

void S_GA::mutationClock ()
{
    //TODO
    if (pm <= 1e-6) return; // can't deal with too small pm

    int pointer = (int) (log(1-myRand.uniform()) / log(1-pm) + 1);

    while (pointer < nNextGeneration * ell) {

	int q = pointer / ell;
	int r = pointer % ell;

        offspring[q].setVal(r, myRand.uniformInt( 1, 100));

	// Compute next mutation clock
	pointer += (int) (log(1-myRand.uniform()) / log(1-pm) + 1);
    };
}
*/

void S_GA::showStatistics ()
{

    printf ("Gen:%d  Fitness:(Max/Mean/Min):%f/%f/%f Chromsome Length:%d\n",
        generation, stFitness.getMax (), stFitness.getMean (),
        stFitness.getMin (), population[0].getLength ());
    printf ("best chromosome:");
    population[bestIndex].printf ();
    printf ("\n");
}


void S_GA::replacePopulation ()
{
    if (nNextGeneration != nCurrent) {
        delete[]population;
        population = new S_Chromosome[nNextGeneration];
    }

    for (int i = 0; i < nNextGeneration; i++)
        if( i != bestIndex)
            population[i] = offspring[i];

    nCurrent = nNextGeneration;
}


void S_GA::oneRun ()
{
    int i;

    selection ();
    crossover ();
    //mutation ();
    replacePopulation ();

    // first stage : guy with best fitness
    double min = DBL_MAX;
    stFitness.reset ();
    for (i = 0; i < nCurrent; i++) {
        double fitness = population[i].getFitness ();
        if (fitness < min) {
            min = fitness;
            bestIndex = i;
        }
        stFitness.record (fitness);
    }

    // second stage : guy within constraint and shortest
    if(!any_within_constraint) {
        for (i = 0; i < nCurrent; i++) {
            if (population[i].isWithinConstraint()){
                any_within_constraint = true;
                break;
            }
        }
    }

    if(any_within_constraint){
        int opt_stage = max_stage;
        double min = DBL_MAX;
        for (i = 0; i < nCurrent; i++) {
            // if shorter && within constraint, keep this
            if (opt_stage > population[i].getLength() && population[i].isWithinConstraint()) {
                min = population[i].getFitness();
                opt_stage = population[i].getLength();
                bestIndex = i;
            }
            // if equal && within constraint, check if fitness is better
            else if (opt_stage == population[i].getLength() && population[i].isWithinConstraint() && population[i].getFitness() < min) {
                min = population[i].getFitness();
                opt_stage = population[i].getLength();
                bestIndex = i;
            }

        }
    }

    // record best guy
    if( first_time == true){
        best_guy = population[bestIndex];
        first_time =false;
    }
    else{
        if( best_guy.getFitness() != population[bestIndex].getFitness() ){
                best_guy = population[bestIndex];
            best_counter = 0;
        }
        best_counter++;
    }

    showStatistics ();

    generation++;
}


int S_GA::doIt ()
{
    generation = 0;
    best_counter = 0;

    first_time = true;
    any_within_constraint = false;
    while (!shouldTerminate ()) {
        oneRun ();
    }

    // record best chromosome
    cout<< "best guy --- for "<< best_counter <<" generation(s)" <<endl;
    best_guy.printf();

    return generation;
}


bool S_GA::shouldTerminate ()
{
    bool termination = false;

    // Reach maximal # of function evaluations
    if (maxFe != -1) {
        if (fe > maxFe)
            termination = true;
    }

    // Reach maximal # of generations
    if (maxGen != -1) {
        if (generation > maxGen)
            termination = true;
    }

    // The population loses diversity
    if (stFitness.getMax()-1e-6 < stFitness.getMean())
        termination = true;

    if (best_counter > best_th)
        termination = true;

    return termination;

}
