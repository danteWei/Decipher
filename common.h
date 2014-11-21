/*
 * common.h
 *      Author: Xinjing Wei
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <iostream>
#include <string.h>
#include <cassert>
#include <map>

//stores the probabilities of all letters in English
const double charProb[26]={0.082, 0.001, 0.020, 0.001, 0.023, 0.010, 0.028, 0.091, 0.063, 0.060, 0.001, 0.019, 0.075, 0.067, 0.024, 0.040, 0.008, 0.002, 0.070, 0.061, 0.020, 0.022, 0.127, 0.043, 0.028, 0.015};

using namespace std;

//stores the key to an Affine cipher
typedef struct AffineKey
{
	int alpha;
	int beta;
} AffineKey;


//abstract class for ciphers
template <typename T>
class Cipher
{
protected:
	string ciphertext;		//stores the encrypted message
	string plaintext;		//stores the original message
	T key;				//stores the key, if applicable
	string cipherType;		//stores the cipher type

public:
	void init(string pt="", string ct="", T key=NULL, string cipherType="")
	{
		if (pt.length() != 0 && ct.length() != 0)
			assert(pt.length() == ct.length() && "Lengths of the plaintext and the ciphertext don't match.");
		plaintext=pt;
		ciphertext=ct;
		this->key=key;
		this->cipherType=cipherType;
	}
	
	//a cipher is empty if both the plaintext and the ciphertext are empty strings
	bool isEmpty()
	{
		bool result=false;
		if (plaintext.length() == 0 && ciphertext.length() == 0)
		{
			cout << "The " << cipherType << " cipher is empty." << endl;
			result=true;
		}
		return result;
	}

	//setter
	void setPlaintext(string pt){ this->plaintext=pt; }
	void setKey(T key){ this->key=key; }
	void setCiphertext(string ct){ this->ciphertext=ct; }
	void setCipherType(string type){ cipherType=type; }

	//getter
	virtual string getCiphertext()
	{
		if (isEmpty())
			return "";
		else if (ciphertext.length() == 0)
		{
			cout << "The cipher is not encrypted." << endl;
			return "";
		}
		return ciphertext;
	};

	virtual string getPlaintext()
	{
		if (isEmpty())
			return "";
		else if (plaintext.length() == 0)
		{
			cout << "The cipher is not encrypted." << endl;
			return "";
		}
		return plaintext;
	};

	T getKey(){ return key; };
	virtual string getCipherType()
	{
		if (cipherType.length() == 0)
		{
			cout << "The cipher type is not specified." << endl;
			return "";
		}
		return cipherType;
	}

	//virtual member functions
	virtual string decrypt() = 0;
	virtual string encrypt() = 0;
};

class CaesarCipher: public Cipher<int>
{
private:
	char shifts[26];		//stores the shifts for all 26 letters
public:
	//initialization
	void init(string pt="", string ct="", int shift=0)
	{
		//bound the key to Z_26
		if (shift > 26)
			shift %= 26;
		//check if the shift is correct
		if (pt.length() != 0 && ct.length() != 0)
		{
			char pc=pt.at(0);
			char cc=ct.at(0);
			//calculate the real key
			int realKey=static_cast<int>(cc)-static_cast<int>(pc);
			//bound it to Z_26
			while (realKey < 0)
				realKey+=26;
			if (realKey > 26)
				realKey%=26;
			//the two keys don't match, correct the entered key
			if (shift != realKey)
			{
				if (shift != 0)
					cout << "The key you entered (" << shift << ")"
							<< " does not match the real key (" << realKey << ")"
							<< " to this cipher, the program will set the key to the real key."
							<< endl;
					shift=realKey;
			}
		}
		//calculate the shifted letters
		for (int i=0; i<26; i++)
		{
			char n=static_cast<char> (((i + shift) % 26) + 97);
			if (n >122)
				n-=26;
			shifts[i]=n;
		}
		Cipher<int>::init(pt, ct, shift, "Caesar");
	}

	//getter
	int getShift(){ return key; }
	string getCiphertext(){ return Cipher<int>::getCiphertext(); }
	string getPlaintext(){ return Cipher<int>::getPlaintext(); }
	string getCipherType()
	{
		if (cipherType.length() == 0)
			Cipher<int>::setCipherType("Caesar");
		return Cipher<int>::getCipherType();
	}
	//print the shifted letters
	void printShifts()
	{
		if (key == 0)
			cout << "Fail to print the shifts, the cipher is not yet decrypted." << endl;
		else
		{
			cout << "[";
			for (int i=0; i<26; i++)
			{
				char plainLetter=static_cast<char> (i + 97);
				if (i != 25)
					cout << "(\'" << plainLetter << "\' --> "
							<< "\'" << shifts[i] << "\'), ";
				else
					cout << "(\'" << plainLetter << "\' --> "
							<< "\'" << shifts[i] << "\')";

			}
			cout << "]\n";
		}
	}

	//determine if the cipher is decrypted or not
	bool isDecypted(){ return Cipher<int>::getKey() > 0; }

	//Caesar cipher composition
	friend CaesarCipher operator*(const CaesarCipher&, const CaesarCipher&);

	string encrypt();
	string decrypt();
};

class AffineCipher: public Cipher<AffineKey>
{
private:
	int alpha, beta;		//stores the "keys" to an Affine cipher
	char cipherToPlainArray[];
public:
	//initialization
	void init(string pt="", string ct="", int alpha=0, int beta=0)
	{
		this->alpha=alpha;
		this->beta=beta;
		AffineKey key;
		key.alpha=alpha;
		key.beta=beta;

		Cipher<AffineKey>::init(pt, ct, key, "Affine");
	}
	//determine if the cipher is decrypted or not
	bool isDecypted(){ return alpha != 0; }
	
	 //return inverse modulu for decription method
    int modmulinverse()
    {
        int x = 0,y = 1,u = 1,v = 0;
        int e = 26,f =alpha;
        int c,d,q,r;
        while(f != 1)
        {
            q = e/f;
            r = e%f;
            c = x-q*u;
            d = y-q*v;
            x = u;
            y = v;
            u = c;
            v = d;
            e = f;
            f = r;
        } 
        u = (u+26)%26;
        return u;
    }

	//getter
	int getAlpha(){ return key.alpha; }
	int getBeta(){ return key.beta; }

	string getPlaintext(){ return Cipher<AffineKey>::getPlaintext(); }
	string getCiphertext(){ return Cipher<AffineKey>::getCiphertext(); }
	string getCipherType()
	{
		if (cipherType.length() == 0)
			Cipher<AffineKey>::setCipherType("Affine");
		return Cipher<AffineKey>::getCipherType();
	}

	AffineKey getKey(){ return Cipher<AffineKey>::getKey(); }
	//Affine cipher composition
	friend AffineCipher operator*(const AffineCipher&, const AffineCipher&);

	string encrypt();
	string decrypt();
};

class VigenereCipher: public Cipher<string>
{
private:
	int keyLength;		//stores the keyLength, either computed, or known
	//stores the probability distribution of 26 letter, used for decryption

public:
	//initialization
	void init(string pt="", string ct="", string key="", int keyLen=0)
	{
		Cipher<string>::init(pt, ct, key, "Vigenere");
		keyLength=(keyLen >= key.length() ? keyLen : key.length());
	}

	bool isDecrypted(){ return keyLength == 0; }

	//getter
	string getPlaintext(){ return Cipher<string>::getPlaintext(); }
	string getCiphertext(){ return Cipher<string>::getCiphertext(); }
	string getCipherType()
	{
		if (cipherType.length() == 0)
			Cipher<string>::setCipherType("Vigenere");
		return Cipher<string>::getCipherType();
	}
	int getKeyLength(){ return keyLength; }
	const double *getCharProb(){ return charProb; }

	//Vigenere cipher composition
	friend VigenereCipher operator*(const VigenereCipher&, const VigenereCipher&);

	string encrypt();
	string decrypt();
};


#endif /* COMMON_H_ */
