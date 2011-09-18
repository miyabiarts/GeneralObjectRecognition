#pragma once

#include <opencv2/opencv.hpp>
#include "../GeneralObjectRecognition/Utility.h"

// VisualWord�̍쐬
class VisualWordGenerator
{
public:
  void operator()()
  {
    int descriptorMaxCount = 50000;  // VisualWord���쐬���邽�߂̓����ʂ̍ő吔�i�����邱�Ƃ�����j
    int clusterCount = 500;          // VisualWord�̐�

    // �����̃t�@�C�����
    std::vector< std::string > files = enumerateFiles( "../features" );

    //
    cv::BOWKMeansTrainer trainer( clusterCount );
    cv::RNG rng;
    while( trainer.descripotorsCount() < descriptorMaxCount )
    {
      // �t�@�C����������ʂ����
      // �����_���Ƀt�@�C���͌���
      const std::string &file = std::string( "../features/" ) + files[ rng( files.size() ) ];
      
      cv::FileStorage reader( file, cv::FileStorage::READ );
      cv::Mat_< float > descriptors;
      reader[ "descriptors" ] >> descriptors;     

      // �����ʂ�ǉ�
      trainer.add( descriptors );

      std::cout << trainer.descripotorsCount() << std::endl;
    }

    // �N���X�^�����O�ɂ��VisualWord���Z�o
    cv::Mat_< float > visualwords = trainer.cluster();

    // VisualWord���t�@�C���ɕۑ�
    cv::FileStorage writer( "../visualwords.txt", cv::FileStorage::WRITE );
    cv::write( writer, "visualwords", visualwords );
  }
};
