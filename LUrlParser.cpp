/*
 * Lightweight URL & URI parser (RFC 1738, RFC 3986)
 * Copyright (C) 2015 Sergey Kosarevsky (sk@linderdaum.com)
 * All rights reserved.
 * https://github.com/corporateshark/LUrlParser
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must display the name 'Sergey Kosarevsky'
 *    in the credits of the application, if such credits exist.
 *    The authors of this work must be notified via email (sk@linderdaum.com) in
 *    this case of redistribution.
 *
 * 3. Neither the name of copyright holders nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "LUrlParser.h"

#include <algorithm>
#include <cstring>
#include <stdlib.h>

// check if the scheme name is valid
static bool IsSchemeValid( const std::string& SchemeName )
{
	for ( auto c : SchemeName  )
	{
		if ( !isalpha( c ) && c != '+' && c != '-' && c != '.' ) return false;
	}

	return true;
}

bool LUrlParser::clParseURL::GetPort( volatile int* OutPort ) const
{
	if ( !m_Valid ) { return false; }

	int Port = atoi( m_Port.c_str() );

	if ( Port <= 0 || Port > 65535 ) { return false; }

	if ( OutPort ) { *OutPort = Port; }

	return true;
}

// based on RFC 1738 and RFC 3986
LUrlParser::clParseURL LUrlParser::clParseURL::ParseURL( const std::string& URL )
{
	LUrlParser::clParseURL Result;

	const char* CurrentString = URL.c_str();

	/*
	 *	<scheme>:<scheme-specific-part>
	 *	<scheme> := [a-z\+\-\.]+
	 *	For resiliency, programs interpreting URLs should treat upper case letters as equivalent to lower case in scheme names
	 */

	// try to read scheme
	{
		const char* LocalString = strchr( CurrentString, ':' );

		if ( !LocalString )
		{
			// no scheme character
			return clParseURL();
		}

		// save the scheme name
		Result.m_Scheme = std::string( CurrentString, LocalString - CurrentString );

		if ( !IsSchemeValid( Result.m_Scheme ) )
		{
			// invalid scheme name
			return clParseURL();
		}

		// scheme should be lowercase
		std::transform( Result.m_Scheme.begin(), Result.m_Scheme.end(), Result.m_Scheme.begin(), ::tolower );

		// skip ':'
		CurrentString = LocalString+1;
	}

	/*
	 *	//<user>:<password>@<host>:<port>/<url-path>
	 *	any ":", "@" and "/" must be normalized
	 */

	// skip "//"
	if ( *CurrentString++ != '/' ) return clParseURL();
	if ( *CurrentString++ != '/' ) return clParseURL();

	// check if the user name and password are specified
	bool bHasUserName = false;

	const char* LocalString = CurrentString;

	while ( *LocalString )
	{
		if ( *LocalString == '@' )
		{
			// user name and password are specified
			bHasUserName = true;
			break;
		}
		else if ( *LocalString == '/' )
		{
			// end of <host>:<port> specification
			bHasUserName = false;
			break;
		}

		LocalString++;
	}

	// user name and password
	LocalString = CurrentString;

	if ( bHasUserName )
	{
		// read user name
		while ( *LocalString && *LocalString != ':' && *LocalString != '@' ) LocalString++;

		Result.m_UserName = std::string( CurrentString, LocalString - CurrentString );

		// proceed with the current pointer
		CurrentString = LocalString;

		if ( *CurrentString == ':' )
		{
			// skip ':'
			CurrentString++;

			// read password
			LocalString = CurrentString;

			while ( *LocalString && *LocalString != '@' ) LocalString++;

			Result.m_Password = std::string( CurrentString, LocalString - CurrentString );

			CurrentString = LocalString;
		}

		// skip '@'
		if ( *CurrentString != '@' )
		{
			return clParseURL();
		}

		CurrentString++;
	}

	bool bHasBracket = ( *CurrentString == '[' );

	// go ahead, read the host name
	LocalString = CurrentString;

	while ( *LocalString )
	{
		if ( bHasBracket && *LocalString == ']' )
		{
			// end of IPv6 address
			LocalString++;
			break;
		}
		else if ( !bHasBracket && ( *LocalString == ':' || *LocalString == '/' ) )
		{
			// port number is specified
			break;
		}

		LocalString++;
	}

	Result.m_Host = std::string( CurrentString, LocalString - CurrentString );

	CurrentString = LocalString;

	// is port number specified?
	if ( *CurrentString == ':' )
	{
		CurrentString++;

		// read port number
		LocalString = CurrentString;

		while ( *LocalString && *LocalString != '/' ) LocalString++;

		Result.m_Port = std::string( CurrentString, LocalString - CurrentString );

		CurrentString = LocalString;
	}

	// end of string
	if ( !*CurrentString )
	{
		return clParseURL();
	}

	// skip '/'
	if ( *CurrentString != '/' )
	{
		return clParseURL();
	}

	CurrentString++;

	// parse the path
	LocalString = CurrentString;

	while ( *LocalString && *LocalString != '#' && *LocalString != '?' ) LocalString++;

	Result.m_Path = std::string( CurrentString, LocalString - CurrentString );

	CurrentString = LocalString;

	// check for query
	if ( *CurrentString == '?' )
	{
		// skip '?'
		CurrentString++;

		// read query
		LocalString = CurrentString;

		while ( *LocalString && *LocalString != '#' ) LocalString++;

		Result.m_Query = std::string( CurrentString, LocalString - CurrentString );

		CurrentString = LocalString;
	}

	// check for fragment
	if ( *CurrentString == '#' )
	{
		// skip '#'
		CurrentString++;

		// read fragment
		LocalString = CurrentString;

		while ( *LocalString ) LocalString++;

		Result.m_Fragment = std::string( CurrentString, LocalString - CurrentString );

		CurrentString = LocalString;
	}

	Result.m_Valid = true;

	return Result;
}
