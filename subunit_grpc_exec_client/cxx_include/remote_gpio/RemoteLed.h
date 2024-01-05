#pragma once
#include "grpc_client_api_pigpio.h"

namespace ext::device_ctrl
{
	class RemoteLed;
}

class ext::device_ctrl::RemoteLed : protected ext::grpc_client_api::PiGpio
{
  public:
	enum class EnumStatus : unsigned;
	static EnumStatus Cast_To_EnumStatus(ext::grpc_client_api::EnumPiGpioLevel);

  public:
	explicit RemoteLed(std::string, unsigned);
	void set_on();
	void set_off();
	EnumStatus get_status();

  protected:
	const std::string& m_service_url;
	const unsigned m_gpio_number;
};

enum class ext::device_ctrl::RemoteLed::EnumStatus : unsigned
{
	NULL_VALUE = 0,
	ON,
	OFF,
	ERROR,
	LOADING,
};
