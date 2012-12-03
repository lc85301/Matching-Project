//*************************************************
//  by YodaLee 2012-11-25
//  based on the work S2P_reader.cpp by Georgemouse
//  for SnP_reader demostration
//*************************************************

#include "SnP_reader.h"

int main(){
    SnP_reader test;
    test.init("../testdata/test.s2p");
	test.print();
	vector<freq_response> point_list;
	test.get_data(2.995e+09, point_list);
	for (vector<freq_response>::iterator it = point_list.begin(); it != point_list.end(); ++it) {
		cout << it->freq() << " "<< it->value();
	}
	cout << endl;
    //vector<freq_response>& list = test.get_list();

    //for(vector<freq_response>::iterator it = list.begin();
    //    it != list.end();
    //    ++it){
    //    cout << it->freq() << " " << it->value() << endl;
    //}

    return 0;
}
