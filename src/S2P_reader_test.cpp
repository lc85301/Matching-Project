//*************************************************
//  by Jorgemouse 2012/11/04
//  for S2P_reader demostration
//*************************************************

#include "S2P_reader.h"

int main(){
    S2P_reader test("sample.txt");
    vector<freq_response>& list = test.get_list();

    for(vector<freq_response>::iterator it = list.begin();
        it != list.end();
        ++it){
        cout << it->freq() << " " << it->S11() << endl;
    }

    return 0;
}
