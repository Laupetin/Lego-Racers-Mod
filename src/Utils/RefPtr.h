/*
* Copyright (C) ATLAS Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of ATLAS nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

class RefPtr
{
private:
	uint32_t m_uiAddress;

public:
	RefPtr(uint32_t uiAddress ) noexcept
		: m_uiAddress( uiAddress )
	{
	}

	RefPtr( void* pAddress ) noexcept
		: m_uiAddress( reinterpret_cast< uint32_t >( pAddress ) )
	{
	}

	uint32_t GetAddr() const { return m_uiAddress; }

	explicit operator uint32_t() const
	{
		return m_uiAddress;
	}

	operator BYTE*( ) const
	{
		return PBYTE( m_uiAddress );
	}

	operator void*( ) const
	{
		return LPVOID( m_uiAddress );
	}

	bool operator>=( const RefPtr& n ) const
	{
		return m_uiAddress >= n.m_uiAddress;
	}

	bool operator<=( const RefPtr& n ) const
	{
		return m_uiAddress <= n.m_uiAddress;
	}


	/*RefPtr operator+( const RefPtr& n ) const
	{
		return m_uiAddress + n;
	}*/
};