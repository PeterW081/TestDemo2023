#if(MACROMARK_GRPC_CLIENT == MACROMARK_GRPC_CLIENT_0ENUM_0BOTH || MACROMARK_GRPC_CLIENT == MACROMARK_GRPC_CLIENT_0ENUM_1ONLY_RAW)
#	include "grpc_client_api_pigpio.h"
#	pragma

/// std::string ext::grpc_api::Test
ext::grpc_client_api::Test::Test(std::string service_url)
	: GrpcClientRaw(std::move(service_url))
{
}
std::string ext::grpc_client_api::Test::test_echo(const std::string& str)
{
	// rpc test_echo (MsgString) returns (MsgString) {}
	auto context = grpc::ClientContext();
	auto status = grpc::Status();
	auto request = define0::MsgString();
	auto response = define0::MsgString();

	request.set_content(str);
	status = m_stub->test_echo(&context, request, &response);
	if(!status.ok())
	{
		throw define0::ExceptionGrpc(status);
	}
	return response.content();
}
std::string ext::grpc_client_api::Test::test_ifconfig()
{
	// rpc test_ifconfig(google.protobuf.Empty) returns (MsgString) {}
	auto context = grpc::ClientContext();
	auto status = grpc::Status();
	auto request = define0::MsgEmpty();
	auto response = define0::MsgString();

	status = m_stub->test_ifconfig(&context, request, &response);
	if(!status.ok())
	{
		throw define0::ExceptionGrpc(status);
	}
	return response.content();
}

/// ext::grpc_api::PiGpio
ext::grpc_client_api::PiGpio::PiGpio(std::string service_url)
	: GrpcClientRaw(std::move(service_url))
{
}
int ext::grpc_client_api::PiGpio::gpioInitialise(void)
{
	// rpc gpioInitialise(google.protobuf.Empty) returns (MsgInt32) {}
	auto context = grpc::ClientContext();
	auto status = grpc::Status();
	auto request = define0::MsgEmpty();
	auto response = define0::MsgInt32();

	status = m_stub->gpioInitialise(&context, request, &response);
	if(!status.ok())
	{
		throw define0::ExceptionGrpc(status);
	}
	return response.content();
}
int ext::grpc_client_api::PiGpio::gpioSetMode(unsigned gpio, EnumPiGpioMode mode)
{
	// rpc gpioSetMode(MsgRequestGpioSetMode) returns (MsgInt32) {}
	auto context = grpc::ClientContext();
	auto status = grpc::Status();
	auto request = define0::MsgRequestGpioSetMode();
	auto response = define0::MsgInt32();

	request.set_param01_gpio(gpio);
	request.set_param02_mode(static_cast<unsigned>(mode));
	status = m_stub->gpioSetMode(&context, request, &response);
	if(!status.ok())
	{
		throw define0::ExceptionGrpc(status);
	}
	return response.content();
}
auto ext::grpc_client_api::PiGpio::gpioRead(unsigned gpio) -> EnumPiGpioLevel
{
	// rpc gpioRead(MsgUint32) returns (MsgInt32) {}
	auto context = grpc::ClientContext();
	auto status = grpc::Status();
	auto request = define0::MsgUint32();
	auto response = define0::MsgInt32();

	request.set_content(gpio);
	status = m_stub->gpioRead(&context, request, &response);
	if(!status.ok())
	{
		throw define0::ExceptionGrpc(status);
	}
	return static_cast<EnumPiGpioLevel>(response.content());
}
int ext::grpc_client_api::PiGpio::gpioWrite(unsigned gpio, EnumPiGpioLevel level)
{
	// rpc gpioWrite(MsgRequestGpioWrite) returns (MsgInt32) {}
	auto context = grpc::ClientContext();
	auto status = grpc::Status();
	auto request = define0::MsgRequestGpioWrite();
	auto response = define0::MsgInt32();

	request.set_param01_gpio(gpio);
	request.set_param02_level(static_cast<unsigned>(level));
	status = m_stub->gpioWrite(&context, request, &response);
	if(!status.ok())
	{
		throw define0::ExceptionGrpc(status);
	}
	return response.content();
}

/// ext::grpc_api::PiGpioAdvance
ext::grpc_client_api::PiGpioAdvance::PiGpioAdvance(std::string service_url)
	: GrpcClientRaw(std::move(service_url))
{
}
bool ext::grpc_client_api::PiGpioAdvance::stream01_pigpio_read(unsigned gpio, std::function<bool(EnumPiGpioLevel level)> func)
{
	// rpc stream01_pigpio_read(MsgUint32) returns(stream MsgInt32){};
	auto context = grpc::ClientContext();
	auto status = grpc::Status();
	auto request = ext::grpc_protobuf::MsgUint32();
	auto response_reader = std::unique_ptr<grpc::ClientReader<ext::grpc_protobuf::MsgInt32>>();

	auto is_continue = true;
	auto packet = ext::grpc_protobuf::MsgInt32();
	auto packet_content = EnumPiGpioLevel();

	request.set_content(gpio);
	response_reader = m_stub->stream01_pigpio_read(&context, request);
	while(is_continue && response_reader->Read(&packet))
	{
		packet_content = static_cast<EnumPiGpioLevel>(packet.content());
		is_continue = func(packet_content);
	}
	if(is_continue)
	{
		status = response_reader->Finish();
		if(!status.ok())
		{
			throw define0::ExceptionGrpc(status);
		}
	}
	return is_continue && status.ok();
}
#endif
