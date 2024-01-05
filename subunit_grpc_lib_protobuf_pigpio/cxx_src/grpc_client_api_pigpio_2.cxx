#if(MACROMARK_GRPC_CLIENT == MACROMARK_GRPC_CLIENT_0ENUM_0BOTH || MACROMARK_GRPC_CLIENT == MACROMARK_GRPC_CLIENT_0ENUM_2ONLY_QT)
#	include "grpc_client_api_pigpio.h"
#	pragma
#	include <QEventLoop>

/// std::string ext::grpc_api::Test
ext::grpc_client_api::Test::Test(std::string service_url)
	: GrpcClientQt(std::move(service_url))
{
}
std::string ext::grpc_client_api::Test::test_echo(const std::string& str)
{
	// rpc test_echo (MsgString) returns (MsgString) {}
	auto status = QGrpcStatus();
	auto request = define0::MsgString();
	auto response = define0::MsgString();

	request.setContent(str.c_str());
	status = m_client->test_echo(request, &response);
	if(status.code() != QGrpcStatus::StatusCode::Ok)
	{
		throw define0::ExceptionGrpc(status);
	}
	return response.content().toStdString();
}
std::string ext::grpc_client_api::Test::test_ifconfig()
{
	// rpc test_ifconfig(google.protobuf.Empty) returns (MsgString) {}
	auto status = QGrpcStatus();
	auto request = define0::MsgEmpty();
	auto response = define0::MsgString();

	status = m_client->test_ifconfig(request, &response);
	if(status.code() != QGrpcStatus::StatusCode::Ok)
	{
		throw define0::ExceptionGrpc(status);
	}
	return response.content().toStdString();
}

/// ext::grpc_api::PiGpio
ext::grpc_client_api::PiGpio::PiGpio(std::string service_url)
	: GrpcClientQt(std::move(service_url))
{
}
int ext::grpc_client_api::PiGpio::gpioInitialise(void)
{
	// rpc gpioInitialise(google.protobuf.Empty) returns (MsgInt32) {}
	auto status = QGrpcStatus();
	auto request = define0::MsgEmpty();
	auto response = define0::MsgInt32();

	status = m_client->gpioInitialise(request, &response);
	if(status.code() != QGrpcStatus::StatusCode::Ok)
	{
		throw define0::ExceptionGrpc(status);
	}
	return response.content();
}
int ext::grpc_client_api::PiGpio::gpioSetMode(unsigned gpio, EnumPiGpioMode mode)
{
	// rpc gpioSetMode(MsgRequestGpioSetMode) returns (MsgInt32) {}
	auto status = QGrpcStatus();
	auto request = define0::MsgRequestGpioSetMode();
	auto response = define0::MsgInt32();

	request.setParam01Gpio(gpio);
	request.setParam02Mode(static_cast<unsigned>(mode));
	status = m_client->gpioSetMode(request, &response);
	if(status.code() != QGrpcStatus::StatusCode::Ok)
	{
		throw define0::ExceptionGrpc(status);
	}
	return response.content();
}
auto ext::grpc_client_api::PiGpio::gpioRead(unsigned gpio) -> EnumPiGpioLevel
{
	// rpc gpioRead(MsgUint32) returns (MsgInt32) {}
	auto status = QGrpcStatus();
	auto request = define0::MsgUint32();
	auto response = define0::MsgInt32();

	request.setContent(gpio);
	status = m_client->gpioRead(request, &response);
	if(status.code() != QGrpcStatus::StatusCode::Ok)
	{
		throw define0::ExceptionGrpc(status);
	}
	return static_cast<EnumPiGpioLevel>(static_cast<int>(response.content()));
}
int ext::grpc_client_api::PiGpio::gpioWrite(unsigned gpio, EnumPiGpioLevel level)
{
	// rpc gpioWrite(MsgRequestGpioWrite) returns (MsgInt32) {}
	auto status = QGrpcStatus();
	auto request = define0::MsgRequestGpioWrite();
	auto response = define0::MsgInt32();

	request.setParam01Gpio(gpio);
	request.setParam02Level(static_cast<unsigned>(level));
	status = m_client->gpioWrite(request, &response);
	if(status.code() != QGrpcStatus::StatusCode::Ok)
	{
		throw define0::ExceptionGrpc(status);
	}
	return response.content();
}

/// ext::grpc_api::PiGpioAdvance
ext::grpc_client_api::PiGpioAdvance::PiGpioAdvance(std::string service_url)
	: GrpcClientQt(std::move(service_url))
{
}
bool ext::grpc_client_api::PiGpioAdvance::stream01_pigpio_read(unsigned gpio, std::function<bool(EnumPiGpioLevel level)> func)
{
	// rpc stream01_pigpio_read(MsgUint32) returns(stream MsgInt32){};
	auto status = QGrpcStatus();
	auto blocker = QEventLoop();
	auto request = define0::MsgUint32();
	auto response_reader = std::shared_ptr<QGrpcStream>();

	auto is_continue = true;
	auto func0 = [&is_continue, &func, &response_reader]() -> void
	{
		auto var = static_cast<EnumPiGpioLevel>(static_cast<int>(response_reader->read<define0::MsgInt32>().content()));
		is_continue = func(var);
		if(!is_continue)
		{
			response_reader->abort();
		}
	};

	request.setContent(gpio);
	response_reader = m_client->streamStream01_pigpio_read(request);
	QObject::connect(response_reader.get(), &decltype(response_reader)::element_type::errorOccurred, &std::remove_pointer_t<decltype(this)>::SlotErrorOccurred);
	QObject::connect(response_reader.get(), &decltype(response_reader)::element_type::messageReceived, func0);
	QObject::connect(response_reader.get(), &decltype(response_reader)::element_type::finished, &blocker, &QEventLoop::quit);
	blocker.exec();

	if(status.code() != QGrpcStatus::StatusCode::Ok)
	{
		throw define0::ExceptionGrpc(status);
	}
	return is_continue && (status.code() == QGrpcStatus::StatusCode::Ok);
}
#endif
