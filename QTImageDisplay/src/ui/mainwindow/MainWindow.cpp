#include "MainWindow.h"
#include <QTimer>

/******************************************************************
 * @brief     
 * @details   
 * @param     parent
 * @return    
 * @author    Qiao Tan
 * @date      2019/11/15
 ******************************************************************/
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    ui.roiImageWidget->setFixedSize(600, 750);

	ui.roiImageWidget->setAutoFillBackground(true);
	QPalette label_palette = ui.roiImageWidget->palette();
	label_palette.setColor(QPalette::Window, Qt::lightGray);
	ui.roiImageWidget->setPalette(label_palette);
	ui.roiImageWidget->setEnabled(true);

	connect(ui.actionOpenFile, SIGNAL(triggered()), this, SLOT(slot_open_img_file()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));

    QTimer* timer = new QTimer(this);
    timer->setInterval(500);
    connect(timer, &QTimer::timeout, [=]() {
        ui.fps->setText(QString::number(ui.roiImageWidget->getFPS()));
        ui.ips->setText(QString::number(ui.roiImageWidget->getIPS()));
    });
    timer->start();
}

/******************************************************************
 * @brief     open front image
 * @details   
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/15
 ******************************************************************/
void MainWindow::slot_open_img_file() {

	QString image_path = QFileDialog::getOpenFileName(this, tr("select image file"), ".//", tr("Image (*.png *.jpg *.xpm *.bmp *.svg)"));
	QImage* image = new QImage();
	if (!image_path.isEmpty()) 
    {
		if (!(image->load(image_path))) 
        {
			QMessageBox::information(this, tr("info"), tr("open image fail!"));
			delete image;
			return;
		}
        ui.roiImageWidget->setImage(*image);
	}
	else 
    {
		QMessageBox::information(this, tr("info"), tr("you select no file!"));
	}

}