#include "../GeneralObjectRecognition/FeatureExtractor.h"

int main()
{
  FeatureExtractor extractor;
  extractor.extract( "../101_ObjectCategories/accordion/image_0001.jpg" );

  // 特徴点検出結果を表示
  cv::Mat_< cv::Vec3b > in = cv::imread( "../101_ObjectCategories/accordion/image_0001.jpg" );
  
  cv::Mat_< cv::Vec3b > result;
  cv::drawKeypoints( in, extractor.keypoints, result );
  cv::imshow( "Feature", result );
  cv::waitKey( -1 );

  return 0;
}
