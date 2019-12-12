#pragma once
#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <QMessageBox>
#include <QImage>
#include "ui_qtimagedisplay.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);

private:
	Ui::QTImageDisplayClass ui;

private slots:
	void slot_open_img_file();
};
