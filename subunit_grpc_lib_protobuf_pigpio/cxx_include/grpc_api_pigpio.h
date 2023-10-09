#pragma once
#include <grpcpp/grpcpp.h>
#include "grpc_api_define0.h"
#include "grpc_pigpio.grpc.pb.h"

namespace ext::grpc_api
{
	namespace define0
	{
		using namespace ext::grpc_protobuf;
		using google::protobuf::Empty;
	}
	enum class EnumPiGpioMode : unsigned;
	enum class EnumPiGpioLevel : unsigned;
	class Test;
	class PiGpio;
	class PiGpioAdvance;
}

enum class ext::grpc_api::EnumPiGpioMode : unsigned
{
	PI_INPUT = 0,
	PI_OUTPUT = 1,
};

enum class ext::grpc_api::EnumPiGpioLevel : unsigned
{
	PI_OFF = 0,
	PI_ON = 1,
};

class ext::grpc_api::Test : protected define0::PrototypeGrpcApi<define0::ServiceTest>
{
  public:
	explicit Test(std::string);
	std::string test_echo(const std::string&);
	std::string test_ifconfig();
};

class ext::grpc_api::PiGpio : protected define0::PrototypeGrpcApi<define0::ServicePiGpio>
{
  public:
	explicit PiGpio(std::string);
	int gpioInitialise(void);
	int gpioSetMode(unsigned, EnumPiGpioMode);
	EnumPiGpioLevel gpioRead(unsigned);
	int gpioWrite(unsigned, EnumPiGpioLevel);
};

class ext::grpc_api::PiGpioAdvance : protected define0::PrototypeGrpcApi<define0::ServicePiGpioAdvance>
{
  public:
	explicit PiGpioAdvance(std::string);
	bool stream01_pigpio_read(unsigned, std::function<bool(EnumPiGpioLevel)>);
};
