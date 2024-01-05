#pragma once
#include "grpc_pigpio.grpc.pb.h"

namespace ext::grpc_server
{
	namespace define0
	{
		using namespace ext::grpc_protobuf;
	}
	class ServiceImplTest;
	class ServiceImplPiGpio;
	class ServiceImplPiGpioAdvance;
}

class ext::grpc_server::ServiceImplPiGpio : public define0::ServicePiGpio::Service
{
  public:
	grpc::Status gpioInitialise(grpc::ServerContext*, const define0::MsgEmpty*, define0::MsgInt32*) override;
	grpc::Status gpioSetMode(grpc::ServerContext*, const define0::MsgRequestGpioSetMode*, define0::MsgInt32*) override;
	grpc::Status gpioRead(grpc::ServerContext*, const define0::MsgUint32*, define0::MsgInt32*) override;
	grpc::Status gpioWrite(grpc::ServerContext*, const define0::MsgRequestGpioWrite*, define0::MsgInt32*) override;
};

class ext::grpc_server::ServiceImplPiGpioAdvance : public define0::ServicePiGpioAdvance::Service
{
  public:
	grpc::Status stream01_pigpio_read(grpc::ServerContext*, const define0::MsgUint32*, grpc::ServerWriter<define0::MsgInt32>*) override;
  private:
	static constexpr auto M_LOOP_MAX_TIMES = 32;
	static constexpr auto M_LOOP_INTERVAL_TIMEV = std::chrono::milliseconds(500);
};
