/*

 * DeciperDemo.cpp
 *
 *  Created on: 2014.10.15
 *      Author: Dante
 */


#include <iostream>
#include <string.h>
#include "common.h"

using namespace std;

int main(int argc, char **argv)
{
	CaesarCipher cc, cc1;
	cc.init("abcd", "bcde", 1);
	cc1.init("bcde", "efgi");
	CaesarCipher cComposed=cc*cc1;
	cout << cComposed.getKey() << endl;
	cComposed.printShifts();
	CaesarCipher cc2;
	cc2.init("abcd");

	cout << cc2.getCiphertext() << endl;

	return 0;
}
