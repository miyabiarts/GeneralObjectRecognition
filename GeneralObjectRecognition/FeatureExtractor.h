#pragma once

#include <opencv2/opencv.hpp>

//
class FeatureExtractor
{
public:

  void operator()()
  {

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
