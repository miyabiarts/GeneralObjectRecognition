#pragma once

#include <opencv2/opencv.hpp>

// 学習
class Trainer
{
public:
  void operator()()
  {
    // 学習するカテゴリ
    std::vector< std::string > categories;
    categories.push_back( "accordion" );
    categories.push_back( "airplanes" );
    categories.push_back( "anchor" );
    categories.push_back( "ant" );
    categories.push_back( "bass" );
    categories.push_back( "bonsai" );


    // 学習する枚数（カテゴリあたり）
    // 最初から連続する数の画像を利用
    int imageCount = 20;

    // データを用意
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

    // 識別器
    cv::SVM svm;
    svm.train( data, response );    
    
    // 保存
    svm.save( "../trained.txt" );
  }
};
