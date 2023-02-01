// Andy Wagner
// Computer Architechture
// Cache Simulator

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#define ROWS 16

using namespace std;

string hex2bin(string);

int main()
{
	ifstream inputFile;
	inputFile.open("input.txt");

	int OFFSET = 6; // OFFSET 64B block -->  2^6 = 6 bits
	int INDEX = 3;	// INDEX 512B/64B --> 2^9/2^6 = 2^3 = 3 bits
	int TAG = 7;	// TAG 16 bits - 6 bits - 3 bits = tag (7 bits)

	string addr[16];
	int val[16];
	string temp;
	string temp2;

	string addr_bin[16];
	string tag[16];
	string offset[16];
	string index[16];
	string HitMiss[16];

	string set[8] = {"000", "001", "010", "011", "100", "101", "110", "111"};
	int V[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	string Ftag[8];
	int Fdata[8];

	int miss = 0;
	int hit = 0;

	for (unsigned int i = 0; i < ROWS; i++)
	{
		inputFile >> addr[i];
		inputFile >> val[i];
		addr_bin[i] = hex2bin(addr[i]);
		temp = addr_bin[i];

		for (unsigned int j = 0; j < 7; j++)
		{
			tag[i] = tag[i] + temp[j];
		}
		for (unsigned int j = 7; j < 10; j++)
		{
			index[i] = index[i] + temp[j];
		}
		for (unsigned int j = 10; j < 16; j++)
		{
			offset[i] = offset[i] + temp[j];
		}
	}

	////for (unsigned int i = 0; i < ROWS; i++) {
	////	cout << "Mem Addr: " << addr[i] << endl;
	////	cout << "Mem Addr Bin: " << addr_bin[i] << endl;
	////	cout << "Value: " << val[i] << endl;
	////	cout << "TAG     INDEX OFFSET" <<  endl << tag[i] << " " << index[i] << "   " << offset[i] << endl;
	////	cout << endl;
	////}

	for (unsigned int i = 0; i < ROWS; i++)
	{

		for (unsigned int j = 0; j < 8; j++)
		{
			if (index[i] == set[j])
			{
				if (V[j] == 0)
				{
					V[j] = 1;
					Ftag[j] = tag[i];
					Fdata[j] = val[i];
					HitMiss[i] = "M";
				}
				else if (tag[i] == Ftag[j])
				{
					HitMiss[i] = "H";
				}
				else if (tag[i] != Ftag[j])
				{
					Ftag[j] = tag[i];
					Fdata[j] = val[i];
					HitMiss[i] = "M";
				}
			}
		}
	}

	cout << "Direct-mapped cache - Final contents" << endl
		 << "Index V Tag      Data" << endl;
	for (unsigned int i = 0; i < 8; i++)
	{
		if (V[i] == 0)
		{
			Ftag[i] = " ";
			Fdata[i] = NULL;
		}
		cout << set[i] << "   " << V[i] << " " << Ftag[i] << "  " << Fdata[i] << endl;
	}
	for (unsigned int i = 0; i < ROWS; i++)
	{
		cout << addr[i] << " --> " << HitMiss[i] << endl;
		if (HitMiss[i] == "M")
		{
			miss = miss + 1;
		}
		else if (HitMiss[i] == "H")
		{
			hit = hit + 1;
		}
	}

	cout << endl
		 << "Hits: " << hit << endl
		 << "Misses: " << miss << endl;

	OFFSET = 6; // OFFSET 64B block -->  2^6 = 6 bits
	INDEX = 2;	// INDEX 512B/64B --> 2^9/(2^1+2^6) = 2^2 = 2 bits
	TAG = 8;	// TAG 16 bits - 6 bits - 2 bits = tag (8 bits)

	string addr2[16];
	int val2[16];
	string addr_bin2[16];

	string tag2[16];
	string offset2[16];
	string index2[16];

	string HitMiss2[16];
	int miss2 = 0;
	int hit2 = 0;

	for (unsigned int i = 0; i < ROWS; i++)
	{
		addr2[i] = addr[i];
		val2[i] = val[i];
		addr_bin2[i] = addr_bin[i];
		temp2 = addr_bin2[i];

		for (unsigned int j = 0; j < 8; j++)
		{
			tag2[i] = tag2[i] + temp2[j];
		}
		for (unsigned int j = 8; j < 10; j++)
		{
			index2[i] = index2[i] + temp2[j];
		}
		for (unsigned int j = 10; j < 16; j++)
		{
			offset2[i] = offset2[i] + temp2[j];
		}
	}

	string set2[4] = {"00", "01", "10", "11"};
	int V1[4] = {0, 0, 0, 0};
	int V2[4] = {0, 0, 0, 0};
	string Way1[4];
	int data1[4] = {0, 0, 0, 0};
	string Way2[4];
	int data2[4] = {0, 0, 0, 0};

	// for (unsigned int i = 0; i < ROWS; i++) {
	//	cout << "Mem Addr: " << addr[i] << endl;
	//	cout << "Mem Addr Bin: " << addr_bin[i] << endl;
	//	cout << "Value: " << val[i] << endl;
	//	cout << "TAG     INDEX OFFSET" <<  endl << tag2[i] << " " << index2[i] << "   " << offset2[i] << endl;
	//	cout << endl;
	// }
	int LastS1[4] = {0, 0, 0, 0};
	int LastS2[4] = {0, 0, 0, 0};
	for (unsigned int i = 0; i < ROWS; i++)
	{
		for (unsigned int j = 0; j < 4; j++)
		{
			if (index2[i] == set2[j])
			{
				if ((V1[j] == 0) && (LastS1[j] <= LastS2[j]))
				{
					LastS1[j] = LastS1[j] + 1;
					V1[j] = 1;
					Way1[j] = tag2[i];
					data1[j] = val2[i];
					HitMiss2[i] = "M";
				}
				if ((V2[j] == 0) && (LastS2[j] <= LastS1[j]))
				{
					LastS2[j] = LastS2[j] + 1;
					V2[j] = 1;
					Way2[j] = tag2[i];
					data2[j] = val2[i];
					HitMiss2[i] = "M";
				}
				if ((V1[j] == 1) && (tag2[i] == Way1[j]))
				{
					HitMiss2[i] = "H";
				}
				else if ((V2[j] == 1) && (tag2[i] == Way2[j]))
				{
					HitMiss2[i] = "H";
				}
				if ((V1[j] == 1) && (LastS1[j] <= LastS2[j]) && (tag2[i] != Way1[j]))
				{
					Way1[j] = tag2[i];
					data1[j] = val2[i];
					HitMiss2[i] = "M";
				}
				else if ((V2[j] == 1) && (LastS2[j] <= LastS1[j]) && (tag2[i] != Way2[j]))
				{
					Way2[j] = tag2[i];
					data2[j] = val2[i];
					HitMiss2[i] = "M";
				}
			}
		}
	}

	cout << "2-way set associative - Final contents" << endl
		 << "Index V Tag       Data" << endl;
	for (unsigned int i = 0; i < 4; i++)
	{
		if (V[i] == 0)
		{
			Way1[i] = " ";
			data1[i] = NULL;
		}
		else if (V2[i] == 0)
		{
			Way2[i] = " ";
			data2[i] = NULL;
		}
		cout << set2[i] << "    " << V1[i] << " " << Way1[i] << "  " << data1[i] << endl;
		cout << set2[i] << "    " << V2[i] << " " << Way2[i] << "  " << data2[i] << endl;
	}
	for (unsigned int i = 0; i < ROWS; i++)
	{
		cout << addr[i] << " --> " << HitMiss2[i] << endl;
		if (HitMiss2[i] == "M")
		{
			miss2 = miss2 + 1;
		}
		else if (HitMiss2[i] == "H")
		{
			hit2 = hit2 + 1;
		}
	}

	cout << endl
		 << "Hits: " << hit2 << endl
		 << "Misses: " << miss2 << endl;
	return 0;
}

string hex2bin(string hex)
{
	string bin[4];
	string binary;

	for (int i = 2; i < hex.size(); i++)
	{
		switch (hex[i])
		{
		case '0':
			bin[i - 2] = "0000";
			break;
		case '1':
			bin[i - 2] = "0001";
			break;
		case '2':
			bin[i - 2] = "0010";
			break;
		case '3':
			bin[i - 2] = "0011";
			break;
		case '4':
			bin[i - 2] = "0100";
			break;
		case '5':
			bin[i - 2] = "0101";
			break;
		case '6':
			bin[i - 2] = "0110";
			break;
		case '7':
			bin[i - 2] = "0111";
			break;
		case '8':
			bin[i - 2] = "1000";
			break;
		case '9':
			bin[i - 2] = "1001";
			break;
		case 'A':
			bin[i - 2] = "1010";
			break;
		case 'B':
			bin[i - 2] = "1011";
			break;
		case 'C':
			bin[i - 2] = "1100";
			break;
		case 'D':
			bin[i - 2] = "1101";
			break;
		case 'E':
			bin[i - 2] = "1110";
			break;
		case 'F':
			bin[i - 2] = "1111";
			break;
		}
	}

	binary = bin[0] + bin[1] + bin[2] + bin[3];

	return binary;
}
