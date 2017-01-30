#include <string>
#include <fstream>
#include <iostream>

#include <pcl/common/common_headers.h>
#include <pcl/PolygonMesh.h>
#include <pcl/TextureMesh.h>
#include <pcl/io/ply_io.h>

#include "creation.hpp"
#include "preprocessing.hpp"
#include "processing.hpp"
#include "savingandpostprocessing.hpp"
#include "tools.hpp"
#include "visualization.hpp"

class Cloud
{
  public:
    Cloud(std::string name_, std::string newname_, int scale_ = -1);

    void createCloud();
    void visualize();
    void filterCloud();
    void generateNormals();
    void constructMesh();
    void cropCloud();
    void getinfo();
    void saveCloud();
    void buildthreejsdatafromCloud();
    bool getstatusofzeros();

  private:
    pcl::PointCloud<pcl::PointXYZ>::Ptr pcptr;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr pcrgbptr;
    pcl::PointCloud<pcl::PointNormal>::Ptr pcnormptr;
    std::string meshmethod;
    std::string normalmethod;
    std::string filtermethod;
    std::string texmeshstatus;
    std::string croppedstatus;
    pcl::PolygonMesh mesh;
    pcl::PointCloud<pcl::Normal>::Ptr normptr;
    pcl::TextureMesh texMesh;
    std::string name;
    std::string newname;
    int scale;
};
