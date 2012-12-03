/*;***************************************************************************
 *   Copyright (C) 2004 by Tian-Li Yu                                      *
 *   tianliyu@cc.ee.ntu.edu.tw                                             *
 ***************************************************************************/

#include <iostream>
#include <vector>
#include <float.h>
#include <cassert>
#include "global.h"
#include "chromosome.h"
#include "line_operator.h"
using namespace std;

S2P_reader Chromosome::source_list;
S2P_reader Chromosome::target_list;
string Chromosome::device_list;
double Chromosome::center_freq;
double Chromosome::up_freq;
double Chromosome::down_freq;
double Chromosome::RL;

Chromosome::Chromosome ()
{
    length = 0;
    gene = NULL;
    evaluated = false;
}


Chromosome::Chromosome (int n_length)
{
    gene = NULL;
    init (n_length);
}


Chromosome::~Chromosome ()
{
    delete[]gene;
}

void Chromosome::init (int n_length)
{
    length = n_length;

    if (gene != NULL)
        delete[]gene;

    gene = new int[length];
    evaluated = false;
}

int Chromosome::getVal (int index) const
{
    if (index < 0 || index > length)
        outputErrMsg ("Index overrange in Chromosome::operator[]");

    return gene[index];
}


void Chromosome::setVal (int index, int val)
{
    if (index < 0 || index > length)
        outputErrMsg ("Index overrange in Chromosome::operator[]");

    gene[index] = val;
    evaluated = false;
}


double Chromosome::getFitness ()
{
    if (evaluated)
        return fitness;
    else
        return (fitness = evaluate ());
}


bool Chromosome::isEvaluated () const
{
    return evaluated;
}


double Chromosome::evaluate ()
{
    evaluated = true;
	checked = true;
	return matching ();
    //return oneMax ();
}

bool Chromosome::check()
{
    evaluated = true;
	checked = true;
	matching();
	return within_constraint;
}

double Chromosome::matching(){
	double line_fitness = 0;
	int list_index = 0;
	complex<double> point;
	double freqratio;
	double line_length;
	within_constraint = true;
	vector<freq_response>& source = Chromosome::source_list.get_list();
	vector<freq_response>& target = Chromosome::target_list.get_list();
	//source_list and target_list has to be same size
	assert(source.size() == target.size());

	for (vector<freq_response>::iterator s_it = source.begin(), t_it = target.begin();
		 s_it != source.end();
		 ++s_it, ++t_it
		 ) {
		list_index = 0;
		point = s_it->S11();
		freqratio = s_it->freq() / Chromosome::center_freq;
		while (Chromosome::device_list[list_index] !='\0' ) {
			line_length = getVal(list_index);
			if (line_length > 90 or line_length < 20) { 
				line_fitness += 10000;
			}
			switch(Chromosome::device_list[list_index]){
			  case 's':
			  case 'S':
				  point = ShortStub(point,freqratio*line_length);
				  break;
			  case 't':
			  case 'T':
				  point = Tline(point, freqratio*line_length);
				  break;
			  case 'o':
			  case 'O':
				  if (line_length > 75) { line_fitness += 10000; }
				  point = OpenStub(point, freqratio*line_length);
				  break;
			}
			++list_index;
		}
		double temp = abs(point - t_it->S11());
		line_fitness += temp * temp;
		// check constraint
		if (s_it->freq() > Chromosome::down_freq && s_it->freq() < up_freq && temp > Chromosome::RL) {
			within_constraint = false;
		}
	}
	return line_fitness;
}

bool Chromosome::isCheck() const
{
	return checked;
}

void Chromosome:: output() const
{
	cout << "chromosome result\n";
	for (int i = 0; i < length; ++i) {
		cout << "electric length of " << i << "th line is: " << getVal(i)<< endl;
	}
}

// OneMax
double Chromosome::oneMax () const
{
    int i;
    double result = 0;

    for (i = 0; i < length; i++)
        result += gene[i];

    return result;
}


Chromosome & Chromosome::operator= (const Chromosome & c)
{
    int i;

    if (length != c.length) {
        length = c.length;
        delete[]gene;
        init (length);
    }

    evaluated = c.evaluated;
    fitness = c.fitness;

    for (i = 0; i < length; i++)
        gene[i] = c.gene[i];

    return *this;
}


void Chromosome::printf () const
{
    int i;
    for (i = 0; i < length; i++)
        cout << gene[i] <<",";
}


int Chromosome::getLength () const
{
    return length;
}


double Chromosome::getMaxFitness () const
{
    // For OneMax
    return ((double)length-1e-6);
}
