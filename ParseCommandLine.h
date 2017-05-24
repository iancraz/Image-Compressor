#pragma once
#define PARSER_ERROR	-1
typedef bool(*pCallback) (char *, char*, void *);

class ParseCommandLine
{
public:
	ParseCommandLine(int argc, char *argv[]);
	int PCL(pCallback p, void *userData);
protected:
	int argc;
	char**argv;
};