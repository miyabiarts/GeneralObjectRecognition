#pragma once

#include <opencv2/opencv.hpp>

// �w�K
class Trainer
{
public:
  void operator()()
  {
    // �w�K����J�e�S��
    std::vector< std::string > categories;
    categories.push_back( "accordion" );
    categories.push_back( "airplanes" );
    categories.push_back( "anchor" );
    categories.push_back( "ant" );
    categories.push_back( "bass" );
    categories.push_back( "bonsai" );


    // �w�K���閇���i�J�e�S��������j
    // �ŏ�����A�����鐔�̉摜�𗘗p
    int imageCount = 20;

    // �f�[�^��p��
    cv::Mat_< float > data( categories.size() * imageCount, 500 );
    cv::Mat_< int > response( categories.size() * imageCount, 1 );

    int cat = 0;
    int idx = 0;
    for( std::vector< std::string >::iterator itr = categories.begin() ; itr != categories.end() ; ++itr )
    {
      for( int i = 0 ; i < imageCount ; ++i )
      {
        char path[256];
        sprintf( path, "../bof/%s_image_%04d.jpg.txt", itr->c_str(), i+1 );
        cv::FileStorage reader( path, cv::FileStorage::READ );
        cv::Mat_< float > bof;
        reader[ "descriptors" ] >> bof;
        for( int j = 0 ; j < 500 ; ++j )
        {
          data( idx, j ) = bof( 0, j );
        }
        response( idx, 0 ) = cat;
        ++idx;
      }

      ++cat;
    }

    // ���ʊ�
    cv::SVM svm;
    svm.train( data, response );    
    
    // �ۑ�
    svm.save( "../trained.txt" );
  }
};
