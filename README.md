Decipher Documentation
===

The program (right now it is just a prototype) aims to encrypt/decrypt (or at least approximate the key to) Caesar ciphers, Affine ciphers, and Vigenere ciphers. It is written in C++. I also included a python program that can list all possible plaintexts if given an Affine ciphertext. The solution to the ciphertext in that python program is: alpha=25, beta=16.

***

Group:
-----
**Igor Epshtein**: Caesar Cipher & Affine Cipher (done)

**Justin Cheuing**: PPT

**Stephanie Heisler**: Report

**Xinjing Wei**: Vigenere Cipher (done)

***

Usage:
-----

TBA

***

Data Structure
-----

All data structures are defined in "common.h", all function declaration is done in "common.h", some of the functions are (will be) implemented in "Decipher.cpp"

- Global variable: 

	- const double charProb[26]: stores the probability distribution (in English language) of the 26 English letters

- `Cipher<T>`

	- It is the abstract class for all the three types of ciphers
	
	- Class members:

		- string *ciphertext*: stores the encrypted message, if provided or applicable

		- string *plaintext*: stores the decrypted message, if provided or applicable

		- T *key*: stores the key

			- Caesar: an integer type

			- Affine: a data structure called [AffineKey](#AffineKey)

			- Vigenere: a string type

		- string cipherType: stores the cipher type

	- Functions:

		- void init(string, string, T, string): do initialization

		- ~Cipher( ): de-structor

		- <font color='orange'>bool</font> isEmpty( ): return <font color='orange'>true</font> if both ciphertext and plaintext are empty strings, <font color="orange">false</font> otherwise

		- setter functions: set the values of class members

		- virtual getter functions: get the values of class mebers

		- pure virutal functions:

			- <font color="orange">virtual</font> string decrypt( ) = 0;

			- <font color="orange">virtual</font> string encrypt( ) = 0;

- `CaesarCipher: Cipher<int>`

	- The class for caesar ciphers (aka, shift ciphers)

	- Class members:

		- char *shifts*[26]: stores the shifted letters (e.g. a is shifted to c, etc.)

	- Functions:

		- setters and getters: set/get the values of class members

		- init(string, string, int): initialization

		- void printShifts( ): print the shifted letters (e.g. ('a' --> 'e'))

		- <font color="orange">bool</font> isDecrypted( ): return <font color="orange">true</font> if the key is greater than 0, <font color="orange">false</font> otherwise

		- <font color="orange">friend</font> CaesarCipher operator*(<font color="pink">const</font> CaesarCipher &, <font color="pink">const</font> CaesarCipher &): apply a Caesar cipher to another encrypted Caesar cipher

		- string encrypt( ): encrypt the cipher, if applicable (not yet implmented)

		- string decrypt( ): decrypt the cipher, if applicable (not yet implemented)

- `AffineCipher: Cipher<AffineKey>`

	- The class for Affine ciphers

	- Class members:

		- int alpha, beta: the two variable that is used to encrypt the plaintext

		- char cipherToPlainArray[26]: stores the cipher letters and their corresponding plain letters (not yet implemented)

	- Functions:

		- setters and getters: set/get the values of class members

		- ~AffineCipher( ): de-structor

		- init(string, string, int, int): initialization

		- <font color="orange">bool</font> isDecrypted( ): return <font color="orange">true</font> if the key is greater than 0, <font color="orange">false</font> otherwise

		- <font color="orange">friend</font> AffineCipher operator*(<font color="pink">const</font> AffineCipher &, <font color="pink">const</font> AffineCipher &): apply an Affine cipher to another encrypted Affine cipher 

		- string encrypt( ): encrypt the cipher, if applicable (not yet implemented)

		- string decrypt( ): decrypt the cipher, if applicable (not yet implemented)

- `VigenereCipher: Cipher<string>`

	- The class for Vigenere ciphers

	- Class members:

		- int keyLength: stores the key length, either computed, or known

	- Functions:

		- init(string, string, string, int): initialization

		- <font color="orange">bool</font> isDecrypted( ): return <font color="orange">true</font> if the key is greater than 0, <font color="orange">false</font> otherwise

		- <font color="orange">friend</font> VigenereCipher operator*(<font color="pink">const</font> VigenereCipher &, <font color="pink">const</font> VigenereCipher &): apply an Affine cipher to another encrypted Vigenere cipher 

		- string encrypt( ): encrypt the cipher, if applicable (not yet implemented)

		- string decrypt( ): decrypt the cipher, if applicable (not yet implemented)

- <a name="AffineKey"></a>AffineKey:

	- A struct for the keys to Affine ciphers

	- Struct members:

		- int alpha: the factor of the plain letters

		- int beta: the value added to the factored letters

***

Algorithms:
-----

- Caesar ciphers: The algorithm of solving a Caesar cipher is to do a brute-force attack. Since there are only 26 letters, therefore there are only 25 possible keys. The program will list all possible plaintexts and let the users choose the most possible one.

- Affine ciphers: The equation for enryption is `c_i=alpha*p_i+beta`. Since alpha has only 12 possible values (all of which are co-primes to 26), and beta has only 26 possible values. Therefore, there are 12*26=312 possibilities. Hence a brute-force attack will be efficient.

- Vigenere ciphers: The algorithm is as follow (assume the max key length is 20):

		for i <-- 1 to 20, do
			for j <-- 1 to n-20, do
				if cipher[j] == cipher[j+i]
					count[i]++;
		keyLength <-- the index of max(count[1..20])

		for every keyLength letters, do
			count the number of occurrence of each letter, store them in occurLetter[26][keyLength]
			//occurLetter[0][0] stores the numebr of occurence in every keyLength letters of 'a'
			//starting from the first letter of the ciphertext

		multiply every row of occurLetter with 26 permutations of cahrProb[26], find the largest entries in each column, the corresponding letters form the key (or at least an approximation of the key)

***

Known Issues:
-----

- Cannot get the constructors working, fortunately the program does not require pointers of objects 

***

**Author: Xinjing Wei**
