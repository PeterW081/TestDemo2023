#include <gtest/gtest.h>
#pragma

#include <thread>
#include "grpc_client_api_pigpio.h"

namespace test_config0
{
	static const std::string SERVICE_URL = MACRO_GRPC_SERVICE_URL;
	static const int PIN_NUMBER_WATERLEVEL = 4;
	static const int PIN_NUMBER_LED = 21;
}
namespace
{
	using ext::grpc_client_api::EnumPiGpioLevel;
	using ext::grpc_client_api::EnumPiGpioMode;
}

TEST(Example, Test01_Led)
{
	// GTEST_SKIP();
	static const int PIN_NUMBER = test_config0::PIN_NUMBER_LED;
	auto itc_pigpio_01 = ext::grpc_client_api::PiGpio(test_config0::SERVICE_URL);

	itc_pigpio_01.gpioSetMode(PIN_NUMBER, EnumPiGpioMode::PI_OUTPUT);
	switch(itc_pigpio_01.gpioRead(PIN_NUMBER))
	{
		case EnumPiGpioLevel::PI_OFF:
			itc_pigpio_01.gpioWrite(PIN_NUMBER, EnumPiGpioLevel::PI_ON);
			break;
		case EnumPiGpioLevel::PI_ON:
			itc_pigpio_01.gpioWrite(PIN_NUMBER, EnumPiGpioLevel::PI_OFF);
			break;
	}

	std::string str;
	switch(itc_pigpio_01.gpioRead(PIN_NUMBER))
	{
		case EnumPiGpioLevel::PI_OFF:
			str = "OFF";
			break;
		case EnumPiGpioLevel::PI_ON:
			str = "ON";
			break;
	}
	std::cout << str << std::endl;
}

TEST(Example, Test02_WaterLevel)
{
	// GTEST_SKIP();
	static const int PIN_NUMBER = test_config0::PIN_NUMBER_WATERLEVEL;
	auto itc_pigpio_01 = ext::grpc_client_api::PiGpio(test_config0::SERVICE_URL);

	itc_pigpio_01.gpioSetMode(PIN_NUMBER, EnumPiGpioMode::PI_INPUT);
	for(int i = 0, j = 16; i < j; i++)
	{
		std::string str;
		switch(itc_pigpio_01.gpioRead(PIN_NUMBER))
		{
			case EnumPiGpioLevel::PI_OFF:
				str = "OFF";
				break;
			case EnumPiGpioLevel::PI_ON:
				str = "ON";
				break;
		}
		std::cout << str << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

TEST(Example, Test03_WaterLevel_Advance)
{
	// GTEST_SKIP();
	static const int PIN_NUMBER = test_config0::PIN_NUMBER_WATERLEVEL;
	auto itc_pigpio_01 = ext::grpc_client_api::PiGpio(test_config0::SERVICE_URL);
	auto itc_pigpio_02 = ext::grpc_client_api::PiGpioAdvance(test_config0::SERVICE_URL);

	auto times = 0;
	auto is_ok = false;
	auto func = [&times](EnumPiGpioLevel level) -> bool
	{
		if(times++ >= 3)
		{
			std::cout << "times up !" << std::endl;
			return false;
		}
		switch(level)
		{
			case EnumPiGpioLevel::PI_OFF:
				std::cout << "OFF" << std::endl;
				break;
			case EnumPiGpioLevel::PI_ON:
				std::cout << "ON" << std::endl;
				break;
		}
		return true;
	};

	is_ok = itc_pigpio_02.stream01_pigpio_read(PIN_NUMBER, func);
	std::cout << is_ok << std::endl;
}
