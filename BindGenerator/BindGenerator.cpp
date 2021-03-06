// BindGenerator.cpp : Defines the entry point for the console application.
// Parameter 1: Source text filename
// Parameter 2: Alias name, unique"
// Parameter 3: Key to ind f.e "kp_5" (optional)

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <clocale>
#include <string>

int main(int argc, char *argv[])
{
	using namespace std;
	setlocale(LC_ALL, "");

	if (argc < 3)
	{
		cerr << "Not enough parameters.\n"
			"BindGenerator.exe generates config file for CS:GO (or other source games). It creates an alias, which when used, sends chat messages containing next line of source text file. At the end the text will loop. Put contents of output file Bind.cfg to autoexec.cfg file.\n\n"
			"Syntax is: BindGenerator.exe <source> <alias> [<key>]\n"
			"\tsource:\tSource text file\n"
			"\talias:\tAlias name, f.e \"mytrashtalk\"\n"
			"\tkey:\t(Optional) Key which will loop the text (f.e 'KP_END' for NUM1). When used, output config will contain a command binding text loop to the specified key.\n";
		exit(1);
	}

	wifstream intf(argv[1]);

	if (!intf)
	{
		cerr << "Could not open " << argv[1] << " file.\n";
		exit(1);
	}

	wofstream outf("Bind.cfg", ios::trunc);

	if (!outf)
	{
		cerr << "Could not create output config file.\n";
		exit(1);
	}

	wstring wers;
	wstring nazwa;
	string s_nazwa(argv[2]);

	nazwa.assign(s_nazwa.begin(), s_nazwa.end());

	int numer{ 1 };

	outf << "alias " << nazwa << " " << nazwa << numer << endl;


	while (intf)
	{
		getline(intf, wers);
		outf << "alias " << nazwa << numer << " \"say " <<
			wers << "; alias " << nazwa << " " << nazwa << numer + 1 << ";\"\n";
		numer++;
	}
	
	outf << "alias " << nazwa << numer << " " << nazwa << "1;\n";
	

	if (argc > 3)
	{
		outf << "bind " << argv[3] << " " << nazwa << ";\n";
	}

    return 0;
}

