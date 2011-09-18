#pragma once

#include <opencv2/opencv.hpp>
#include "../GeneralObjectRecognition/Utility.h"

// Bag of Feature�̐���
class BoFGenerator
{
public:
  void operator()()
  {
    // VisualWord�̓ǂݍ���
    cv::Mat_< float > visualword;
    cv::FileStorage reader( "../visualwords.txt", cv::FileStorage::READ );
    reader[ "visualwords" ] >> visualword;

    // BoF�������o��̏���
    cv::Ptr< cv::DescriptorExtractor > dextractor( new cv::SiftDescriptorExtractor() );
    cv::Ptr< cv::DescriptorMatcher > dmatcher( new cv::BruteForceMatcher< cv::L2< float > >() );
    
    cv::BOWImgDescriptorExtractor extractor( dextractor, dmatcher );
    extractor.setVocabulary( visualword );


    // �f�B���N�g���ȉ��̑S�摜��BoF�����ɕϊ�
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

        // �O���C�X�P�[���œ��͉摜��ǂݍ���
        cv::Mat_< unsigned char > in = cv::imread( path, 0 );

        cv::SiftFeatureDetector detector;
        std::vector< cv::KeyPoint > keypoints;
        detector.detect( in, keypoints );

        cv::Mat_< float > descriptors;
        extractor.compute( in, keypoints, descriptors );

        // BoF�����ʂ̃t�@�C���o��
        // �u�J�e�S����_�摜�t�@�C����.txt�v�ŏo��
        std::string filename = "../bof/" + *itr + "_" + *fn_itr + ".txt";
        cv::FileStorage writer( filename, cv::FileStorage::WRITE ); 
        cv::write( writer, "descriptors", descriptors );
      }
    }
  }
};
