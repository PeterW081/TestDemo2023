#pragma once

#if(MACROMARK_GRPC_CLIENT == MACROMARK_GRPC_CLIENT_0ENUM_0BOTH || MACROMARK_GRPC_CLIENT == MACROMARK_GRPC_CLIENT_0ENUM_1ONLY_RAW)
#	include <grpcpp/grpcpp.h>

template<typename GrpcService>
concept concept_grpc_service = requires(std::shared_ptr<grpc::Channel> grpc_channel) {
	typename GrpcService::Stub;
	GrpcService::NewStub(grpc_channel);
};

namespace ext::grpc_client_api::define0
{
	template<typename GrpcService>
		requires concept_grpc_service<GrpcService>
	class GrpcClientRaw;
}

template<typename GrpcService>
	requires concept_grpc_service<GrpcService>
class ext::grpc_client_api::define0::GrpcClientRaw
{
  protected:
	const std::string m_service_url;
	std::shared_ptr<grpc::Channel> m_channel;
	std::unique_ptr<typename GrpcService::Stub> m_stub;
	explicit GrpcClientRaw(std::string);
};

/// ext::grpc_api::define0::PrototypeGrpcApi
template<typename GrpcService>
	requires concept_grpc_service<GrpcService>
ext::grpc_client_api::define0::GrpcClientRaw<GrpcService>::GrpcClientRaw(std::string service_url)
	: m_service_url(std::move(service_url))
	, m_channel(grpc::CreateChannel(m_service_url, ::grpc::InsecureChannelCredentials()))
	, m_stub(GrpcService::NewStub(m_channel))
{
}
#endif
