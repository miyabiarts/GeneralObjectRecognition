#pragma once

#include <opencv2/opencv.hpp>

//
class Recognizer
{
public:
  void operator()()
  {
     // 認識するカテゴリ
    std::vector< std::string > categories;
    categories.push_back( "accordion" );
    categories.push_back( "airplanes" );
    categories.push_back( "anchor" );
    categories.push_back( "ant" );
    categories.push_back( "bass" );
    categories.push_back( "bonsai" );


    // 認識する枚数（カテゴリあたり）
    // オフセットから連続する数の画像を利用
    int imageOffset = 20;
    int imageCount = 20;

    // 識別器を用意
    cv::SVM svm;
    svm.load( "../trained.txt" );
    
     // データを用意
    cv::Mat_< float > data( 1, 500 );

    int truth = 0;  // 正解数

    int cat = 0;
    int idx = 0;
    for( std::vector< std::string >::iterator itr = categories.begin() ; itr != categories.end() ; ++itr )
    {
      for( int i = 0 ; i < imageCount ; ++i )
      {
        char path[256];
        sprintf( path, "../bof/%s_image_%04d.jpg.txt", itr->c_str(), imageOffset+i+1 );
        cv::FileStorage reader( path, cv::FileStorage::READ );
        cv::Mat_< float > bof;
        reader[ "descriptors" ] >> bof;


        for( int j = 0 ; j < 500 ; ++j )
        {
          data( 0, j ) = bof( 0, j );
        }

        int result = static_cast< int >( svm.predict( data ) );
        if( cat == result )
        {
          ++truth;
        }
       
        ++idx;
      }

      ++cat;
    }

    float rate = static_cast< float >( truth ) / idx;

    std::cout << "Recognition rate:" << std::endl;
    std::cout << rate << std::endl;
  }
};
