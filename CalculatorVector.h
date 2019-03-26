#pragma once

#include <windows.h>
#include <string>

template < typename TType >
class CalculatorVector
{
public:
	HRESULT GetAt( _In_opt_ const unsigned int index, _Out_ TType *item ) const noexcept
	{
		if ( m_vector.size() <= index )
		{
			return E_BOUNDS;
		}
		
		*item = m_vector.at( index );

		return S_OK;
	}

	HRESULT GetSize( _Out_ const unsigned int *size ) const noexcept
	{
		*size = static_cast<unsigned>( m_vector.size() );
		
		return S_OK;
	}

	HRESULT SetAt( _In_ const unsigned int index, _In_opt_ TType item ) noexcept
	{
		if ( m_vector.size() <= index )
		{
			return E_BOUNDS;
		}

		m_vector[index] = item;

		return S_OK;
	}

	HRESULT RemoveAt( _In_ const unsigned int index ) noexcept
	{
		if ( m_vector.size() <= index )
		{
			return E_BOUNDS;
		}

		m_vector.erase( m_vector.begin() + index );

		return S_OK;
	}

	HRESULT InsertAt( _In_ const unsigned int index, _In_ TType item ) noexcept
	{
		auto itor = m_vector.begin() + index;
		m_vector.insert( itor, item );

		return S_OK;
	}

	HRESULT Truncate( _In_ const unsigned int index ) noexcept
	{
		if ( m_vector.size() <= index )
		{
			return E_BOUNDS;
		}

		auto startIter = m_vector.begin() + index;
		m_vector.erase( startIter, m_vector.end() );

		return S_OK;
	}

	HRESULT Append( _In_opt_ TType& Item ) noexcept
	{
		m_vector.push_back( item );

		return S_OK;
	}

	HRESULT RemoveAtEnd( void ) noexcept
	{
		m_vector.erase( --( m_vector.end() ) );

		return S_OK;
	}

	HRESULT Clear( void ) noexcept
	{
		m_vector.clear();

		return S_OK;
	}

	HRESULT GetString( _Out_ std::wstring* expression ) noexcept
	{
		HRESULT hr = S_OK;

		unsigned int nTokens = 0;
		std::pair <std::wstring, int> currentPair;

		hr = this->GetSize( &nTokens );

		if ( true == SUCCEEDED( hr ) )
		{
			for ( unsigned int i = 0; i < nTokens; ++i )
			{
				hr = this->GetAt( i, &currentPair );

				if ( true == SUCCEEDED(hr) )
				{
					expression->append( currentPair.first );

					if (i != ( nTokens - 1 ) )
					{
						expression->append( L" " );
					}
				}
			}

			std::wstring expressionSuffix{};
			hr = GetExpressionSuffix( &expressionSuffix );
			if ( true == SUCCEEDED( hr ) )
			{
				expression->append( expressionSuffix );
			}
		}

		return hr;
	}

	HRESULT GetExpressionSuffix( _Out_ std::wstring* suffix ) noexcept
	{
		*suffix = L" =";

		return S_OK;
	}

private:
	std::vector<TType> m_vector;
};