/*
* IJC-DU2, příklad 1b, 20.4.2013
* Autor: Lukáš Vokráčko, FIT
*/

#include <iostream>
#include <fstream>
#include <string>
#include <queue>

int tail(int numLines, std::istream& f)
{
	int linesRead = 0;
	std::string str;

	if(numLines < 0)
	{
		//tisk řádků od konce
		numLines *= -1;
		std::queue<std::string> l;
		while(!f.eof())
		{
			std::getline(f, str);
			if(f.eof() && str.empty()) break;
			if(++linesRead > numLines)
			{
				l.pop();
			}
			l.push(str);
		}

		for(int i = 0; i < numLines; ++i)
		{
			if(i < linesRead)
			{
				std::cout << l.front() << std::endl;
				l.pop();
			}
		}
	}
	else
	{
		//tisk od řádku
		while(!f.eof())
		{
			std::getline(f, str);
			if(f.eof() && str.empty()) break;
			if(++linesRead >= numLines)
			{
				std::cout << str << std::endl;
			}
		}
	}

	return 0;
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int numLines = -10;
	int res, n = 1;
	char* endptr;
	std::istream* f = &std::cin;
	std::ifstream ff;

	if(argc > 4)
	{	//moc parametrů
		std::cerr << "Neplatný počet parametrů" << std::endl;
		return 1;
	}
	else if(argc == 2)
	{	//zadán pouze soubor
		ff.open(argv[1]);
		f = &ff;
	}
	else if(argc > 2)
	{
		if(argc == 4)
		{	//počet řádků i se souborem, zkouším jestli je soubor zadán jako 1. nebo 3. parametr
			ff.open(argv[3]);
			if(f == NULL)
			{
				n = 2;
				ff.open(argv[1]);
			}
			f = &ff;
		}

		numLines = strtod(argv[n+1], &endptr);
		numLines *= -1;
		if(argv[n] != std::string("-n") || *endptr != '\0')
		{
			std::cerr << "Neplatné parametry" << std::endl;
			if(argc == 4) ff.close();
			return 1;
		}

		if(numLines == 0)
		{
			if(argc == 4) ff.close();
			return 0;
		}

		if(*argv[n+1] == '+' || *argv[n+1] == '-')
		{
			numLines *= -1;
		}
	}

	if(f != &std::cin && ff == NULL)
	{
		std::cerr << "Soubor se nepodařilo otevřít" << std::endl;
		return 1;
	}

	res = tail(numLines, *f);
	ff.close();

	if(res != 0)
	{
		std::cerr << "Došlo k chybě při čtení" << std::endl;
		return 1;
	}

	return 0;
}