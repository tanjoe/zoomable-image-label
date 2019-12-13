# Scalable ROI-selectable Image Label

[TOC]

## 简介

Subclasses of QLabel that supports picture zooming in and out under cursor position as well as ROI selection

自定义的QLabel子类，实现了以鼠标指针为中心缩放图片以及ROI的框选

## Demo

<img src="https://github.com/tanjoe/zoomable-image-label/raw/master/images/demo.gif" alt="demo" style="zoom: 70%;" />

## 原理

可以认为存在三个坐标系

1. **原图像素坐标系O<sub>origin</sub>**

原点P<sub>origin_o</sub> = (0, 0)

最远点P<sub>origin_max</sub>  = (image.width, image.height)

2. **放大图像素坐标系O<sub>zoom</sub>**

原点P<sub>zoom_o</sub> = (0, 0)

最远点P<sub>zoom_max</sub>  = (label.width * zoom_ratio, label.height * zoom_ratio)

3. **控件坐标系O<sub>widget</sub>**

原点P<sub>widget_o</sub> = (0, 0)

最远点P<sub>widget_max</sub>  = (label.width, label.height)

原图像素坐标系和控件坐标系的大小不会改变，而放大图像素坐标系的大小会随zoom_ratio改变而改变。因此，无论是图片显示还是ROI框选，都可以把控件里的点先转到原图上，需要显示时再把对应的点由原图转到控件坐标系里来，步骤如下：

### 1. O<sub>widget</sub>→O<sub>zoom</sub>

已知鼠标位置在O<sub>widget</sub>下的坐标，记为P<sub>widget_a</sub>=(x<sub>w</sub>, y<sub>w</sub>)，需要得到其在O<sub>zoom</sub>下的坐标P<sub>zoom_a</sub>(x<sub>z</sub>, y<sub>z</sub>)

P<sub>zoom_a</sub> = P<sub>widget_a</sub> + display_start_point_

display_start_point_为P<sub>widget_o</sub>在O<sub>zoom</sub>下的坐标

### 2. O<sub>zoom</sub>→O<sub>origin</sub>

已知P<sub>zoom_a</sub>，需要得到其在O<sub>origin</sub>下的坐标P<sub>origin_a</sub>(x<sub>o</sub>, y<sub>o</sub>)

X方向转换比例X<sub>factor</sub> = image.width / (label.width * zoom_ratio)

Y方向转换比例Y<sub>factor</sub> = image.height/ (label.height* zoom_ratio)

则

x<sub>o</sub> = x<sub>z</sub> * X<sub>factor</sub> 

y<sub>o</sub> = y<sub>z</sub> * Y<sub>factor</sub>

### 3. 将P<sub>origin_a</sub>转换到新的O<sub>zoom</sub>下

注意滚轮转动后，zoom_ratio_变为了zoom_ratio_'。此时，原图上的点P<sub>origin_a</sub>在新的O<sub>zoom</sub>下的坐标P<sub>zoom_a</sub>'为

P<sub>zoom_a</sub>'.x = x<sub>z</sub> * zoom_ratio_' / zoom_ratio

P<sub>zoom_a</sub>'.y = x<sub>z</sub> * zoom_ratio_' / zoom_ratio
