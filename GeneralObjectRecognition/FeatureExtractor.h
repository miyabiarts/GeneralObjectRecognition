#pragma once

#include <opencv2/opencv.hpp>
#include "Utility.h"

//
class FeatureExtractor
{
public:

  // ディレクトリ内の画像ファイル全てから特徴を抽出
  void operator()()
  {
    std::string root = "../101_ObjectCategories/";
    std::vector< std::string > directories = enumerateFiles( root );
    for( std::vector< std::string >::iterator itr = directories.begin() ; itr != directories.end() ; ++itr )
    {
      std::vector< std::string > files = enumerateFiles( root + "/" + *itr );

      for( std::vector< std::string >::iterator fn_itr = files.begin() ; fn_itr != files.end() ; ++fn_itr )
      {
        // 入力画像
        std::string path = root + *itr + "/" + *fn_itr;
        std::cout << path << std::endl;

        // 特徴抽出
        extract( path );

        // 特徴量のファイル出力
        // 特徴点の位置などを出力しない
        // 「カテゴリ名_画像ファイル名.txt」で出力
        std::string filename = "../features/" + *itr + "_" + *fn_itr + ".txt";
        cv::FileStorage writer( filename, cv::FileStorage::WRITE ); 
        cv::write( writer, "descriptors", descriptors );
      }
    }
  }

  // 1枚の画像から特徴抽出
  void extract( const std::string &filename )
  {
    // グレイスケールで入力画像を読み込み
    cv::Mat_< unsigned char > in = cv::imread( filename, 0 );

    // 特徴点検出
    cv::SiftFeatureDetector detector;
    detector.detect( in, keypoints );

    // 特徴量抽出
    cv::SiftDescriptorExtractor extractor;
    extractor.compute( in, keypoints, descriptors );
  }

  // 途中で出力しておくものを保存
  std::vector< cv::KeyPoint > keypoints;
  cv::Mat_< float > descriptors;
};
