/*;***************************************************************************
 *   Copyright (C) 2004 by Tian-Li Yu                                      *
 *   tianliyu@cc.ee.ntu.edu.tw                                             *
 ***************************************************************************/

#include <cstdio>
#include <vector>
#include <cmath>
#include <float.h>
#include <cassert>
#include <string>
#include "global.h"
#include "s-chromosome.h"
#include "ga.h"
using namespace std;

int S_Chromosome::nInitial;
int S_Chromosome::selectionPressure;
double S_Chromosome::pc;
double S_Chromosome::pm;
double S_Chromosome::p_winner;
int S_Chromosome::maxGen;
int S_Chromosome::maxFe;
string S_Chromosome::source_file;
string S_Chromosome::target_file;
double S_Chromosome::centerfreq;
bool S_Chromosome::RTR_on;
int S_Chromosome::RTR_th;


S_Chromosome::S_Chromosome ()
{
    gene = "";
    param = NULL;
    evaluated = false;
}

string S_Chromosome::getVal () const
{
    return gene;
}

void S_Chromosome::setVal (string val)
{
    if (!val.length())
        outputErrMsg ("S_Chromosome with 0 length is invalid");

    cout << "gene: " << val << endl;
    gene = val;
    param = new int[gene.length()];
    evaluated = false;
}


double S_Chromosome::getFitness ()
{
    if (evaluated)
        return fitness;
    else
        return (fitness = evaluate ());
}


bool S_Chromosome::isEvaluated () const
{
    return evaluated;
}


double S_Chromosome::evaluate ()
{
    evaluated = true;
    return subGA ();
}

double S_Chromosome::subGA()
{
    double _fitness;
    cout << gene <<" "<< gene.length() <<endl;
    GA ga ( gene.length(), nInitial, selectionPressure, pc, pm, p_winner, maxGen, maxFe, source_file, target_file, gene, centerfreq, RTR_on, RTR_th);
    _fitness = ga.doIt (param);
    return _fitness;
}


S_Chromosome & S_Chromosome::operator= (const S_Chromosome & c)
{
    evaluated = c.evaluated;
    fitness = c.fitness;
    gene = c.gene;

    delete []param;
    param = new int[gene.length()];
    for ( unsigned i=0; i < gene.length(); i++)
        param[i] = c.param[i];

    return *this;
}


void S_Chromosome::printf () const
{
    cout << "s-chromosome: " << gene << endl;
    if(evaluated) {
        cout << "***fitness: " << fitness << " param: ";
        for ( unsigned i=0; i < gene.length(); i++)
            cout << param[i] << " ";
            cout << endl;
    }
}


int S_Chromosome::getLength () const
{
    return gene.length();
}

