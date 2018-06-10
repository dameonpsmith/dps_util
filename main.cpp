#include "dps_util.hpp"
#include <sstream>
#include <iostream>

using namespace std;
using namespace dps;

int main()
{
    stringstream ss{"red,\"ora,nge\",yellow\ngreen,blue,indigo"};
    std::vector<std::vector<std::string>> r;
    ss>>r;
    delimiters.quote='#';
    cout<<r;
    return 0;
}

