//--------------------utech--------------------utech--------------------utech--------------------
//
// ���� ���������� ����� ���� ��������� �����������
//
// ��������� ������������ ������ "����" 29.03.2009�.
// � ���� ���������������� ���������� �������� QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UDEBUGFORM_H
#define UDEBUGFORM_H

#include <QWidget>
#include <QtDebug>
#include <QString>

#include "../ui_headers/ui_UDebugForm.h"
//--------------------utech--------------------utech--------------------utech--------------------
class UDebugForm : public QWidget
{
    Q_OBJECT
    public:
        UDebugForm(QWidget *parent = 0);
		
		~UDebugForm();
    public slots:
		void addString(QString str);
		void addDebugString(QString str);
		void addWarningString(QString str);
		void clearActiveMessageTextEdit();
		void showDebug();
		void checkBox_allWaysOnTop_stateChanged();
    private:
		Ui::UDebugForm ui;
};
//--------------------utech--------------------utech--------------------utech--------------------
class UDebug : public QObject
{
    Q_OBJECT
  public:
	static void uMessageOutput(QtMsgType type, const char *msg); //������� ������� ���������� ��������
	static void createDebugForm();
	static UDebugForm * debugFormPointer;
	static void showDebug();
};
//--------------------utech--------------------utech--------------------utech--------------------
//UDebugForm * UDebug::debugFormPointer = NULL;

#endif

