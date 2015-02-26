#include <string>
#include <iostream>

#include "LUrlParser.h"

using namespace std;
using LUrlParser::clParseURL;

int main()
{
	clParseURL URL = clParseURL::ParseURL( "https://John:Dow@github.com:80/corporateshark/LUrlParser/?&query=ssl#q=frag" );

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
	else
	{
		cout << "Parsing error: " << URL.m_ErrorCode << endl;
	}

	return 0;	
}
