#include <algorithm>
#include <crypt.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
void findPass(string pass, const string& hash)
{
    crypt_data* pCryptData = new crypt_data;
    size_t pos = hash.find_last_of('$');
    string hashHead = hash.substr(0, pos);
    do {
	string newHash(crypt_r(pass.data(), hashHead.data(), pCryptData));
	if(newHash == hash) {
	    cout << "Hash: " << hash << endl << "Pass: " << pass << endl;
	    break;
	}
    } while(next_permutation(pass.begin(), pass.end()));
    delete pCryptData;
}
int main()
{
    ifstream file("/home/artem/hashes1.txt");
	if(!file.good())
		cout<<"file not good!!!"<<endl;
    string pass = "123456789";
    string x;
    while((file >> x).good()) {
	findPass(pass, x);
    }
    return 0;
}