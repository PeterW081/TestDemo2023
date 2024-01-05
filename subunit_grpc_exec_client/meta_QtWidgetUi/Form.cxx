#include "Form.h"
#include "./ui_Form.h"
#pragma

#include <memory>
#include <utility>
#include <thread>
#include "common/assert_with_exception.h"
#include "remote_gpio/RemoteLed.h"
#include "remote_gpio/RemoteWaterLevel.h"
using ext::device_ctrl::RemoteLed;
using ext::device_ctrl::RemoteWaterLevel;

///
namespace config0
{
	static const std::string SERVICE_URL = MACRO_GRPC_SERVICE_URL;
	static const int PIN_NUMBER_WATERLEVEL = 4;
	static const int PIN_NUMBER_LED = 21;
}
enum class Form::InnerEnumDeviceCtrl
{
	ENABLE,
	DISABLE,
};
struct Form::InnerStyleDeviceStatus
{
	static const InnerStyleDeviceStatus CASE_ON;
	static const InnerStyleDeviceStatus CASE_OFF;
	static const InnerStyleDeviceStatus CASE_ERROR;
	static const InnerStyleDeviceStatus CASE_LOADING;
	static const InnerStyleDeviceStatus CASE_HODING;
	QString m_text;
	QString m_style_sheet;
	InnerStyleDeviceStatus() = default;
	InnerStyleDeviceStatus(QString, QString);
};

/// Form
/* clang-format off */
const auto Form::InnerStyleDeviceStatus::CASE_ON      = InnerStyleDeviceStatus( "ON",         "background-color: rgb(0, 128, 0);    " );
const auto Form::InnerStyleDeviceStatus::CASE_OFF     = InnerStyleDeviceStatus( "OFF",        "background-color: rgb(128, 128, 128);" );
const auto Form::InnerStyleDeviceStatus::CASE_ERROR   = InnerStyleDeviceStatus( "ERROR",      "background-color: rgb(0, 0, 0);      " );
const auto Form::InnerStyleDeviceStatus::CASE_LOADING = InnerStyleDeviceStatus( "LOADING...", "                                     " );
const auto Form::InnerStyleDeviceStatus::CASE_HODING  = InnerStyleDeviceStatus( "HODING...",  "                                     " );
/* clang-format on */

/// Form - func
Form::Form(QWidget* parent)
	: QWidget(parent)
	, m_ui(new Ui::Form())
	, m_ctrl_led(nullptr)
	, m_thread_waterlevel_listen_status(nullptr)
{
	m_ui->setupUi(this);
	this->init();
	this->init_connect();
}
void Form::init()
{
	m_ui->_btn01_on->setStyleSheet(InnerStyleDeviceStatus::CASE_ON.m_style_sheet);
	m_ui->_btn02_off->setStyleSheet(InnerStyleDeviceStatus::CASE_OFF.m_style_sheet);
	this->slot_display_refresh_status_led(RemoteLed::EnumStatus::LOADING);
	this->slot_display_refresh_status_waterlevel(RemoteWaterLevel::EnumStatus::LOADING);
}
void Form::init_connect()
{
	auto func_btn_click_btn01_on = [this]()
	{
		if(m_ctrl_led == nullptr)
		{
			this->slot_operate_device_led_reinit();
			if(m_ctrl_led == nullptr)
			{
				return;
			}
		}
		this->slot_operate_device_led_set(RemoteLed::EnumStatus::ON);
		this->slot_operate_device_led_get();
	};
	auto func_btn_click_btn02_off = [this]()
	{
		if(m_ctrl_led == nullptr)
		{
			this->slot_operate_device_led_reinit();
			if(m_ctrl_led == nullptr)
			{
				return;
			}
		}
		this->slot_operate_device_led_set(RemoteLed::EnumStatus::OFF);
		this->slot_operate_device_led_get();
	};
	auto func_lab_click_lab_status01 = [this]()
	{
		this->slot_operate_device_led_reinit();
		this->slot_operate_device_led_get();
	};
	auto func_lab_click_lab_status02 = [this]()
	{
		this->slot_operate_device_waterlevel_reinit();
		this->slot_operate_device_waterlevel_listen_status();
	};
	///
	// clang-format off
	QObject::connect(this, &Form::signal_display_refresh_status_led ,        this, &Form::slot_display_refresh_status_led         );
	QObject::connect(this, &Form::signal_display_refresh_status_waterlevel, this, &Form::slot_display_refresh_status_waterlevel );
	// clang-format off
	QObject::connect(m_ui->_btn01_on,     &QPushButton::clicked, func_btn_click_btn01_on     );
	QObject::connect(m_ui->_btn02_off,    &QPushButton::clicked, func_btn_click_btn02_off    );
	QObject::connect(m_ui->_lab_status01, &Label::clicked,       func_lab_click_lab_status01 );
	QObject::connect(m_ui->_lab_status02, &Label::clicked,       func_lab_click_lab_status02 );
	// clang-format on
}
void Form::func_device_led_ctrl(Form::InnerEnumDeviceCtrl ctrl)
{
	switch(ctrl)
	{
		case InnerEnumDeviceCtrl::ENABLE:
			m_ctrl_led = std::make_unique<RemoteLed>(config0::SERVICE_URL, config0::PIN_NUMBER_LED);
			break;
		case InnerEnumDeviceCtrl::DISABLE:
			m_ctrl_led = nullptr;
			break;
	}
}
void Form::func_device_waterlevel_ctrl(Form::InnerEnumDeviceCtrl ctrl)
{
	switch(ctrl)
	{
		case InnerEnumDeviceCtrl::ENABLE:
			break;
		case InnerEnumDeviceCtrl::DISABLE:
			m_thread_waterlevel_listen_status = nullptr;
			break;
	}
}

