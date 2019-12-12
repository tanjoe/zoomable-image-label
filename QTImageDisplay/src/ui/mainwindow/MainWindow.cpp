#include "MainWindow.h"

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
    ui.roiImageWidget->setFixedSize(600, 850);

	ui.roiImageWidget->setAutoFillBackground(true);
	QPalette label_palette = ui.roiImageWidget->palette();
	label_palette.setColor(QPalette::Window, Qt::lightGray);
	ui.roiImageWidget->setPalette(label_palette);
	ui.roiImageWidget->setEnabled(true);

	connect(ui.actionOpenFile, SIGNAL(triggered()), this, SLOT(slot_open_img_file()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));

    this->slot_open_img_file();
}

/******************************************************************
 * @brief     open front image
 * @details   
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/15
 ******************************************************************/
void MainWindow::slot_open_img_file() {

	//QString image_path = QFileDialog::getOpenFileName(this, tr("select image file"), ".//", tr("Image (*.png *.jpg *.xpm *.bmp *.svg)"));
    QString image_path = "../images/test_image.jpg";
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