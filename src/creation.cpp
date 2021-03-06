#include "creation.hpp"

//string to double
double stod(std::string text) {
    return atof(text.c_str());
}

//Create a Pointcloud with PointXYZ out of the given depth image, scale is used for downsampling the pointcloud
void createPointCloud (pcl::PointCloud<pcl::PointXYZ>::Ptr &pcptr, std::string filename, int scale)
{
  std::cout<<"\ncreate point cloud xyz..." << std::flush;
  //Load depth image
  cv::Mat1s depth_image = cv::imread("./../data/undistfiles/"+filename+"_depth.pgm", CV_LOAD_IMAGE_ANYDEPTH);
  
  std::ifstream is;
  is.open("./../data/cameraparameters.txt");
  std::string line;

  //Depth Intrinsic Parameters
  double fx_d,fy_d,cx_d,cy_d;    //From calibration
  getline (is,line);
  fx_d = stod(line.substr(7,line.size()-7));
  getline (is,line);
  fy_d = stod(line.substr(7,line.size()-7));
  getline (is,line);
  cx_d = stod(line.substr(7,line.size()-7));
  getline (is,line);
  cy_d = stod(line.substr(7,line.size()-7));
  is.close();
  
  pcptr->width = depth_image.cols/scale;  //Dimensions must be initialized to use 2-D indexing
  pcptr->height = depth_image.rows/scale;
  pcptr->resize(pcptr->width*pcptr->height);
  for(int v=0; v< depth_image.rows; v++)     //2-D indexing
  {
      for(int u=0; u< depth_image.cols; u++) {
	if((u%scale==0)&&(v%scale==0))
	{
	  double z = depth_image(v,u)*10.0/65535; //actual depth according to file format of depth_image (16bit)          
	  //3-D position
	  (*pcptr)(u/scale,v/scale).x = z*(u-cx_d)/fx_d;
	  (*pcptr)(u/scale,v/scale).y = z*(v-cy_d)/fy_d;
	  (*pcptr)(u/scale,v/scale).z = z;
	}
      }
  }
  std::cout<<"finished" << std::endl;
}

//Create a Pointcloud with PointXYZRGB out of the given depth and rgb image, scale is used for downsampling the pointcloud
void createPointCloud (pcl::PointCloud<pcl::PointXYZRGB>::Ptr &pcrgbptr, std::string filename, int scale)
{
  std::cout<<"\ncreate point cloud xyzrgb..." << std::flush;
  //Load rgb-image
  cv::Mat3b color_image = cv::imread("./../data/undistfiles/"+filename+"_rgb.ppm", CV_LOAD_IMAGE_COLOR);
  
  //Load disparity image
  cv::Mat1s depth_image = cv::imread("./../data/undistfiles/"+filename+"_depth.pgm", CV_LOAD_IMAGE_ANYDEPTH);
  
  std::ifstream is;
  is.open("./../data/cameraparameters.txt");
  std::string line;

  //Depth Intrinsic Parameters
  double fx_d,fy_d,cx_d,cy_d;    //From calibration
  getline (is,line);
  fx_d = stod(line.substr(7,line.size()-7));
  getline (is,line);
  fy_d = stod(line.substr(7,line.size()-7));
  getline (is,line);
  cx_d = stod(line.substr(7,line.size()-7));
  getline (is,line);
  cy_d = stod(line.substr(7,line.size()-7));
  is.close();
  
  pcrgbptr->width = depth_image.cols/scale;  //Dimensions must be initialized to use 2-D indexing
  pcrgbptr->height = depth_image.rows/scale;
  pcrgbptr->resize(pcrgbptr->width*pcrgbptr->height);
  
  for(int v=0; v< depth_image.rows; v++)     //2-D indexing
  {
      for(int u=0; u< depth_image.cols; u++) {
	if((u%scale==0)&&(v%scale==0))
	{
	  double z = depth_image(v,u)*10.0/65535;
	  if(z!=0)
	  {
	    //3-D position
	    (*pcrgbptr)(u/scale,v/scale).x = z*(u-cx_d)/fx_d;
	    (*pcrgbptr)(u/scale,v/scale).y = z*(v-cy_d)/fy_d;
	    (*pcrgbptr)(u/scale,v/scale).z = z;
	    //Color
	    (*pcrgbptr)(u/scale,v/scale).b = color_image(v,u)[0]; //originally (vc,uc)
	    (*pcrgbptr)(u/scale,v/scale).g = color_image(v,u)[1];
	    (*pcrgbptr)(u/scale,v/scale).r = color_image(v,u)[2];
	  }
	}
      }
  }
  std::cout<<"finished" << std::endl;
}

