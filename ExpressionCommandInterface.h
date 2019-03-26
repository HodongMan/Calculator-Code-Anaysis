#pragma once

#include "CalculatorVector.h"
#include "Command.h"

class ISerializeCommandVisitor;


class IExpressionCommand
{
public:
	virtual CalculationManager::CommandType		GetCommandType( void ) const noexcept = 0;
	virtual void								Accept( _In_ ISerializeCommandVisitor & commandVisitor ) noexcept = 0;
};

class IOperatorCommand : public IExpressionCommand
{
public:
	virtual void								SetCommand( int command ) noexcept = 0;
};

class IUnaryCommand : public IOperatorCommand
{
public:
	virtual const std::shared_ptr<CalculatorVector<int>> & GetCommands( void ) const noexcept = 0;
	virtual void								SetCommand( int command1, int command2 ) noexcept = 0;
};

class IBinnaryCommand : public IOperatorCommand
{
	virtual void								SetCommand( int command ) noexcept override = 0;
	virtual int									GetCommand( void ) const noexcept = 0;
};

class IOpndCommand : public IExpressionCommand
{
public:
	virtual const std::shared_ptr<CalculatorVector<int>> & GetCommands() const noexcept = 0;
	virtual void								AppendCommand( int command ) noexcept = 0;
	virtual void								ToggleSign( void ) noexcept = 0;
	virtual void								RemoveFromEnd( void ) noexcept = 0;

	virtual bool								IsNegative( void ) const noexcept = 0;
	virtual bool								IsSciFmt( void ) const noexcept = 0;
	virtual bool								IsDecimalPresent( void ) const noexcept = 0;

	virtual const std::wstring &				GetToken( wchar_t decimalSymbol ) noexcept = 0;
	virtual void								SetCommands( std::shared_ptr<CalculatorVector<int>> const& commands ) noexcept = 0;
};

class IParenthesisCommand : public IExpressionCommand
{
public:
    virtual int									GetCommand( void ) const = 0;
};