#include <string>
#include <iostream>

#include "LUrlParser.h"

using namespace std;

int main()
{
	LUrlParser::clParseURL URL = LUrlParser::clParseURL::ParseURL( "https://John:Dow@github.com:80/corporateshark/LUrlParser" );

	if ( URL.IsValid() )
	{
		cout << "Scheme    : " << URL.m_Scheme << endl;
		cout << "Host      : " << URL.m_Host << endl;
		cout << "Port      : " << URL.m_Port << endl;
		cout << "Path      : " << URL.m_Path << endl;
		cout << "Query     : " << URL.m_Query << endl;
		cout << "Fragment  : " << URL.m_Fragment << endl;
		cout << "User name : " << URL.m_UserName << endl;
		cout << "Password  : " << URL.m_Password << endl;
	}

	return 0;	
}
