#include <algorithm>
#include <crypt.h>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
using namespace std;
void findPass(string pass, const string& hash)
{
    crypt_data* pCryptData = new crypt_data;
    size_t pos = hash.find_last_of('$');
    string hashHead = hash.substr(0, pos);
    do {
	string newHash(crypt_r(pass.data(), hashHead.data(), pCryptData));
	if(newHash == hash) {
	    static mutex mtx;
	    {
		lock_guard<mutex> lock(mtx);
		cout << "Hash: " << hash << endl << "Pass: " << pass << endl;
		break;
	    }
	}
    } while(next_permutation(pass.begin(), pass.end()));
    delete pCryptData;
}
int main()
{
    ifstream file("/home/artem/hashes1.txt");
    if(!file.good())
	cout << "file not good!!!" << endl;
    string pass = "123456789";
    string x;
    string y;
    thread th_1;
    thread th_2;
    while((file >> x).good()) {
	th_1 = thread(findPass, pass, x);
	if((file >> y).good())
	    th_2 = thread(findPass, pass, y);
	if(th_1.joinable())
	    th_1.join();
	if(th_2.joinable())
	    th_2.join();
    }
    return 0;
}