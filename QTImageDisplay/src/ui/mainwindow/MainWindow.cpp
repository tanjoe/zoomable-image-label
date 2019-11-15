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
    ui.roiImageLabel->setFixedSize(600, 850);

	ui.roiImageLabel->setAutoFillBackground(true);
	QPalette label_palette = ui.roiImageLabel->palette();
	label_palette.setColor(QPalette::Window, Qt::lightGray);
	ui.roiImageLabel->setPalette(label_palette);
	ui.roiImageLabel->setEnabled(true);

	connect(ui.actionOpenFile, SIGNAL(triggered()), this, SLOT(slot_open_img_file()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui.enableRoi, SIGNAL(clicked()), this, SLOT(slot_enable_roi()));
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
        ui.roiImageLabel->setImage(*image);
	}
	else 
    {
		QMessageBox::information(this, tr("info"), tr("you select no file!"));
	}

}

/******************************************************************
 * @brief     
 * @details   
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18
 ******************************************************************/
void MainWindow::slot_enable_roi()
{
    static bool is_roi_enabled = false;
    is_roi_enabled = !is_roi_enabled;
    ui.roiImageLabel->enableRoiSelection(is_roi_enabled);
}
