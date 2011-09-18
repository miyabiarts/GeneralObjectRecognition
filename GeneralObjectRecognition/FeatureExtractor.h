#pragma once

#include <opencv2/opencv.hpp>
#include "Utility.h"

//
class FeatureExtractor
{
public:

  // �f�B���N�g�����̉摜�t�@�C���S�Ă�������𒊏o
  void operator()()
  {
    std::string root = "../101_ObjectCategories/";
    std::vector< std::string > directories = enumerateFiles( root );
    for( std::vector< std::string >::iterator itr = directories.begin() ; itr != directories.end() ; ++itr )
    {
      std::vector< std::string > files = enumerateFiles( root + "/" + *itr );

      for( std::vector< std::string >::iterator fn_itr = files.begin() ; fn_itr != files.end() ; ++fn_itr )
      {
        // ���͉摜
        std::string path = root + *itr + "/" + *fn_itr;
        std::cout << path << std::endl;

        // �������o
        extract( path );

        // �����ʂ̃t�@�C���o��
        // �����_�̈ʒu�Ȃǂ��o�͂��Ȃ�
        // �u�J�e�S����_�摜�t�@�C����.txt�v�ŏo��
        std::string filename = "../features/" + *itr + "_" + *fn_itr + ".txt";
        cv::FileStorage writer( filename, cv::FileStorage::WRITE ); 
        cv::write( writer, "descriptors", descriptors );
      }
    }
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
