#pragma once

namespace hodong
{
	enum class NetworkAccessBehavior
	{
		Normal	= 0,
		OptIn	= 1,
		Offline = 2,
	};

	void NetworkBehaviorChangedHandler( NetworkAccessBehavior behavior ) noexcept;

	class NetworkManager
	{
	public:
		NetworkManager( void );

		static NetworkAccessBehavior GetNetworkAccessBehavior( void ) noexcept;

	private:
		~NetworkManager( void );

	};
}