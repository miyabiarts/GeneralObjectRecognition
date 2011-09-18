#pragma once

#include <opencv2/opencv.hpp>
#include "../GeneralObjectRecognition/Utility.h"

// Bag of Featureの生成
class BoFGenerator
{
public:
  void operator()()
  {
    // VisualWordの読み込み
    cv::Mat_< float > visualword;
    cv::FileStorage reader( "../visualwords.txt", cv::FileStorage::READ );
    reader[ "visualwords" ] >> visualword;

    // BoF特徴抽出器の準備
    cv::Ptr< cv::DescriptorExtractor > dextractor( new cv::SiftDescriptorExtractor() );
    cv::Ptr< cv::DescriptorMatcher > dmatcher( new cv::BruteForceMatcher< cv::L2< float > >() );
    
    cv::BOWImgDescriptorExtractor extractor( dextractor, dmatcher );
    extractor.setVocabulary( visualword );


    // ディレクトリ以下の全画像をBoF特徴に変換
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

        // グレイスケールで入力画像を読み込み
        cv::Mat_< unsigned char > in = cv::imread( path, 0 );

        cv::SiftFeatureDetector detector;
        std::vector< cv::KeyPoint > keypoints;
        detector.detect( in, keypoints );

        cv::Mat_< float > descriptors;
        extractor.compute( in, keypoints, descriptors );

        // BoF特徴量のファイル出力
        // 「カテゴリ名_画像ファイル名.txt」で出力
        std::string filename = "../bof/" + *itr + "_" + *fn_itr + ".txt";
        cv::FileStorage writer( filename, cv::FileStorage::WRITE ); 
        cv::write( writer, "descriptors", descriptors );
      }
    }
  }
};
