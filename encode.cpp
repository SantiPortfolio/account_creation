#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

string encoder(string to_Encrypt, int key)
{
    string encrypted_Word;
    for(int i=0; i<to_Encrypt.length(); i++)
    {
        if(isupper(to_Encrypt[i]))
        {
            encrypted_Word += char(int(to_Encrypt[i] + key - 65) % 26 + 65);
        }
        else
        {
            encrypted_Word += char(int(to_Encrypt[i] + key - 97) % 25 + 97);
        }
    }
    return encrypted_Word;
}