#include "Settings.h"
#include "Defines.h"
#include "Logger.h"
#include <QBoxLayout>
#include <QGroupBox>
#include <fstream>

namespace Settings
{
	bool firstTimeStart = false;

	int size = 600;
	bool sleep = true;
	bool fallWhenSleep = true;
	std::string screenshotPath = "../screenshots";
	QKeySequence screenshotFastHotKey = QKeySequence::fromString("Ctrl+P");
	QKeySequence exitHotKey = QKeySequence();
	QKeySequence hideHotKey = QKeySequence();
	QKeySequence clearItemHotKey = QKeySequence();
	bool allowItemSpawn = true;
	int itemGravity = 10;
	QKeySequence screenshotHotKey = QKeySequence::fromString("Ctrl+Shift+P");
	bool hideWhenScreenshot = false;
	int mainFps = 30;
	int itemFps = 30;
	bool expandToStateBar = false;
	QKeySequence thLauncherHotkey = QKeySequence();
	QKeySequence editScreenshotHotkey = QKeySequence();
	QKeySequence openScreenshotHotkey = QKeySequence();

	std::string HotkeyToString(QKeySequence key)
	{
		if (!key.isEmpty())
			return key.toString().toStdString();
		else
			return "None";
	}
	QKeySequence StringToHotkey(std::string s)
	{
		if (s == "None")
			return QKeySequence();
		else
			return QKeySequence::fromString(s.c_str());
	}

	void Save()
	{
		Logger::MakeDir(Def::settingsSavePath);
		std::ofstream out(std::string(Def::settingsSavePath) + "/settings.txt");

		out << size << std::endl;
		out << sleep << std::endl;
		out << fallWhenSleep << std::endl;
		out << screenshotPath << std::endl;
		out << HotkeyToString(screenshotFastHotKey) << std::endl;
		out << HotkeyToString(exitHotKey) << std::endl;
		out << HotkeyToString(hideHotKey) << std::endl;
		out << HotkeyToString(clearItemHotKey) << std::endl;
		out << allowItemSpawn << std::endl;
		out << itemGravity << std::endl;
		out << HotkeyToString(screenshotHotKey) << std::endl;
		out << hideWhenScreenshot << std::endl;
		out << mainFps << std::endl;
		out << itemFps << std::endl;
		out << expandToStateBar << std::endl;
		out << HotkeyToString(thLauncherHotkey) << std::endl;
		out << HotkeyToString(editScreenshotHotkey) << std::endl;
		out << HotkeyToString(openScreenshotHotkey) << std::endl;

		out.close();
		Logger::Print("Settings saved");
	}

	void Load()
	{
		std::ifstream in(std::string(Def::settingsSavePath) + "/settings.txt");
		if (!in)
		{
			Logger::Print("Can't open settings file");
			Logger::Print("Use default settings");
			firstTimeStart = true;
			return;
		}

		std::string temp;

		in >> size;
		in >> sleep;
		in >> fallWhenSleep;
		std::getline(in.ignore(), screenshotPath);
		std::getline(in, temp), screenshotFastHotKey = StringToHotkey(temp), temp.clear();
		std::getline(in, temp), exitHotKey = StringToHotkey(temp), temp.clear();
		std::getline(in, temp), hideHotKey = StringToHotkey(temp), temp.clear();
		std::getline(in, temp), clearItemHotKey = StringToHotkey(temp), temp.clear();
		in >> allowItemSpawn;
		in >> itemGravity;
		std::getline(in.ignore(), temp), screenshotHotKey = StringToHotkey(temp), temp.clear();
		in >> hideWhenScreenshot;
		in >> mainFps;
		in >> itemFps;
		in >> expandToStateBar;
		std::getline(in.ignore(), temp), thLauncherHotkey = StringToHotkey(temp), temp.clear();
		std::getline(in, temp), editScreenshotHotkey = StringToHotkey(temp), temp.clear();
		std::getline(in, temp), openScreenshotHotkey = StringToHotkey(temp), temp.clear();

		in.close();
		Logger::Print("Settings loaded");
	}
};

