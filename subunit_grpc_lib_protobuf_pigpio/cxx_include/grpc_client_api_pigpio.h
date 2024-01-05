#pragma once
#include "grpc_client_api.h"

#if(MACROMARK_GRPC_CLIENT == MACROMARK_GRPC_CLIENT_0ENUM_0BOTH || MACROMARK_GRPC_CLIENT == MACROMARK_GRPC_CLIENT_0ENUM_1ONLY_RAW)
#	include <grpcpp/grpcpp.h>
#	include "grpc_pigpio.grpc.pb.h"
#elif(MACROMARK_GRPC_CLIENT == MACROMARK_GRPC_CLIENT_0ENUM_2ONLY_QT)
#	include "grpc_pigpio.qpb.h"
#	include "grpc_pigpio_client.grpc.qpb.h"
#endif


namespace ext::grpc_client_api
{
	namespace define0
	{
#if(MACROMARK_GRPC_CLIENT == MACROMARK_GRPC_CLIENT_0ENUM_0BOTH || MACROMARK_GRPC_CLIENT == MACROMARK_GRPC_CLIENT_0ENUM_1ONLY_RAW)
		using namespace ext::grpc_protobuf;
#elif(MACROMARK_GRPC_CLIENT == MACROMARK_GRPC_CLIENT_0ENUM_2ONLY_QT)
		using namespace prefix_grpc_qt::ext::grpc_protobuf;
		using ServiceTest = prefix_grpc_qt::ext::grpc_protobuf::ServiceTest::Client;
		using ServicePiGpio = prefix_grpc_qt::ext::grpc_protobuf::ServicePiGpio::Client;
		using ServicePiGpioAdvance = prefix_grpc_qt::ext::grpc_protobuf::ServicePiGpioAdvance::Client;
#endif
	}

	enum class EnumPiGpioMode : unsigned;
	enum class EnumPiGpioLevel : unsigned;

	class Test;
	class PiGpio;
	class PiGpioAdvance;
}

enum class ext::grpc_client_api::EnumPiGpioMode : unsigned
{
	PI_INPUT = 0,
	PI_OUTPUT = 1,
};

enum class ext::grpc_client_api::EnumPiGpioLevel : unsigned
{
	PI_OFF = 0,
	PI_ON = 1,
};

class ext::grpc_client_api::Test : protected define0::GrpcClient<define0::ServiceTest>
{
  public:
	explicit Test(std::string);
	std::string test_echo(const std::string&);
	std::string test_ifconfig();
};

class ext::grpc_client_api::PiGpio : protected define0::GrpcClient<define0::ServicePiGpio>
{
  public:
	explicit PiGpio(std::string);
	int gpioInitialise(void);
	int gpioSetMode(unsigned, EnumPiGpioMode);
	EnumPiGpioLevel gpioRead(unsigned);
	int gpioWrite(unsigned, EnumPiGpioLevel);
};

class ext::grpc_client_api::PiGpioAdvance : protected define0::GrpcClient<define0::ServicePiGpioAdvance>
{
  public:
	explicit PiGpioAdvance(std::string);
	bool stream01_pigpio_read(unsigned, std::function<bool(EnumPiGpioLevel)>);
};
