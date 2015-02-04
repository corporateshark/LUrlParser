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

#pragma once

#include <string>

namespace LUrlParser
{

	class clParseURL
	{
	public:
		bool m_Valid;
		std::string m_Scheme;
		std::string m_Host;
		std::string m_Port;
		std::string m_Path;
		std::string m_Query;
		std::string m_Fragment;
		std::string m_UserName;
		std::string m_Password;

		clParseURL()
			: m_Valid( false )
		{}

		/// return 'true' if the parsing was successful
		bool IsValid() const { return m_Valid; }

		/// helper to convert the port number to int, return 'true' if the port is valid (within the 0..65535 range)
		bool GetPort( int* OutPort ) const { return GetPort( ( volatile int* )OutPort ); }

		/// helper to convert the port number to int, return 'true' if the port is valid (within the 0..65535 range)
		bool GetPort( volatile int* OutPort ) const;

		/// parse the URL
		static clParseURL ParseURL( const std::string& URL );
	};

} // namespace LUrlParser
