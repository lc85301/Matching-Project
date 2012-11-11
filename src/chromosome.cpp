/*;***************************************************************************
 *   Copyright (C) 2004 by Tian-Li Yu                                      *
 *   tianliyu@cc.ee.ntu.edu.tw                                             *
 ***************************************************************************/

#include <cstdio>
#include <vector>
#include <cmath>
#include "global.h"
#include "chromosome.h"
#include "line_operator.cpp"

S2P_reader Chromosome::source_list;
S2P_reader Chromosome::target_list;
string Chromosome::device_list;
double Chromosome::center_freq;

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

    gene = new bool[length];
    evaluated = false;
}

int Chromosome::getVal (int index) const
{
    if (index < 0 || index > length)
        outputErrMsg ("Index overrange in Chromosome::operator[]");

    return (gene[index])? 1:0;
}


void Chromosome::setVal (int index, int val)
{
    if (index < 0 || index > length)
        outputErrMsg ("Index overrange in Chromosome::operator[]");

    gene[index] = (val==1)? true:false;
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
    //return oneMax ();
	return matching ();
}

//********************************************
// Function: get_line_length
// Description: get the length of specific part
//	ex: chromosome 10101101....1111111
//	get_line_length(0), return 127
//********************************************
int Chromosome::get_line_length(int part_num) const{
	int start_point = part_num * 7;
	int ratio = 1;
	int line_length = 0;
	for (int i = start_point; i < start_point+7; ++i) {
		if (gene[i]) {
			line_length += ratio;
		}
		ratio *= 2;
	}
	return line_length;
}

double Chromosome::matching() const{
	double line_fitness;
	int list_index = 0;
	complex<double> point;
	double freqratio;
	int line_length;
	vector<freq_response>& source = Chromosome::source_list.get_list();
	vector<freq_response>& target = Chromosome::target_list.get_list();
	

	for (vector<freq_response>::iterator s_it = source.begin(), t_it = target.begin();
		 s_it != source.end(), t_it != target.end();
		 ++s_it, ++t_it
		 ) {
		list_index = 0;
		while (Chromosome::device_list[list_index] != EOF) {
			point = s_it->S11();
			freqratio = s_it->freq() / Chromosome::center_freq;
			line_length = get_line_length(list_index);
			switch(Chromosome::device_list[list_index]){
			  case 's':
			  case 'S':
				  point = ShortStub(point, freqratio,line_length );
				  break;
			  case 't':
			  case 'T':
				  point = Tline(point, freqratio, line_length);
				  break;
			  case 'o':
			  case 'O':
				  point = OpenStub(point, freqratio, line_length);
				  break;
			}
			++list_index;
		}
		line_fitness += abs(point - t_it->S11());
		++t_it;
	}
	return line_fitness;
}

void Chromosome:: output() const
{
	//!! 7 is a const
	cout << "chromosome result\n";
	for (int i = 0; i < length/7; ++i) {
		cout << "electric length of " << i << "th line is: " << get_line_length(i)<< endl;
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
        ::printf ("%d", gene[i]);
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
