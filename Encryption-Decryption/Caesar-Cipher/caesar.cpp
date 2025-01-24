/*
Author: Joyce Vieira Ferreira Dos Santos
Course: CSCI-136
Instructor: Tong Yi
Assignment: Lab6 B

This program will report all characthers from the input encrypted with ceaser cipher method.
*/

#include <iostream>
#include <string>
using namespace std;



char shiftChar(char c, int rshift) {

	char temp = c;

	if (65 <= int(temp) && int(temp) <= 90) {
		temp += rshift;

		if (int(temp) > 90) {
			temp -= 26;
		}
	}
	else if (97 <= int(temp) && int(temp) <= 122) {
		if (int(temp) + rshift > 122) {
			temp = temp - 26 + rshift;
		}
		else {
			temp += rshift;
		}
	}
	return temp;
}

string encryptCaesar(string plaintext, int rshift) {
	string returnString = "";

	for (int i = 0; i < plaintext.length(); i++) {
		returnString += shiftChar(plaintext[i], rshift);
	}
	return returnString;

}
int main() {

	string inputString;
	int shift;

	cout << "Enter a text: " << endl;
	getline(cin, inputString);

	cout << "Chose a shift to encrypt: " << endl;
	cin >> shift;



	cout << encryptCaesar(inputString, shift) << endl;


	return 0;
}
