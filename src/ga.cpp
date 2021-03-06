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
#include "ga.h"
#include "S2P_reader.h"
using namespace std;

GA::GA ()
{
    ell = 0;
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


GA::GA (int n_ell, int n_nInitial, int n_selectionPressure, double n_pc, double n_pm, double p_win, int n_maxGen, int n_maxFe, string devicelist, bool _RTR_on, int RTR_th)
{
    init (n_ell, n_nInitial, n_selectionPressure, n_pc, n_pm, p_win, n_maxGen, n_maxFe,  devicelist, _RTR_on,  RTR_th);
}


GA::~GA ()
{

    delete[]population;
    delete[]offspring;
    delete[]selectionIndex;
}


void
GA::init (int n_ell, int n_nInitial, int n_selectionPressure, double n_pc,
double n_pm, double p_win, int n_maxGen, int n_maxFe, string devicelist, bool _RTR_on, int RTR_th)
{
    int i;

    ell = n_ell;
    nInitial = n_nInitial;
    nCurrent = nInitial;
    selectionPressure = n_selectionPressure;
    pc = n_pc;
    pm = n_pm;
    p_winner = p_win;
    maxGen = n_maxGen;
    maxFe = n_maxFe;
    RTR_on = _RTR_on;
    RTR_threshold = RTR_th;

    population = new Chromosome[nInitial];
    offspring = new Chromosome[nInitial];
    selectionIndex = new int[nInitial];

    Chromosome::device_list = devicelist;

    for (i = 0; i < nInitial; i++) {
        population[i].init (ell);
        offspring[i].init (ell);
    }
    best_guy.init(ell);

    initializePopulation ();
}

void GA::initializePopulation ()
{
    int i, j;

    for (i = 0; i < nInitial; i++)
        for (j = 0; j < ell; j++)
                population[i].setVal (j, myRand.uniformInt( 1, 100));

}

// For now, assuming fixed population size
int GA::getNextPopulation ()
{
    return nCurrent;
}

void GA::selection ()
{
    //rwSelection ();
    tournamentSelection ();
}

// Roulette wheel selection
// This is a O(n^2) implementation
// You can achieve O(nlogn) by using binary search
void GA::rwSelection ()
{
    int i, j;

    // Adjusting population size 
    nNextGeneration = getNextPopulation ();

    if (nNextGeneration != nCurrent) {
        delete[]selectionIndex;
        delete[]offspring;
        selectionIndex = new int[nNextGeneration];
        offspring = new Chromosome[nNextGeneration];

        for (i = 0; i < nNextGeneration; i++)
            offspring[i].init (ell);
    }

    double totalFitness = 0.0;
    for (i = 0; i < nCurrent; i++) 
	totalFitness += population[i].getFitness();

    for (i = 0; i < nNextGeneration; i++) {
	double pointer = totalFitness * myRand.uniform();
	int index = -1;
	double partialSum = 0.0;
	for (j = 0; j < nCurrent; j++) {
	    partialSum += population[j].getFitness();
            if (partialSum >= pointer) {
                index = j;
                break;
            }
	}
	if (index == -1) index = nCurrent - 1;

	selectionIndex[i] = index;
    }

}

// tournamentSelection without replacement
void GA::tournamentSelection ()
{

    int i, j;

    // Adjusting population size 
    nNextGeneration = getNextPopulation ();

    if (nNextGeneration != nCurrent) {
        delete[]selectionIndex;
        delete[]offspring;
        selectionIndex = new int[nNextGeneration];
        offspring = new Chromosome[nNextGeneration];

        for (i = 0; i < nNextGeneration; i++)
            offspring[i].init (ell);
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
        double temp = myRand.uniform();

        if(temp < p_winner){
            for (j = 0; j < selectionPressure; j++) {
                int challenger = randArray[selectionPressure * i + j];
                double challengerFitness = population[challenger].getFitness ();

                if (challengerFitness < winnerFitness) {
                    winner = challenger;
                    winnerFitness = challengerFitness;
                }

            }
        }
        else{ // loser wins
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


void GA::crossover ()
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


void GA::pairwiseXO (const Chromosome & p1, const Chromosome & p2, Chromosome & c1, Chromosome & c2)
{
    if (myRand.uniform () < pc) {
	//onePointXO (p1, p2, c1, c2);
    //uniformXO (p1, p2, c1, c2, 0.5);
    extendedLineXO(p1, p2, c1, c2, 0.25);
    }
    else {
        c1 = p1;
        c2 = p2;
    }
}

void GA::extendedLineXO (const Chromosome & p1, const Chromosome & p2, Chromosome & c1, Chromosome & c2, double alpha_w)
{
    int i;
    double alpha;
    for (i = 0; i < ell; i++) {
        alpha = (1+2*alpha_w)*myRand.uniform() - alpha_w;
        c1.setVal (i, (int)( alpha*(double)p1.getVal(i) + (1-alpha)*(double)p2.getVal(i) + 0.5 ));
        alpha = (1+2*alpha_w)*myRand.uniform() - alpha_w;
        c2.setVal (i, (int)( alpha*(double)p1.getVal(i) + (1-alpha)*(double)p2.getVal(i) + 0.5 ));
    }
    /*
    cout << "parent" << endl;
    p1.printf();cout<<endl;
    p2.printf();cout<<endl;
    cout << "offspring" <<endl;
    c1.printf();cout<<endl;
    c2.printf();cout<<endl;
    */
}

void GA::onePointXO (const Chromosome & p1, const Chromosome & p2, Chromosome & c1, Chromosome & c2)
{
    int i;
    int crossSite = myRand.uniformInt(1, ell-1);

    for (i = 0; i < crossSite; i++) {
            c1.setVal (i, p1.getVal(i));
            c2.setVal (i, p2.getVal(i));
    }

    for (i = crossSite; i < ell; i++) {
            c1.setVal (i, p2.getVal(i));
            c2.setVal (i, p1.getVal(i));
    }
}

void GA::uniformXO (const Chromosome & p1, const Chromosome & p2, Chromosome & c1, Chromosome & c2, double prob)
{
    int i;

    for (i = 0; i < ell; i++) {
        if (myRand.flip (prob)) {
            c1.setVal (i, p1.getVal(i));
            c2.setVal (i, p2.getVal(i));
        }
        else {
            c1.setVal (i, p2.getVal(i));
            c2.setVal (i, p1.getVal(i));
        }
    }
}

void GA::mutation ()
{
    //simpleMutation ();
    mutationClock ();
}


void GA::simpleMutation ()
{
    int i, j;

    for (i = 0; i < nNextGeneration; i++)
        for (j = 0; j< ell; j++)
            if (myRand.flip(pm)) {
                offspring[i].setVal(j, myRand.uniformInt( 1, 100));
            }
}

void GA::mutationClock ()
{
    if (pm < 1e-6) return; // can't deal with too small pm

    int pointer = (int) (log(1-myRand.uniform()) / log(1-pm) + 1);

    while (pointer < nNextGeneration * ell) {

	int q = pointer / ell;
	int r = pointer % ell;

        offspring[q].setVal(r, myRand.uniformInt( 1, 100));

	// Compute next mutation clock
	pointer += (int) (log(1-myRand.uniform()) / log(1-pm) + 1);
    };
}


void GA::showStatistics ()
{

    printf ("Gen:%d  Fitness:(Max/Mean/Min):%f/%f/%f Chromsome Length:%d\n",
        generation, stFitness.getMax (), stFitness.getMean (),
        stFitness.getMin (), population[0].getLength ());
    printf ("best chromosome: ");
    population[bestIndex].printf ();
}


void GA::replacePopulation ()
{
    int i;

    if(!RTR_on) { //RTR off
        if (nNextGeneration != nCurrent) {
            delete[]population;
            population = new Chromosome[nNextGeneration];
        }

        for (i = 0; i < nNextGeneration; i++)
            population[i] = offspring[i];

        nCurrent = nNextGeneration;
    }
    else { //RTR on
        int j, min, index, temp;

        for( i = 0; i < nNextGeneration; i++) {
            min = INT_MAX;
            for( j = 0; j < nCurrent; j++) {
                temp = gene_distance( offspring[i], population[j]);
                if( temp < min) {
                    index = j;
                    min = temp;
                }
            }
            if( population[index].getFitness() > offspring[i].getFitness())
                population[index] = offspring[i];
        }
    }
}

int GA::gene_distance (const Chromosome & c1, const Chromosome & c2) const
{
    int dist = 0, temp;
    for (int i = 0; i < ell; i++) {
        temp = abs(c1.getVal(i)- c2.getVal(i));
        dist += temp*temp;
    }
    return dist;
}


void GA::oneRun ()
{
    int i;

    selection ();
    crossover ();
    mutation ();
    replacePopulation ();

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
    //population[bestIndex].printf();
    //cout<<endl;

    if( first_time == true){
        best_guy = population[bestIndex];
        first_time =false;
    }
    else{
        if( best_guy.getFitness() > population[bestIndex].getFitness() ){
            best_guy = population[bestIndex];
            best_counter = 0;
        }
        best_counter++;
    }

    //showStatistics ();

    generation++;
}


double GA::doIt (int *param, bool &within_constraint)
{
    generation = 0;
    best_counter = 0;

    first_time = true;
    while (!shouldTerminate ()) {
        oneRun ();
    }

    // record best chromosome
    for( int i=0; i < ell; i++){
        param[i] = best_guy.getVal(i);
    }

    within_constraint = best_guy.check();

    //if(!RTR_on){
        cout<< "best guy --- for "<< best_counter <<" generation(s) ";
        best_guy.printf();
        cout << " fitness is "<<best_guy.getFitness() <<", within constraint: " << within_constraint <<endl;
    //}

    return best_guy.getFitness();
}


bool GA::shouldTerminate ()
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

    // Found a satisfactory solution
    //if (population[0].getMaxFitness() <= stFitness.getMean();)
    //    termination = true;

    // The population loses diversity
    if (stFitness.getMax()-1e-6 < stFitness.getMean())
        termination = true;

    if ( RTR_on && best_counter > RTR_threshold)
        termination = true;

    return termination;

}
