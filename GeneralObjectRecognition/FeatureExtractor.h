#pragma once

#include <opencv2/opencv.hpp>

//
class FeatureExtractor
{
public:

  void operator()()
  {

  }

  // 1���̉摜����������o
  void extract( const std::string &filename )
  {
    // �O���C�X�P�[���œ��͉摜��ǂݍ���
    cv::Mat_< unsigned char > in = cv::imread( filename, 0 );

    // �����_���o
    cv::SiftFeatureDetector detector;
    detector.detect( in, keypoints );

    // �����ʒ��o
    cv::SiftDescriptorExtractor extractor;
    extractor.compute( in, keypoints, descriptors );
  }

  // �r���ŏo�͂��Ă������̂�ۑ�
  std::vector< cv::KeyPoint > keypoints;
  cv::Mat_< float > descriptors;
};
