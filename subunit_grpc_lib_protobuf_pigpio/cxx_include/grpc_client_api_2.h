#pragma once

#if(MACROMARK_GRPC_CLIENT == MACROMARK_GRPC_CLIENT_0ENUM_0BOTH || MACROMARK_GRPC_CLIENT == MACROMARK_GRPC_CLIENT_0ENUM_2ONLY_QT)
#	include <string>
#	include <QGrpcHttp2Channel>

template<typename GrpcService>
concept concept_grpc_service = !std::is_same_v<QAbstractGrpcClient, GrpcService> && std::is_base_of_v<QAbstractGrpcClient, GrpcService>;

namespace ext::grpc_client_api::define0
{
	template<typename GrpcService>
		requires concept_grpc_service<GrpcService>
	class GrpcClientQt;
}

template<typename GrpcService>
	requires concept_grpc_service<GrpcService>
class ext::grpc_client_api::define0::GrpcClientQt
{
  protected:
	static inline const std::string M_URL_PREFIX = "http://";
	static void SlotErrorOccurred(const QGrpcStatus& status);

  protected:
	const std::string m_service_url;
	std::shared_ptr<GrpcService> m_client;
	explicit GrpcClientQt(std::string);
};

/// ext::grpc_api::define0::PrototypeGrpcApi
template<typename GrpcService>
	requires concept_grpc_service<GrpcService>
ext::grpc_client_api::define0::GrpcClientQt<GrpcService>::GrpcClientQt(std::string service_url)
	: m_service_url(std::move(service_url))
	, m_client(std::make_shared<GrpcService>())
{
	QObject::connect(m_client.get(), &GrpcService::errorOccurred, &std::remove_pointer_t<decltype(this)>::SlotErrorOccurred);

	auto itcQGrpcChannelOptions = QGrpcChannelOptions(QUrl((M_URL_PREFIX + m_service_url).c_str()));
	auto ptrQGrpcHttp2Channel = std::make_shared<QGrpcHttp2Channel>(itcQGrpcChannelOptions);
	m_client->attachChannel(ptrQGrpcHttp2Channel);
}
template<typename GrpcService>
	requires concept_grpc_service<GrpcService>
void ext::grpc_client_api::define0::GrpcClientQt<GrpcService>::SlotErrorOccurred(const QGrpcStatus& status)
{
	throw status;
}
#endif