//Converts the PointXYZ to a PointXYZRGB Pointcloud with the given rgb image
pcl::PointCloud<pcl::PointXYZRGB>::Ptr colorPointCloud (pcl::PointCloud<pcl::PointXYZ>::Ptr &pcptr, std::string filename)
{
  std::cout<<"\ncreate color pointcloud..."<<std::flush;
  //Load rgb-image
  cv::Mat3b color_image = cv::imread("./../data/undistfiles/"+filename+"_rgb.ppm", CV_LOAD_IMAGE_COLOR);

  pcl::PointCloud<pcl::PointXYZRGB>::Ptr pcrgbptr (new pcl::PointCloud<pcl::PointXYZRGB>);
 
  pcrgbptr->width = pcptr->width;  //Dimensions must be initialized to use 2-D indexing
  pcrgbptr->height = pcptr->height;
  pcrgbptr->resize(pcrgbptr->width*pcrgbptr->height);
  
  int scale = (int)(color_image.cols/pcptr->width);
  
  for(int v=0; v< color_image.rows; v++)     //2-D indexing
  {
      for(int u=0; u< color_image.cols; u++) {
	if((u%scale==0)&&(v%scale==0))
	{
           if((*pcptr)(u/scale,v/scale).z!=0)
	   {
	       //3-D position
	       (*pcrgbptr)(u/scale,v/scale).x = (*pcptr)(u/scale,v/scale).x;
	       (*pcrgbptr)(u/scale,v/scale).y = (*pcptr)(u/scale,v/scale).y;
	       (*pcrgbptr)(u/scale,v/scale).z = (*pcptr)(u/scale,v/scale).z;
	       //Color
	       (*pcrgbptr)(u/scale,v/scale).b = color_image(v,u)[0]; //originally (vc,uc)
	       (*pcrgbptr)(u/scale,v/scale).g = color_image(v,u)[1];
	       (*pcrgbptr)(u/scale,v/scale).r = color_image(v,u)[2];
	   }
	}
      }
  }
  std::cout<<"pointcloud colored"<<std::endl;
  return pcrgbptr;
}

//Projects a texture onto the polygon mesh
pcl::TextureMesh textureMesh(pcl::PolygonMesh &mesh, std::string filename, int scale)
{ 
  std::cout<<"\ntexture mesh..."<<std::flush;
  //Load color image
  cv::Mat3b color_image = cv::imread("./../data/undistfiles/"+filename+"_rgb.ppm", CV_LOAD_IMAGE_COLOR);
  cv::imwrite("./../data/undistfiles/"+filename+"_rgb.png",color_image);

  pcl::TextureMesh texMesh;
  texMesh.tex_polygons.push_back(mesh.polygons);
  texMesh.header = mesh.header;
  texMesh.cloud = mesh.cloud;
  std::vector<Eigen::Vector2f,Eigen::aligned_allocator<Eigen::Vector2f> > tmp_coordinates;
  Eigen::Vector2f tmp_VT;
  for(int v=0; v< mesh.cloud.height*scale; v++)     //2-D indexing
  {
      for(int u=0; u< mesh.cloud.width*scale; u++) {
	if((u%scale==0)&&(v%scale==0))
	{
	tmp_VT(0,0) = u*1.0/(mesh.cloud.width*scale-1);
	tmp_VT(1,0) = 1.0-v*1.0/(mesh.cloud.height*scale-1);
	tmp_coordinates.push_back(tmp_VT);
	}
      }
  }
  texMesh.tex_coordinates.push_back(tmp_coordinates);
  
  pcl::TexMaterial materials;
  // material
  materials.tex_name = "material_0";
  materials.tex_file = "./../data/undistfiles/"+filename+"_rgb.png";

  texMesh.tex_materials.push_back(materials);
  std::cout<<"finished" << std::endl;
  return texMesh;
}
