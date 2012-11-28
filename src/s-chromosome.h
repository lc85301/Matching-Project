/***************************************************************************
 *   Copyright (C) 2004 by Tian-Li Yu                                      *
 *   tianliyu@cc.ee.ntu.edu.tw                                             *
 ***************************************************************************/

#ifndef _S_CHROMOSOME_H
#define _S_CHROMOSOME_H

#include <string>
using namespace std;

class S_Chromosome
{
    public:
        S_Chromosome ();

        //~S_Chromosome ();

        S_Chromosome& operator= (const S_Chromosome & c);

        void init (string _gene);

        string getVal () const;
        void setVal (string val);

        double getFitness ();

        /** real evaluator */
        double evaluate ();
        double subGA(); //add by georgemouse

        bool isEvaluated () const;

        void printf () const;

        int getLength () const;

        static int nInitial;
        static int selectionPressure;
        static double pc;
        static double pm;
        static double p_winner;
        static int maxGen;
        static int maxFe;
        static string source_file;
        static string target_file;
        static double centerfreq;
        static bool RTR_on;
        static int RTR_th;

    protected:
        string gene;
        int *param;
        double fitness;
        bool evaluated;
};
#endif
