#include <opencv2/opencv.hpp>
#include "Utility.h"

// �f�B���N�g�����̉摜�t�@�C���S�Ă�������𒊏o
void extractFeatureAllImages()
{
  std::string root = "../101_ObjectCategories/";
  std::vector< std::string > directories = enumerateFiles( root );
  for( std::vector< std::string >::iterator itr = directories.begin() ; itr != directories.end() ; ++itr )
  {
    enumerateFiles( root + "/" + *itr );
  }
}

//
int main()
{
  extractFeatureAllImages();

  return 0;
}