/// Form - func qt slot
void Form::enterEvent(QEnterEvent* event)
{
	if(!m_flag_is_init)
	{
		m_flag_is_init = true;
		this->slot_operate_device_led_reinit();
		this->slot_operate_device_waterlevel_reinit();
		this->slot_operate_device_led_get();
	}
}
void Form::closeEvent(QCloseEvent*)
{
	auto func_close = [this]() -> void
	{
		this->slot_operate_device_led_set(RemoteLed::EnumStatus::OFF);
		QApplication::quit();
	};
	QMetaObject::invokeMethod(this, func_close, Qt::QueuedConnection);
}
void Form::slot_display_refresh_status_led(RemoteLed::EnumStatus status)
{
	auto style = InnerStyleDeviceStatus::CASE_ERROR;
	switch(status)
	{
		case RemoteLed::EnumStatus::ON:
			style = InnerStyleDeviceStatus::CASE_ON;
			break;
		case RemoteLed::EnumStatus::OFF:
			style = InnerStyleDeviceStatus::CASE_OFF;
			break;
		case RemoteLed::EnumStatus::LOADING:
			style = InnerStyleDeviceStatus::CASE_LOADING;
			break;
		default:
			break;
	}
	m_ui->_lab_status01->setText(style.m_text);
	m_ui->_lab_status01->setStyleSheet(style.m_style_sheet);
}
void Form::slot_display_refresh_status_waterlevel(RemoteWaterLevel::EnumStatus status)
{
	auto style = InnerStyleDeviceStatus::CASE_ERROR;
	switch(status)
	{
		case RemoteWaterLevel::EnumStatus::ON:
			style = InnerStyleDeviceStatus::CASE_ON;
			break;
		case RemoteWaterLevel::EnumStatus::OFF:
			style = InnerStyleDeviceStatus::CASE_OFF;
			break;
		case RemoteWaterLevel::EnumStatus::LOADING:
			style = InnerStyleDeviceStatus::CASE_LOADING;
			break;
		case RemoteWaterLevel::EnumStatus::HODING:
			style = InnerStyleDeviceStatus::CASE_HODING;
			break;
		default:
			break;
	}
	m_ui->_lab_status02->setText(style.m_text);
	m_ui->_lab_status02->setStyleSheet(style.m_style_sheet);
}
void Form::slot_operate_device_led_reinit()
{
	this->setDisabled(true);
	try
	{
		emit this->signal_display_refresh_status_led(RemoteLed::EnumStatus::LOADING);
		this->func_device_led_ctrl(InnerEnumDeviceCtrl::ENABLE);
	} catch(...)
	{
		this->func_device_led_ctrl(InnerEnumDeviceCtrl::DISABLE);
		emit this->signal_display_refresh_status_led(RemoteLed::EnumStatus::ERROR);
	}
	this->setDisabled(false);
}
void Form::slot_operate_device_led_set(RemoteLed::EnumStatus status)
{
	try
	{
		ext::assert::Assert_With_Exception_Is_Not_Null(m_ctrl_led);
		switch(status)
		{
			case RemoteLed::EnumStatus::ON:
				m_ctrl_led->set_on();
				break;
			case RemoteLed::EnumStatus::OFF:
				m_ctrl_led->set_off();
				break;
			default:
				break;
		}
	} catch(...)
	{
		this->func_device_led_ctrl(InnerEnumDeviceCtrl::DISABLE);
		emit this->signal_display_refresh_status_led(RemoteLed::EnumStatus::ERROR);
	}
}
void Form::slot_operate_device_led_get()
{
	try
	{
		ext::assert::Assert_With_Exception_Is_Not_Null(m_ctrl_led);
		auto status = m_ctrl_led->get_status();
		emit this->signal_display_refresh_status_led(status);
	} catch(...)
	{
		this->func_device_led_ctrl(InnerEnumDeviceCtrl::DISABLE);
		emit this->signal_display_refresh_status_led(RemoteLed::EnumStatus::ERROR);
	}
}
void Form::slot_operate_device_waterlevel_reinit()
{
	this->setDisabled(true);
	try
	{
		m_thread_waterlevel_listen_status = nullptr;
		emit this->signal_display_refresh_status_waterlevel(RemoteWaterLevel::EnumStatus::LOADING);
		this->func_device_waterlevel_ctrl(InnerEnumDeviceCtrl::ENABLE);
		emit this->signal_display_refresh_status_waterlevel(RemoteWaterLevel::EnumStatus::HODING);
	} catch(...)
	{
		this->func_device_waterlevel_ctrl(InnerEnumDeviceCtrl::DISABLE);
		emit this->signal_display_refresh_status_waterlevel(RemoteWaterLevel::EnumStatus::ERROR);
	}
	this->setDisabled(false);
}
void Form::slot_operate_device_waterlevel_listen_status()
{
	auto func_waterlevel_status = [this](RemoteWaterLevel::EnumStatus status) -> bool
	{
		emit this->signal_display_refresh_status_waterlevel(status);
		switch(status)
		{
			case RemoteWaterLevel::EnumStatus::OFF:
			case RemoteWaterLevel::EnumStatus::ON:
				return true;
			default:
				return false;
		}
	};
	auto func_thread = [this, func_waterlevel_status]() -> void
	{
		auto ctrl_waterlevel = std::make_unique<RemoteWaterLevel>(config0::SERVICE_URL, config0::PIN_NUMBER_WATERLEVEL);

		bool is_ok;
		try
		{
			is_ok = ctrl_waterlevel->listen_status(func_waterlevel_status);
		} catch(...)
		{
			is_ok = false;
		}
		auto status = is_ok ? RemoteWaterLevel::EnumStatus::HODING : RemoteWaterLevel::EnumStatus::ERROR;
		emit this->signal_display_refresh_status_waterlevel(status);
	};
	try
	{
		m_thread_waterlevel_listen_status = nullptr;
		m_thread_waterlevel_listen_status = std::make_shared<std::thread>(func_thread);
		m_thread_waterlevel_listen_status->detach();
	} catch(...)
	{
		this->func_device_waterlevel_ctrl(InnerEnumDeviceCtrl::DISABLE);
		emit this->signal_display_refresh_status_waterlevel(RemoteWaterLevel::EnumStatus::ERROR);
	}
}

/// Form::InnerStyleDeviceStatus
Form::InnerStyleDeviceStatus::InnerStyleDeviceStatus(QString text, QString style_sheet)
	: m_text(std::move(text))
	, m_style_sheet(std::move(style_sheet))
{
}
