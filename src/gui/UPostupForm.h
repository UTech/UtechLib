//--------------------utech--------------------utech--------------------utech--------------------
//
// ���� ���������� ����� UPostupForm �������� ����������� ��������
//
// ��������� ������������ ������ "����" 17.07.2007�.
// � ���� ���������������� ���������� �������� QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UPOSTUPFORM_H
#define UPOSTUPFORM_H

#include <QWidget>
#include <QtDebug>

#include "../ui_headers/ui_UPostupForm.h"

//--------------------utech--------------------utech--------------------utech--------------------
class UPostupForm : public QWidget
{
        Q_OBJECT

    public:
        UPostupForm(QWidget *parent = 0, int count=10);
		
		~UPostupForm();
    public slots:
		void inc_pos();
		void incPos();
		void showLable(bool b);
		void setPostupLabel(QString label);
		void setNumPos(int count);
		void setCurrentPos(int pos);

    private:
		Ui::UPostupForm ui;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
