**Lightweight URL & URI parser (RFC 1738, RFC 3986)**

(C) Sergey Kosarevsky, 2015

support@linderdaum.com

http://www.linderdaum.com
http://blog.linderdaum.com

=============================

A tiny and lightweight URL & URI parser (RFC 1738, RFC 3986) written in C++.

=============================

Usage example:

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

=============================
