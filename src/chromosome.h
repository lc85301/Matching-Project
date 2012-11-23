/***************************************************************************
 *   Copyright (C) 2004 by Tian-Li Yu                                      *
 *   tianliyu@cc.ee.ntu.edu.tw                                             *
 ***************************************************************************/

#ifndef _CHROMOSOME_H
#define _CHROMOSOME_H

#include "S2P_reader.h"


class Chromosome
{
    public:
        Chromosome ();
        Chromosome (int n_ell);

        ~Chromosome ();

        Chromosome& operator= (const Chromosome & c);

        void init (int n_ell);

        int getVal (int index) const;
        void setVal (int index, int val);

        double getFitness ();

        /** real evaluator */
        double evaluate ();

        double oneMax () const;

		// add by yodalee and georgemouse
        double matching () const;
		void output() const;
		// end add

        bool isEvaluated () const;

        void printf () const;

        int getLength () const;

        double getMaxFitness () const;

		static S2P_reader source_list;
		static S2P_reader target_list;
		static string device_list;
		static double center_freq;
		//static double up_freq;
		//static double down_freq;
		//static souble RL_req;
    protected:
        int *gene;
        int length;
        double fitness;
        bool evaluated;
};
#endif
