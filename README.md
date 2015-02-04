**URL/URI Parser**

(C) Sergey Kosarevsky, 2015

support@linderdaum.com

http://www.linderdaum.com
http://blog.linderdaum.com

=============================

A tiny URL/URI parser in C++.

=============================

Usage example:

	LUrlParser::clParseURL URL = LUrlParser::clParseURL::ParseURL( UriString );

	if ( !URL.IsValid() ) return false;
	
	std::string Name     = URL.m_UserName;
	std::string Password = URL.m_Password;

=============================
