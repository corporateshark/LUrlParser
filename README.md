**Lightweight URL & URI parser (RFC 1738, RFC 3986)**

(C) Sergey Kosarevsky, 2015-2020

@corporateshark sk@linderdaum.com

http://www.linderdaum.com

http://blog.linderdaum.com

=============================

A tiny and lightweight URL & URI parser (RFC 1738, RFC 3986) written in C++.

=============================

Usage example:

	const auto URL = LUrlParser::ParseURL::ParseURL( "https://John:Dow@github.com:80/corporateshark/LUrlParser" );

	if ( URL.isValid() )
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

=============================
