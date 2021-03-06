//Normal visualization; funktion für verschiebung des viewpoints, und erzeugung eines screenshots

//#include <pcl/common/common_headers.h>

#include <string>
#include <fstream>
#include <iostream>

#include <pcl/common/common_headers.h>
#include <pcl/PolygonMesh.h>
#include <pcl/TextureMesh.h>
#include <pcl/io/ply_io.h>

#include <cloud.hpp>
#include "creation.hpp"
#include "preprocessing.hpp"
#include "processing.hpp"
#include "savingandpostprocessing.hpp"
#include "tools.hpp"
#include "visualization.hpp"

int main()
{
  std::cout<<std::string(25,'\n');
  std::cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%% PCL Processing Programm %%%%%%%%%%%%%%%%%%%%%%%%%%%\n"<<std::endl;
  Cloud *c;
  bool cloud = false;
  std::cout<<"\tCreate a Cloud[c]    Load Cloud[l]    Load Example[e]    Quit[q]\n\n###>";
  char start;
  cin>>start;
  std::cout<<std::string(25,'\n');
  std::cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%% PCL Processing Programm %%%%%%%%%%%%%%%%%%%%%%%%%%%\n"<<std::endl;
  std::string name;
  std::string newname;
  int scale;
  switch( start ) 
  {
    case  'c': {
      std::cout<<"Create Cloud:"<<std::endl;
      std::cout<<"\n\tEnter source name: ";
      std::cin>>name;
      std::cout<<"\n\tEnter desired name of the point cloud: ";
      std::cin>>newname;
      std::cout<<"\n\tEnter desired scaling ('1'=no scaling, 'n'=1/n^2 of available point data): ";
      std::cin>>scale;
      c = new Cloud(name,newname,scale);
      cloud = true;
      if(c->getstatusofzeros()==true) {
	std::cout<<std::string(25,'\n');
	std::cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%% PCL Processing Programm %%%%%%%%%%%%%%%%%%%%%%%%%%%\n"<<std::endl;
	std::cout<<"The cloud contains points with no depth information (per default set to zero). Interpolate depth and proceed with interpolated cloud (the corresponding images are saved as well)? The interpolation could take a while.[y/n]\n\n###>";
	char proc;
	cin>>proc;
	if(proc = 'y') {
	  interpolateDepthData(name,newname);
	  delete c;
	  c = new Cloud(newname,newname,scale);
	}
      }
      break;
    }
    case  'l': {
      std::cout << "Load cloud:"<<std::endl;
      std::cout<<"\n\tEnter source name without ending: ";
      std::cin>>name;
      c = new Cloud(name,name,-1);
      cloud = true;
      break;
    }
    case  'e': {
      c = new Cloud("3","examplecloud",4);
      cloud = true;
      break;
    }
  }
  while(cloud==true) {
    std::cout<<std::string(25,'\n');
    std::cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%% PCL Processing Programm %%%%%%%%%%%%%%%%%%%%%%%%%%%\n"<<std::endl;
    std::cout<<"\tVisualize[v]\t\tFilter[f]\t\tEstimate Normals[n]\n\tGenerate Mesh[m]\tCrop Cloud[c]\t\tInfo about Cloud[i]\n\tSave[s]\t\t\tBuild Three.js data[t]\tQuit[q]\n\n###>";
    char entry;
    cin>>entry;
    std::cout<<std::string(25,'\n');
    std::cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%% PCL Processing Programm %%%%%%%%%%%%%%%%%%%%%%%%%%%\n"<<std::endl;
    switch( entry )
    {
      case 'v': {
	c->visualize();
	break;
      }
      case 'f': {
	c->filterCloud();
	break;
      }
      case 'n': {
	c->generateNormals();
	break;
      }
      case 'm': {
	c->constructMesh();
	break;
      }
      case 'c': {
	c->cropCloud();
	break;
      }
      case 'i': {
	c->getinfo();
	break;
      }
      case 's': {
	c->saveCloud();
	break;
      }
      case 't': {
	c->buildthreejsdatafromCloud();
	break;
      }
      case 'q': {
	cloud=false;
	break;
      }
    }
  }
  std::cout<<"                                       BYE                                      \n"<<std::endl;
  std::cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"<<std::endl;
  return (0);
}
