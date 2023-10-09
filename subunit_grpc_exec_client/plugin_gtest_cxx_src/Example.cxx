#include <gtest/gtest.h>
#pragma

#include "remote_gpio/RemoteLed.h"
#include "remote_gpio/RemoteWaterLevel.h"

namespace test_config0
{
	static const std::string SERVICE_URL = MACRO_GRPC_SERVICE_URL;
	static const int PIN_NUMBER_WATERLEVEL = 4;
	static const int PIN_NUMBER_LED = 21;
}
namespace
{
	using ext::device_ctrl::RemoteLed;
	using ext::device_ctrl::RemoteWaterLevel;
}

TEST(Example, Test01_RemoteLed)
{
	// GTEST_SKIP();
	RemoteLed led = RemoteLed(test_config0::SERVICE_URL, test_config0::PIN_NUMBER_LED);

	led.set_on();
	switch(led.get_status())
	{
		case RemoteLed::EnumStatus::ON:
			std::cout << "ON" << std::endl;
			break;
		case RemoteLed::EnumStatus::OFF:
			std::cout << "OFF" << std::endl;
			break;
		default:
		case RemoteLed::EnumStatus::NULL_VALUE:
			std::cout << "Error" << std::endl;
			break;
	}
	sleep(3);

	led.set_off();
	switch(led.get_status())
	{
		case RemoteLed::EnumStatus::ON:
			std::cout << "ON" << std::endl;
			break;
		case RemoteLed::EnumStatus::OFF:
			std::cout << "OFF" << std::endl;
			break;
		case RemoteLed::EnumStatus::NULL_VALUE:
			std::cout << "Error" << std::endl;
			break;
	}
	sleep(3);
}

TEST(Example, Test02_RemoteWaterLevel)
{
	// GTEST_SKIP();
	RemoteWaterLevel waterlevel = RemoteWaterLevel(test_config0::SERVICE_URL, test_config0::PIN_NUMBER_WATERLEVEL);

	auto times = 0;
	auto func = [&times](RemoteWaterLevel::EnumStatus status) -> bool
	{
		if(times++ >= 3)
		{
			std::cout << "times up !" << std::endl;
			return false;
		}
		switch(status)
		{
			case RemoteWaterLevel::EnumStatus::OFF:
				std::cout << "OFF" << std::endl;
				return true;
			case RemoteWaterLevel::EnumStatus::ON:
				std::cout << "ON" << std::endl;
				return true;
			default:
			case RemoteWaterLevel::EnumStatus::NULL_VALUE:
				std::cout << "NULL_VALUE" << std::endl;
				return false;
		}
	};

	waterlevel.listen_status(func);
}
