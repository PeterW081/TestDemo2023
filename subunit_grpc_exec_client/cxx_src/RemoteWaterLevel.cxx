#include "remote_gpio/RemoteWaterLevel.h"
#pragma

using ext::grpc_client_api::EnumPiGpioLevel;
using ext::grpc_client_api::EnumPiGpioMode;

/// ext::remote_gpio::RemoteWaterLevel - static
auto ext::device_ctrl::RemoteWaterLevel::Cast_To_EnumStatus(ext::grpc_client_api::EnumPiGpioLevel var) -> EnumStatus
{
	EnumStatus result;
	switch(var)
	{
		case EnumPiGpioLevel::PI_OFF:
			result = EnumStatus::OFF;
			break;
		case EnumPiGpioLevel::PI_ON:
			result = EnumStatus::ON;
			break;
		default:
			result = EnumStatus::NULL_VALUE;
			break;
	}
	return result;
}

/// ext::remote_gpio::RemoteWaterLevel
ext::device_ctrl::RemoteWaterLevel::RemoteWaterLevel(std::string service_url, unsigned gpio_number)
	: PiGpio(service_url)
	, PiGpioAdvance(service_url)
	, m_service_url(this->PiGpio::m_service_url)
	, m_gpio_number(gpio_number)
{
	this->gpioSetMode(m_gpio_number, EnumPiGpioMode::PI_INPUT);
}
auto ext::device_ctrl::RemoteWaterLevel::get_status() -> EnumStatus
{
	auto gpio_level = this->gpioRead(m_gpio_number);
	return Cast_To_EnumStatus(gpio_level);
}
bool ext::device_ctrl::RemoteWaterLevel::listen_status(std::function<bool(EnumStatus status)> func_waterlevel_status)
{
	auto func_gpio_level = [func_waterlevel_status](EnumPiGpioLevel level) -> bool
	{
		return func_waterlevel_status(Cast_To_EnumStatus(level));
	};
	return this->stream01_pigpio_read(m_gpio_number, func_gpio_level);
}
