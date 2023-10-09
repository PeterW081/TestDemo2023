#include <iostream>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include "grpc_server_pigpio.h"
namespace ext::pigpio
{
#include <pigpio.h>
}

namespace config0
{
	static const std::string SERVICE_URL = MACRO_GRPC_SERVICE_URL;
	static const std::vector<std::shared_ptr<grpc::Service>> services = {
		std::make_shared<ext::grpc_server::ServiceImplTest>(),
		std::make_shared<ext::grpc_server::ServiceImplPiGpio>(),
		std::make_shared<ext::grpc_server::ServiceImplPiGpioAdvance>(),
	};
}

int main(int argc, char* argv[])
{
	std::string service_url;
	if(argc <= 1)
	{
		service_url = config0::SERVICE_URL;
	} else
	{
		service_url = argv[1];
	}

	if(ext::pigpio::gpioInitialise() < 0)
	{
		std::cerr << "pigpio initialisation failed\n" << std::endl;
		return 1;
	}

	grpc::EnableDefaultHealthCheckService(true);
	grpc::reflection::InitProtoReflectionServerBuilderPlugin();

	grpc::ServerBuilder builder;
	builder.AddListeningPort(service_url, grpc::InsecureServerCredentials());
	for(auto& service : config0::services)
	{
		builder.RegisterService(service.get());
	}

	std::unique_ptr<grpc::Server> server = builder.BuildAndStart();
	std::cout << "Server listening on " << service_url << std::endl;
	server->Wait();
	return 0;
}
