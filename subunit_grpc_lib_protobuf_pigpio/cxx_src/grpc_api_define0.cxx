#include "grpc_api_define0.h"
#pragma

/// ext::grpc_api::define0::ExceptionGrpc
ext::grpc_api::define0::ExceptionGrpc::ExceptionGrpc(grpc::Status status)
	: m_status(std::move(status))
{
}
