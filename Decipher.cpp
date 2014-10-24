/*

 * Decipher.cpp
 *
 *  Created on: 2014.10.13
 *      Author: Dante
 */

#include <iostream>
#include <string.h>
#include <cassert>
#include "common.h"

//Encrypt & decrypt functions for all ciphers
string CaesarCipher::encrypt()
{

	return "";
}

string CaesarCipher::decrypt()
{
	return "";
}

string AffineCipher::encrypt()
{
	return "";
}

string AffineCipher::decrypt()
{
	return "";
}

string VigenereCipher::encrypt()
{
	return "";
}

string VigenereCipher::decrypt()
{
	return "";
}

//cipher compositions (of the same type)
//no need to check the key as long as the ciphertext of the first one equals the plaintext of the second one
AffineCipher operator*(const AffineCipher &a1, const AffineCipher &a2)
{

	assert(((a2.alpha != 0 && a2.ciphertext.compare("") == 0 && a2.plaintext.compare("") == 0) || (a1.ciphertext.compare(a2.plaintext) == 0)) && "Cipher composition failed, text doesn't match.");
	AffineCipher result;
	result.init(a1.plaintext, a1.ciphertext, (a1.alpha*a2.alpha), (a2.alpha*a1.beta+a2.beta));
	if (a2.ciphertext.compare("") == 0)
			result.encrypt();
	return result;
}

CaesarCipher operator*(const CaesarCipher &c1, const CaesarCipher &c2)
{
	assert(((c2.key != 0 && c2.ciphertext.compare("") == 0 && c2.plaintext.compare("") == 0) || (c1.ciphertext.compare(c2.plaintext) == 0)) && "Cipher composition failed, text doesn't match.");
	CaesarCipher result;

	result.init(c1.plaintext, c2.ciphertext, ((c1.key + c2.key) % 26));
	if (c2.ciphertext.compare("") == 0)
			result.encrypt();
	return result;
}

VigenereCipher operator*(const VigenereCipher &v1, const VigenereCipher &v2)
{
	assert(((v2.key.compare("") && v2.ciphertext.compare("") == 0 && v2.plaintext.compare("") == 0) || (v1.ciphertext.compare(v2.plaintext) == 0)) && "Cipher composition failed, text doesn't match.");
	VigenereCipher result;

	string s="";
	for (int i=0; i<v1.keyLength; i++)
	{
		int k1=(static_cast<int> (v1.key.at(i))) - 97;
		int k2=(static_cast<int> (v2.key.at(i))) - 97;
		s+=static_cast<char> (((k1 + k2) % 26) + 97);
	}

	result.init(v1.plaintext, v2.ciphertext, s);
	if (v2.ciphertext.compare("") == 0)
			result.encrypt();
	return result;
}
