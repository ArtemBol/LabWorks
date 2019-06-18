#include "Perestan.h"

Perestan::Perestan(const int key)
{
    k=key;
    if(k==1 || k<=0){
        throw cipher_error("Invalid key");
    }
}
std::string Perestan::encrypt(const std::string& t)
{
    std::string m=getValidOpenText(t);
    std::string chipher_text;
    chipher_text.clear();
    int sim=0;
    sim=m.length();
    int strok=(sim-1)/k + 1;
    char **masiv1= new char* [strok];
    for (int i = 0; i < strok; i++) {
        masiv1[i] = new char [k];
    }
    for (int i=0; i<strok; i++) {
        int p=i*k;
        for (int j=0; j<k; j++) {
            if(p+j<sim and m[p+j]>='A' and m[p+j]<='Z')
                masiv1[i][j]=m[p+j];
            else {
                masiv1[i][j]='*';
            }
        }
    }
    for (int j=k-1; j>=0; j--) {
        for (int i=0; i<strok; i++)
            if(masiv1[i][j]!='*')
                chipher_text=chipher_text+masiv1[i][j];
    }
    for (int i = 0; i<strok; i++)
        delete[] masiv1[i];
    delete[] masiv1;
    return chipher_text;
}
std::string Perestan::decrypt(const std::string& z)
{
    std::string m=getValidCipherText(z);
    std::string chipher_text;
    std::string temp;
    temp.clear();
    chipher_text.clear();
    int sim=0;
    sim=m.length();
    for(int i=sim-1; i>=0; i--)
        temp=temp+m[i];
    int strok=(sim-1)/k + 1;
    int d=k*strok-sim;
    char **masiv1= new char* [strok];
    for (int i = 0; i < strok; i++) {
        masiv1[i] = new char [k];
    }
    int p=0;
    int t=0;
    for (int j=0; j<k; j++) {
        p=j*strok;
        for (int i=0; i<strok; i++) {
            if(i==0 and j>k-1-d) {
                masiv1[i][j]='*';
                t++;
            } else
                masiv1[i][j]=temp[p+i-t];
        }
    }
    for (int i=strok-1; i>=0; i--) {
        for (int j=0; j<k; j++)
            if(masiv1[i][j]!='*')
                chipher_text=chipher_text+masiv1[i][j];
    }
    for (int i = 0; i<strok; i++)
        delete[] masiv1[i];
    delete[] masiv1;
    return chipher_text;
}
std::string Perestan::getValidOpenText(const std::string & s){
    std::string tmp;
    for (auto c:s) {
        if (isalpha(c)) {
            if (islower(c))
                tmp.push_back(toupper(c));
            else
                tmp.push_back(c);
        }
    }
    if (tmp.length()<=k)
        throw cipher_error("Short text");
    return tmp;
}
inline std::string Perestan::getValidCipherText(const std::string & s)
{
    if(s.length()<=k)
        throw cipher_error("Short cipher text");
    for (auto c:s) {
        if (!isupper(c))
            throw cipher_error(std::string("Invalid cipher text "));
    }
    return s;
}
