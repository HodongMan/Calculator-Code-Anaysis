#pragma once

#include "CalculatorVector.h"
#include "ExpressionCommandInterface.h"
#include <vector>


class ICalcDisplay
{
public:
	virtual void setPrimaryDisplay( const std::wstring& pszText, bool isError ) noexcept = 0;
	virtual void setIsInError( bool isInError ) noexcept = 0;
	virtual void setExpressionDisplay( _Inout_ std::shared_ptr<CalculatorVector<std::pair<std::wstring, int>>> const &tokens, _Inout_ std::shared_ptr<CalculatorVector<std::shared_ptr<IExpressionCommand>>> const &commands ) noexcept = 0;
	virtual void setParenDisplayText( const std::wstring& pszText ) noexcept = 0;
	virtual void onNoRightParentAdded(void) noexcept = 0;
	virtual void maxDigitsReached( void ) noexcept = 0;
	virtual void binaryOperatorReceived( void ) noexcept = 0;
	virtual void onHistoryItemAdded( _In_ unsigned int addedItemIndex ) noexcept = 0;
	virtual void setMemorizedNumber( const std::vector<std::wstring>& memorizedNumber ) noexcept = 0;
	virtual void memoryItemChaned( unsigned int indexOfMemory) noexcept = 0;
};