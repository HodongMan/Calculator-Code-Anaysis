#pragma once

#include "ratpak.h"
#include <vector>


namespace CalcEngine
{
	class Number
	{
	public:
		Number( void ) noexcept;
		Number( int32_t sign, int32_t exp, std::vector<uint32_t> const& mantissa ) noexcept;

		explicit Number( PNUMBER p ) noexcept;
		PNUMBER ToPNUMBER( void ) const noexcept;

		int32_t const& sign( void ) const noexcept;
		int32_t const& exp( void ) const noexcept;
		std::vector<uint32_t> const& Mantissa( void ) const noexcept;

		bool isZero( void ) const noexcept;

	private:
		int32_t m_sign;
		int32_t m_exp;
		std::vector<uint32_t> m_mantissa;

	};
}