#include <opencv2/opencv.hpp>
#include "Utility.h"

// ディレクトリ内の画像ファイル全てから特徴を抽出
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
