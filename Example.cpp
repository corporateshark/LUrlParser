#include <string>
#include <iostream>

#include "LUrlParser.h"

using namespace std;

int main()
{
	const auto URL = LUrlParser::ParseURL::parseURL("https://John:Dow@github.com:80/corporateshark/LUrlParser/?&query=ssl#q=frag");

	if (URL.isValid())
	{
		cout << "Scheme    : " << URL.scheme_ << endl;
		cout << "Host      : " << URL.host_ << endl;
		cout << "Port      : " << URL.port_ << endl;
		cout << "Path      : " << URL.path_ << endl;
		cout << "Query     : " << URL.query_ << endl;
		cout << "Fragment  : " << URL.fragment_ << endl;
		cout << "User name : " << URL.userName_ << endl;
		cout << "Password  : " << URL.password_ << endl;
	}
	else
	{
		cout << "Parsing error: " << URL.errorCode_ << endl;
	}

	return 0;
}
