#pragma once
#include <exception>


#if(MACROMARK_GRPC_CLIENT == MACROMARK_GRPC_CLIENT_0ENUM_0BOTH || MACROMARK_GRPC_CLIENT == MACROMARK_GRPC_CLIENT_0ENUM_1ONLY_RAW)
#	include <grpcpp/grpcpp.h>
namespace ext::grpc_client_api::define0
{
	using GrpcStatus = grpc::Status;
}
#elif(MACROMARK_GRPC_CLIENT == MACROMARK_GRPC_CLIENT_0ENUM_2ONLY_QT)
#	include <QGrpcStatus>
namespace ext::grpc_client_api::define0
{
	using GrpcStatus = QGrpcStatus;
}
#endif

namespace ext::grpc_client_api::define0
{
	template<typename TYPE_GrpcStatus = GrpcStatus>
	class ExceptionGrpc;
}

template<typename TYPE_GrpcStatus>
class ext::grpc_client_api::define0::ExceptionGrpc : public std::exception
{
  public:
	explicit ExceptionGrpc(TYPE_GrpcStatus);
  private:
	const TYPE_GrpcStatus m_status;
};
