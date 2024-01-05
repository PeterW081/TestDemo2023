#include "grpc_client_api.h"
#pragma

namespace define0 = ext::grpc_client_api::define0;

/// ext::grpc_api::define0::ExceptionGrpc
template<>
ext::grpc_client_api::define0::ExceptionGrpc<define0::GrpcStatus>::ExceptionGrpc(define0::GrpcStatus status)
	: m_status(std::move(status))
{
}
