#include "grpc_server_pigpio.h"

#pragma
#include <thread>
namespace ext::pigpio
{
#include <pigpio.h>
}

/// ext::grpc_server::ServiceImplPiGpio
grpc::Status ext::grpc_server::ServiceImplPiGpio::gpioInitialise(grpc::ServerContext* context, const define0::MsgEmpty* request, define0::MsgInt32* response)
{
	auto result = ext::pigpio::gpioInitialise();
	//-
	response->set_content(result);
	return grpc::Status::OK;
}
grpc::Status ext::grpc_server::ServiceImplPiGpio::gpioSetMode(grpc::ServerContext* context, const define0::MsgRequestGpioSetMode* request, define0::MsgInt32* response)
{
	auto result = ext::pigpio::gpioSetMode(request->param01_gpio(), request->param02_mode());
	//-
	response->set_content(result);
	return grpc::Status::OK;
}
grpc::Status ext::grpc_server::ServiceImplPiGpio::gpioRead(grpc::ServerContext* context, const define0::MsgUint32* request, define0::MsgInt32* response)
{
	auto result = ext::pigpio::gpioRead(request->content());
	//-
	response->set_content(result);
	return grpc::Status::OK;
}
grpc::Status ext::grpc_server::ServiceImplPiGpio::gpioWrite(grpc::ServerContext* context, const define0::MsgRequestGpioWrite* request, define0::MsgInt32* response)
{
	auto result = ext::pigpio::gpioWrite(request->param01_gpio(), request->param02_level());
	//-
	response->set_content(result);
	return grpc::Status::OK;
}

/// ext::grpc_server::ServiceImplPiGpioAdvance
grpc::Status ext::grpc_server::ServiceImplPiGpioAdvance::stream01_pigpio_read(grpc::ServerContext* context, const define0::MsgUint32* request, grpc::ServerWriter<define0::MsgInt32>* writer)
{
	unsigned pin_number = request->content();
	int result;
	int result_last;

	///
	auto is_loop_continue = true;
	auto loop_times = 0;
	auto writer_packet = define0::MsgInt32();
	result_last = result = ext::pigpio::gpioRead(pin_number);
	while(is_loop_continue)
	{
		writer_packet.Clear();
		writer_packet.set_content(result_last);
		is_loop_continue = writer->Write(writer_packet);
		if(is_loop_continue)
		{
			while(result_last == result && is_loop_continue)
			{
				std::this_thread::sleep_for(M_LOOP_INTERVAL_TIMEV);
				result = ext::pigpio::gpioRead(pin_number);
				loop_times++;
				is_loop_continue = loop_times < M_LOOP_MAX_TIMES;
			}
			result_last = result;
		}
	}
	return grpc::Status::OK;
}
