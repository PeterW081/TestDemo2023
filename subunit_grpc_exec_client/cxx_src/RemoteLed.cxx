#include <utility>

#include "remote_gpio/RemoteLed.h"
#pragma

using ext::grpc_api::EnumPiGpioLevel;
using ext::grpc_api::EnumPiGpioMode;

/// ext::remote_gpio::RemoteLed - static
auto ext::device_ctrl::RemoteLed::Cast_To_EnumStatus(ext::grpc_api::EnumPiGpioLevel var) -> EnumStatus
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

/// ext::remote_gpio::RemoteLed
ext::device_ctrl::RemoteLed::RemoteLed(std::string service_url, unsigned gpio_number)
	: PiGpio(std::move(service_url))
	, m_service_url(this->PiGpio::m_service_url)
	, m_gpio_number(gpio_number)
{
	this->gpioSetMode(m_gpio_number, EnumPiGpioMode::PI_OUTPUT);
}
void ext::device_ctrl::RemoteLed::set_on()
{
	this->gpioWrite(m_gpio_number, EnumPiGpioLevel::PI_ON);
}
void ext::device_ctrl::RemoteLed::set_off()
{
	this->gpioWrite(m_gpio_number, EnumPiGpioLevel::PI_OFF);
}
auto ext::device_ctrl::RemoteLed::get_status() -> EnumStatus
{
	auto status = this->gpioRead(m_gpio_number);
	return Cast_To_EnumStatus(status);
}
