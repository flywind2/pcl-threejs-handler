#ifndef _creation_hpp_
#define _creation_hpp_

#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <typeinfo>
#include <pcl/common/common_headers.h>
#include <pcl/io/pcd_io.h>

double stod(std::string text);

//Create a Pointcloud with PointXYZ out of the given depth image, scale is used for downsampling the pointcloud
void createPointCloud (pcl::PointCloud<pcl::PointXYZ>::Ptr &pcptr, std::string filename, int scale);

//Create a Pointcloud with PointXYZRGB out of the given depth and rgb image, scale is used for downsampling the pointcloud
void createPointCloud (pcl::PointCloud<pcl::PointXYZRGB>::Ptr &pcrgbptr, std::string filename, int scale);

//Converts the PointXYZ to a PointXYZRGB Pointcloud with the given rgb image
pcl::PointCloud<pcl::PointXYZRGB>::Ptr colorPointCloud (pcl::PointCloud<pcl::PointXYZ>::Ptr &pcptr, std::string filename);

//Texture the Mesh, only applicable if an rgb image is avaible
pcl::TextureMesh textureMesh(pcl::PolygonMesh &mesh, std::string filename, int scale);

#endif
