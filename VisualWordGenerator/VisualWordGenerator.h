#pragma once

#include <opencv2/opencv.hpp>
#include "../GeneralObjectRecognition/Utility.h"

// VisualWordの作成
class VisualWordGenerator
{
public:
  void operator()()
  {
    int descriptorMaxCount = 50000;  // VisualWordを作成するための特徴量の最大数（超えることもある）
    int clusterCount = 500;          // VisualWordの数

    // 特徴のファイルを列挙
    std::vector< std::string > files = enumerateFiles( "../features" );

    //
    cv::BOWKMeansTrainer trainer( clusterCount );
    cv::RNG rng;
    while( trainer.descripotorsCount() < descriptorMaxCount )
    {
      // ファイルから特徴量を入力
      // ランダムにファイルは決定
      const std::string &file = files[ rng( files.size() ) ];
      
      cv::FileStorage reader( file, cv::FileStorage::READ );
      cv::FileNode node = reader.getFirstTopLevelNode();
      cv::Mat_< float > descriptors;
      cv::read( node[ "descriptors" ], descriptors );

      // 特徴量を追加
      trainer.add( descriptors );
    }

    // クラスタリングによりVisualWordを算出
    cv::Mat_< float > visualwords = trainer.cluster();

    // VisualWordをファイルに保存
    cv::FileStorage writer( "../visualwords.txt", cv::FileStorage::WRITE );
    cv::write( writer, "visualwords", visualwords );

  }
};
