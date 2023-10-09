#pragma once
#include "grpc_api_pigpio.h"

namespace ext::device_ctrl
{
	class RemoteWaterLevel;
}

class ext::device_ctrl::RemoteWaterLevel
	: protected ext::grpc_api::PiGpio
	, protected ext::grpc_api::PiGpioAdvance
{
  public:
	enum class EnumStatus : unsigned;
	static EnumStatus Cast_To_EnumStatus(ext::grpc_api::EnumPiGpioLevel);

  public:
	explicit RemoteWaterLevel(std::string, unsigned);
	EnumStatus get_status();
	bool listen_status(std::function<bool(EnumStatus)>);

  protected:
	const std::string& m_service_url;
	const unsigned m_gpio_number;
};

enum class ext::device_ctrl::RemoteWaterLevel::EnumStatus : unsigned
{
	NULL_VALUE = 0,
	ON,
	OFF,
	ERROR,
	LOADING,
	HODING,
};
