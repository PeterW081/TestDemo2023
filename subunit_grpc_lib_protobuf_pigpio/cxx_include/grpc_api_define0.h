#pragma once
#include <grpcpp/grpcpp.h>

template<typename GrpcService>
concept concept_grpc_service = requires(std::shared_ptr<grpc::Channel> grpc_channel) {
	typename GrpcService::Stub;
	GrpcService::NewStub(grpc_channel);
};

namespace ext::grpc_api::define0
{
	class ExceptionGrpc;

	template<typename GrpcService>
		requires concept_grpc_service<GrpcService>
	class PrototypeGrpcApi;
};

class ext::grpc_api::define0::ExceptionGrpc : public std::exception
{
  public:
	explicit ExceptionGrpc(grpc::Status);
  private:
	const grpc::Status m_status;
};

template<typename GrpcService>
	requires concept_grpc_service<GrpcService>
class ext::grpc_api::define0::PrototypeGrpcApi
{
  protected:
	const std::string m_service_url;
	std::shared_ptr<grpc::Channel> m_channel;
	std::unique_ptr<typename GrpcService::Stub> m_stub;
	explicit PrototypeGrpcApi(std::string);
};

/// ext::grpc_api::define0::PrototypeGrpcApi
template<typename GrpcService>
	requires concept_grpc_service<GrpcService>
ext::grpc_api::define0::PrototypeGrpcApi<GrpcService>::PrototypeGrpcApi(std::string service_url)
	: m_service_url(std::move(service_url))
	, m_channel(grpc::CreateChannel(m_service_url, ::grpc::InsecureChannelCredentials()))
	, m_stub(GrpcService::NewStub(m_channel))
{
}
