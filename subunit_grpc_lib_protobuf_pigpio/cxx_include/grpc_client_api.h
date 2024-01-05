#pragma once
#include "grpc_client_api_0.h"
#include "grpc_client_api_1.h"
#include "grpc_client_api_2.h"

namespace ext::grpc_client_api::define0
{
#if(MACROMARK_GRPC_CLIENT == MACROMARK_GRPC_CLIENT_0ENUM_0BOTH || MACROMARK_GRPC_CLIENT == MACROMARK_GRPC_CLIENT_0ENUM_1ONLY_RAW)
	template<typename GrpcService>
	using GrpcClient = GrpcClientRaw<GrpcService>;
#elif(MACROMARK_GRPC_CLIENT == MACROMARK_GRPC_CLIENT_0ENUM_2ONLY_QT)
	template<typename GrpcService>
	using GrpcClient = GrpcClientQt<GrpcService>;
#endif
}