SettingsMenu::SettingsMenu(QWidget* parent)
	: QDialog(parent)
{
	this->setWindowTitle("DeskFairy->����");

	QFont font = this->font();
	font.setPixelSize(Def::settingsMenuFontSize);
	this->setFont(font);

	QPushButton* _applyBtn = new QPushButton(this);
	_applyBtn->setText("ȷ��");
	connect(_applyBtn, &QPushButton::clicked, this, &SettingsMenu::Apply);
	QPushButton* _cancelBtn = new QPushButton(this);
	_cancelBtn->setText("ȡ��");
	connect(_cancelBtn, &QPushButton::clicked, this, &SettingsMenu::Cancel);

	_items.push_back(new SettingItemInt("�ߴ�", &Settings::size, 50, 2000, 10));
	_items.push_back(new SettingItemInt("����֡��", &Settings::mainFps, 15, 60, 5));
	_items.push_back(new SettingItemInt("����֡��", &Settings::itemFps, 15, 60, 5));
	_items.push_back(new SettingItemBool("�������չ��״̬��", &Settings::expandToStateBar));
	_items.push_back(new SettingItemHotKey("�򿪶���������", &Settings::thLauncherHotkey));
	_items.push_back(new SettingItemBool("�Զ�˯��", &Settings::sleep));
	_items.push_back(new SettingItemBool("˯��ʱ����", &Settings::fallWhenSleep));
	_items.push_back(new SettingItemHotKey("ѡ����ͼ", &Settings::screenshotHotKey));
	_items.push_back(new SettingItemHotKey("���ٽ�ͼ", &Settings::screenshotFastHotKey));
	_items.push_back(new SettingItemHotKey("�༭��ͼ", &Settings::editScreenshotHotkey));
	_items.push_back(new SettingItemHotKey("�򿪽�ͼ����·��", &Settings::openScreenshotHotkey));
	_items.push_back(new SettingItemPath("��ͼ����·��", &Settings::screenshotPath));
	_items.push_back(new SettingItemBool("��ͼʱ����", &Settings::hideWhenScreenshot));
	_items.push_back(new SettingItemHotKey("�������", &Settings::clearItemHotKey));
	_items.push_back(new SettingItemBool("��������", &Settings::allowItemSpawn));
	_items.push_back(new SettingItemInt("��������", &Settings::itemGravity, -20, 20, 1));
	_items.push_back(new SettingItemHotKey("����", &Settings::hideHotKey));
	_items.push_back(new SettingItemHotKey("�˳�", &Settings::exitHotKey));

	QVBoxLayout* windowLayout = new QVBoxLayout;
	QGridLayout* settingsLayout = new QGridLayout;
	QHBoxLayout* buttonsLayout = new QHBoxLayout;

	int y = std::ceil(_items.size() * 0.5) + 0.1;
	for(int i = 0; i < _items.size(); i++)
	{
		auto item = _items[i];
		item->label->setMinimumWidth(Def::settingsMenuLabelWidth);
		item->label->setMaximumWidth(Def::settingsMenuLabelWidth);
		item->widget->setMinimumWidth(Def::settingsMenuWidgetWidth);
		item->widget->setMaximumWidth(Def::settingsMenuWidgetWidth);
		item->widget->setContentsMargins(0, 0, 0, 0);
		item->label->setMinimumHeight(Def::settingsMenuItemHeight);
		item->label->setMaximumHeight(Def::settingsMenuItemHeight);
		QHBoxLayout* layout = new QHBoxLayout;
		layout->addWidget(item->label);
		layout->addWidget(item->widget);
		settingsLayout->addLayout(layout, i % y, i / y);
	}

	QGroupBox* group = new QGroupBox;
	group->setLayout(settingsLayout);

	buttonsLayout->addWidget(_cancelBtn);
	buttonsLayout->addWidget(_applyBtn);

	QLabel* title = new QLabel("����");
	QHBoxLayout* lay = new QHBoxLayout;
	QGroupBox* titleGroup = new QGroupBox;
	title->setAlignment(Qt::AlignHCenter);
	lay->addWidget(title);
	titleGroup->setLayout(lay);

	windowLayout->addWidget(titleGroup);
	windowLayout->addWidget(group);
	windowLayout->addLayout(buttonsLayout);
	this->setLayout(windowLayout);
}

SettingsMenu::~SettingsMenu()
{
	for (auto item : _items)
	{
		delete item;
	}
}

void SettingsMenu::Apply()
{
	for (auto item : _items)
	{
		item->Apply();
	}
	Settings::Save();
	this->accept();
}

void SettingsMenu::Cancel()
{
	this->reject();
}
