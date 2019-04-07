#pragma once

#include "CalculatorVector.h"


class IHistoryDisplay
{
public:
	virtual ~IHistoryDisplay( void ) {};
	virtual unsigned int AddToHistory( _In_ std::shared_ptr<CalculatorVector <std::pair<std::wstring, int>>> const &tokens, _In_ std::shared_ptr<CalculatorVector<std::shared_ptr<IExpressionCommand>>> const &commands, _In_ std::wstring_view result ) = 0;
};