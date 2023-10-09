#pragma once
#include <QWidget>
#include "remote_gpio/RemoteLed.h"
#include "remote_gpio/RemoteWaterLevel.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
	class Form;
}
QT_END_NAMESPACE

class Form : public QWidget
{
	Q_OBJECT
	enum class InnerEnumDeviceCtrl;
	struct InnerStyleDeviceStatus;

  public:
	explicit Form(QWidget* parent = nullptr);

  private:
	std::shared_ptr<Ui::Form> m_ui;
	bool m_flag_is_init = false;
	std::unique_ptr<ext::device_ctrl::RemoteLed> m_ctrl_led;
	std::unique_ptr<ext::device_ctrl::RemoteWaterLevel> m_ctrl_waterlevel;
	std::shared_ptr<std::thread> m_thread_waterlevel_listen_status;
	void init();
	void init_connect();
	void func_device_led_ctrl(InnerEnumDeviceCtrl);
	void func_device_waterlevel_ctrl(InnerEnumDeviceCtrl);

  signals:
	void signal_display_refresh_status_led(ext::device_ctrl::RemoteLed::EnumStatus);
	void signal_display_refresh_status_waterlevel(ext::device_ctrl::RemoteWaterLevel::EnumStatus);

  private slots:
	void enterEvent(QEnterEvent* event) override;
	void closeEvent(QCloseEvent*) override;
	void slot_display_refresh_status_led(ext::device_ctrl::RemoteLed::EnumStatus);
	void slot_display_refresh_status_waterlevel(ext::device_ctrl::RemoteWaterLevel::EnumStatus);
	void slot_operate_device_led_reinit();
	void slot_operate_device_led_set(ext::device_ctrl::RemoteLed::EnumStatus);
	void slot_operate_device_led_get();
	void slot_operate_device_waterlevel_reinit();
	void slot_operate_device_waterlevel_listen_status();
};
