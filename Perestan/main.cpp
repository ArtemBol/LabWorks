#include "Perestan.h"
using namespace std;
int main()
{
    string  s;
    int key;
    int op;
    cout<<"Введите количество столбцов таблицы: ";
    cin>>key;
    try{
    Perestan chipher(key);
    do {
        cout<<"Выберите операцию (0-exit, 1-encrypt, 2-decrypt): ";
        cin>>op;
        if (op > 2) {
            cout<<"Illegal operation\n";
        } else if (op >0) {
            cout<<"Введите текст: ";
            cin>>s;
                if (op==1) {
                    cout<<"Зашифрованный текст: "<<chipher.encrypt(s)<<endl;
                } else {
                    cout<<"Расшифрованный текст: "<<chipher.decrypt(s)<<endl;
                }
        }
    } while (op!=0);
    }catch(const cipher_error & e) {
        cerr<<"Error: "<<e.what()<<endl;
    }
}
